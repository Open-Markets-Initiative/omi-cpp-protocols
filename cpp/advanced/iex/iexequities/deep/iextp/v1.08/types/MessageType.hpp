#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace iex::iexequities::deep::iextp::v1_08 {

// message_type
struct message_type {

    enum class enum_type : char {
        system_event_message = 'S',
        security_directory_message = 'D',
        trading_status_message = 'H',
        retail_liquidity_indicator_message = 'I',
        operational_halt_status_message = 'O',
        short_sale_price_test_status_message = 'P',
        security_event_message = 'E',
        price_level_buy_update_message = '8',
        price_level_sell_update_message = '5',
        trade_report_message = 'T',
        official_price_message = 'X',
        trade_break_message = 'B',
        auction_information_message = 'A'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 13> from_string_map = {{
        {"Auction Information Message", enum_type::auction_information_message},
        {"Official Price Message", enum_type::official_price_message},
        {"Operational Halt Status Message", enum_type::operational_halt_status_message},
        {"Price Level Buy Update Message", enum_type::price_level_buy_update_message},
        {"Price Level Sell Update Message", enum_type::price_level_sell_update_message},
        {"Retail Liquidity Indicator Message", enum_type::retail_liquidity_indicator_message},
        {"Security Directory Message", enum_type::security_directory_message},
        {"Security Event Message", enum_type::security_event_message},
        {"Short Sale Price Test Status Message", enum_type::short_sale_price_test_status_message},
        {"System Event Message", enum_type::system_event_message},
        {"Trade Break Message", enum_type::trade_break_message},
        {"Trade Report Message", enum_type::trade_report_message},
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
            case enum_type::price_level_buy_update_message: return "Price Level Buy Update Message";
            case enum_type::price_level_sell_update_message: return "Price Level Sell Update Message";
            case enum_type::trade_report_message: return "Trade Report Message";
            case enum_type::official_price_message: return "Official Price Message";
            case enum_type::trade_break_message: return "Trade Break Message";
            case enum_type::auction_information_message: return "Auction Information Message";
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
            set(enum_type::auction_information_message);
    }

  protected:
    enum_type value;
};
}
