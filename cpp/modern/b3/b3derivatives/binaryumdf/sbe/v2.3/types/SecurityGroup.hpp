#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {


// securityGroup
struct SecurityGroup {

    static constexpr auto name = "Security Group";
    static constexpr std::size_t size = 3;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr SecurityGroup()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityGroup(const type &value)
     : value{ value } {}

    // get value of SecurityGroup field
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
