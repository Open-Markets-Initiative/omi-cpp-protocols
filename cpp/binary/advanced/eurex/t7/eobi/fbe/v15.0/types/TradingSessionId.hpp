#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

// trading_session_id
struct trading_session_id {

    enum class enum_type : std::uint8_t {
        day = 1,
        morning = 3,
        evening = 5,
        after_hours = 6,
        holiday = 7,
        no_value = 0xFF
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 6> from_string_map = {{
        {"After Hours", enum_type::after_hours},
        {"Day", enum_type::day},
        {"Evening", enum_type::evening},
        {"Holiday", enum_type::holiday},
        {"Morning", enum_type::morning},
        {"No Value", enum_type::no_value}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::day: return "Day";
            case enum_type::morning: return "Morning";
            case enum_type::evening: return "Evening";
            case enum_type::after_hours: return "After Hours";
            case enum_type::holiday: return "Holiday";
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

    static constexpr const char* name = "trading_session_id";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<trading_session_id::enum_type>;
    using storage_type = result_type;

    constexpr trading_session_id()
     : value{ enum_type{} } {}

    constexpr trading_session_id(enum_type v)
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
            set(static_cast<enum_type>(0xFF));
    }

  protected:
    enum_type value;
};
}
