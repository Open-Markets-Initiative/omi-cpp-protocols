#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace asx::asxderivatives::ntp::itch::v1_05 {


// Participant identifier of the owner of the buying order. Blank for anonymous instruments.
struct ParticipantIdBuyer {

    static constexpr auto name = "Participant Id Buyer";
    static constexpr std::size_t size = 3;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr ParticipantIdBuyer()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ParticipantIdBuyer(const type &value)
     : value{ value } {}

    // get value of ParticipantIdBuyer field
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
