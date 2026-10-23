#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Reference number of the Seller’s order – 0 if order is aggressive.
struct SellerOrderId {

    static constexpr const char* name = "Seller Order Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr SellerOrderId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SellerOrderId(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of SellerOrderId field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
