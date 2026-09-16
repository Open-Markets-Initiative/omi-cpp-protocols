#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// imbalance_direction
struct imbalance_direction {

    enum class enum_type : char {
        buy = 'B',
        sell = 'S',
        none = 'N',
        insufficient_orders = 'O',
        paused = 'P'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Buy", enum_type::buy},
        {"Insufficient Orders", enum_type::insufficient_orders},
        {"None", enum_type::none},
        {"Paused", enum_type::paused},
        {"Sell", enum_type::sell}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::buy: return "Buy";
            case enum_type::sell: return "Sell";
            case enum_type::none: return "None";
            case enum_type::insufficient_orders: return "Insufficient Orders";
            case enum_type::paused: return "Paused";
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

    static constexpr const char* name = "imbalance_direction";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<imbalance_direction::enum_type>;
    using storage_type = result_type;

    constexpr imbalance_direction()
     : value{ enum_type::buy } {}

    constexpr imbalance_direction(enum_type v)
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
            set(enum_type::paused);
    }

  protected:
    enum_type value;
};
}
