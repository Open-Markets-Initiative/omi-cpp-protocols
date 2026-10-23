#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// message_type
struct message_type {

    enum class enum_type : std::uint8_t {
        system_time_message = 49,
        symbol_update_message = 1,
        system_state_message = 83,
        security_trading_status_notification_message = 4,
        symbol_clear_message = 5,
        add_order_message = 20,
        modify_order_message = 21,
        delete_order_message = 23,
        order_execution_message = 24,
        trade_message = 10,
        trade_cancel_message = 11
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 11> from_string_map = {{
        {"Add Order Message", enum_type::add_order_message},
        {"Delete Order Message", enum_type::delete_order_message},
        {"Modify Order Message", enum_type::modify_order_message},
        {"Order Execution Message", enum_type::order_execution_message},
        {"Security Trading Status Notification Message", enum_type::security_trading_status_notification_message},
        {"Symbol Clear Message", enum_type::symbol_clear_message},
        {"Symbol Update Message", enum_type::symbol_update_message},
        {"System State Message", enum_type::system_state_message},
        {"System Time Message", enum_type::system_time_message},
        {"Trade Cancel Message", enum_type::trade_cancel_message},
        {"Trade Message", enum_type::trade_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::system_time_message: return "System Time Message";
            case enum_type::symbol_update_message: return "Symbol Update Message";
            case enum_type::system_state_message: return "System State Message";
            case enum_type::security_trading_status_notification_message: return "Security Trading Status Notification Message";
            case enum_type::symbol_clear_message: return "Symbol Clear Message";
            case enum_type::add_order_message: return "Add Order Message";
            case enum_type::modify_order_message: return "Modify Order Message";
            case enum_type::delete_order_message: return "Delete Order Message";
            case enum_type::order_execution_message: return "Order Execution Message";
            case enum_type::trade_message: return "Trade Message";
            case enum_type::trade_cancel_message: return "Trade Cancel Message";
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
            set(enum_type::trade_cancel_message);
    }

  protected:
    enum_type value;
};
}
