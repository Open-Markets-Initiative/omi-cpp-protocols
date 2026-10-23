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
