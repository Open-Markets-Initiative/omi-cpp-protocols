#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

// md_entry_type
struct md_entry_type {

    enum class enum_type : char {
        bid = '0',
        offer = '1',
        trade = '2',
        index_value = '3',
        opening_price = '4',
        closing_price = '5',
        settlement_price = '6',
        session_high_price = '7',
        session_low_price = '8',
        execution_statistics = '9',
        imbalance = 'A',
        trade_volume = 'B',
        open_interest = 'C',
        empty_book = 'J',
        security_trading_state_phase = 'c',
        price_band = 'g',
        quantity_band = 'h',
        composite_underlying_price = 'D',
        execution_summary = 's',
        volatility_price = 'v',
        trade_bust = 'u'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 21> from_string_map = {{
        {"Bid", enum_type::bid},
        {"Closing Price", enum_type::closing_price},
        {"Composite Underlying Price", enum_type::composite_underlying_price},
        {"Empty Book", enum_type::empty_book},
        {"Execution Statistics", enum_type::execution_statistics},
        {"Execution Summary", enum_type::execution_summary},
        {"Imbalance", enum_type::imbalance},
        {"Index Value", enum_type::index_value},
        {"Offer", enum_type::offer},
        {"Open Interest", enum_type::open_interest},
        {"Opening Price", enum_type::opening_price},
        {"Price Band", enum_type::price_band},
        {"Quantity Band", enum_type::quantity_band},
        {"Security Trading State Phase", enum_type::security_trading_state_phase},
        {"Session High Price", enum_type::session_high_price},
        {"Session Low Price", enum_type::session_low_price},
        {"Settlement Price", enum_type::settlement_price},
        {"Trade", enum_type::trade},
        {"Trade Bust", enum_type::trade_bust},
        {"Trade Volume", enum_type::trade_volume},
        {"Volatility Price", enum_type::volatility_price}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::bid: return "Bid";
            case enum_type::offer: return "Offer";
            case enum_type::trade: return "Trade";
            case enum_type::index_value: return "Index Value";
            case enum_type::opening_price: return "Opening Price";
            case enum_type::closing_price: return "Closing Price";
            case enum_type::settlement_price: return "Settlement Price";
            case enum_type::session_high_price: return "Session High Price";
            case enum_type::session_low_price: return "Session Low Price";
            case enum_type::execution_statistics: return "Execution Statistics";
            case enum_type::imbalance: return "Imbalance";
            case enum_type::trade_volume: return "Trade Volume";
            case enum_type::open_interest: return "Open Interest";
            case enum_type::empty_book: return "Empty Book";
            case enum_type::security_trading_state_phase: return "Security Trading State Phase";
            case enum_type::price_band: return "Price Band";
            case enum_type::quantity_band: return "Quantity Band";
            case enum_type::composite_underlying_price: return "Composite Underlying Price";
            case enum_type::execution_summary: return "Execution Summary";
            case enum_type::volatility_price: return "Volatility Price";
            case enum_type::trade_bust: return "Trade Bust";
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

    static constexpr const char* name = "md_entry_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<md_entry_type::enum_type>;
    using storage_type = result_type;

    constexpr md_entry_type()
     : value{ enum_type::bid } {}

    constexpr md_entry_type(enum_type v)
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
            set(enum_type::trade_bust);
    }

  protected:
    enum_type value;
};
}
