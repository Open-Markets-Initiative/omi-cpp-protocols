#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::tops::iextp::v1_66 {

// Byte offset of the data stream
struct StreamOffset {

    static constexpr const char* name = "Stream Offset";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr StreamOffset()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StreamOffset(const std::uint64_t value)
     : value{ value } {}

    // get value of StreamOffset field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
