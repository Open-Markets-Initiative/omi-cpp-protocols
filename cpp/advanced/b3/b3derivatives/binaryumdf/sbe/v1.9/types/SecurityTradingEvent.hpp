#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// security_trading_event
struct security_trading_event {

    enum class enum_type : std::uint8_t {
        trading_session_change = 4,
        security_status_change = 101,
        security_rejoins_security_group_status = 102,
        no_value = 255
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"No Value", enum_type::no_value},
        {"Security Rejoins Security Group Status", enum_type::security_rejoins_security_group_status},
        {"Security Status Change", enum_type::security_status_change},
        {"Trading Session Change", enum_type::trading_session_change}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::trading_session_change: return "Trading Session Change";
            case enum_type::security_status_change: return "Security Status Change";
            case enum_type::security_rejoins_security_group_status: return "Security Rejoins Security Group Status";
            case enum_type::no_value: return "No Value";
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

    static constexpr const char* name = "security_trading_event";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<security_trading_event::enum_type>;
    using storage_type = result_type;

    constexpr security_trading_event()
     : value{ enum_type::trading_session_change } {}

    constexpr security_trading_event(enum_type v)
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
            set(static_cast<enum_type>(255));
    }

  protected:
    enum_type value;
};
}
