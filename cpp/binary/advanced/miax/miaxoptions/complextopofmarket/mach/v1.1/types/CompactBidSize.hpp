// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: types/CompactBidSize.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// compact_bid_size
struct compact_bid_size {

    static constexpr const char* name = "compact_bid_size";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint16_t>;
    using storage_type = result_type;

    constexpr compact_bid_size()
     : value{ 0 } {}

    constexpr compact_bid_size(std::uint16_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::uint16_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint16_t value;
};
}
