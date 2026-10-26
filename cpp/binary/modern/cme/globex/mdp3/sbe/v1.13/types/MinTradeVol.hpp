#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// The minimum trading volume for a security
struct MinTradeVol {

    static constexpr const char* name = "Min Trade Vol";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr MinTradeVol()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MinTradeVol(const std::uint32_t value)
     : value{ value } {}

    // get value of MinTradeVol field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
