// Databento.MarketData.Normalized.Dbn.v2: types/FreezeStatus.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

// freeze_status
struct freeze_status {

    static constexpr const char* name = "freeze_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint8_t>;
    using storage_type = result_type;

    constexpr freeze_status()
     : value{ 0 } {}

    constexpr freeze_status(std::uint8_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::uint8_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint8_t value;
};
}
