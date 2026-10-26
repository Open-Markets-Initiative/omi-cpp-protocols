#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {


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

    // runtime length of field: its characters up to the fill after the last of them, so a space
    // or a null inside the text is kept
    [[nodiscard]] std::size_t length() const {
        std::size_t index = size;
        for (; index > 0; --index) {
            if (value[index - 1] != '\0') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
