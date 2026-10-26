#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// message_type
struct message_type {

    enum class enum_type : std::uint8_t {
        time_reference_message = 0xB1,
        time_message = 0x20,
        unit_clear_message = 0x97,
        futures_instrument_definition_message = 0xBB,
        futures_variance_symbol_mapping_message = 0xFA,
        price_limits_message = 0xBE,
        add_order_long_message = 0x21,
        add_order_short_message = 0x22,
        order_executed_message = 0x23,
        reduce_size_long_message = 0x25,
        reduce_size_short_message = 0x26,
        modify_order_long_message = 0x27,
        modify_order_short_message = 0x28,
        delete_order_message = 0x29,
        trade_long_message = 0x2A,
        trade_short_message = 0x2B,
        transaction_begin_message = 0xBC,
        transaction_end_message = 0xBD,
        trade_break_message = 0x2C,
        settlement_message = 0xB9,
        open_interest_message = 0xD3,
        end_of_day_summary_message = 0xBA,
        trading_status_message = 0x31,
        end_of_session_message = 0x2D
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 24> from_string_map = {{
        {"Add Order Long Message", enum_type::add_order_long_message},
        {"Add Order Short Message", enum_type::add_order_short_message},
        {"Delete Order Message", enum_type::delete_order_message},
        {"End Of Day Summary Message", enum_type::end_of_day_summary_message},
        {"End Of Session Message", enum_type::end_of_session_message},
        {"Futures Instrument Definition Message", enum_type::futures_instrument_definition_message},
        {"Futures Variance Symbol Mapping Message", enum_type::futures_variance_symbol_mapping_message},
        {"Modify Order Long Message", enum_type::modify_order_long_message},
        {"Modify Order Short Message", enum_type::modify_order_short_message},
        {"Open Interest Message", enum_type::open_interest_message},
        {"Order Executed Message", enum_type::order_executed_message},
        {"Price Limits Message", enum_type::price_limits_message},
        {"Reduce Size Long Message", enum_type::reduce_size_long_message},
        {"Reduce Size Short Message", enum_type::reduce_size_short_message},
        {"Settlement Message", enum_type::settlement_message},
        {"Time Message", enum_type::time_message},
        {"Time Reference Message", enum_type::time_reference_message},
        {"Trade Break Message", enum_type::trade_break_message},
        {"Trade Long Message", enum_type::trade_long_message},
        {"Trade Short Message", enum_type::trade_short_message},
        {"Trading Status Message", enum_type::trading_status_message},
        {"Transaction Begin Message", enum_type::transaction_begin_message},
        {"Transaction End Message", enum_type::transaction_end_message},
        {"Unit Clear Message", enum_type::unit_clear_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::time_reference_message: return "Time Reference Message";
            case enum_type::time_message: return "Time Message";
            case enum_type::unit_clear_message: return "Unit Clear Message";
            case enum_type::futures_instrument_definition_message: return "Futures Instrument Definition Message";
            case enum_type::futures_variance_symbol_mapping_message: return "Futures Variance Symbol Mapping Message";
            case enum_type::price_limits_message: return "Price Limits Message";
            case enum_type::add_order_long_message: return "Add Order Long Message";
            case enum_type::add_order_short_message: return "Add Order Short Message";
            case enum_type::order_executed_message: return "Order Executed Message";
            case enum_type::reduce_size_long_message: return "Reduce Size Long Message";
            case enum_type::reduce_size_short_message: return "Reduce Size Short Message";
            case enum_type::modify_order_long_message: return "Modify Order Long Message";
            case enum_type::modify_order_short_message: return "Modify Order Short Message";
            case enum_type::delete_order_message: return "Delete Order Message";
            case enum_type::trade_long_message: return "Trade Long Message";
            case enum_type::trade_short_message: return "Trade Short Message";
            case enum_type::transaction_begin_message: return "Transaction Begin Message";
            case enum_type::transaction_end_message: return "Transaction End Message";
            case enum_type::trade_break_message: return "Trade Break Message";
            case enum_type::settlement_message: return "Settlement Message";
            case enum_type::open_interest_message: return "Open Interest Message";
            case enum_type::end_of_day_summary_message: return "End Of Day Summary Message";
            case enum_type::trading_status_message: return "Trading Status Message";
            case enum_type::end_of_session_message: return "End Of Session Message";
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
            set(enum_type::end_of_session_message);
    }

  protected:
    enum_type value;
};
}
