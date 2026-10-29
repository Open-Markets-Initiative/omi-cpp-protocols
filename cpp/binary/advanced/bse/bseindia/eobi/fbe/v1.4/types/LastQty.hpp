#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// last_qty
struct last_qty {

    static constexpr const char* name = "last_qty";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = false;

    using result_type = required<std::int64_t>;
    using storage_type = result_type;

    constexpr last_qty()
     : value{ 0 } {}

    constexpr last_qty(std::int64_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::int64_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::int64_t value;
};
}
