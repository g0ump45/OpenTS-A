#pragma once
#include <cstdint>
#include <map>
#include <span>
#include <string>

bool Read_Language_Strings(std::span<unsigned char const> bytes, unsigned language,
    std::map<unsigned, std::string> & strings);
bool Compatible_Language_Format(std::string const & original, std::string const & translated);
