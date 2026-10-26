#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

// significant_imbalance
struct significant_imbalance {

    enum class enum_type : char {
        default_value = ' ',
        the_current_imbalance_is_significant = 'Y'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Default", enum_type::default_value},
        {"The Current Imbalance Is Significant", enum_type::the_current_imbalance_is_significant}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::default_value: return "Default";
            case enum_type::the_current_imbalance_is_significant: return "The Current Imbalance Is Significant";
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

    static constexpr const char* name = "significant_imbalance";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<significant_imbalance::enum_type>;
    using storage_type = result_type;

    constexpr significant_imbalance()
     : value{ enum_type{} } {}

    constexpr significant_imbalance(enum_type v)
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
            set(enum_type::the_current_imbalance_is_significant);
    }

  protected:
    enum_type value;
};
}
