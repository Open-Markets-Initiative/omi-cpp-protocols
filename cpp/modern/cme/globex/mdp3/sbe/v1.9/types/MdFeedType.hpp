#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cme::mdp3::v9 {


// Describes a class of service for a given data feed. GBX- Real Book, GBI-Implied Book
struct MdFeedType {

    static constexpr auto name = "Md Feed Type";
    static constexpr std::size_t size = 3;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr MdFeedType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdFeedType(const type &value)
     : value{ value } {}

    // get value of MdFeedType field
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
