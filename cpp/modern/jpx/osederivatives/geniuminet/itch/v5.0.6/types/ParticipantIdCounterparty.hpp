#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {


// Counterparty ID (blank for anonymous markets)
struct ParticipantIdCounterparty {

    static constexpr auto name = "Participant Id Counterparty";
    static constexpr std::size_t size = 7;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr ParticipantIdCounterparty()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ParticipantIdCounterparty(const type &value)
     : value{ value } {}

    // get value of ParticipantIdCounterparty field
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
