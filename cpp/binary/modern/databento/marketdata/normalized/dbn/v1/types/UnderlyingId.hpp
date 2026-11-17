// Databento.MarketData.Normalized.Dbn.v1: types/UnderlyingId.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {

// The underlying id
struct UnderlyingId {

    static constexpr const char* name = "Underlying Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr UnderlyingId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnderlyingId(const std::uint32_t value)
     : value{ value } {}

    // get value of UnderlyingId field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
