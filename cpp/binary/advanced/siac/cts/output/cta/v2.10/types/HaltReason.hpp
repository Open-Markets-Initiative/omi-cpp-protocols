#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_10 {

// halt_reason
struct halt_reason {

    enum class enum_type : char {
        not_applicable = ' ',
        additional_information_requested = 'A',
        regulatory_concern = 'C',
        news_released = 'D',
        merger_effective = 'E',
        etf_component_prices_not_available = 'F',
        order_imbalance = 'I',
        limit_up_limit_down_trading_pause = 'M',
        corporate_action = 'N',
        new_security_offering = 'O',
        news_pending = 'P',
        intraday_indicative_value_not_available = 'V',
        operational = 'X',
        subpenny_trading = 'Y',
        market_wide_circuit_breaker_level_1_breached = '1',
        market_wide_circuit_breaker_level_2_breached = '2',
        market_wide_circuit_breaker_level_3_breached = '3'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 17> from_string_map = {{
        {"Additional Information Requested", enum_type::additional_information_requested},
        {"Corporate Action", enum_type::corporate_action},
        {"Etf Component Prices Not Available", enum_type::etf_component_prices_not_available},
        {"Intraday Indicative Value Not Available", enum_type::intraday_indicative_value_not_available},
        {"Limit Up Limit Down Trading Pause", enum_type::limit_up_limit_down_trading_pause},
        {"Market Wide Circuit Breaker Level 1 Breached", enum_type::market_wide_circuit_breaker_level_1_breached},
        {"Market Wide Circuit Breaker Level 2 Breached", enum_type::market_wide_circuit_breaker_level_2_breached},
        {"Market Wide Circuit Breaker Level 3 Breached", enum_type::market_wide_circuit_breaker_level_3_breached},
        {"Merger Effective", enum_type::merger_effective},
        {"New Security Offering", enum_type::new_security_offering},
        {"News Pending", enum_type::news_pending},
        {"News Released", enum_type::news_released},
        {"Not Applicable", enum_type::not_applicable},
        {"Operational", enum_type::operational},
        {"Order Imbalance", enum_type::order_imbalance},
        {"Regulatory Concern", enum_type::regulatory_concern},
        {"Subpenny Trading", enum_type::subpenny_trading}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::not_applicable: return "Not Applicable";
            case enum_type::additional_information_requested: return "Additional Information Requested";
            case enum_type::regulatory_concern: return "Regulatory Concern";
            case enum_type::news_released: return "News Released";
            case enum_type::merger_effective: return "Merger Effective";
            case enum_type::etf_component_prices_not_available: return "Etf Component Prices Not Available";
            case enum_type::order_imbalance: return "Order Imbalance";
            case enum_type::limit_up_limit_down_trading_pause: return "Limit Up Limit Down Trading Pause";
            case enum_type::corporate_action: return "Corporate Action";
            case enum_type::new_security_offering: return "New Security Offering";
            case enum_type::news_pending: return "News Pending";
            case enum_type::intraday_indicative_value_not_available: return "Intraday Indicative Value Not Available";
            case enum_type::operational: return "Operational";
            case enum_type::subpenny_trading: return "Subpenny Trading";
            case enum_type::market_wide_circuit_breaker_level_1_breached: return "Market Wide Circuit Breaker Level 1 Breached";
            case enum_type::market_wide_circuit_breaker_level_2_breached: return "Market Wide Circuit Breaker Level 2 Breached";
            case enum_type::market_wide_circuit_breaker_level_3_breached: return "Market Wide Circuit Breaker Level 3 Breached";
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

    static constexpr const char* name = "halt_reason";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<halt_reason::enum_type>;
    using storage_type = result_type;

    constexpr halt_reason()
     : value{ enum_type{} } {}

    constexpr halt_reason(enum_type v)
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
            set(enum_type::market_wide_circuit_breaker_level_3_breached);
    }

  protected:
    enum_type value;
};
}
