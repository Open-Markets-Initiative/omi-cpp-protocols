#pragma once

#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v1_91 {


// Specifies the number of days that may elapse before delivery of the security
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
