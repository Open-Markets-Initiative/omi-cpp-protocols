#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

// cross_type
struct cross_type {

    enum class enum_type : char {
        opening_cross = 'O',
        closing_cross = 'C',
        cross_halted_or_paused = 'H',
        intraday_cross_and_post_close_cross = 'I'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Closing Cross", enum_type::closing_cross},
        {"Cross Halted Or Paused", enum_type::cross_halted_or_paused},
        {"Intraday Cross And Post Close Cross", enum_type::intraday_cross_and_post_close_cross},
        {"Opening Cross", enum_type::opening_cross}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::opening_cross: return "Opening Cross";
            case enum_type::closing_cross: return "Closing Cross";
            case enum_type::cross_halted_or_paused: return "Cross Halted Or Paused";
            case enum_type::intraday_cross_and_post_close_cross: return "Intraday Cross And Post Close Cross";
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
            set(enum_type::intraday_cross_and_post_close_cross);
    }

  protected:
    enum_type value;
};
}
