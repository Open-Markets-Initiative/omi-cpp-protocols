#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {


// securityDesc data struct
struct SecurityDesc {

    static constexpr auto name = "Security Desc";
    static constexpr std::size_t size = 0;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr SecurityDesc()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityDesc(const type &value)
     : value{ value } {}

    // get value of SecurityDesc field
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
