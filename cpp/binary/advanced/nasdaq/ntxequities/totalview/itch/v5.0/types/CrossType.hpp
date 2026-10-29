#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

// cross_type
struct cross_type {

    enum class enum_type : char {
        nasdaq_texas_opening_cross = 'O',
        nasdaq_texas_closing_cross = 'C',
        cross_for_ipo_and_halted_paused = 'H',
        nasdaq_texas_cross_network = 'I'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Cross For Ipo And Halted Paused", enum_type::cross_for_ipo_and_halted_paused},
        {"Nasdaq Texas Closing Cross", enum_type::nasdaq_texas_closing_cross},
        {"Nasdaq Texas Cross Network", enum_type::nasdaq_texas_cross_network},
        {"Nasdaq Texas Opening Cross", enum_type::nasdaq_texas_opening_cross}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::nasdaq_texas_opening_cross: return "Nasdaq Texas Opening Cross";
            case enum_type::nasdaq_texas_closing_cross: return "Nasdaq Texas Closing Cross";
            case enum_type::cross_for_ipo_and_halted_paused: return "Cross For Ipo And Halted Paused";
            case enum_type::nasdaq_texas_cross_network: return "Nasdaq Texas Cross Network";
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

    static constexpr const char* name = "cross_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<cross_type::enum_type>;
    using storage_type = result_type;

    constexpr cross_type()
     : value{ enum_type{} } {}

    constexpr cross_type(enum_type v)
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
            set(enum_type::nasdaq_texas_cross_network);
    }

  protected:
    enum_type value;
};
}
