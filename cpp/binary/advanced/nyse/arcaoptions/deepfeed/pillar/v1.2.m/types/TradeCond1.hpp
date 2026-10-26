#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// trade_cond_1
struct trade_cond_1 {

    enum class enum_type : char {
        outright_series_orderquote_trading_electronically_with_a_outright_series_cube_order_or_outright_series_cube_order_trading_electronically_with_outright_series_cube_contra_order = 'a',
        trading_of_an_outright_series_qcc_order_or_customer_to_customer_cross_order = 'c',
        outright_series_floor_trade = 'e',
        all_outright_series_electronic_trades_excluding_away_market_executions_that_were_not_part_of_certain_transactions = 'I',
        all_outright_series_trades_generated_as_part_of_an_intermarket_sweep_order = 'S',
        transaction_is_being_reported_late_but_is_in_the_correct_sequence = 'D',
        complex_order_trades_that_were_not_part_of_certain_transactions = 'f',
        complex_order_trading_electronically_with_a_complex_cube_order_or_complex_cube_order_trading_electronically_with_complex_cube_contra_order = 'g',
        trading_of_a_complex_qcc_order_or_customer_to_customer_cross_order = 'h',
        complex_order_to_complex_order_floor_trade = 'i',
        complex_order_trading_electronically_with_the_outright_series_ordersquotes = 'j',
        complex_order_to_outright_series_order_floor_trade = 'm',
        complex_order_with_stock_to_complex_order_with_stock_floor_trade = 'p',
        complex_order_with_stock_to_outright_series_order_floor_trade = 's',
        extended_hours_trade = 'v'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 15> from_string_map = {{
        {"All Outright Series Electronic Trades Excluding Away Market Executions That Were Not Part Of Certain Transactions", enum_type::all_outright_series_electronic_trades_excluding_away_market_executions_that_were_not_part_of_certain_transactions},
        {"All Outright Series Trades Generated As Part Of An Intermarket Sweep Order", enum_type::all_outright_series_trades_generated_as_part_of_an_intermarket_sweep_order},
        {"Complex Order To Complex Order Floor Trade", enum_type::complex_order_to_complex_order_floor_trade},
        {"Complex Order To Outright Series Order Floor Trade", enum_type::complex_order_to_outright_series_order_floor_trade},
        {"Complex Order Trades That Were Not Part Of Certain Transactions", enum_type::complex_order_trades_that_were_not_part_of_certain_transactions},
        {"Complex Order Trading Electronically With A Complex Cube Order Or Complex Cube Order Trading Electronically With Complex Cube Contra Order", enum_type::complex_order_trading_electronically_with_a_complex_cube_order_or_complex_cube_order_trading_electronically_with_complex_cube_contra_order},
        {"Complex Order Trading Electronically With The Outright Series Ordersquotes", enum_type::complex_order_trading_electronically_with_the_outright_series_ordersquotes},
        {"Complex Order With Stock To Complex Order With Stock Floor Trade", enum_type::complex_order_with_stock_to_complex_order_with_stock_floor_trade},
        {"Complex Order With Stock To Outright Series Order Floor Trade", enum_type::complex_order_with_stock_to_outright_series_order_floor_trade},
        {"Extended Hours Trade", enum_type::extended_hours_trade},
        {"Outright Series Floor Trade", enum_type::outright_series_floor_trade},
        {"Outright Series Orderquote Trading Electronically With A Outright Series Cube Order Or Outright Series Cube Order Trading Electronically With Outright Series Cube Contra Order", enum_type::outright_series_orderquote_trading_electronically_with_a_outright_series_cube_order_or_outright_series_cube_order_trading_electronically_with_outright_series_cube_contra_order},
        {"Trading Of A Complex Qcc Order Or Customer To Customer Cross Order", enum_type::trading_of_a_complex_qcc_order_or_customer_to_customer_cross_order},
        {"Trading Of An Outright Series Qcc Order Or Customer To Customer Cross Order", enum_type::trading_of_an_outright_series_qcc_order_or_customer_to_customer_cross_order},
        {"Transaction Is Being Reported Late But Is In The Correct Sequence", enum_type::transaction_is_being_reported_late_but_is_in_the_correct_sequence}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::outright_series_orderquote_trading_electronically_with_a_outright_series_cube_order_or_outright_series_cube_order_trading_electronically_with_outright_series_cube_contra_order: return "Outright Series Orderquote Trading Electronically With A Outright Series Cube Order Or Outright Series Cube Order Trading Electronically With Outright Series Cube Contra Order";
            case enum_type::trading_of_an_outright_series_qcc_order_or_customer_to_customer_cross_order: return "Trading Of An Outright Series Qcc Order Or Customer To Customer Cross Order";
            case enum_type::outright_series_floor_trade: return "Outright Series Floor Trade";
            case enum_type::all_outright_series_electronic_trades_excluding_away_market_executions_that_were_not_part_of_certain_transactions: return "All Outright Series Electronic Trades Excluding Away Market Executions That Were Not Part Of Certain Transactions";
            case enum_type::all_outright_series_trades_generated_as_part_of_an_intermarket_sweep_order: return "All Outright Series Trades Generated As Part Of An Intermarket Sweep Order";
            case enum_type::transaction_is_being_reported_late_but_is_in_the_correct_sequence: return "Transaction Is Being Reported Late But Is In The Correct Sequence";
            case enum_type::complex_order_trades_that_were_not_part_of_certain_transactions: return "Complex Order Trades That Were Not Part Of Certain Transactions";
            case enum_type::complex_order_trading_electronically_with_a_complex_cube_order_or_complex_cube_order_trading_electronically_with_complex_cube_contra_order: return "Complex Order Trading Electronically With A Complex Cube Order Or Complex Cube Order Trading Electronically With Complex Cube Contra Order";
            case enum_type::trading_of_a_complex_qcc_order_or_customer_to_customer_cross_order: return "Trading Of A Complex Qcc Order Or Customer To Customer Cross Order";
            case enum_type::complex_order_to_complex_order_floor_trade: return "Complex Order To Complex Order Floor Trade";
            case enum_type::complex_order_trading_electronically_with_the_outright_series_ordersquotes: return "Complex Order Trading Electronically With The Outright Series Ordersquotes";
            case enum_type::complex_order_to_outright_series_order_floor_trade: return "Complex Order To Outright Series Order Floor Trade";
            case enum_type::complex_order_with_stock_to_complex_order_with_stock_floor_trade: return "Complex Order With Stock To Complex Order With Stock Floor Trade";
            case enum_type::complex_order_with_stock_to_outright_series_order_floor_trade: return "Complex Order With Stock To Outright Series Order Floor Trade";
            case enum_type::extended_hours_trade: return "Extended Hours Trade";
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

    static constexpr const char* name = "trade_cond_1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<trade_cond_1::enum_type>;
    using storage_type = result_type;

    constexpr trade_cond_1()
     : value{ enum_type{} } {}

    constexpr trade_cond_1(enum_type v)
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
            set(enum_type::extended_hours_trade);
    }

  protected:
    enum_type value;
};
}
