#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_11_b {

// security_status
struct security_status {

    enum class enum_type : char {
        security_status_not_applicable = ' ',
        reserved_1 = '1',
        trading_halt = '2',
        resume = '3',
        reserved_4 = '4',
        price_indication = '5',
        trading_range_indication = '6',
        market_imbalance_buy = '7',
        market_imbalance_sell = '8',
        closing_imbalance_buy = '9',
        closing_imbalance_sell = 'A',
        reserved_b = 'B',
        no_market_imbalance = 'C',
        no_closing_imbalance = 'D',
        short_sale_restriction = 'E',
        limit_up_limit_down = 'F'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 16> from_string_map = {{
        {"Closing Imbalance Buy", enum_type::closing_imbalance_buy},
        {"Closing Imbalance Sell", enum_type::closing_imbalance_sell},
        {"Limit Up Limit Down", enum_type::limit_up_limit_down},
        {"Market Imbalance Buy", enum_type::market_imbalance_buy},
        {"Market Imbalance Sell", enum_type::market_imbalance_sell},
        {"No Closing Imbalance", enum_type::no_closing_imbalance},
        {"No Market Imbalance", enum_type::no_market_imbalance},
        {"Price Indication", enum_type::price_indication},
        {"Reserved 1", enum_type::reserved_1},
        {"Reserved 4", enum_type::reserved_4},
        {"Reserved B", enum_type::reserved_b},
        {"Resume", enum_type::resume},
        {"Security Status Not Applicable", enum_type::security_status_not_applicable},
        {"Short Sale Restriction", enum_type::short_sale_restriction},
        {"Trading Halt", enum_type::trading_halt},
        {"Trading Range Indication", enum_type::trading_range_indication}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::security_status_not_applicable: return "Security Status Not Applicable";
            case enum_type::reserved_1: return "Reserved 1";
            case enum_type::trading_halt: return "Trading Halt";
            case enum_type::resume: return "Resume";
            case enum_type::reserved_4: return "Reserved 4";
            case enum_type::price_indication: return "Price Indication";
            case enum_type::trading_range_indication: return "Trading Range Indication";
            case enum_type::market_imbalance_buy: return "Market Imbalance Buy";
            case enum_type::market_imbalance_sell: return "Market Imbalance Sell";
            case enum_type::closing_imbalance_buy: return "Closing Imbalance Buy";
            case enum_type::closing_imbalance_sell: return "Closing Imbalance Sell";
            case enum_type::reserved_b: return "Reserved B";
            case enum_type::no_market_imbalance: return "No Market Imbalance";
            case enum_type::no_closing_imbalance: return "No Closing Imbalance";
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
