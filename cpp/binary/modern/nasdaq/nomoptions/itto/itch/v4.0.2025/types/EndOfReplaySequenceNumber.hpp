#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {


// Use this sequence number to resume on the real time Mold channel.
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
