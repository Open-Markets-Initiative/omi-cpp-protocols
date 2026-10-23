#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace asx::asxderivatives::ntp::itch::v1_05 {


// Buying participant identifier of the owner of the aggressive order.
struct BuyerParticipantId {

    static constexpr auto name = "Buyer Participant Id";
    static constexpr std::size_t size = 3;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr BuyerParticipantId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BuyerParticipantId(const type &value)
     : value{ value } {}

    // get value of BuyerParticipantId field
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
