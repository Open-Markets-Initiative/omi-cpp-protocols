#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {


// Use this sequence number to resume on the real time Mold Channel. ASCII representation of the sequence number.
struct EndOfReplaySequenceNumber {

    static constexpr auto name = "End Of Replay Sequence Number";
    static constexpr std::size_t size = 20;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr EndOfReplaySequenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit EndOfReplaySequenceNumber(const type &value)
     : value{ value } {}

    // get value of EndOfReplaySequenceNumber field
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
