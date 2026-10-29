#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v3_0 {


// 
struct SecurityTradingStatus {

    static constexpr auto name = "Security Trading Status";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 0xFF;
static const type maximum_value = 211;
static const type minimum_value = 200;

    // default constructor
    constexpr SecurityTradingStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityTradingStatus(const std::uint8_t &value)
     : value{ value } {}

    // get value of SecurityTradingStatus field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
