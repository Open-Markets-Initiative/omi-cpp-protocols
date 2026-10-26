#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Settle (Value) Date corresponding to Trade Date
struct SettlDate {

    static constexpr const char* name = "Settl Date";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 65535;

    // default constructor
    constexpr SettlDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SettlDate(const std::uint16_t value)
     : value{ value } {}

    // get value of SettlDate field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
