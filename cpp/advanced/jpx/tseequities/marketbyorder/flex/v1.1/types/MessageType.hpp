#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// message_type
struct message_type {

    enum class enum_type : char {
        seconds_timestamp_message = 'T',
        trading_status_message = 'O',
        execution_summary_message = 'K',
        add_order_message = 'A',
        order_executed_message = 'E',
        order_executed_with_price_message = 'C',
        order_delete_message = 'D',
        reset_message = 'R',
        communication_control_message = 'L'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 9> from_string_map = {{
        {"Add Order Message", enum_type::add_order_message},
        {"Communication Control Message", enum_type::communication_control_message},
        {"Execution Summary Message", enum_type::execution_summary_message},
        {"Order Delete Message", enum_type::order_delete_message},
        {"Order Executed Message", enum_type::order_executed_message},
        {"Order Executed With Price Message", enum_type::order_executed_with_price_message},
        {"Reset Message", enum_type::reset_message},
        {"Seconds Timestamp Message", enum_type::seconds_timestamp_message},
        {"Trading Status Message", enum_type::trading_status_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::seconds_timestamp_message: return "Seconds Timestamp Message";
            case enum_type::trading_status_message: return "Trading Status Message";
            case enum_type::execution_summary_message: return "Execution Summary Message";
            case enum_type::add_order_message: return "Add Order Message";
            case enum_type::order_executed_message: return "Order Executed Message";
            case enum_type::order_executed_with_price_message: return "Order Executed With Price Message";
            case enum_type::order_delete_message: return "Order Delete Message";
            case enum_type::reset_message: return "Reset Message";
            case enum_type::communication_control_message: return "Communication Control Message";
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
     : value{ enum_type::seconds_timestamp_message } {}

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
            set(enum_type::communication_control_message);
    }

  protected:
    enum_type value;
};
}
