#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {


// Instrument status.
struct SecurityStatus {

    static constexpr auto name = "Security Status";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr SecurityStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityStatus(const std::uint8_t &value)
     : value{ value } {}

    // get value of SecurityStatus field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
