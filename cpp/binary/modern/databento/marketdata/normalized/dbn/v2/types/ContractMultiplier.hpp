#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v2 {

// The contract multiplier
struct ContractMultiplier {

    static constexpr const char* name = "Contract Multiplier";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr ContractMultiplier()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ContractMultiplier(const std::int32_t value)
     : value{ value } {}

    // get value of ContractMultiplier field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
