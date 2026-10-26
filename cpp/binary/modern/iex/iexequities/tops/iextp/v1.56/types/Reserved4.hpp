#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::tops::iextp::v1_56 {

// Reserved bytes
struct Reserved4 {

    static constexpr const char* name = "Reserved 4";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Reserved4()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Reserved4(const std::uint32_t value)
     : value{ value } {}

    // get value of Reserved4 field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
