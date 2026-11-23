// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/MarketOrderImbalanceVolume.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// Indicates The Share Imbalance When Considering Moc Orders Only Note This Will Not Change From Freeze Period As Moc Orders Are Not Allowed After This Time
struct MarketOrderImbalanceVolume {

    static constexpr const char* name = "Market Order Imbalance Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0;

    // default constructor: the null the model states, where it states one
    constexpr MarketOrderImbalanceVolume()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit MarketOrderImbalanceVolume(const std::uint32_t value)
     : value{ value } {}

    // get value of MarketOrderImbalanceVolume field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
