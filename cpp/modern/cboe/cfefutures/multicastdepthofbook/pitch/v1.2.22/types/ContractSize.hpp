#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Contract size of Instrument. Contract sizes less than 1 are represented with a 0 value; refer to the product specification for the contract size.
struct ContractSize {

    static constexpr const char* name = "Contract Size";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr ContractSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ContractSize(const std::uint16_t value)
     : value{ value } {}

    // get value of ContractSize field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
