#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <string_view>

// Text a field states in a single byte encoding, decoded to UTF-8. Latin-1 is U+0000 to U+00FF byte
// for byte; Windows-1252 differs from it at 0x80 to 0x9F alone, where it leaves five bytes undefined:
// each is decoded as U+FFFD, the replacement character, and counted
namespace scaled::delimited::encoding {

// the single byte encodings a field may state its text in
enum class Encoding {
    latin1,
    windows1252,
};

// the replacement character an undefined byte is decoded as
constexpr char32_t replacement = 0xFFFD;

// Windows-1252's characters at 0x80 to 0x9F, where it differs from Latin-1; 0 where it defines none
constexpr std::array<char32_t, 32> windows1252{
    0x20AC, 0x0000, 0x201A, 0x0192, 0x201E, 0x2026, 0x2020, 0x2021, 0x02C6, 0x2030, 0x0160, 0x2039, 0x0152, 0x0000, 0x017D, 0x0000,
    0x0000, 0x2018, 0x2019, 0x201C, 0x201D, 0x2022, 0x2013, 0x2014, 0x02DC, 0x2122, 0x0161, 0x203A, 0x0153, 0x0000, 0x017E, 0x0178,
};

// the bytes decoded as U+FFFD, as their encoding defines no character for them, for a program to report
inline std::uint64_t& undefined() {
    thread_local std::uint64_t count = 0;
    return count;
}

// a character appended as UTF-8
inline void append(std::string& out, const char32_t code) {
    if (code < 0x80) {
        out.push_back(static_cast<char>(code));
        return;
    }
    if (code < 0x800) {
        out.push_back(static_cast<char>(0xC0 | (code >> 6)));
        out.push_back(static_cast<char>(0x80 | (code & 0x3F)));
        return;
    }
    out.push_back(static_cast<char>(0xE0 | (code >> 12)));
    out.push_back(static_cast<char>(0x80 | ((code >> 6) & 0x3F)));
    out.push_back(static_cast<char>(0x80 | (code & 0x3F)));
}

// the character a byte of an encoding is: an undefined one U+FFFD, and counted
inline char32_t character(const unsigned char byte, const Encoding encoding) {
    if (byte < 0x80 || byte >= 0xA0 || encoding == Encoding::latin1) {
        return byte;
    }
    const auto code = windows1252[static_cast<std::size_t>(byte - 0x80)];
    if (code == 0) {
        ++undefined();
        return replacement;
    }
    return code;
}

// bytes of an encoding appended as UTF-8
inline void decode(std::string& out, const std::string_view bytes, const Encoding encoding) {
    for (const char each : bytes) {
        append(out, character(static_cast<unsigned char>(each), encoding));
    }
}

// bytes of an encoding as UTF-8
inline std::string utf8(const std::string_view bytes, const Encoding encoding) {
    std::string out;
    out.reserve(bytes.size());
    decode(out, bytes, encoding);
    return out;
}

}
