#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// trade_condition
struct trade_condition {

    enum class enum_type : char {
        normal_trade = ' ',
        opening_trade = 'O',
        spread_trade = 'S',
        block_trade = 'B',
        ecrp_trade = 'E',
        derived = 'D',
        inter_market_spread_trade = 'I'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 7> from_string_map = {{
        {"Block Trade", enum_type::block_trade},
        {"Derived", enum_type::derived},
        {"Ecrp Trade", enum_type::ecrp_trade},
        {"Inter Market Spread Trade", enum_type::inter_market_spread_trade},
        {"Normal Trade", enum_type::normal_trade},
        {"Opening Trade", enum_type::opening_trade},
        {"Spread Trade", enum_type::spread_trade}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::normal_trade: return "Normal Trade";
            case enum_type::opening_trade: return "Opening Trade";
            case enum_type::spread_trade: return "Spread Trade";
            case enum_type::block_trade: return "Block Trade";
            case enum_type::ecrp_trade: return "Ecrp Trade";
            case enum_type::derived: return "Derived";
            case enum_type::inter_market_spread_trade: return "Inter Market Spread Trade";
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

    static constexpr const char* name = "trade_condition";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<trade_condition::enum_type>;
    using storage_type = result_type;

    constexpr trade_condition()
     : value{ enum_type{} } {}

    constexpr trade_condition(enum_type v)
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
            set(enum_type::inter_market_spread_trade);
    }

  protected:
    enum_type value;
};
}
