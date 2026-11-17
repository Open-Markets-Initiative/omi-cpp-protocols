// Databento.MarketData.Normalized.Dbn.v3: types/UpdateAction.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {


// Indicates if the statistic is newly added or deleted
struct UpdateAction {

    static constexpr auto name = "Update Action";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr UpdateAction()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UpdateAction(const std::uint8_t &value)
     : value{ value } {}

    // get value of UpdateAction field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
