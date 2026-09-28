#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {


// languageCode
struct LanguageCode {

    static constexpr auto name = "Language Code";
    static constexpr std::size_t size = 2;

    // underlying type
    using type = std::array<char, size>;

    // whether the optional LanguageCode field is present
    [[nodiscard]] bool has_value() const {
        return value[0] != '\0';
    }

    // default constructor
    constexpr LanguageCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LanguageCode(const type &value)
     : value{ value } {}

    // get value of LanguageCode field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field
    [[nodiscard]] std::size_t length() const {
        std::size_t index = 0;
        for (; index < size; ++index) {
            if (value[index] == '\0') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
