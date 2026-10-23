#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_11_b {

// category_1
struct category_1 {

    enum class enum_type : char {
        regular_settlement = ' ',
        cash_trade_same_day_clearing = 'C',
        reserved = 'N',
        seller = 'R'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Cash Trade Same Day Clearing", enum_type::cash_trade_same_day_clearing},
        {"Regular Settlement", enum_type::regular_settlement},
        {"Reserved", enum_type::reserved},
        {"Seller", enum_type::seller}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::regular_settlement: return "Regular Settlement";
            case enum_type::cash_trade_same_day_clearing: return "Cash Trade Same Day Clearing";
            case enum_type::reserved: return "Reserved";
            case enum_type::seller: return "Seller";
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

    static constexpr const char* name = "category_1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<category_1::enum_type>;
    using storage_type = result_type;

    constexpr category_1()
     : value{ enum_type{} } {}

    constexpr category_1(enum_type v)
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
            set(enum_type::seller);
    }

  protected:
    enum_type value;
};
}
