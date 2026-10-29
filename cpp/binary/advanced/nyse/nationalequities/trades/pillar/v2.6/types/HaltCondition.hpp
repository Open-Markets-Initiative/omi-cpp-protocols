#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

// halt_condition
struct halt_condition {

    enum class enum_type : char {
        security_not_delayedhalted = '~',
        news_released_news_dissemination = 'D',
        order_imbalance = 'I',
        news_pending = 'P',
        luld_pause = 'M',
        equipment_changeover = 'X',
        additional_information_requested = 'A',
        regulatory_concern = 'C',
        merger_effective = 'E',
        etf_component_prices_not_available = 'F',
        corporate_action = 'N',
        new_security_offering = 'O',
        intraday_indicative_value_not_available = 'V',
        suspend = '6',
        market_wide_circuit_breaker_halt_level_1 = '1',
        market_wide_circuit_breaker_halt_level_2 = '2',
        market_wide_circuit_breaker_halt_level_3 = '3'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 17> from_string_map = {{
        {"Additional Information Requested", enum_type::additional_information_requested},
        {"Corporate Action", enum_type::corporate_action},
        {"Equipment Changeover", enum_type::equipment_changeover},
        {"Etf Component Prices Not Available", enum_type::etf_component_prices_not_available},
        {"Intraday Indicative Value Not Available", enum_type::intraday_indicative_value_not_available},
        {"Luld Pause", enum_type::luld_pause},
        {"Market Wide Circuit Breaker Halt Level 1", enum_type::market_wide_circuit_breaker_halt_level_1},
        {"Market Wide Circuit Breaker Halt Level 2", enum_type::market_wide_circuit_breaker_halt_level_2},
        {"Market Wide Circuit Breaker Halt Level 3", enum_type::market_wide_circuit_breaker_halt_level_3},
        {"Merger Effective", enum_type::merger_effective},
        {"New Security Offering", enum_type::new_security_offering},
        {"News Pending", enum_type::news_pending},
        {"News Released News Dissemination", enum_type::news_released_news_dissemination},
        {"Order Imbalance", enum_type::order_imbalance},
        {"Regulatory Concern", enum_type::regulatory_concern},
        {"Security Not Delayedhalted", enum_type::security_not_delayedhalted},
        {"Suspend", enum_type::suspend}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::security_not_delayedhalted: return "Security Not Delayedhalted";
            case enum_type::news_released_news_dissemination: return "News Released News Dissemination";
            case enum_type::order_imbalance: return "Order Imbalance";
            case enum_type::news_pending: return "News Pending";
            case enum_type::luld_pause: return "Luld Pause";
            case enum_type::equipment_changeover: return "Equipment Changeover";
            case enum_type::additional_information_requested: return "Additional Information Requested";
            case enum_type::regulatory_concern: return "Regulatory Concern";
            case enum_type::merger_effective: return "Merger Effective";
            case enum_type::etf_component_prices_not_available: return "Etf Component Prices Not Available";
            case enum_type::corporate_action: return "Corporate Action";
            case enum_type::new_security_offering: return "New Security Offering";
            case enum_type::intraday_indicative_value_not_available: return "Intraday Indicative Value Not Available";
            case enum_type::suspend: return "Suspend";
            case enum_type::market_wide_circuit_breaker_halt_level_1: return "Market Wide Circuit Breaker Halt Level 1";
            case enum_type::market_wide_circuit_breaker_halt_level_2: return "Market Wide Circuit Breaker Halt Level 2";
            case enum_type::market_wide_circuit_breaker_halt_level_3: return "Market Wide Circuit Breaker Halt Level 3";
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

    static constexpr const char* name = "halt_condition";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<halt_condition::enum_type>;
    using storage_type = result_type;

    constexpr halt_condition()
     : value{ enum_type{} } {}

    constexpr halt_condition(enum_type v)
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
            set(enum_type::market_wide_circuit_breaker_halt_level_3);
    }

  protected:
    enum_type value;
};
}
