#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

// cash_margin_type
struct cash_margin_type {

    enum class enum_type : char {
        cash = '1',
        margin_open_negotiable = '2',
        margin_close_negotiable = '3',
        margin_open_standardized = '4',
        margin_close_standardized = '5'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Cash", enum_type::cash},
        {"Margin Close Negotiable", enum_type::margin_close_negotiable},
        {"Margin Close Standardized", enum_type::margin_close_standardized},
        {"Margin Open Negotiable", enum_type::margin_open_negotiable},
        {"Margin Open Standardized", enum_type::margin_open_standardized}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::cash: return "Cash";
            case enum_type::margin_open_negotiable: return "Margin Open Negotiable";
            case enum_type::margin_close_negotiable: return "Margin Close Negotiable";
            case enum_type::margin_open_standardized: return "Margin Open Standardized";
            case enum_type::margin_close_standardized: return "Margin Close Standardized";
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

    static constexpr const char* name = "cash_margin_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<cash_margin_type::enum_type>;
    using storage_type = result_type;

    constexpr cash_margin_type()
     : value{ enum_type{} } {}

    constexpr cash_margin_type(enum_type v)
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
            set(enum_type::margin_close_standardized);
    }

  protected:
    enum_type value;
};
}
