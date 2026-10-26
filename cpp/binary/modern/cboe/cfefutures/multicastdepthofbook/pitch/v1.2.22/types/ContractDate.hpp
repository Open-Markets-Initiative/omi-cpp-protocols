#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Populated for single leg instruments only. Zero-filled for spread instruments. The date that should be used in describing the future's third party symbol and the measurement period of the contract.
struct ContractDate {

    static constexpr const char* name = "Contract Date";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ContractDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ContractDate(const std::uint32_t value)
     : value{ value } {}

    // get value of ContractDate field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
