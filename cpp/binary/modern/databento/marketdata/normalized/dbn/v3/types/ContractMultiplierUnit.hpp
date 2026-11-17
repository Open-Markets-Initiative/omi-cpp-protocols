// Databento.MarketData.Normalized.Dbn.v3: types/ContractMultiplierUnit.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {


// The contract multiplier unit
struct ContractMultiplierUnit {

    static constexpr auto name = "Contract Multiplier Unit";
    static constexpr std::size_t size = 1;
    using type = std::int8_t;

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
