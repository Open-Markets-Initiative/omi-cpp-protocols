#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// Contract quantity
struct ContractMultiplier {

    static constexpr const char* name = "Contract Multiplier";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr ContractMultiplier()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ContractMultiplier(const std::uint16_t value)
     : value{ value } {}

    // get value of ContractMultiplier field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
