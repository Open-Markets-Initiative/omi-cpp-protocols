#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Denotes the IPO release time, in seconds since midnight, for quotation to the nearest second
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

  protected:
    std::uint32_t value;
};
}
