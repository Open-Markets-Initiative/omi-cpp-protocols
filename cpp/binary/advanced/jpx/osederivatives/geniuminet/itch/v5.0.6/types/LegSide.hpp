#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// leg_side
struct leg_side {

    enum class enum_type : char {
        as_defined = 'B',
        opposite = 'C'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"As Defined", enum_type::as_defined},
        {"Opposite", enum_type::opposite}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::as_defined: return "As Defined";
            case enum_type::opposite: return "Opposite";
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

    static constexpr const char* name = "leg_side";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<leg_side::enum_type>;
    using storage_type = result_type;

    constexpr leg_side()
     : value{ enum_type{} } {}

    constexpr leg_side(enum_type v)
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
            set(enum_type::opposite);
    }

  protected:
    enum_type value;
};
}
