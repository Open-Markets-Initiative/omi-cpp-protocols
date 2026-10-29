#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// series_type
struct series_type {

    enum class enum_type : std::uint8_t {
        standard = 0,
        flex = 1,
        flex_percentage = 2
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Flex", enum_type::flex},
        {"Flex Percentage", enum_type::flex_percentage},
        {"Standard", enum_type::standard}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::standard: return "Standard";
            case enum_type::flex: return "Flex";
            case enum_type::flex_percentage: return "Flex Percentage";
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

    static constexpr const char* name = "series_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<series_type::enum_type>;
    using storage_type = result_type;

    constexpr series_type()
     : value{ enum_type{} } {}

    constexpr series_type(enum_type v)
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
            set(enum_type::flex_percentage);
    }

  protected:
    enum_type value;
};
}
