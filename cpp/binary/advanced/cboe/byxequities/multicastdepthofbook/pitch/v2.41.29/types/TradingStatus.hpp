#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {

// trading_status
struct trading_status {

    enum class enum_type : char {
        accepting_orders_for_queuing = 'A',
        halted = 'H',
        quote_only = 'Q',
        exchange_specific_suspension = 'S',
        trading = 'T'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Accepting Orders For Queuing", enum_type::accepting_orders_for_queuing},
        {"Exchange Specific Suspension", enum_type::exchange_specific_suspension},
        {"Halted", enum_type::halted},
        {"Quote Only", enum_type::quote_only},
        {"Trading", enum_type::trading}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::accepting_orders_for_queuing: return "Accepting Orders For Queuing";
            case enum_type::halted: return "Halted";
            case enum_type::quote_only: return "Quote Only";
            case enum_type::exchange_specific_suspension: return "Exchange Specific Suspension";
            case enum_type::trading: return "Trading";
            default: return "unknown";
        }
    }

    static constexpr std::optional<enum_type> from_string(std::string_view str) {
        auto it = std::lower_bound(
            from_string_map.begin(),
            from_string_map.end(),
            str,
            [](const auto& pair, std::string_view s) { return pair.first < s; }
        );
        if (it != from_string_map.end() && it->first == str) {
            return it->second;
        }
        return std::nullopt;
    }

    static constexpr const char* name = "trading_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<trading_status::enum_type>;
    using storage_type = result_type;

    constexpr trading_status()
     : value{ enum_type{} } {}

    constexpr trading_status(enum_type v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(enum_type v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(enum_type::trading);
    }

  protected:
    enum_type value;
};
}
