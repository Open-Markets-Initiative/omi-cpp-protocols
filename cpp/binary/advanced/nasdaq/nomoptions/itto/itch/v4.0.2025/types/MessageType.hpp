#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// message_type
struct message_type {

    enum class enum_type : char {
        system_event_message = 'S',
        options_directory_message = 'R',
        trading_action_message = 'H',
        security_open_message = 'O',
        add_order_message_short_message_form = 'a',
        add_order_message_long_form_message = 'A',
        add_quote_message_short_form_message = 'j',
        add_quote_message_long_form_message = 'J',
        single_side_executed_message = 'E',
        single_side_executed_with_price_message = 'C',
        order_cancel_message = 'X',
        single_side_replace_message_short_form = 'u',
        single_side_replace_message_long_form = 'U',
        single_side_delete_message = 'D',
        single_side_change_message = 'G',
        quote_replace_message_short_form = 'k',
        quote_replace_message_long_form = 'K',
        quote_delete_message = 'Y',
        options_trade_messages_non_auction = 'P',
        options_cross_trade_message = 'Q',
        broken_trade_order_executed_message = 'B',
        noii_message = 'I'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 22> from_string_map = {{
        {"Add Order Message Long Form Message", enum_type::add_order_message_long_form_message},
        {"Add Order Message Short Message Form", enum_type::add_order_message_short_message_form},
        {"Add Quote Message Long Form Message", enum_type::add_quote_message_long_form_message},
        {"Add Quote Message Short Form Message", enum_type::add_quote_message_short_form_message},
        {"Broken Trade Order Executed Message", enum_type::broken_trade_order_executed_message},
        {"Noii Message", enum_type::noii_message},
        {"Options Cross Trade Message", enum_type::options_cross_trade_message},
        {"Options Directory Message", enum_type::options_directory_message},
        {"Options Trade Messages Non Auction", enum_type::options_trade_messages_non_auction},
        {"Order Cancel Message", enum_type::order_cancel_message},
        {"Quote Delete Message", enum_type::quote_delete_message},
        {"Quote Replace Message Long Form", enum_type::quote_replace_message_long_form},
        {"Quote Replace Message Short Form", enum_type::quote_replace_message_short_form},
        {"Security Open Message", enum_type::security_open_message},
        {"Single Side Change Message", enum_type::single_side_change_message},
        {"Single Side Delete Message", enum_type::single_side_delete_message},
        {"Single Side Executed Message", enum_type::single_side_executed_message},
        {"Single Side Executed With Price Message", enum_type::single_side_executed_with_price_message},
        {"Single Side Replace Message Long Form", enum_type::single_side_replace_message_long_form},
        {"Single Side Replace Message Short Form", enum_type::single_side_replace_message_short_form},
        {"System Event Message", enum_type::system_event_message},
        {"Trading Action Message", enum_type::trading_action_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::system_event_message: return "System Event Message";
            case enum_type::options_directory_message: return "Options Directory Message";
            case enum_type::trading_action_message: return "Trading Action Message";
            case enum_type::security_open_message: return "Security Open Message";
            case enum_type::add_order_message_short_message_form: return "Add Order Message Short Message Form";
            case enum_type::add_order_message_long_form_message: return "Add Order Message Long Form Message";
            case enum_type::add_quote_message_short_form_message: return "Add Quote Message Short Form Message";
            case enum_type::add_quote_message_long_form_message: return "Add Quote Message Long Form Message";
            case enum_type::single_side_executed_message: return "Single Side Executed Message";
            case enum_type::single_side_executed_with_price_message: return "Single Side Executed With Price Message";
            case enum_type::order_cancel_message: return "Order Cancel Message";
            case enum_type::single_side_replace_message_short_form: return "Single Side Replace Message Short Form";
            case enum_type::single_side_replace_message_long_form: return "Single Side Replace Message Long Form";
            case enum_type::single_side_delete_message: return "Single Side Delete Message";
            case enum_type::single_side_change_message: return "Single Side Change Message";
            case enum_type::quote_replace_message_short_form: return "Quote Replace Message Short Form";
            case enum_type::quote_replace_message_long_form: return "Quote Replace Message Long Form";
            case enum_type::quote_delete_message: return "Quote Delete Message";
            case enum_type::options_trade_messages_non_auction: return "Options Trade Messages Non Auction";
            case enum_type::options_cross_trade_message: return "Options Cross Trade Message";
            case enum_type::broken_trade_order_executed_message: return "Broken Trade Order Executed Message";
            case enum_type::noii_message: return "Noii Message";
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
            set(enum_type::noii_message);
    }

  protected:
    enum_type value;
};
}
