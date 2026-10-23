#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// open_state
struct open_state {

    enum class enum_type : char {
        open_for_auto_execution = 'Y',
        closed_for_auto_execution = 'N'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Closed For Auto Execution", enum_type::closed_for_auto_execution},
        {"Open For Auto Execution", enum_type::open_for_auto_execution}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::open_for_auto_execution: return "Open For Auto Execution";
            case enum_type::closed_for_auto_execution: return "Closed For Auto Execution";
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

    static constexpr const char* name = "open_state";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<open_state::enum_type>;
    using storage_type = result_type;

    constexpr open_state()
     : value{ enum_type{} } {}

    constexpr open_state(enum_type v)
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
            set(enum_type::closed_for_auto_execution);
    }

  protected:
    enum_type value;
};
}
