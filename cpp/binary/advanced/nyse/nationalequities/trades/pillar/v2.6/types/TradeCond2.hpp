#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

// trade_cond_2
struct trade_cond_2 {

    enum class enum_type : char {
        na = ' ',
        intermarket_sweep_order = 'F',
        market_center_opening_trade = 'O',
        derivatively_priced_trf_only = '4',
        reopening_trade = '5',
        market_center_closing_trade = '6',
        qualified_contingent_trade_trf_or_texas_only = '7',
        corrected_consolidated_close = '9'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 8> from_string_map = {{
        {"Corrected Consolidated Close", enum_type::corrected_consolidated_close},
        {"Derivatively Priced Trf Only", enum_type::derivatively_priced_trf_only},
        {"Intermarket Sweep Order", enum_type::intermarket_sweep_order},
        {"Market Center Closing Trade", enum_type::market_center_closing_trade},
        {"Market Center Opening Trade", enum_type::market_center_opening_trade},
        {"Na", enum_type::na},
        {"Qualified Contingent Trade Trf Or Texas Only", enum_type::qualified_contingent_trade_trf_or_texas_only},
        {"Reopening Trade", enum_type::reopening_trade}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::na: return "Na";
            case enum_type::intermarket_sweep_order: return "Intermarket Sweep Order";
            case enum_type::market_center_opening_trade: return "Market Center Opening Trade";
            case enum_type::derivatively_priced_trf_only: return "Derivatively Priced Trf Only";
            case enum_type::reopening_trade: return "Reopening Trade";
            case enum_type::market_center_closing_trade: return "Market Center Closing Trade";
            case enum_type::qualified_contingent_trade_trf_or_texas_only: return "Qualified Contingent Trade Trf Or Texas Only";
            case enum_type::corrected_consolidated_close: return "Corrected Consolidated Close";
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

    static constexpr const char* name = "trade_cond_2";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<trade_cond_2::enum_type>;
    using storage_type = result_type;

    constexpr trade_cond_2()
     : value{ enum_type{} } {}

    constexpr trade_cond_2(enum_type v)
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
            set(enum_type::corrected_consolidated_close);
    }

  protected:
    enum_type value;
};
}
