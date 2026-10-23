#pragma once

#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {


// Specifies the number of days that may elapse before delivery of the security. Allowed values 2 through 60 days
struct SellersSaleDays {

    static constexpr auto name = "Sellers Sale Days";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr SellersSaleDays()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SellersSaleDays(const std::uint8_t &value)
     : value{ value } {}

    // get value of SellersSaleDays field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
