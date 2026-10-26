#pragma once

#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {


// Corrected number of days that may elapse before delivery of the security
struct CorrectedSellersSaleDays {

    static constexpr auto name = "Corrected Sellers Sale Days";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr CorrectedSellersSaleDays()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CorrectedSellersSaleDays(const std::uint8_t &value)
     : value{ value } {}

    // get value of CorrectedSellersSaleDays field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
