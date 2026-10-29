#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// Unique ID assigned by MIAX Futures Onyx for a Complex instrument and is permanent for the life of an instrument
struct StrategyId {

    static constexpr const char* name = "Strategy Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr StrategyId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StrategyId(const std::uint32_t value)
     : value{ value } {}

    // get value of StrategyId field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
