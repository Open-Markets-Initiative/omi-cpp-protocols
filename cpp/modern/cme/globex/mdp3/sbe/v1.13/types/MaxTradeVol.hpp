#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// The maximum trading volume for a security
struct MaxTradeVol {

    static constexpr const char* name = "Max Trade Vol";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr MaxTradeVol()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MaxTradeVol(const std::uint32_t value)
     : value{ value } {}

    // get value of MaxTradeVol field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
