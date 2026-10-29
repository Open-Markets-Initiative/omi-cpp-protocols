#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// message_type
struct message_type {

    enum class enum_type : char {
        market_event_message = 'A',
        symbol_information_message = 'B',
        symbol_state_message = 'C',
        new_order_add_message = 'D',
        order_partial_cancel_message = 'F',
        order_cancel_all_message = 'G',
        order_executed_message = 'J',
        trade_message = 'K',
        trade_cancel_message = 'L',
        trade_correct_message = 'M'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 10> from_string_map = {{
        {"Market Event Message", enum_type::market_event_message},
        {"New Order Add Message", enum_type::new_order_add_message},
        {"Order Cancel All Message", enum_type::order_cancel_all_message},
        {"Order Executed Message", enum_type::order_executed_message},
        {"Order Partial Cancel Message", enum_type::order_partial_cancel_message},
        {"Symbol Information Message", enum_type::symbol_information_message},
        {"Symbol State Message", enum_type::symbol_state_message},
        {"Trade Cancel Message", enum_type::trade_cancel_message},
        {"Trade Correct Message", enum_type::trade_correct_message},
        {"Trade Message", enum_type::trade_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::market_event_message: return "Market Event Message";
            case enum_type::symbol_information_message: return "Symbol Information Message";
            case enum_type::symbol_state_message: return "Symbol State Message";
            case enum_type::new_order_add_message: return "New Order Add Message";
            case enum_type::order_partial_cancel_message: return "Order Partial Cancel Message";
            case enum_type::order_cancel_all_message: return "Order Cancel All Message";
            case enum_type::order_executed_message: return "Order Executed Message";
            case enum_type::trade_message: return "Trade Message";
            case enum_type::trade_cancel_message: return "Trade Cancel Message";
            case enum_type::trade_correct_message: return "Trade Correct Message";
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
            set(enum_type::trade_correct_message);
    }

  protected:
    enum_type value;
};
}
