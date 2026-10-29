#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// message_type
struct message_type {

    enum class enum_type : char {
        system_event_message = 'S',
        complex_strategy_directory_message = 'R',
        strategy_trading_action_message = 'H',
        strategy_open_closed_message = 'O',
        complex_strategy_order_on_book_message = 'L',
        complex_strategy_auction_message = 'J'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 6> from_string_map = {{
        {"Complex Strategy Auction Message", enum_type::complex_strategy_auction_message},
        {"Complex Strategy Directory Message", enum_type::complex_strategy_directory_message},
        {"Complex Strategy Order On Book Message", enum_type::complex_strategy_order_on_book_message},
        {"Strategy Open Closed Message", enum_type::strategy_open_closed_message},
        {"Strategy Trading Action Message", enum_type::strategy_trading_action_message},
        {"System Event Message", enum_type::system_event_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::system_event_message: return "System Event Message";
            case enum_type::complex_strategy_directory_message: return "Complex Strategy Directory Message";
            case enum_type::strategy_trading_action_message: return "Strategy Trading Action Message";
            case enum_type::strategy_open_closed_message: return "Strategy Open Closed Message";
            case enum_type::complex_strategy_order_on_book_message: return "Complex Strategy Order On Book Message";
            case enum_type::complex_strategy_auction_message: return "Complex Strategy Auction Message";
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
            set(enum_type::complex_strategy_auction_message);
    }

  protected:
    enum_type value;
};
}
