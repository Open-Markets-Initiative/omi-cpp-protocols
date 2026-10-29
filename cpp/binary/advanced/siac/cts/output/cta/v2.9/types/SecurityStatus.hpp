#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_9 {

// security_status
struct security_status {

    enum class enum_type : char {
        not_applicable = ' ',
        trading_halt = '2',
        resume = '3',
        price_indication = '5',
        trading_range_indication = '6',
        market_imbalance_buy = '7',
        market_imbalance_sell = '8',
        market_on_close_imbalance_buy = '9',
        market_on_close_imbalance_sell = 'A',
        no_market_imbalance = 'C',
        no_market_on_close_imbalance = 'D',
        short_sale_restriction = 'E',
        limit_up_limit_down = 'F'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 13> from_string_map = {{
        {"Limit Up Limit Down", enum_type::limit_up_limit_down},
        {"Market Imbalance Buy", enum_type::market_imbalance_buy},
        {"Market Imbalance Sell", enum_type::market_imbalance_sell},
        {"Market On Close Imbalance Buy", enum_type::market_on_close_imbalance_buy},
        {"Market On Close Imbalance Sell", enum_type::market_on_close_imbalance_sell},
        {"No Market Imbalance", enum_type::no_market_imbalance},
        {"No Market On Close Imbalance", enum_type::no_market_on_close_imbalance},
        {"Not Applicable", enum_type::not_applicable},
        {"Price Indication", enum_type::price_indication},
        {"Resume", enum_type::resume},
        {"Short Sale Restriction", enum_type::short_sale_restriction},
        {"Trading Halt", enum_type::trading_halt},
        {"Trading Range Indication", enum_type::trading_range_indication}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::not_applicable: return "Not Applicable";
            case enum_type::trading_halt: return "Trading Halt";
            case enum_type::resume: return "Resume";
            case enum_type::price_indication: return "Price Indication";
            case enum_type::trading_range_indication: return "Trading Range Indication";
            case enum_type::market_imbalance_buy: return "Market Imbalance Buy";
            case enum_type::market_imbalance_sell: return "Market Imbalance Sell";
            case enum_type::market_on_close_imbalance_buy: return "Market On Close Imbalance Buy";
            case enum_type::market_on_close_imbalance_sell: return "Market On Close Imbalance Sell";
            case enum_type::no_market_imbalance: return "No Market Imbalance";
            case enum_type::no_market_on_close_imbalance: return "No Market On Close Imbalance";
            case enum_type::short_sale_restriction: return "Short Sale Restriction";
            case enum_type::limit_up_limit_down: return "Limit Up Limit Down";
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

    static constexpr const char* name = "security_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<security_status::enum_type>;
    using storage_type = result_type;

    constexpr security_status()
     : value{ enum_type{} } {}

    constexpr security_status(enum_type v)
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
            set(enum_type::limit_up_limit_down);
    }

  protected:
    enum_type value;
};
}
