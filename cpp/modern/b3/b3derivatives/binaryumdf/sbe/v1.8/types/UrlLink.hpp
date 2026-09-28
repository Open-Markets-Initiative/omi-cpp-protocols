#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {


// uRLLink data struct
struct UrlLink {

    static constexpr auto name = "Url Link";
    static constexpr std::size_t size = 0;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr UrlLink()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UrlLink(const type &value)
     : value{ value } {}

    // get value of UrlLink field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field
    [[nodiscard]] std::size_t length() const {
        std::size_t index = 0;
        for (; index < size; ++index) {
            if (value[index] == ' ') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
