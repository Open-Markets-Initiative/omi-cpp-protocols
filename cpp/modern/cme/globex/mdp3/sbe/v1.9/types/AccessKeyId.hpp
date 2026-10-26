#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cme::mdp3::v9 {


// Contains the AccessKeyID assigned to this session on this port
struct AccessKeyId {

    static constexpr auto name = "Access Key Id";
    static constexpr std::size_t size = 20;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr AccessKeyId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AccessKeyId(const type &value)
     : value{ value } {}

    // get value of AccessKeyId field
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
