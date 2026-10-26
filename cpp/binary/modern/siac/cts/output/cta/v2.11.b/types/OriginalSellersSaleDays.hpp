#pragma once

#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {


// Original number of days that may elapse before delivery of the security
struct OriginalSellersSaleDays {

    static constexpr auto name = "Original Sellers Sale Days";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr OriginalSellersSaleDays()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OriginalSellersSaleDays(const std::uint8_t &value)
     : value{ value } {}

    // get value of OriginalSellersSaleDays field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
