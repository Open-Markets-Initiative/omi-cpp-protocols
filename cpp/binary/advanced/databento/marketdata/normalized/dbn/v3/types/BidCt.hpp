// Databento.MarketData.Normalized.Dbn.v3: types/BidCt.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

// bid_ct
struct bid_ct {

    static constexpr const char* name = "bid_ct";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint32_t>;
    using storage_type = result_type;

    constexpr bid_ct()
     : value{ 0 } {}

    constexpr bid_ct(std::uint32_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::uint32_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint32_t value;
};
}
