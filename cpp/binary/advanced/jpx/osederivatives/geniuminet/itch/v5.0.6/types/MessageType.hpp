#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// message_type
struct message_type {

    enum class enum_type : char {
        seconds_message = 'T',
        order_book_directory = 'R',
        combination_orderbook_leg = 'M',
        tick_size_table_entry = 'L',
        system_event_message = 'S',
        order_book_state_message = 'O',
        add_order_no_mpid = 'A',
        add_order_with_mpid = 'F',
        order_executed_message = 'E',
        order_executed_with_price_message = 'C',
        order_replace_message = 'U',
        order_delete_message = 'D',
        trade_message = 'P',
        equilibrium_price_update = 'Z'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 14> from_string_map = {{
        {"Add Order No Mpid", enum_type::add_order_no_mpid},
        {"Add Order With Mpid", enum_type::add_order_with_mpid},
        {"Combination Orderbook Leg", enum_type::combination_orderbook_leg},
        {"Equilibrium Price Update", enum_type::equilibrium_price_update},
        {"Order Book Directory", enum_type::order_book_directory},
        {"Order Book State Message", enum_type::order_book_state_message},
        {"Order Delete Message", enum_type::order_delete_message},
        {"Order Executed Message", enum_type::order_executed_message},
        {"Order Executed With Price Message", enum_type::order_executed_with_price_message},
        {"Order Replace Message", enum_type::order_replace_message},
        {"Seconds Message", enum_type::seconds_message},
        {"System Event Message", enum_type::system_event_message},
        {"Tick Size Table Entry", enum_type::tick_size_table_entry},
        {"Trade Message", enum_type::trade_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::seconds_message: return "Seconds Message";
            case enum_type::order_book_directory: return "Order Book Directory";
            case enum_type::combination_orderbook_leg: return "Combination Orderbook Leg";
            case enum_type::tick_size_table_entry: return "Tick Size Table Entry";
            case enum_type::system_event_message: return "System Event Message";
            case enum_type::order_book_state_message: return "Order Book State Message";
            case enum_type::add_order_no_mpid: return "Add Order No Mpid";
            case enum_type::add_order_with_mpid: return "Add Order With Mpid";
            case enum_type::order_executed_message: return "Order Executed Message";
            case enum_type::order_executed_with_price_message: return "Order Executed With Price Message";
            case enum_type::order_replace_message: return "Order Replace Message";
            case enum_type::order_delete_message: return "Order Delete Message";
            case enum_type::trade_message: return "Trade Message";
            case enum_type::equilibrium_price_update: return "Equilibrium Price Update";
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
            set(enum_type::equilibrium_price_update);
    }

  protected:
    enum_type value;
};
}
