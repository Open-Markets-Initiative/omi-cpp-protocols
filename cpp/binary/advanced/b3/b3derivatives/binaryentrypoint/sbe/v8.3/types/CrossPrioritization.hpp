#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// cross_prioritization
struct cross_prioritization {

    enum class enum_type : std::uint8_t {
        none = 0,
        buy_side_is_prioritized = 1,
        sell_side_is_prioritized = 2,
        no_value = 255
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Buy Side Is Prioritized", enum_type::buy_side_is_prioritized},
        {"No Value", enum_type::no_value},
        {"None", enum_type::none},
        {"Sell Side Is Prioritized", enum_type::sell_side_is_prioritized}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::none: return "None";
            case enum_type::buy_side_is_prioritized: return "Buy Side Is Prioritized";
            case enum_type::sell_side_is_prioritized: return "Sell Side Is Prioritized";
            case enum_type::no_value: return "No Value";
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

    static constexpr const char* name = "cross_prioritization";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<cross_prioritization::enum_type>;
    using storage_type = result_type;

    constexpr cross_prioritization()
     : value{ enum_type{} } {}

    constexpr cross_prioritization(enum_type v)
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
            set(static_cast<enum_type>(255));
    }

  protected:
    enum_type value;
};
}
