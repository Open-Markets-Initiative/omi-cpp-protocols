#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

// iex_tp_message_type
struct iex_tp_message_type {

    enum class enum_type : char {
        system_event_message = 'S',
        security_directory_message = 'D',
        trading_status_message = 'H',
        retail_liquidity_indicator_message = 'I',
        operational_halt_status_message = 'O',
        short_sale_price_test_status_message = 'P',
        security_event_message = 'E',
        add_order_message = 'a',
        order_modify_message = 'M',
        order_delete_message = 'R',
        order_executed_message = 'L',
        trade_message = 'T',
        trade_break_message = 'B',
        clear_book_message = 'C'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 14> from_string_map = {{
        {"Add Order Message", enum_type::add_order_message},
        {"Clear Book Message", enum_type::clear_book_message},
        {"Operational Halt Status Message", enum_type::operational_halt_status_message},
        {"Order Delete Message", enum_type::order_delete_message},
        {"Order Executed Message", enum_type::order_executed_message},
        {"Order Modify Message", enum_type::order_modify_message},
        {"Retail Liquidity Indicator Message", enum_type::retail_liquidity_indicator_message},
        {"Security Directory Message", enum_type::security_directory_message},
        {"Security Event Message", enum_type::security_event_message},
        {"Short Sale Price Test Status Message", enum_type::short_sale_price_test_status_message},
        {"System Event Message", enum_type::system_event_message},
        {"Trade Break Message", enum_type::trade_break_message},
        {"Trade Message", enum_type::trade_message},
        {"Trading Status Message", enum_type::trading_status_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::system_event_message: return "System Event Message";
            case enum_type::security_directory_message: return "Security Directory Message";
            case enum_type::trading_status_message: return "Trading Status Message";
            case enum_type::retail_liquidity_indicator_message: return "Retail Liquidity Indicator Message";
            case enum_type::operational_halt_status_message: return "Operational Halt Status Message";
            case enum_type::short_sale_price_test_status_message: return "Short Sale Price Test Status Message";
            case enum_type::security_event_message: return "Security Event Message";
            case enum_type::add_order_message: return "Add Order Message";
            case enum_type::order_modify_message: return "Order Modify Message";
            case enum_type::order_delete_message: return "Order Delete Message";
            case enum_type::order_executed_message: return "Order Executed Message";
            case enum_type::trade_message: return "Trade Message";
            case enum_type::trade_break_message: return "Trade Break Message";
            case enum_type::clear_book_message: return "Clear Book Message";
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

    static constexpr const char* name = "iex_tp_message_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<iex_tp_message_type::enum_type>;
    using storage_type = result_type;

    constexpr iex_tp_message_type()
     : value{ enum_type::system_event_message } {}

    constexpr iex_tp_message_type(enum_type v)
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
            set(enum_type::clear_book_message);
    }

  protected:
    enum_type value;
};
}
