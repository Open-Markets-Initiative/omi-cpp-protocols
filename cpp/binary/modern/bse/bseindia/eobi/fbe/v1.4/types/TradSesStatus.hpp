#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {


// Miscellaneous state information.
struct TradSesStatus {

    static constexpr auto name = "Trad Ses Status";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr TradSesStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradSesStatus(const std::uint8_t &value)
     : value{ value } {}

    // get value of TradSesStatus field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
