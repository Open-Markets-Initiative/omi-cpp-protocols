#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

// cross_type
struct cross_type {

    enum class enum_type : char {
        opening = 'O',
        closing = 'C',
        ipo_and_halted = 'H',
        cross_network = 'I'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Closing", enum_type::closing},
        {"Cross Network", enum_type::cross_network},
        {"Ipo And Halted", enum_type::ipo_and_halted},
        {"Opening", enum_type::opening}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::opening: return "Opening";
            case enum_type::closing: return "Closing";
            case enum_type::ipo_and_halted: return "Ipo And Halted";
            case enum_type::cross_network: return "Cross Network";
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
            set(enum_type::cross_network);
    }

  protected:
    enum_type value;
};
}
