// Databento.MarketData.Normalized.Dbn.v2: types/StartDate.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

// start_date
struct start_date {

    static constexpr const char* name = "start_date";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint32_t>;
    using storage_type = result_type;

    constexpr start_date()
     : value{ 0 } {}

    constexpr start_date(std::uint32_t v)
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
