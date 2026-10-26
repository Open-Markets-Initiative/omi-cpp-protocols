#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deepplus::iextp::v1_01 {

// Unique identifier of the higher layer protocol
struct MessageProtocolId {

    static constexpr const char* name = "Message Protocol Id";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type static_value = 32773;

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
