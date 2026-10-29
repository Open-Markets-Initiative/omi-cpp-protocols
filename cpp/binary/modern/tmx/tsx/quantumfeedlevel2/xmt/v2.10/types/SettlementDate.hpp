#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// Settlement Date Associated With The Order
struct SettlementDate {

    static constexpr const char* name = "Settlement Date";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0;

    // default constructor
    constexpr SettlementDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SettlementDate(const std::uint32_t value)
     : value{ value } {}

    // get value of SettlementDate field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
