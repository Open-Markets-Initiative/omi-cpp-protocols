#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

// trade_condition
struct trade_condition {

    enum class enum_type : char {
        complex_to_complex_electronic_trade = 'f',
        complex_auction_trade = 'g',
        complex_cross = 'h',
        complex_electronic_trade_against_single = 'j',
        complex_with_stock_options_auction_trade = 'k',
        complex_with_stock_electronic_trade = 'n',
        complex_with_stock_cross = 'o',
        electronic_trade = 'I',
        opening_trade = 'O'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 9> from_string_map = {{
        {"Complex Auction Trade", enum_type::complex_auction_trade},
        {"Complex Cross", enum_type::complex_cross},
        {"Complex Electronic Trade Against Single", enum_type::complex_electronic_trade_against_single},
        {"Complex To Complex Electronic Trade", enum_type::complex_to_complex_electronic_trade},
        {"Complex With Stock Cross", enum_type::complex_with_stock_cross},
        {"Complex With Stock Electronic Trade", enum_type::complex_with_stock_electronic_trade},
        {"Complex With Stock Options Auction Trade", enum_type::complex_with_stock_options_auction_trade},
        {"Electronic Trade", enum_type::electronic_trade},
        {"Opening Trade", enum_type::opening_trade}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::complex_to_complex_electronic_trade: return "Complex To Complex Electronic Trade";
            case enum_type::complex_auction_trade: return "Complex Auction Trade";
            case enum_type::complex_cross: return "Complex Cross";
            case enum_type::complex_electronic_trade_against_single: return "Complex Electronic Trade Against Single";
            case enum_type::complex_with_stock_options_auction_trade: return "Complex With Stock Options Auction Trade";
            case enum_type::complex_with_stock_electronic_trade: return "Complex With Stock Electronic Trade";
            case enum_type::complex_with_stock_cross: return "Complex With Stock Cross";
            case enum_type::electronic_trade: return "Electronic Trade";
            case enum_type::opening_trade: return "Opening Trade";
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
            set(enum_type::opening_trade);
    }

  protected:
    enum_type value;
};
}
