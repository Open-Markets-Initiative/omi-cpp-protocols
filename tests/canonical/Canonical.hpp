#pragma once

// Canonical values: what a generated parser read, written as the model's traits say, and compared
// with what the model reads (tests/values/), address by address. A format is held to every value it
// reads; a value it does not read is not asked of it.

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <map>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace canonical {

// One datagram's values, by indexed address
using Listing = std::map<std::string, std::string>;

// An integer as its digits; an enum as the integer it holds; a duration as the count it holds
template <typename T>
std::string number(T value) {
    if constexpr (requires { value.count(); }) {
        return number(value.count());
    } else if constexpr (std::is_enum_v<T>) {
        return number(std::to_underlying(value));
    } else if constexpr (std::is_signed_v<T>) {
        return std::to_string(static_cast<long long>(value));
    } else {
        return std::to_string(static_cast<unsigned long long>(value));
    }
}

// An integer scaled by a power of ten, written exactly: no floating point, no zeros after the last
// digit that counts, and no point when nothing follows it (1234500 at -4 is 123.45)
template <typename T>
std::string scaled(T mantissa, int scale) {
    bool negative = false;
    unsigned long long magnitude = 0;

    if constexpr (std::is_signed_v<T>) {
        negative = mantissa < 0;
        magnitude = negative ? 0ULL - static_cast<unsigned long long>(mantissa) : static_cast<unsigned long long>(mantissa);
    } else {
        magnitude = static_cast<unsigned long long>(mantissa);
    }

    std::string digits = std::to_string(magnitude);

    if (scale >= 0) {
        return (negative ? "-" : "") + digits + (magnitude == 0 ? std::string{} : std::string(static_cast<std::size_t>(scale), '0'));
    }

    const std::size_t places = static_cast<std::size_t>(-scale);

    if (digits.size() < places + 1) {
        digits.insert(0, places + 1 - digits.size(), '0');
    }

    std::string whole = digits.substr(0, digits.size() - places);
    std::string fraction = digits.substr(digits.size() - places);

    while (!fraction.empty() && fraction.back() == '0') { fraction.pop_back(); }

    std::string text = fraction.empty() ? whole : whole + "." + fraction;

    return negative && text != "0" ? "-" + text : text;
}

// A character a format reads, as text: a char as itself, an enum of characters as the character it holds
template <typename T>
std::string character(T value) {
    if constexpr (std::is_enum_v<T>) {
        return std::string(1, static_cast<char>(std::to_underlying(value)));
    } else {
        return std::string(1, static_cast<char>(value));
    }
}

// Text as the model leaves it: the fill it names taken off the side its justification leaves open
inline std::string text(std::string value, char fill, bool right) {
    if (right) {
        const auto first = value.find_first_not_of(fill);
        return first == std::string::npos ? std::string{} : value.substr(first);
    }

    const auto last = value.find_last_not_of(fill);
    return last == std::string::npos ? std::string{} : value.substr(0, last + 1);
}

// Text stating no fill: every character kept
inline std::string text(std::string value) {
    return value;
}

// A nullable field holding no value, as the model lists it
inline std::string absent() {
    return "(null)";
}

// Numeric text as the number it spells, without the zeros or spaces in front of it
inline std::string numeric(std::string value) {
    const auto first = value.find_first_not_of(" \0", 0, 2);

    if (first == std::string::npos) { return std::string{}; }

    const auto last = value.find_last_not_of(" \0", std::string::npos, 2);
    std::string digits = value.substr(first, last - first + 1);
    const bool negative = !digits.empty() && digits[0] == '-';

    if (negative) { digits.erase(0, 1); }

    const auto significant = digits.find_first_not_of('0');
    digits = significant == std::string::npos ? "0" : digits.substr(significant);

    return negative && digits != "0" ? "-" + digits : digits;
}

// The model's values of a sample: one listing per datagram, or per stream, in capture order
inline std::vector<Listing> load(const std::string& path) {
    std::ifstream file(path);
    std::vector<Listing> listings;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') { continue; }

        if (line.rfind("datagram ", 0) == 0 || line.rfind("stream ", 0) == 0) {
            listings.emplace_back();
            continue;
        }

        const auto equals = line.find(" = ");

        if (equals != std::string::npos && !listings.empty()) {
            listings.back()[line.substr(0, equals)] = line.substr(equals + 3);
        }
    }

    return listings;
}

// Where the model's values are: the directory the test run names
inline std::string root() {
    const char* value = std::getenv("OMI_VALUES_DIR");

    if (value == nullptr) {
        std::printf("FAIL: OMI_VALUES_DIR is not set\n");
        std::exit(1);
    }

    return std::string{value};
}

// Hold what a format read from one datagram to what the model reads: every value it read must be the
// model's at its address. Returns the differences, printing the first of them.
inline int compare(const char* sample, std::size_t datagram, const Listing& model, const Listing& read) {
    int differences = 0;

    for (const auto& [address, value] : read) {
        const auto found = model.find(address);

        if (found == model.end()) {
            if (++differences <= 5) { std::printf("FAIL %s datagram %zu: %s = %s is not a value the model reads\n", sample, datagram, address.c_str(), value.c_str()); }
        } else if (found->second != value) {
            if (++differences <= 5) { std::printf("FAIL %s datagram %zu: %s = %s, the model reads %s\n", sample, datagram, address.c_str(), value.c_str(), found->second.c_str()); }
        }
    }

    return differences;
}

} // namespace canonical