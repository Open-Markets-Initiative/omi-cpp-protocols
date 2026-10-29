#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// lower_exec_limit
struct lower_exec_limit {

    static constexpr const char* name = "lower_exec_limit";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = false;
    static constexpr int exponent = -6;

    using result_type = required<std::int64_t>;
    using storage_type = result_type;

    constexpr lower_exec_limit()
     : value{ 0 } {}

    constexpr lower_exec_limit(std::int64_t v)
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
