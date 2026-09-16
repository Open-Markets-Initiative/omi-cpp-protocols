#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// round_lots_only
struct round_lots_only {

    enum class enum_type : char {
        yes = 'Y',
        no = 'N'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"No", enum_type::no},
        {"Yes", enum_type::yes}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::yes: return "Yes";
            case enum_type::no: return "No";
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

    static constexpr const char* name = "round_lots_only";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<round_lots_only::enum_type>;
    using storage_type = result_type;

    constexpr round_lots_only()
     : value{ enum_type::yes } {}

    constexpr round_lots_only(enum_type v)
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
            set(enum_type::no);
    }

  protected:
    enum_type value;
};
}
