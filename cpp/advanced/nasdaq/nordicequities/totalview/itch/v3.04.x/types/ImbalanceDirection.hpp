#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// imbalance_direction
struct imbalance_direction {

    enum class enum_type : char {
        buy_imbalance = 'B',
        sell_imbalance = 'S',
        no_imbalance = 'N',
        insufficient_orders_to_calculate = 'O'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Buy Imbalance", enum_type::buy_imbalance},
        {"Insufficient Orders To Calculate", enum_type::insufficient_orders_to_calculate},
        {"No Imbalance", enum_type::no_imbalance},
        {"Sell Imbalance", enum_type::sell_imbalance}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::buy_imbalance: return "Buy Imbalance";
            case enum_type::sell_imbalance: return "Sell Imbalance";
            case enum_type::no_imbalance: return "No Imbalance";
            case enum_type::insufficient_orders_to_calculate: return "Insufficient Orders To Calculate";
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
     : value{ enum_type{} } {}

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
            set(enum_type::insufficient_orders_to_calculate);
    }

  protected:
    enum_type value;
};
}
