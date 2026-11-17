// Databento.MarketData.Normalized.Dbn.v1: types/MdSecurityTradingStatus.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {


// The current trading state of the instrument
struct MdSecurityTradingStatus {

    static constexpr auto name = "Md Security Trading Status";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr MdSecurityTradingStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdSecurityTradingStatus(const std::uint8_t &value)
     : value{ value } {}

    // get value of MdSecurityTradingStatus field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
