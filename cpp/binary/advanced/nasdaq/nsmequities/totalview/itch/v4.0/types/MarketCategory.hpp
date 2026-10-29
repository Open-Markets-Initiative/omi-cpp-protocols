#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

// market_category
struct market_category {

    enum class enum_type : char {
        cqs = 'T',
        nasdaq_global_select_market = 'Q',
        nasdaq_global_market = 'G',
        nasdaq_capital_market = 'S'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Cqs", enum_type::cqs},
        {"Nasdaq Capital Market", enum_type::nasdaq_capital_market},
        {"Nasdaq Global Market", enum_type::nasdaq_global_market},
        {"Nasdaq Global Select Market", enum_type::nasdaq_global_select_market}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::cqs: return "Cqs";
            case enum_type::nasdaq_global_select_market: return "Nasdaq Global Select Market";
            case enum_type::nasdaq_global_market: return "Nasdaq Global Market";
            case enum_type::nasdaq_capital_market: return "Nasdaq Capital Market";
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

    static constexpr const char* name = "market_category";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<market_category::enum_type>;
    using storage_type = result_type;

    constexpr market_category()
     : value{ enum_type{} } {}

    constexpr market_category(enum_type v)
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
            set(enum_type::nasdaq_capital_market);
    }

  protected:
    enum_type value;
};
}
