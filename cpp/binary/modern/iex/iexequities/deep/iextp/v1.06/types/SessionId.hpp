#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deep::iextp::v1_06 {

// Identifies the session
struct SessionId {

    static constexpr const char* name = "Session Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr SessionId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SessionId(const std::uint32_t value)
     : value{ value } {}

    // get value of SessionId field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
