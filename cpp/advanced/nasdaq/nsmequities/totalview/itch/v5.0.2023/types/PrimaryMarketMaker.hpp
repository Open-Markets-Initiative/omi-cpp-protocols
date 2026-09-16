#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// primary_market_maker
struct primary_market_maker {

    enum class enum_type : char {
        primary = 'Y',
        non_primary = 'N'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Non Primary", enum_type::non_primary},
        {"Primary", enum_type::primary}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::primary: return "Primary";
            case enum_type::non_primary: return "Non Primary";
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

    static constexpr const char* name = "primary_market_maker";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<primary_market_maker::enum_type>;
    using storage_type = result_type;

    constexpr primary_market_maker()
     : value{ enum_type::primary } {}

    constexpr primary_market_maker(enum_type v)
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
            set(enum_type::non_primary);
    }

  protected:
    enum_type value;
};
}
