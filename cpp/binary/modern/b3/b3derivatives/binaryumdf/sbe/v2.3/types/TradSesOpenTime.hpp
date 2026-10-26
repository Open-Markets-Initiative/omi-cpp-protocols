#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {


// tradSesOpenTime
struct TradSesOpenTime {

    static constexpr auto name = "Trad Ses Open Time";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor
    constexpr TradSesOpenTime()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradSesOpenTime(const std::uint64_t &value)
     : value{ value } {}

    // get value of TradSesOpenTime field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
