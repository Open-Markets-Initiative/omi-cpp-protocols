// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/AdrRatio.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// ADR ratio with 6 decimal places assumed. Applies to ADR/GDR/NYRS securities only.
struct AdrRatio {

    static constexpr const char* name = "Adr Ratio";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr AdrRatio()
     : value{ 0 } {}

    // constructor for AdrRatio field
    constexpr explicit AdrRatio(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of AdrRatio field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of AdrRatio field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
