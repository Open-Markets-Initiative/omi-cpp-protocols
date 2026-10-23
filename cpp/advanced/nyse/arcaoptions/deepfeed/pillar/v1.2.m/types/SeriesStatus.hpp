#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// series_status
struct series_status {

    enum class enum_type : char {
        trading_halt = '4',
        resume = '5',
        suspend = '6',
        preopening = 'P',
        begin_accepting_orders = 'B',
        core_session = 'O',
        closed = 'X'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 7> from_string_map = {{
        {"Begin Accepting Orders", enum_type::begin_accepting_orders},
        {"Closed", enum_type::closed},
        {"Core Session", enum_type::core_session},
        {"Preopening", enum_type::preopening},
        {"Resume", enum_type::resume},
        {"Suspend", enum_type::suspend},
        {"Trading Halt", enum_type::trading_halt}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::trading_halt: return "Trading Halt";
            case enum_type::resume: return "Resume";
            case enum_type::suspend: return "Suspend";
            case enum_type::preopening: return "Preopening";
            case enum_type::begin_accepting_orders: return "Begin Accepting Orders";
            case enum_type::core_session: return "Core Session";
            case enum_type::closed: return "Closed";
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

    static constexpr const char* name = "series_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<series_status::enum_type>;
    using storage_type = result_type;

    constexpr series_status()
     : value{ enum_type{} } {}

    constexpr series_status(enum_type v)
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
            set(enum_type::closed);
    }

  protected:
    enum_type value;
};
}
