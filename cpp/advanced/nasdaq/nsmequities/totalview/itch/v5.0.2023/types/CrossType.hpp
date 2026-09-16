#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// cross_type
struct cross_type {

    enum class enum_type : char {
        opening = 'O',
        closing = 'C',
        halted_or_paused = 'H',
        extended_close = 'A'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Closing", enum_type::closing},
        {"Extended Close", enum_type::extended_close},
        {"Halted Or Paused", enum_type::halted_or_paused},
        {"Opening", enum_type::opening}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::opening: return "Opening";
            case enum_type::closing: return "Closing";
            case enum_type::halted_or_paused: return "Halted Or Paused";
            case enum_type::extended_close: return "Extended Close";
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
     : value{ enum_type::opening } {}

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
            set(enum_type::extended_close);
    }

  protected:
    enum_type value;
};
}
