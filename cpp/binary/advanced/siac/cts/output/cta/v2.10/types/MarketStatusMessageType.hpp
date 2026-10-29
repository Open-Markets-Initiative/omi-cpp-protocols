#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_10 {

// market_status_message_type
struct market_status_message_type {

    enum class enum_type : char {
        market_wide_circuit_breaker_decline_level_status_message = 'K',
        market_wide_circuit_breaker_status_message = 'L',
        approximate_adjusted_volume_market_center_message = 'N',
        fractional_approximate_adjusted_volume_market_center_message = 'V',
        approximate_trades_and_total_dollar_value_message = 'O',
        crossing_session_summary_message = 'P'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 6> from_string_map = {{
        {"Approximate Adjusted Volume Market Center Message", enum_type::approximate_adjusted_volume_market_center_message},
        {"Approximate Trades And Total Dollar Value Message", enum_type::approximate_trades_and_total_dollar_value_message},
        {"Crossing Session Summary Message", enum_type::crossing_session_summary_message},
        {"Fractional Approximate Adjusted Volume Market Center Message", enum_type::fractional_approximate_adjusted_volume_market_center_message},
        {"Market Wide Circuit Breaker Decline Level Status Message", enum_type::market_wide_circuit_breaker_decline_level_status_message},
        {"Market Wide Circuit Breaker Status Message", enum_type::market_wide_circuit_breaker_status_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::market_wide_circuit_breaker_decline_level_status_message: return "Market Wide Circuit Breaker Decline Level Status Message";
            case enum_type::market_wide_circuit_breaker_status_message: return "Market Wide Circuit Breaker Status Message";
            case enum_type::approximate_adjusted_volume_market_center_message: return "Approximate Adjusted Volume Market Center Message";
            case enum_type::fractional_approximate_adjusted_volume_market_center_message: return "Fractional Approximate Adjusted Volume Market Center Message";
            case enum_type::approximate_trades_and_total_dollar_value_message: return "Approximate Trades And Total Dollar Value Message";
            case enum_type::crossing_session_summary_message: return "Crossing Session Summary Message";
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
            set(enum_type::crossing_session_summary_message);
    }

  protected:
    enum_type value;
};
}
