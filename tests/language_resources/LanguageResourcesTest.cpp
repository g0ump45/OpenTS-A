#include "../../code/language_resources.h"
#include <cassert>
#include <vector>
#include <fstream>
#include <iostream>
int main(int argc, char ** argv) {
    assert(Compatible_Language_Format("Count %d: %s", "Cuenta %d: %s"));
    assert(!Compatible_Language_Format("Count %d", "Cuenta %s"));
    assert(!Compatible_Language_Format("Count %d", "Cuenta %n"));
    assert(Compatible_Language_Format("%*.*s", "%*.*s"));
    std::vector<unsigned char> bytes(1024);
    auto w = [&](size_t p, unsigned v) { bytes[p] = v; bytes[p+1] = v >> 8; };
    auto d = [&](size_t p, unsigned v) { w(p,v); w(p+2,v>>16); };
    w(0,0x5a4d);d(60,64);d(64,0x4550);w(70,1);w(84,224);
    w(88,0x10b);d(200,4096);d(204,512);
    d(320,512);d(324,4096);d(328,512);d(332,512);
    w(512+14,1);d(528,6);d(532,0x80000020);
    w(544+14,1);d(560,1);d(564,0x80000040);
    w(576+14,1);d(592,3082);d(596,96);
    d(608,4224);d(612,40);w(640,4);
    w(642,'H');w(644,'o');w(646,'l');w(648,'a');
    std::map<unsigned,std::string> strings;
    assert(Read_Language_Strings(bytes,10,strings));assert(strings.at(0)=="Hola");
    assert(!Read_Language_Strings(bytes,7,strings));
    w(642,0xd800);assert(!Read_Language_Strings(bytes,10,strings));
    bytes.resize(40);assert(!Read_Language_Strings(bytes,10,strings));
    if(argc>1) {
        std::ifstream file(argv[1], std::ios::binary);
        bytes.assign(std::istreambuf_iterator<char>(file),{});
        assert(Read_Language_Strings(bytes, argc > 2 ? std::stoi(argv[2]) : 10, strings));
        std::cout << "Language resource strings: " << strings.size() << "\n";
    }
    std::cout << "Language resource tests passed\n";
}
