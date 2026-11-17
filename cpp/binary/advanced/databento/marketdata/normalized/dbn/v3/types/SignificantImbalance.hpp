// Databento.MarketData.Normalized.Dbn.v3: types/SignificantImbalance.hpp
#pragma once

#include <cstddef>
#include "../cache/Required.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

// significant_imbalance
struct significant_imbalance {

    static constexpr const char* name = "significant_imbalance";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<char>;
    using storage_type = result_type;

    constexpr significant_imbalance()
     : value{ 0 } {}

    constexpr significant_imbalance(char v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(char v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    char value;
};
}
