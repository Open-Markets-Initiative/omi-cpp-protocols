#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_9 {

// sro_trade_detail
struct sro_trade_detail {

    enum class enum_type : char {
        no_sro_required_trade_detail = ' ',
        average_price_trade = 'B',
        automatic_execution = 'E',
        price_variation_trade = 'H',
        odd_lot_trade = 'I',
        rule_127_or_155 = 'K',
        market_center_official_close = 'M',
        prior_reference_price = 'P',
        market_center_official_open = 'Q',
        contingent_trade = 'V',
        cross_trade = 'X'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 11> from_string_map = {{
        {"Automatic Execution", enum_type::automatic_execution},
        {"Average Price Trade", enum_type::average_price_trade},
        {"Contingent Trade", enum_type::contingent_trade},
        {"Cross Trade", enum_type::cross_trade},
        {"Market Center Official Close", enum_type::market_center_official_close},
        {"Market Center Official Open", enum_type::market_center_official_open},
        {"No Sro Required Trade Detail", enum_type::no_sro_required_trade_detail},
        {"Odd Lot Trade", enum_type::odd_lot_trade},
        {"Price Variation Trade", enum_type::price_variation_trade},
        {"Prior Reference Price", enum_type::prior_reference_price},
        {"Rule 127 Or 155", enum_type::rule_127_or_155}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::no_sro_required_trade_detail: return "No Sro Required Trade Detail";
            case enum_type::average_price_trade: return "Average Price Trade";
            case enum_type::automatic_execution: return "Automatic Execution";
            case enum_type::price_variation_trade: return "Price Variation Trade";
            case enum_type::odd_lot_trade: return "Odd Lot Trade";
            case enum_type::rule_127_or_155: return "Rule 127 Or 155";
            case enum_type::market_center_official_close: return "Market Center Official Close";
            case enum_type::prior_reference_price: return "Prior Reference Price";
            case enum_type::market_center_official_open: return "Market Center Official Open";
            case enum_type::contingent_trade: return "Contingent Trade";
            case enum_type::cross_trade: return "Cross Trade";
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

    static constexpr const char* name = "sro_trade_detail";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<sro_trade_detail::enum_type>;
    using storage_type = result_type;

    constexpr sro_trade_detail()
     : value{ enum_type{} } {}

    constexpr sro_trade_detail(enum_type v)
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
            set(enum_type::cross_trade);
    }

  protected:
    enum_type value;
};
}
