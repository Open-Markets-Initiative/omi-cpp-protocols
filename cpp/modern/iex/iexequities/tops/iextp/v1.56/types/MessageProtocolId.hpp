#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::tops::iextp::v1_56 {

// Unique identifier of the higher layer protocol
struct MessageProtocolId {

    static constexpr const char* name = "Message Protocol Id";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr MessageProtocolId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MessageProtocolId(const std::uint16_t value)
     : value{ value } {}

    // get value of MessageProtocolId field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
