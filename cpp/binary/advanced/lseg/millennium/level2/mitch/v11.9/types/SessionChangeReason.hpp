#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// session_change_reason
struct session_change_reason {

    enum class enum_type : std::uint8_t {
        scheduled_transition = 0,
        extended_by_market_ops = 1,
        shortened_by_market_ops = 2,
        market_order_imbalance = 3,
        price_outside_range = 4,
        unavailable_recovery_service_only = 9
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 6> from_string_map = {{
        {"Extended By Market Ops", enum_type::extended_by_market_ops},
        {"Market Order Imbalance", enum_type::market_order_imbalance},
        {"Price Outside Range", enum_type::price_outside_range},
        {"Scheduled Transition", enum_type::scheduled_transition},
        {"Shortened By Market Ops", enum_type::shortened_by_market_ops},
        {"Unavailable Recovery Service Only", enum_type::unavailable_recovery_service_only}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::scheduled_transition: return "Scheduled Transition";
            case enum_type::extended_by_market_ops: return "Extended By Market Ops";
            case enum_type::shortened_by_market_ops: return "Shortened By Market Ops";
            case enum_type::market_order_imbalance: return "Market Order Imbalance";
            case enum_type::price_outside_range: return "Price Outside Range";
            case enum_type::unavailable_recovery_service_only: return "Unavailable Recovery Service Only";
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

    static constexpr const char* name = "session_change_reason";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<session_change_reason::enum_type>;
    using storage_type = result_type;

    constexpr session_change_reason()
     : value{ enum_type{} } {}

    constexpr session_change_reason(enum_type v)
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
            set(enum_type::unavailable_recovery_service_only);
    }

  protected:
    enum_type value;
};
}
