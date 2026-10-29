#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// The proxy price reported on the original trade transaction
struct OriginalProxyPrice {

    static constexpr const char* name = "Original Proxy Price";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr OriginalProxyPrice()
     : value{ 0 } {}

    // constructor for OriginalProxyPrice field
    constexpr explicit OriginalProxyPrice(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of OriginalProxyPrice field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of OriginalProxyPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
