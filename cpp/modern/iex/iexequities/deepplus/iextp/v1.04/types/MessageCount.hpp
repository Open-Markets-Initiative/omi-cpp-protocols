#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deepplus::iextp::v1_04 {

// Number of messages in the payload
struct MessageCount {

    static constexpr const char* name = "Message Count";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr MessageCount()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MessageCount(const std::uint16_t value)
     : value{ value } {}

    // get value of MessageCount field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
