// Databento.MarketData.Normalized.Dbn.v2: types/SystemCode.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

// system_code
struct system_code {

    enum class enum_type : std::uint8_t {
        heartbeat = 0,
        subscription_ack = 1,
        slow_reader_warning = 2,
        replay_completed = 3,
        end_of_interval = 4,
        unsubscribe_ack = 5,
        unset = 255
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 7> from_string_map = {{
        {"End Of Interval", enum_type::end_of_interval},
        {"Heartbeat", enum_type::heartbeat},
        {"Replay Completed", enum_type::replay_completed},
        {"Slow Reader Warning", enum_type::slow_reader_warning},
        {"Subscription Ack", enum_type::subscription_ack},
        {"Unset", enum_type::unset},
        {"Unsubscribe Ack", enum_type::unsubscribe_ack}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::heartbeat: return "Heartbeat";
            case enum_type::subscription_ack: return "Subscription Ack";
            case enum_type::slow_reader_warning: return "Slow Reader Warning";
            case enum_type::replay_completed: return "Replay Completed";
            case enum_type::end_of_interval: return "End Of Interval";
            case enum_type::unsubscribe_ack: return "Unsubscribe Ack";
            case enum_type::unset: return "Unset";
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

    static constexpr const char* name = "system_code";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<system_code::enum_type>;
    using storage_type = result_type;

    constexpr system_code()
     : value{ enum_type{} } {}

    constexpr system_code(enum_type v)
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
            set(enum_type::unset);
    }

  protected:
    enum_type value;
};
}
