#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// market_status
struct market_status {

    enum class enum_type : std::uint8_t {
        morning_session_order_acceptance_time = 11,
        morning_session_trading_hours = 12,
        end_of_morning_session = 19,
        afternoon_session_order_acceptance_time = 21,
        afternoon_session_trading_hours = 22,
        afternoon_session_preclosing = 23,
        end_of_afternoon_session = 29
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 7> from_string_map = {{
        {"Afternoon Session Order Acceptance Time", enum_type::afternoon_session_order_acceptance_time},
        {"Afternoon Session Preclosing", enum_type::afternoon_session_preclosing},
        {"Afternoon Session Trading Hours", enum_type::afternoon_session_trading_hours},
        {"End Of Afternoon Session", enum_type::end_of_afternoon_session},
        {"End Of Morning Session", enum_type::end_of_morning_session},
        {"Morning Session Order Acceptance Time", enum_type::morning_session_order_acceptance_time},
        {"Morning Session Trading Hours", enum_type::morning_session_trading_hours}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::morning_session_order_acceptance_time: return "Morning Session Order Acceptance Time";
            case enum_type::morning_session_trading_hours: return "Morning Session Trading Hours";
            case enum_type::end_of_morning_session: return "End Of Morning Session";
            case enum_type::afternoon_session_order_acceptance_time: return "Afternoon Session Order Acceptance Time";
            case enum_type::afternoon_session_trading_hours: return "Afternoon Session Trading Hours";
            case enum_type::afternoon_session_preclosing: return "Afternoon Session Preclosing";
            case enum_type::end_of_afternoon_session: return "End Of Afternoon Session";
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

    static constexpr const char* name = "market_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<market_status::enum_type>;
    using storage_type = result_type;

    constexpr market_status()
     : value{ enum_type::morning_session_order_acceptance_time } {}

    constexpr market_status(enum_type v)
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
            set(enum_type::end_of_afternoon_session);
    }

  protected:
    enum_type value;
};
}
