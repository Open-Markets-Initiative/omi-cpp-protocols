#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// opening_condition
struct opening_condition {

    enum class enum_type : char {
        would_open = 'O',
        need_quote_to_open = 'Q',
        need_more_buyers = 'B',
        need_more_sellers = 'S',
        crossed_composite_market = 'C'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Crossed Composite Market", enum_type::crossed_composite_market},
        {"Need More Buyers", enum_type::need_more_buyers},
        {"Need More Sellers", enum_type::need_more_sellers},
        {"Need Quote To Open", enum_type::need_quote_to_open},
        {"Would Open", enum_type::would_open}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::would_open: return "Would Open";
            case enum_type::need_quote_to_open: return "Need Quote To Open";
            case enum_type::need_more_buyers: return "Need More Buyers";
            case enum_type::need_more_sellers: return "Need More Sellers";
            case enum_type::crossed_composite_market: return "Crossed Composite Market";
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

    static constexpr const char* name = "opening_condition";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<opening_condition::enum_type>;
    using storage_type = result_type;

    constexpr opening_condition()
     : value{ enum_type{} } {}

    constexpr opening_condition(enum_type v)
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
            set(enum_type::crossed_composite_market);
    }

  protected:
    enum_type value;
};
}
