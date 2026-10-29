#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// market_segment_id
struct market_segment_id {

    static constexpr const char* name = "market_segment_id";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;

    using result_type = required<std::int32_t>;
    using storage_type = result_type;

    constexpr market_segment_id()
     : value{ 0 } {}

    constexpr market_segment_id(std::int32_t v)
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
