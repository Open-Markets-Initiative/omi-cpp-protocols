#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// message_type
struct message_type {

    enum class enum_type : char {
        system_event_message = 'S',
        stock_directory_message = 'R',
        stock_trading_action_message = 'H',
        reg_sho_short_sale_price_test_restricted_indicator_message = 'Y',
        market_participant_position_message = 'L',
        mwcb_decline_level_message = 'V',
        mwcb_status_level_message = 'W',
        ipo_quoting_period_update = 'K',
        luld_auction_collar_message = 'J',
        operational_halt_message = 'h',
        add_order_no_mpid_attribution_message = 'A',
        add_order_with_mpid_attribution_message = 'F',
        order_executed_message = 'E',
        order_executed_with_price_message = 'C',
        order_cancel_message = 'X',
        order_delete_message = 'D',
        order_replace_message = 'U',
        non_cross_trade_message = 'P',
        cross_trade_message = 'Q',
        broken_trade_message = 'B',
        net_order_imbalance_indicator_message = 'I',
        retail_price_improvement_indicator_message = 'N',
        direct_listing_with_capital_raise_price_discovery_message = 'O'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 23> from_string_map = {{
        {"Add Order No Mpid Attribution Message", enum_type::add_order_no_mpid_attribution_message},
        {"Add Order With Mpid Attribution Message", enum_type::add_order_with_mpid_attribution_message},
        {"Broken Trade Message", enum_type::broken_trade_message},
        {"Cross Trade Message", enum_type::cross_trade_message},
        {"Direct Listing With Capital Raise Price Discovery Message", enum_type::direct_listing_with_capital_raise_price_discovery_message},
        {"Ipo Quoting Period Update", enum_type::ipo_quoting_period_update},
        {"Luld Auction Collar Message", enum_type::luld_auction_collar_message},
        {"Market Participant Position Message", enum_type::market_participant_position_message},
        {"Mwcb Decline Level Message", enum_type::mwcb_decline_level_message},
        {"Mwcb Status Level Message", enum_type::mwcb_status_level_message},
        {"Net Order Imbalance Indicator Message", enum_type::net_order_imbalance_indicator_message},
        {"Non Cross Trade Message", enum_type::non_cross_trade_message},
        {"Operational Halt Message", enum_type::operational_halt_message},
        {"Order Cancel Message", enum_type::order_cancel_message},
        {"Order Delete Message", enum_type::order_delete_message},
        {"Order Executed Message", enum_type::order_executed_message},
        {"Order Executed With Price Message", enum_type::order_executed_with_price_message},
        {"Order Replace Message", enum_type::order_replace_message},
        {"Reg Sho Short Sale Price Test Restricted Indicator Message", enum_type::reg_sho_short_sale_price_test_restricted_indicator_message},
        {"Retail Price Improvement Indicator Message", enum_type::retail_price_improvement_indicator_message},
        {"Stock Directory Message", enum_type::stock_directory_message},
        {"Stock Trading Action Message", enum_type::stock_trading_action_message},
        {"System Event Message", enum_type::system_event_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::system_event_message: return "System Event Message";
            case enum_type::stock_directory_message: return "Stock Directory Message";
            case enum_type::stock_trading_action_message: return "Stock Trading Action Message";
            case enum_type::reg_sho_short_sale_price_test_restricted_indicator_message: return "Reg Sho Short Sale Price Test Restricted Indicator Message";
            case enum_type::market_participant_position_message: return "Market Participant Position Message";
            case enum_type::mwcb_decline_level_message: return "Mwcb Decline Level Message";
            case enum_type::mwcb_status_level_message: return "Mwcb Status Level Message";
            case enum_type::ipo_quoting_period_update: return "Ipo Quoting Period Update";
            case enum_type::luld_auction_collar_message: return "Luld Auction Collar Message";
            case enum_type::operational_halt_message: return "Operational Halt Message";
            case enum_type::add_order_no_mpid_attribution_message: return "Add Order No Mpid Attribution Message";
            case enum_type::add_order_with_mpid_attribution_message: return "Add Order With Mpid Attribution Message";
            case enum_type::order_executed_message: return "Order Executed Message";
            case enum_type::order_executed_with_price_message: return "Order Executed With Price Message";
            case enum_type::order_cancel_message: return "Order Cancel Message";
            case enum_type::order_delete_message: return "Order Delete Message";
            case enum_type::order_replace_message: return "Order Replace Message";
            case enum_type::non_cross_trade_message: return "Non Cross Trade Message";
            case enum_type::cross_trade_message: return "Cross Trade Message";
            case enum_type::broken_trade_message: return "Broken Trade Message";
            case enum_type::net_order_imbalance_indicator_message: return "Net Order Imbalance Indicator Message";
            case enum_type::retail_price_improvement_indicator_message: return "Retail Price Improvement Indicator Message";
            case enum_type::direct_listing_with_capital_raise_price_discovery_message: return "Direct Listing With Capital Raise Price Discovery Message";
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
     : value{ enum_type::system_event_message } {}

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
            set(enum_type::direct_listing_with_capital_raise_price_discovery_message);
    }

  protected:
    enum_type value;
};
}
