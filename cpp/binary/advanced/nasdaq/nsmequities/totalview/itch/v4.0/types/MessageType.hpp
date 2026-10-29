#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

// message_type
struct message_type {

    enum class enum_type : char {
        timestamp_message = 'T',
        system_event_message = 'S',
        stock_directory_message = 'R',
        stock_trading_action_message = 'H',
        market_participant_position_message = 'L',
        add_order_message = 'A',
        add_order_with_mpid_message = 'F',
        order_executed_message = 'E',
        order_executed_with_price_message = 'C',
        order_cancel_message = 'X',
        order_delete_message = 'D',
        order_replace_message = 'U',
        trade_message = 'P',
        cross_trade_message = 'Q',
        broken_trade_message = 'B',
        net_order_imbalance_indicator_message = 'I'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 16> from_string_map = {{
        {"Add Order Message", enum_type::add_order_message},
        {"Add Order With Mpid Message", enum_type::add_order_with_mpid_message},
        {"Broken Trade Message", enum_type::broken_trade_message},
        {"Cross Trade Message", enum_type::cross_trade_message},
        {"Market Participant Position Message", enum_type::market_participant_position_message},
        {"Net Order Imbalance Indicator Message", enum_type::net_order_imbalance_indicator_message},
        {"Order Cancel Message", enum_type::order_cancel_message},
        {"Order Delete Message", enum_type::order_delete_message},
        {"Order Executed Message", enum_type::order_executed_message},
        {"Order Executed With Price Message", enum_type::order_executed_with_price_message},
        {"Order Replace Message", enum_type::order_replace_message},
        {"Stock Directory Message", enum_type::stock_directory_message},
        {"Stock Trading Action Message", enum_type::stock_trading_action_message},
        {"System Event Message", enum_type::system_event_message},
        {"Timestamp Message", enum_type::timestamp_message},
        {"Trade Message", enum_type::trade_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::timestamp_message: return "Timestamp Message";
            case enum_type::system_event_message: return "System Event Message";
            case enum_type::stock_directory_message: return "Stock Directory Message";
            case enum_type::stock_trading_action_message: return "Stock Trading Action Message";
            case enum_type::market_participant_position_message: return "Market Participant Position Message";
            case enum_type::add_order_message: return "Add Order Message";
            case enum_type::add_order_with_mpid_message: return "Add Order With Mpid Message";
            case enum_type::order_executed_message: return "Order Executed Message";
            case enum_type::order_executed_with_price_message: return "Order Executed With Price Message";
            case enum_type::order_cancel_message: return "Order Cancel Message";
            case enum_type::order_delete_message: return "Order Delete Message";
            case enum_type::order_replace_message: return "Order Replace Message";
            case enum_type::trade_message: return "Trade Message";
            case enum_type::cross_trade_message: return "Cross Trade Message";
            case enum_type::broken_trade_message: return "Broken Trade Message";
            case enum_type::net_order_imbalance_indicator_message: return "Net Order Imbalance Indicator Message";
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
            set(enum_type::net_order_imbalance_indicator_message);
    }

  protected:
    enum_type value;
};
}
