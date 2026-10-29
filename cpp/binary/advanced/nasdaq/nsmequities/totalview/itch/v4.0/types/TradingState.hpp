#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

// trading_state
struct trading_state {

    enum class enum_type : char {
        halted_or_paused = 'H',
        halted_or_paused_on_nasdaq = 'V',
        quotation_only_period = 'Q',
        quotation_only_period_on_nasdaq = 'R',
        trading = 'T'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Halted Or Paused", enum_type::halted_or_paused},
        {"Halted Or Paused On Nasdaq", enum_type::halted_or_paused_on_nasdaq},
        {"Quotation Only Period", enum_type::quotation_only_period},
        {"Quotation Only Period On Nasdaq", enum_type::quotation_only_period_on_nasdaq},
        {"Trading", enum_type::trading}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::halted_or_paused: return "Halted Or Paused";
            case enum_type::halted_or_paused_on_nasdaq: return "Halted Or Paused On Nasdaq";
            case enum_type::quotation_only_period: return "Quotation Only Period";
            case enum_type::quotation_only_period_on_nasdaq: return "Quotation Only Period On Nasdaq";
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
     : value{ enum_type{} } {}

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
