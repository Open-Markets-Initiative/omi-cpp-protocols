#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace iex::iexequities::tops::iextp::v1_66 {

// imbalance_side
struct imbalance_side {

    enum class enum_type : char {
        buy = 'B',
        sell = 'S',
        none = 'N'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Buy", enum_type::buy},
        {"None", enum_type::none},
        {"Sell", enum_type::sell}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::buy: return "Buy";
            case enum_type::sell: return "Sell";
            case enum_type::none: return "None";
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

    static constexpr const char* name = "imbalance_side";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<imbalance_side::enum_type>;
    using storage_type = result_type;

    constexpr imbalance_side()
     : value{ enum_type::buy } {}

    constexpr imbalance_side(enum_type v)
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
            set(enum_type::none);
    }

  protected:
    enum_type value;
};
}
