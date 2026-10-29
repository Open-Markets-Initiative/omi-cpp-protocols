#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

// short_selling_state
struct short_selling_state {

    enum class enum_type : char {
        no_price_restriction = '0',
        price_restriction_in_effect = '1'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"No Price Restriction", enum_type::no_price_restriction},
        {"Price Restriction In Effect", enum_type::price_restriction_in_effect}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::no_price_restriction: return "No Price Restriction";
            case enum_type::price_restriction_in_effect: return "Price Restriction In Effect";
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

    static constexpr const char* name = "short_selling_state";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<short_selling_state::enum_type>;
    using storage_type = result_type;

    constexpr short_selling_state()
     : value{ enum_type{} } {}

    constexpr short_selling_state(enum_type v)
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
            set(enum_type::price_restriction_in_effect);
    }

  protected:
    enum_type value;
};
}
