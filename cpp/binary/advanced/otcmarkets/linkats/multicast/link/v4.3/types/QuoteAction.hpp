// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/QuoteAction.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// quote_action
struct quote_action {

    static constexpr const char* name = "quote_action";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint8_t>;
    using storage_type = result_type;

    constexpr quote_action()
     : value{ 0 } {}

    constexpr quote_action(std::uint8_t v)
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
