#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace asx::asxderivatives::ntp::itch::v1_05 {


// Participant identifier of the aggressive party to the execution in non-anonymous markets. Space filled for anonymous instruments.
struct CounterPartyId {

    static constexpr auto name = "Counter Party Id";
    static constexpr std::size_t size = 3;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr CounterPartyId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CounterPartyId(const type &value)
     : value{ value } {}

    // get value of CounterPartyId field
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
