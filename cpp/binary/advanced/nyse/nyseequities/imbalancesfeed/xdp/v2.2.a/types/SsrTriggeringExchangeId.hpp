#pragma once

#include <cstddef>
#include "../cache/Required.hpp"

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {

// ssr_triggering_exchange_id
struct ssr_triggering_exchange_id {

    static constexpr const char* name = "ssr_triggering_exchange_id";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<char>;
    using storage_type = result_type;

    constexpr ssr_triggering_exchange_id()
     : value{ 0 } {}

    constexpr ssr_triggering_exchange_id(char v)
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
