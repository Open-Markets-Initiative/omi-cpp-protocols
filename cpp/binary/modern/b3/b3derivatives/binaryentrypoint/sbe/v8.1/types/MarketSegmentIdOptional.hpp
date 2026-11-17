// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.1: types/MarketSegmentIdOptional.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {


// marketSegmentID
struct MarketSegmentIdOptional {

    static constexpr auto name = "Market Segment Id Optional";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 0;

    // default constructor
    constexpr MarketSegmentIdOptional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketSegmentIdOptional(const std::uint8_t &value)
     : value{ value } {}

    // get value of MarketSegmentIdOptional field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
