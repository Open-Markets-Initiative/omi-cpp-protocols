#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Contains the workup ID; unique per instrument per day
struct TradeLinkId {

    static constexpr const char* name = "Trade Link Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TradeLinkId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeLinkId(const std::uint32_t value)
     : value{ value } {}

    // get value of TradeLinkId field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
