#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// contractMultiplier
struct ContractMultiplier {

    static constexpr const char* name = "Contract Multiplier";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
    using type = std::int64_t;
static const type no_value = (-9223372036854775807LL - 1);

    // default constructor
    constexpr ContractMultiplier()
     : value{ 0 } {}

    // constructor for ContractMultiplier field
    constexpr explicit ContractMultiplier(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of ContractMultiplier field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of ContractMultiplier field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
