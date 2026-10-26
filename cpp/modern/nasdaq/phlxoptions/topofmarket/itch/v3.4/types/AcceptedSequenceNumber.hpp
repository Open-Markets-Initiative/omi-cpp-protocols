#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {


// The sequence number in ASCII of the next Sequenced Message to be sent. Left padded with spaces.
struct AcceptedSequenceNumber {

    static constexpr auto name = "Accepted Sequence Number";
    static constexpr std::size_t size = 20;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr AcceptedSequenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AcceptedSequenceNumber(const type &value)
     : value{ value } {}

    // get value of AcceptedSequenceNumber field
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
