// Databento.MarketData.Normalized.Dbn.v3: types/TradingEvent.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

// trading_event
struct trading_event {

    enum class enum_type : std::uint16_t {
        none = 0,
        no_cancel = 1,
        change_trading_session = 2,
        implied_matching_on = 3,
        implied_matching_off = 4
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Change Trading Session", enum_type::change_trading_session},
        {"Implied Matching Off", enum_type::implied_matching_off},
        {"Implied Matching On", enum_type::implied_matching_on},
        {"No Cancel", enum_type::no_cancel},
        {"None", enum_type::none}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::none: return "None";
            case enum_type::no_cancel: return "No Cancel";
            case enum_type::change_trading_session: return "Change Trading Session";
            case enum_type::implied_matching_on: return "Implied Matching On";
            case enum_type::implied_matching_off: return "Implied Matching Off";
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

    static constexpr const char* name = "trading_event";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;

    using result_type = required<trading_event::enum_type>;
    using storage_type = result_type;

    constexpr trading_event()
     : value{ enum_type{} } {}

    constexpr trading_event(enum_type v)
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
            set(enum_type::implied_matching_off);
    }

  protected:
    enum_type value;
};
}
