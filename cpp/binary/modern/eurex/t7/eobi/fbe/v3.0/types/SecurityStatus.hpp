#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v3_0 {


// 
struct SecurityStatus {

    static constexpr auto name = "Security Status";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 0xFF;
static const type maximum_value = 9;
static const type minimum_value = 1;

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
