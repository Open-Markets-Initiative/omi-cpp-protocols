#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// operational_halt_action
struct operational_halt_action {

    enum class enum_type : char {
        halted = 'H',
        trading_resumed = 'T'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Halted", enum_type::halted},
        {"Trading Resumed", enum_type::trading_resumed}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::halted: return "Halted";
            case enum_type::trading_resumed: return "Trading Resumed";
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

    static constexpr const char* name = "operational_halt_action";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<operational_halt_action::enum_type>;
    using storage_type = result_type;

    constexpr operational_halt_action()
     : value{ enum_type::halted } {}

    constexpr operational_halt_action(enum_type v)
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
            set(enum_type::trading_resumed);
    }

  protected:
    enum_type value;
};
}
