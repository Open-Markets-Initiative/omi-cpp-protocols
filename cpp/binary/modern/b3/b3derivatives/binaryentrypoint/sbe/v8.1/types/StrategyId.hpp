#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// strategyID
struct StrategyId {

    static constexpr const char* name = "Strategy Id";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;
static const type no_value = 0;

    // default constructor
    constexpr StrategyId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StrategyId(const std::int32_t value)
     : value{ value } {}

    // get value of StrategyId field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
