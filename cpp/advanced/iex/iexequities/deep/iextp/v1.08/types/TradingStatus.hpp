#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace iex::iexequities::deep::iextp::v1_08 {

// trading_status
struct trading_status {

    enum class enum_type : char {
        trading_halted_across_all_us_equity_markets = 'H',
        trading_halt_released_into_an_order_acceptance_period_on_iex = 'O',
        trading_paused_and_order_acceptance_period_on_iex = 'P',
        trading_on_iex = 'T'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Trading Halt Released Into An Order Acceptance Period On Iex", enum_type::trading_halt_released_into_an_order_acceptance_period_on_iex},
        {"Trading Halted Across All Us Equity Markets", enum_type::trading_halted_across_all_us_equity_markets},
        {"Trading On Iex", enum_type::trading_on_iex},
        {"Trading Paused And Order Acceptance Period On Iex", enum_type::trading_paused_and_order_acceptance_period_on_iex}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::trading_halted_across_all_us_equity_markets: return "Trading Halted Across All Us Equity Markets";
            case enum_type::trading_halt_released_into_an_order_acceptance_period_on_iex: return "Trading Halt Released Into An Order Acceptance Period On Iex";
            case enum_type::trading_paused_and_order_acceptance_period_on_iex: return "Trading Paused And Order Acceptance Period On Iex";
            case enum_type::trading_on_iex: return "Trading On Iex";
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
     : value{ enum_type::trading_halted_across_all_us_equity_markets } {}

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
            set(enum_type::trading_on_iex);
    }

  protected:
    enum_type value;
};
}
