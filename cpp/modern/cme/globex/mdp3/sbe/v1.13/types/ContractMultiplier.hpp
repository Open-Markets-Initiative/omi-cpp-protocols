#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Number of deliverable units per instrument, e.g., peak days in maturity month or number of calendar days in maturity month
struct ContractMultiplier {

    static constexpr const char* name = "Contract Multiplier";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;
static const type no_value = 2147483647;

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
