#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {


// The ID of the client requesting this retransmission . This field is up to 9 characters, null terminated.
struct SourceId {

    static constexpr auto name = "Source Id";
    static constexpr std::size_t size = 10;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr SourceId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SourceId(const type &value)
     : value{ value } {}

    // get value of SourceId field
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
