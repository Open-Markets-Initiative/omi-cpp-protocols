// Databento.MarketData.Normalized.Dbn.v1: types/MinLotSize.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

// min_lot_size
struct min_lot_size {

    static constexpr const char* name = "min_lot_size";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;

    using result_type = required<std::int32_t>;
    using storage_type = result_type;

    constexpr min_lot_size()
     : value{ 0 } {}

    constexpr min_lot_size(std::int32_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::int32_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::int32_t value;
};
}
