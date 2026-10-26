#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_11_b {

// market_status_message_type
struct market_status_message_type {

    enum class enum_type : char {
        market_wide_circuit_breaker_decline_level_status = 'K',
        market_wide_circuit_breaker_status = 'L',
        approximate_adjusted_volume_market_center = 'N',
        fractional_approximate_adjusted_volume_market_center = 'V',
        approximate_trades_and_total_dollar_value = 'O',
        crossing_session_summary = 'P'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 6> from_string_map = {{
        {"Approximate Adjusted Volume Market Center", enum_type::approximate_adjusted_volume_market_center},
        {"Approximate Trades And Total Dollar Value", enum_type::approximate_trades_and_total_dollar_value},
        {"Crossing Session Summary", enum_type::crossing_session_summary},
        {"Fractional Approximate Adjusted Volume Market Center", enum_type::fractional_approximate_adjusted_volume_market_center},
        {"Market Wide Circuit Breaker Decline Level Status", enum_type::market_wide_circuit_breaker_decline_level_status},
        {"Market Wide Circuit Breaker Status", enum_type::market_wide_circuit_breaker_status}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::market_wide_circuit_breaker_decline_level_status: return "Market Wide Circuit Breaker Decline Level Status";
            case enum_type::market_wide_circuit_breaker_status: return "Market Wide Circuit Breaker Status";
            case enum_type::approximate_adjusted_volume_market_center: return "Approximate Adjusted Volume Market Center";
            case enum_type::fractional_approximate_adjusted_volume_market_center: return "Fractional Approximate Adjusted Volume Market Center";
            case enum_type::approximate_trades_and_total_dollar_value: return "Approximate Trades And Total Dollar Value";
            case enum_type::crossing_session_summary: return "Crossing Session Summary";
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

    static constexpr const char* name = "market_status_message_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<market_status_message_type::enum_type>;
    using storage_type = result_type;

    constexpr market_status_message_type()
     : value{ enum_type{} } {}

    constexpr market_status_message_type(enum_type v)
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
            set(enum_type::crossing_session_summary);
    }

  protected:
    enum_type value;
};
}
