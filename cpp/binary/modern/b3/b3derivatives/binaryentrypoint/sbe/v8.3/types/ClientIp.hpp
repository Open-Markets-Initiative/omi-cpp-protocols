#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {


// clientIP data struct
struct ClientIp {

    static constexpr auto name = "Client Ip";
    static constexpr std::size_t size = 0;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr ClientIp()
     : value{} {}

    // standard constructor
    constexpr explicit ClientIp(const type &value)
     : value{ value } {}

    // get value of ClientIp field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field: its characters up to the fill after the last of them, so a space
    // or a null inside the text is kept
    [[nodiscard]] std::size_t length() const {
        std::size_t index = size;
        for (; index > 0; --index) {
            if (value[index - 1] != ' ') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
