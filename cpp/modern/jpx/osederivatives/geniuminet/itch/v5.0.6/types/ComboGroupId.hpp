#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Used to group combination executions
struct ComboGroupId {

    static constexpr const char* name = "Combo Group Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ComboGroupId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ComboGroupId(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of ComboGroupId field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
