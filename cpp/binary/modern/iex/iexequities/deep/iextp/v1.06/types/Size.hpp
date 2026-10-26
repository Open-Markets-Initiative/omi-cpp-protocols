#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deep::iextp::v1_06 {

// Aggregate quoted size
struct Size {

    static constexpr const char* name = "Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Size()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Size(const std::uint32_t value)
     : value{ value } {}

    // get value of Size field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
