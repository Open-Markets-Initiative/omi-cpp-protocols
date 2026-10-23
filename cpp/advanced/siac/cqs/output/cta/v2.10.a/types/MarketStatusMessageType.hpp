#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cqs::output::cta::v2_10_a {

// market_status_message_type
struct market_status_message_type {

    enum class enum_type : char {
        market_wide_circuit_breaker_decline_level_status = 'K',
        market_wide_circuit_breaker_status = 'L'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Market Wide Circuit Breaker Decline Level Status", enum_type::market_wide_circuit_breaker_decline_level_status},
        {"Market Wide Circuit Breaker Status", enum_type::market_wide_circuit_breaker_status}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::market_wide_circuit_breaker_decline_level_status: return "Market Wide Circuit Breaker Decline Level Status";
            case enum_type::market_wide_circuit_breaker_status: return "Market Wide Circuit Breaker Status";
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
            set(enum_type::market_wide_circuit_breaker_status);
    }

  protected:
    enum_type value;
};
}
