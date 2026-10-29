#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v1_91 {

// Trade volume of the original transaction
struct TradeVolumeLong {

    static constexpr const char* name = "Trade Volume Long";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TradeVolumeLong()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeVolumeLong(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of TradeVolumeLong field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
