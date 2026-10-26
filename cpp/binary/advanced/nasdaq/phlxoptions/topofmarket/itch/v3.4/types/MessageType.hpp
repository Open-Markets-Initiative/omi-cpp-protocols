#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// message_type
struct message_type {

    enum class enum_type : char {
        timestamp_message = 'T',
        system_event_message = 'S',
        options_directory_message = 'D',
        trading_action_message = 'H',
        security_open_closed_message = 'O',
        short_best_bid_and_ask_update_message = 'q',
        long_best_bid_and_ask_update_message = 'Q',
        short_best_ask_update_message = 'a',
        short_best_bid_update_message = 'b',
        long_best_ask_update_message = 'A',
        long_best_bid_update_message = 'B',
        trade_report_message = 'R',
        broken_trade_report_message = 'X'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 13> from_string_map = {{
        {"Broken Trade Report Message", enum_type::broken_trade_report_message},
        {"Long Best Ask Update Message", enum_type::long_best_ask_update_message},
        {"Long Best Bid And Ask Update Message", enum_type::long_best_bid_and_ask_update_message},
        {"Long Best Bid Update Message", enum_type::long_best_bid_update_message},
        {"Options Directory Message", enum_type::options_directory_message},
        {"Security Open Closed Message", enum_type::security_open_closed_message},
        {"Short Best Ask Update Message", enum_type::short_best_ask_update_message},
        {"Short Best Bid And Ask Update Message", enum_type::short_best_bid_and_ask_update_message},
        {"Short Best Bid Update Message", enum_type::short_best_bid_update_message},
        {"System Event Message", enum_type::system_event_message},
        {"Timestamp Message", enum_type::timestamp_message},
        {"Trade Report Message", enum_type::trade_report_message},
        {"Trading Action Message", enum_type::trading_action_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::timestamp_message: return "Timestamp Message";
            case enum_type::system_event_message: return "System Event Message";
            case enum_type::options_directory_message: return "Options Directory Message";
            case enum_type::trading_action_message: return "Trading Action Message";
            case enum_type::security_open_closed_message: return "Security Open Closed Message";
            case enum_type::short_best_bid_and_ask_update_message: return "Short Best Bid And Ask Update Message";
            case enum_type::long_best_bid_and_ask_update_message: return "Long Best Bid And Ask Update Message";
            case enum_type::short_best_ask_update_message: return "Short Best Ask Update Message";
            case enum_type::short_best_bid_update_message: return "Short Best Bid Update Message";
            case enum_type::long_best_ask_update_message: return "Long Best Ask Update Message";
            case enum_type::long_best_bid_update_message: return "Long Best Bid Update Message";
            case enum_type::trade_report_message: return "Trade Report Message";
            case enum_type::broken_trade_report_message: return "Broken Trade Report Message";
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
            set(enum_type::broken_trade_report_message);
    }

  protected:
    enum_type value;
};
}
