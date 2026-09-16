#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// trading_state
struct trading_state {

    enum class enum_type : char {
        halted = 'H',
        paused = 'P',
        quotation_only_period = 'Q',
        trading = 'T'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Halted", enum_type::halted},
        {"Paused", enum_type::paused},
        {"Quotation Only Period", enum_type::quotation_only_period},
        {"Trading", enum_type::trading}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::halted: return "Halted";
            case enum_type::paused: return "Paused";
            case enum_type::quotation_only_period: return "Quotation Only Period";
            case enum_type::trading: return "Trading";
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

    static constexpr const char* name = "trading_state";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<trading_state::enum_type>;
    using storage_type = result_type;

    constexpr trading_state()
     : value{ enum_type::halted } {}

    constexpr trading_state(enum_type v)
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
            set(enum_type::trading);
    }

  protected:
    enum_type value;
};
}
