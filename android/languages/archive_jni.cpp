#include <jni.h>
#include <archive.h>
#include <archive_entry.h>
#include <cstdio>
#include <string>
#include <memory>
#include <vector>

extern "C" JNIEXPORT void JNICALL
Java_com_opents_game_LanguageArchive_extract(JNIEnv * env, jclass, jstring source,
    jstring directory, jobjectArray paths, jobjectArray names, jlongArray lengths, jobject progress)
{
    auto fail = [&](char const * message) {
        if (!env->ExceptionCheck()) env->ThrowNew(env->FindClass("java/io/IOException"), message);
    };
    auto text = [&](jstring value) {
        char const * raw = env->GetStringUTFChars(value, nullptr);
        std::string result = raw ? raw : "";
        if (raw) env->ReleaseStringUTFChars(value, raw);
        return result;
    };
    std::string input = text(source), output = text(directory);
    int count = env->GetArrayLength(paths);
    if (count != env->GetArrayLength(names) || count != env->GetArrayLength(lengths) || count > 200) { fail("Invalid language manifest."); return; }
    std::vector<std::string> from, to;
    std::vector<jlong> sizes(count);
    env->GetLongArrayRegion(lengths, 0, count, sizes.data());
    for (int i = 0; i < count; ++i) {
        auto path = static_cast<jstring>(env->GetObjectArrayElement(paths, i));
        auto name = static_cast<jstring>(env->GetObjectArrayElement(names, i));
        from.push_back(text(path)); to.push_back(text(name));
        env->DeleteLocalRef(path); env->DeleteLocalRef(name);
        if (to.back().empty() || to.back().find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_.-") != std::string::npos || to.back().find("..") != std::string::npos || sizes[i] <= 0 || sizes[i] > 2LL * 1024 * 1024 * 1024) { fail("Invalid language output."); return; }
    }
    auto reader = std::unique_ptr<archive, decltype(&archive_read_free)>(archive_read_new(), archive_read_free);
    archive_read_support_format_rar5(reader.get());
    if (archive_read_open_filename(reader.get(), input.c_str(), 65536) != ARCHIVE_OK) { fail("Cannot open language archive."); return; }
    jclass type = env->GetObjectClass(progress);
    jmethodID update = env->GetMethodID(type, "update", "(Ljava/lang/String;)V");
    env->DeleteLocalRef(type);
    if (!update || env->ExceptionCheck()) return;
    int found = 0, result;
    archive_entry * entry = nullptr;
    std::vector<char> buffer(65536);
    while ((result = archive_read_next_header(reader.get(), &entry)) == ARCHIVE_OK) {
        char const * path = archive_entry_pathname(entry);
        std::string normalized = path ? path : "";
        for (char & c : normalized) if (c == '\\') c = '/';
        int index = 0;
        for (; index < count && from[index] != normalized; ++index) {}
        if (index == count) { if (archive_read_data_skip(reader.get()) != ARCHIVE_OK) { fail("Damaged language archive."); return; } continue; }
        if (archive_entry_filetype(entry) != AE_IFREG || archive_entry_symlink(entry) || archive_entry_hardlink(entry) || archive_entry_size(entry) != sizes[index]) { fail("Language archive entry changed."); return; }
        std::string target = output + "/" + to[index], temporary = target + ".language-part";
        auto file = std::unique_ptr<FILE, decltype(&std::fclose)>(std::fopen(temporary.c_str(), "wb"), std::fclose);
        if (!file) { fail("Cannot write language files."); return; }
        int64_t bytes = 0;
        for (;;) {
            std::string status = "Unpacking Spanish: " + to[index] + " (" + std::to_string(bytes * 100 / sizes[index]) + "%)";
            jstring message = env->NewStringUTF(status.c_str());
            env->CallVoidMethod(progress, update, message); env->DeleteLocalRef(message);
            if (env->ExceptionCheck()) { file.reset(); std::remove(temporary.c_str()); return; }
            auto read = archive_read_data(reader.get(), buffer.data(), buffer.size());
            if (read == 0) break;
            if (read < 0 || read > sizes[index] - bytes || std::fwrite(buffer.data(), 1, read, file.get()) != static_cast<size_t>(read)) { file.reset(); std::remove(temporary.c_str()); fail("Language file is damaged or storage is full."); return; }
            bytes += read;
        }
        int close = std::fclose(file.release());
        if (close != 0 || bytes != sizes[index] || std::rename(temporary.c_str(), target.c_str()) != 0) { std::remove(temporary.c_str()); fail("Cannot complete language file."); return; }
        ++found;
    }
    if (result != ARCHIVE_EOF || found != count) fail("Language archive is incomplete.");
}
