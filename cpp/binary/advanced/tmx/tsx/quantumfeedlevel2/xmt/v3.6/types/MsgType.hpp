// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/MsgType.hpp
#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// msg_type
struct msg_type {

    enum class enum_type : char {
        heartbeat = '0',
        symbol_status_message = 'J',
        order_book_message = 'G',
        order_book_terms_message = 'j',
        assign_cop_orders_message = 'A',
        assign_cop_no_orders_message = 'B',
        assign_limit_message = 'C',
        market_state_update_message = 'E',
        moc_imbalance_message = 'F',
        order_booked_message = 'P',
        order_booked_terms_message = 'm',
        order_cancelled_message = 'Q',
        order_cancelled_terms_message = 'n',
        order_price_time_assigned_message = 'R',
        order_price_time_assigned_terms_message = 'o',
        stock_status_message = 'I',
        trade_report_message = 'S',
        trade_report_terms_message = 'p',
        trade_cancelled_message = 'T',
        trade_cancelled_terms_message = 'q',
        trade_correction_message = 'U',
        trade_correction_terms_message = 'r'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 22> from_string_map = {{
        {"Assign Cop No Orders Message", enum_type::assign_cop_no_orders_message},
        {"Assign Cop Orders Message", enum_type::assign_cop_orders_message},
        {"Assign Limit Message", enum_type::assign_limit_message},
        {"Heartbeat", enum_type::heartbeat},
        {"Market State Update Message", enum_type::market_state_update_message},
        {"Moc Imbalance Message", enum_type::moc_imbalance_message},
        {"Order Book Message", enum_type::order_book_message},
        {"Order Book Terms Message", enum_type::order_book_terms_message},
        {"Order Booked Message", enum_type::order_booked_message},
        {"Order Booked Terms Message", enum_type::order_booked_terms_message},
        {"Order Cancelled Message", enum_type::order_cancelled_message},
        {"Order Cancelled Terms Message", enum_type::order_cancelled_terms_message},
        {"Order Price Time Assigned Message", enum_type::order_price_time_assigned_message},
        {"Order Price Time Assigned Terms Message", enum_type::order_price_time_assigned_terms_message},
        {"Stock Status Message", enum_type::stock_status_message},
        {"Symbol Status Message", enum_type::symbol_status_message},
        {"Trade Cancelled Message", enum_type::trade_cancelled_message},
        {"Trade Cancelled Terms Message", enum_type::trade_cancelled_terms_message},
        {"Trade Correction Message", enum_type::trade_correction_message},
        {"Trade Correction Terms Message", enum_type::trade_correction_terms_message},
        {"Trade Report Message", enum_type::trade_report_message},
        {"Trade Report Terms Message", enum_type::trade_report_terms_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::heartbeat: return "Heartbeat";
            case enum_type::symbol_status_message: return "Symbol Status Message";
            case enum_type::order_book_message: return "Order Book Message";
            case enum_type::order_book_terms_message: return "Order Book Terms Message";
            case enum_type::assign_cop_orders_message: return "Assign Cop Orders Message";
            case enum_type::assign_cop_no_orders_message: return "Assign Cop No Orders Message";
            case enum_type::assign_limit_message: return "Assign Limit Message";
            case enum_type::market_state_update_message: return "Market State Update Message";
            case enum_type::moc_imbalance_message: return "Moc Imbalance Message";
            case enum_type::order_booked_message: return "Order Booked Message";
            case enum_type::order_booked_terms_message: return "Order Booked Terms Message";
            case enum_type::order_cancelled_message: return "Order Cancelled Message";
            case enum_type::order_cancelled_terms_message: return "Order Cancelled Terms Message";
            case enum_type::order_price_time_assigned_message: return "Order Price Time Assigned Message";
            case enum_type::order_price_time_assigned_terms_message: return "Order Price Time Assigned Terms Message";
            case enum_type::stock_status_message: return "Stock Status Message";
            case enum_type::trade_report_message: return "Trade Report Message";
            case enum_type::trade_report_terms_message: return "Trade Report Terms Message";
            case enum_type::trade_cancelled_message: return "Trade Cancelled Message";
            case enum_type::trade_cancelled_terms_message: return "Trade Cancelled Terms Message";
            case enum_type::trade_correction_message: return "Trade Correction Message";
            case enum_type::trade_correction_terms_message: return "Trade Correction Terms Message";
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

    static constexpr const char* name = "msg_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<msg_type::enum_type>;
    using storage_type = result_type;

    constexpr msg_type()
     : value{ enum_type{} } {}

    constexpr msg_type(enum_type v)
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
            set(enum_type::trade_correction_terms_message);
    }

  protected:
    enum_type value;
};
}
