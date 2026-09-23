#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Specifies the next sequence number in ASCII the client wants to receive upon connection, or 0 to start receiving the most recently generated message.
struct RequestedSequenceNumber {

    static constexpr auto name = "Requested Sequence Number";
    static constexpr std::size_t size = 20;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr RequestedSequenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RequestedSequenceNumber(const type &value)
     : value{ value } {}

    // get value of RequestedSequenceNumber field
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
