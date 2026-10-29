#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_9 {

// market_wide_circuit_breaker_level_indicator
struct market_wide_circuit_breaker_level_indicator {

    enum class enum_type : char {
        not_applicable = ' ',
        level_1_breached = '1',
        level_2_breached = '2',
        level_3_breached = '3'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Level 1 Breached", enum_type::level_1_breached},
        {"Level 2 Breached", enum_type::level_2_breached},
        {"Level 3 Breached", enum_type::level_3_breached},
        {"Not Applicable", enum_type::not_applicable}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::not_applicable: return "Not Applicable";
            case enum_type::level_1_breached: return "Level 1 Breached";
            case enum_type::level_2_breached: return "Level 2 Breached";
            case enum_type::level_3_breached: return "Level 3 Breached";
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

    static constexpr const char* name = "market_wide_circuit_breaker_level_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<market_wide_circuit_breaker_level_indicator::enum_type>;
    using storage_type = result_type;

    constexpr market_wide_circuit_breaker_level_indicator()
     : value{ enum_type{} } {}

    constexpr market_wide_circuit_breaker_level_indicator(enum_type v)
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
            set(enum_type::level_3_breached);
    }

  protected:
    enum_type value;
};
}
