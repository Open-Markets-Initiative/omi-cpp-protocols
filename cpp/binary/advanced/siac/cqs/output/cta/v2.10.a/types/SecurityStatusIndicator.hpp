#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cqs::output::cta::v2_10_a {

// security_status_indicator
struct security_status_indicator {

    enum class enum_type : char {
        security_status_indicator_not_applicable = ' ',
        additional_information_requested = 'A',
        regulatory_concern = 'C',
        news_released = 'D',
        merger_effective = 'E',
        etf_component_prices_not_available = 'F',
        trading_range_indication = 'G',
        order_imbalance = 'I',
        limit_up_limit_down_trading_pause = 'M',
        corporate_action = 'N',
        new_security_offering = 'O',
        news_pending = 'P',
        intraday_indicative_value_not_available = 'V',
        resume = 'T',
        operational = 'X',
        sup_penny_trading = 'Y',
        reserved = 'Z',
        limit_up_limit_down_price_band = '0',
        market_wide_circuit_breaker_level_1_breached = '1',
        market_wide_circuit_breaker_level_2_breached = '2',
        market_wide_circuit_breaker_level_3_breached = '3',
        republished_limit_up_limit_down_price_band = '9'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 22> from_string_map = {{
        {"Additional Information Requested", enum_type::additional_information_requested},
        {"Corporate Action", enum_type::corporate_action},
        {"Etf Component Prices Not Available", enum_type::etf_component_prices_not_available},
        {"Intraday Indicative Value Not Available", enum_type::intraday_indicative_value_not_available},
        {"Limit Up Limit Down Price Band", enum_type::limit_up_limit_down_price_band},
        {"Limit Up Limit Down Trading Pause", enum_type::limit_up_limit_down_trading_pause},
        {"Market Wide Circuit Breaker Level 1 Breached", enum_type::market_wide_circuit_breaker_level_1_breached},
        {"Market Wide Circuit Breaker Level 2 Breached", enum_type::market_wide_circuit_breaker_level_2_breached},
        {"Market Wide Circuit Breaker Level 3 Breached", enum_type::market_wide_circuit_breaker_level_3_breached},
        {"Merger Effective", enum_type::merger_effective},
        {"New Security Offering", enum_type::new_security_offering},
        {"News Pending", enum_type::news_pending},
        {"News Released", enum_type::news_released},
        {"Operational", enum_type::operational},
        {"Order Imbalance", enum_type::order_imbalance},
        {"Regulatory Concern", enum_type::regulatory_concern},
        {"Republished Limit Up Limit Down Price Band", enum_type::republished_limit_up_limit_down_price_band},
        {"Reserved", enum_type::reserved},
        {"Resume", enum_type::resume},
        {"Security Status Indicator Not Applicable", enum_type::security_status_indicator_not_applicable},
        {"Sup Penny Trading", enum_type::sup_penny_trading},
        {"Trading Range Indication", enum_type::trading_range_indication}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::security_status_indicator_not_applicable: return "Security Status Indicator Not Applicable";
            case enum_type::additional_information_requested: return "Additional Information Requested";
            case enum_type::regulatory_concern: return "Regulatory Concern";
            case enum_type::news_released: return "News Released";
            case enum_type::merger_effective: return "Merger Effective";
            case enum_type::etf_component_prices_not_available: return "Etf Component Prices Not Available";
            case enum_type::trading_range_indication: return "Trading Range Indication";
            case enum_type::order_imbalance: return "Order Imbalance";
            case enum_type::limit_up_limit_down_trading_pause: return "Limit Up Limit Down Trading Pause";
            case enum_type::corporate_action: return "Corporate Action";
            case enum_type::new_security_offering: return "New Security Offering";
            case enum_type::news_pending: return "News Pending";
            case enum_type::intraday_indicative_value_not_available: return "Intraday Indicative Value Not Available";
            case enum_type::resume: return "Resume";
            case enum_type::operational: return "Operational";
            case enum_type::sup_penny_trading: return "Sup Penny Trading";
            case enum_type::reserved: return "Reserved";
            case enum_type::limit_up_limit_down_price_band: return "Limit Up Limit Down Price Band";
            case enum_type::market_wide_circuit_breaker_level_1_breached: return "Market Wide Circuit Breaker Level 1 Breached";
            case enum_type::market_wide_circuit_breaker_level_2_breached: return "Market Wide Circuit Breaker Level 2 Breached";
            case enum_type::market_wide_circuit_breaker_level_3_breached: return "Market Wide Circuit Breaker Level 3 Breached";
            case enum_type::republished_limit_up_limit_down_price_band: return "Republished Limit Up Limit Down Price Band";
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

    static constexpr const char* name = "security_status_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<security_status_indicator::enum_type>;
    using storage_type = result_type;

    constexpr security_status_indicator()
     : value{ enum_type{} } {}

    constexpr security_status_indicator(enum_type v)
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
            set(enum_type::republished_limit_up_limit_down_price_band);
    }

  protected:
    enum_type value;
};
}
