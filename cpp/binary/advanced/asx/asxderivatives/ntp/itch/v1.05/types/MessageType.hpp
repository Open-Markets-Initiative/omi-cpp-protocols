#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

// message_type
struct message_type {

    enum class enum_type : char {
        seconds_message = 'T',
        end_of_business_trade_date_message = 'S',
        future_symbol_directory_message = 'f',
        options_symbol_directory_message = 'h',
        combination_symbol_directory_message = 'M',
        bundles_symbol_directory = 'm',
        order_book_state_message = 'O',
        add_order_message = 'A',
        order_volume_cancelled_message = 'X',
        order_deleted_message = 'D',
        order_executed_message = 'E',
        auction_order_executed_message = 'C',
        combination_order_executed_message = 'e',
        implied_order_added_message = 'j',
        implied_order_replaced_message = 'l',
        implied_order_deleted_message = 'k',
        trade_executed_message = 'P',
        combination_trade_executed_message = 'p',
        trade_cancellation_message = 'B',
        equilibrium_price_message = 'Z',
        open_high_low_last_trade_adjustment_message = 't',
        market_settlement_message = 'Y',
        text_message = 'x',
        request_for_quote_message = 'q',
        anomalous_order_threshold_publish_message = 'W',
        volume_and_open_interest_message = 'V'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 26> from_string_map = {{
        {"Add Order Message", enum_type::add_order_message},
        {"Anomalous Order Threshold Publish Message", enum_type::anomalous_order_threshold_publish_message},
        {"Auction Order Executed Message", enum_type::auction_order_executed_message},
        {"Bundles Symbol Directory", enum_type::bundles_symbol_directory},
        {"Combination Order Executed Message", enum_type::combination_order_executed_message},
        {"Combination Symbol Directory Message", enum_type::combination_symbol_directory_message},
        {"Combination Trade Executed Message", enum_type::combination_trade_executed_message},
        {"End Of Business Trade Date Message", enum_type::end_of_business_trade_date_message},
        {"Equilibrium Price Message", enum_type::equilibrium_price_message},
        {"Future Symbol Directory Message", enum_type::future_symbol_directory_message},
        {"Implied Order Added Message", enum_type::implied_order_added_message},
        {"Implied Order Deleted Message", enum_type::implied_order_deleted_message},
        {"Implied Order Replaced Message", enum_type::implied_order_replaced_message},
        {"Market Settlement Message", enum_type::market_settlement_message},
        {"Open High Low Last Trade Adjustment Message", enum_type::open_high_low_last_trade_adjustment_message},
        {"Options Symbol Directory Message", enum_type::options_symbol_directory_message},
        {"Order Book State Message", enum_type::order_book_state_message},
        {"Order Deleted Message", enum_type::order_deleted_message},
        {"Order Executed Message", enum_type::order_executed_message},
        {"Order Volume Cancelled Message", enum_type::order_volume_cancelled_message},
        {"Request For Quote Message", enum_type::request_for_quote_message},
        {"Seconds Message", enum_type::seconds_message},
        {"Text Message", enum_type::text_message},
        {"Trade Cancellation Message", enum_type::trade_cancellation_message},
        {"Trade Executed Message", enum_type::trade_executed_message},
        {"Volume And Open Interest Message", enum_type::volume_and_open_interest_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::seconds_message: return "Seconds Message";
            case enum_type::end_of_business_trade_date_message: return "End Of Business Trade Date Message";
            case enum_type::future_symbol_directory_message: return "Future Symbol Directory Message";
            case enum_type::options_symbol_directory_message: return "Options Symbol Directory Message";
            case enum_type::combination_symbol_directory_message: return "Combination Symbol Directory Message";
            case enum_type::bundles_symbol_directory: return "Bundles Symbol Directory";
            case enum_type::order_book_state_message: return "Order Book State Message";
            case enum_type::add_order_message: return "Add Order Message";
            case enum_type::order_volume_cancelled_message: return "Order Volume Cancelled Message";
            case enum_type::order_deleted_message: return "Order Deleted Message";
            case enum_type::order_executed_message: return "Order Executed Message";
            case enum_type::auction_order_executed_message: return "Auction Order Executed Message";
            case enum_type::combination_order_executed_message: return "Combination Order Executed Message";
            case enum_type::implied_order_added_message: return "Implied Order Added Message";
            case enum_type::implied_order_replaced_message: return "Implied Order Replaced Message";
            case enum_type::implied_order_deleted_message: return "Implied Order Deleted Message";
            case enum_type::trade_executed_message: return "Trade Executed Message";
            case enum_type::combination_trade_executed_message: return "Combination Trade Executed Message";
            case enum_type::trade_cancellation_message: return "Trade Cancellation Message";
            case enum_type::equilibrium_price_message: return "Equilibrium Price Message";
            case enum_type::open_high_low_last_trade_adjustment_message: return "Open High Low Last Trade Adjustment Message";
            case enum_type::market_settlement_message: return "Market Settlement Message";
            case enum_type::text_message: return "Text Message";
            case enum_type::request_for_quote_message: return "Request For Quote Message";
            case enum_type::anomalous_order_threshold_publish_message: return "Anomalous Order Threshold Publish Message";
            case enum_type::volume_and_open_interest_message: return "Volume And Open Interest Message";
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

    static constexpr const char* name = "message_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<message_type::enum_type>;
    using storage_type = result_type;

    constexpr message_type()
     : value{ enum_type{} } {}

    constexpr message_type(enum_type v)
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
            set(enum_type::volume_and_open_interest_message);
    }

  protected:
    enum_type value;
};
}
