#include "language_resources.h"
#include <stdexcept>
#include <vector>

namespace {
struct Reader {
    std::span<unsigned char const> Bytes;
    void Check(size_t offset, size_t count) const {
        if (offset > Bytes.size() || count > Bytes.size() - offset) throw std::out_of_range("language resource");
    }
    unsigned Word(size_t offset) const { Check(offset, 2); return Bytes[offset] | unsigned(Bytes[offset + 1]) << 8; }
    unsigned Dword(size_t offset) const { return Word(offset) | Word(offset + 2) << 16; }
};
void Append_UTF8(std::string & text, unsigned code) {
    if (code < 128) text += char(code);
    else if (code < 2048) { text += char(0xc0 | code >> 6); text += char(0x80 | (code & 63)); }
    else if (code < 65536) { text += char(0xe0 | code >> 12); text += char(0x80 | ((code >> 6) & 63)); text += char(0x80 | (code & 63)); }
    else { text += char(0xf0 | code >> 18); text += char(0x80 | ((code >> 12) & 63)); text += char(0x80 | ((code >> 6) & 63)); text += char(0x80 | (code & 63)); }
}
std::string Format(std::string const & text) {
    std::string result;
    for (size_t i = 0; i < text.size(); ++i) {
        if (text[i] != '%') continue;
        if (++i == text.size()) return "invalid";
        if (text[i] == '%') continue;
        while (i < text.size() && std::string("-+ #0.123456789").find(text[i]) != std::string::npos) ++i;
        if (i < text.size() && text[i] == '*') { result += '*'; ++i; }
        while (i < text.size() && std::string(".123456789").find(text[i]) != std::string::npos) ++i;
        if (i < text.size() && text[i] == '*') { result += '*'; ++i; }
        while (i < text.size() && std::string("hljztL").find(text[i]) != std::string::npos) result += text[i++];
        if (i == text.size() || std::string("diuoxXfFeEgGaAcsp").find(text[i]) == std::string::npos) return "invalid";
        result += text[i]; result += ';';
    }
    return result;
}
}

bool Compatible_Language_Format(std::string const & original, std::string const & translated)
{
    std::string signature = Format(original);
    return signature != "invalid" && signature == Format(translated);
}

bool Read_Language_Strings(std::span<unsigned char const> bytes, unsigned language,
    std::map<unsigned, std::string> & strings)
{
    strings.clear();
    try {
        Reader r{bytes};
        if (bytes.size() > 4 * 1024 * 1024 || r.Word(0) != 0x5a4d) return false;
        size_t pe = r.Dword(0x3c);
        if (r.Dword(pe) != 0x4550) return false;
        unsigned sections = r.Word(pe + 6), optional_size = r.Word(pe + 20);
        size_t optional = pe + 24;
        unsigned magic = r.Word(optional);
        size_t directories = magic == 0x10b ? 96 : magic == 0x20b ? 112 : 0;
        if (!directories || optional_size < directories + 24 || sections > 96) return false;
        r.Check(optional, optional_size);
        unsigned resource_rva = r.Dword(optional + directories + 16), resource_size = r.Dword(optional + directories + 20);
        auto resolve = [&](unsigned address, unsigned length) -> size_t {
            for (unsigned i = 0; i < sections; ++i) {
                size_t section = optional + optional_size + i * 40;
                r.Check(section, 40);
                unsigned va = r.Dword(section + 12), raw_size = r.Dword(section + 16), raw = r.Dword(section + 20);
                if (address >= va && address - va <= raw_size && length <= raw_size - (address - va)) {
                    size_t offset = size_t(raw) + (address - va); r.Check(offset, length); return offset;
                }
            }
            throw std::out_of_range("language section");
        };
        size_t base = resolve(resource_rva, resource_size);
        auto resource = [&](unsigned offset, unsigned size) -> size_t {
            if (offset > resource_size || size > resource_size - offset) throw std::out_of_range("language directory");
            return base + offset;
        };
        auto entries = [&](unsigned offset) {
            size_t directory = resource(offset, 16);
            unsigned count = r.Word(directory + 12) + r.Word(directory + 14);
            if (count > 4096) throw std::out_of_range("language entries");
            resource(offset + 16, count * 8);
            return count;
        };
        for (unsigned t = 0, count = entries(0); t < count; ++t) {
            size_t type = resource(16 + t * 8, 8);
            if (r.Dword(type) != 6 || !(r.Dword(type + 4) & 0x80000000)) continue;
            unsigned blocks = r.Dword(type + 4) & 0x7fffffff;
            for (unsigned b = 0, block_count = entries(blocks); b < block_count; ++b) {
                size_t block = resource(blocks + 16 + b * 8, 8);
                unsigned id = r.Dword(block), languages = r.Dword(block + 4);
                if (!id || id > 4096 || !(languages & 0x80000000)) continue;
                languages &= 0x7fffffff;
                for (unsigned l = 0, language_count = entries(languages); l < language_count; ++l) {
                    size_t leaf = resource(languages + 16 + l * 8, 8);
                    if ((r.Dword(leaf) & 0x3ff) != language || (r.Dword(leaf + 4) & 0x80000000)) continue;
                    size_t data = resource(r.Dword(leaf + 4), 16);
                    unsigned length = r.Dword(data + 4);
                    size_t position = resolve(r.Dword(data), length), end = position + length;
                    for (unsigned s = 0; s < 16; ++s) {
                        if (end - position < 2) throw std::out_of_range("language string");
                        unsigned units = r.Word(position); position += 2;
                        if (units > 4096 || units * 2 > end - position) throw std::out_of_range("language string");
                        std::string text;
                        for (unsigned u = 0; u < units; ++u) {
                            unsigned code = r.Word(position); position += 2;
                            if (code >= 0xd800 && code <= 0xdbff) {
                                if (++u == units) throw std::out_of_range("language surrogate");
                                unsigned low = r.Word(position); position += 2;
                                if (low < 0xdc00 || low > 0xdfff) throw std::out_of_range("language surrogate");
                                code = 0x10000 + ((code - 0xd800) << 10) + low - 0xdc00;
                            } else if ((code >= 0xdc00 && code <= 0xdfff) || code == 0) throw std::out_of_range("language character");
                            Append_UTF8(text, code);
                        }
                        if (!text.empty()) strings.emplace((id - 1) * 16 + s, std::move(text));
                    }
                    break;
                }
            }
        }
        return !strings.empty();
    } catch (std::out_of_range const &) { strings.clear(); return false; }
}
