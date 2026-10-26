#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {


// Indicates the type of multiplier being applied to the product. Optionally used in combination with tag 231-ContractMultiplier
struct ContractMultiplierUnit {

    static constexpr auto name = "Contract Multiplier Unit";
    static constexpr std::size_t size = 1;
    using type = std::int8_t;
static const type no_value = 127;

    // default constructor
    constexpr ContractMultiplierUnit()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ContractMultiplierUnit(const std::int8_t &value)
     : value{ value } {}

    // get value of ContractMultiplierUnit field
    [[nodiscard]] std::int8_t get() const {
        return value;
    }

  protected:
    std::int8_t value;
};
}
