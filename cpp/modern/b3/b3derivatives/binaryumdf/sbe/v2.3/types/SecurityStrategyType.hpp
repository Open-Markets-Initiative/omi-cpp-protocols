#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {


// securityStrategyType
struct SecurityStrategyType {

    static constexpr auto name = "Security Strategy Type";
    static constexpr std::size_t size = 3;

    // underlying type
    using type = std::array<char, size>;

    // whether the optional SecurityStrategyType field is present
    [[nodiscard]] bool has_value() const {
        return value[0] != '\0';
    }

    // default constructor
    constexpr SecurityStrategyType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityStrategyType(const type &value)
     : value{ value } {}

    // get value of SecurityStrategyType field
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
