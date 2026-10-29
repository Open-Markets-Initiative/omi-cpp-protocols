#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {


// clientAppVersion data struct
struct ClientAppVersion {

    static constexpr auto name = "Client App Version";
    static constexpr std::size_t size = 0;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr ClientAppVersion()
     : value{} {}

    // standard constructor
    constexpr explicit ClientAppVersion(const type &value)
     : value{ value } {}

    // get value of ClientAppVersion field
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
