#pragma once

#include <bit>
#include <chrono>
#include <cstddef>
#include <cstdint>

#include "../common/Day.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

// Denotes the IPO release time, in seconds since midnight, for quotation to the nearest second.
struct IpoQuotationReleaseTime {

    static constexpr const char* name = "Ipo Quotation Release Time";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr IpoQuotationReleaseTime()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IpoQuotationReleaseTime(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of IpoQuotationReleaseTime field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

    // IpoQuotationReleaseTime on a day: its seconds since midnight, America/New_York, as UTC Unix nanoseconds
    [[nodiscard]] std::int64_t utc(const calendar::Day& day) const {
        return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(get()) * 1000000000);
    }

  protected:
    std::uint32_t value;
};
}
