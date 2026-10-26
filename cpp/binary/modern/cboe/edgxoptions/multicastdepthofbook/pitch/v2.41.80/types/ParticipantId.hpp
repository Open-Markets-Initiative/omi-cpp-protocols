#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {


// Optionally specified. If specified, MPID (equities) or Executing Firm ID (options) of firm attributed to this quote. Alternatively "RTAL" for retail specified orders (equities). Space filled otherwise.
struct ParticipantId {

    static constexpr auto name = "Participant Id";
    static constexpr std::size_t size = 4;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr ParticipantId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ParticipantId(const type &value)
     : value{ value } {}

    // get value of ParticipantId field
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
