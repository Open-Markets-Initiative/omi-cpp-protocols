#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// message_type
struct message_type {

    enum class enum_type : std::uint8_t {
        time_message = 0x54,
        system_event_message = 0x53,
        symbol_directory_message = 0x52,
        symbol_status_message = 0x48,
        add_order_message = 0x41,
        add_attributed_order_message = 0x46,
        order_deleted_message = 0x44,
        order_modified_message = 0x55,
        order_book_clear_message = 0x79,
        order_executed_message = 0x45,
        order_executed_with_price_size_message = 0x43,
        trade_message = 0x50,
        auction_trade_message = 0x51,
        auction_info_message = 0x49,
        statistics_message = 0x77,
        top_of_book_message = 0x71
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 16> from_string_map = {{
        {"Add Attributed Order Message", enum_type::add_attributed_order_message},
        {"Add Order Message", enum_type::add_order_message},
        {"Auction Info Message", enum_type::auction_info_message},
        {"Auction Trade Message", enum_type::auction_trade_message},
        {"Order Book Clear Message", enum_type::order_book_clear_message},
        {"Order Deleted Message", enum_type::order_deleted_message},
        {"Order Executed Message", enum_type::order_executed_message},
        {"Order Executed With Price Size Message", enum_type::order_executed_with_price_size_message},
        {"Order Modified Message", enum_type::order_modified_message},
        {"Statistics Message", enum_type::statistics_message},
        {"Symbol Directory Message", enum_type::symbol_directory_message},
        {"Symbol Status Message", enum_type::symbol_status_message},
        {"System Event Message", enum_type::system_event_message},
        {"Time Message", enum_type::time_message},
        {"Top Of Book Message", enum_type::top_of_book_message},
        {"Trade Message", enum_type::trade_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::time_message: return "Time Message";
            case enum_type::system_event_message: return "System Event Message";
            case enum_type::symbol_directory_message: return "Symbol Directory Message";
            case enum_type::symbol_status_message: return "Symbol Status Message";
            case enum_type::add_order_message: return "Add Order Message";
            case enum_type::add_attributed_order_message: return "Add Attributed Order Message";
            case enum_type::order_deleted_message: return "Order Deleted Message";
            case enum_type::order_modified_message: return "Order Modified Message";
            case enum_type::order_book_clear_message: return "Order Book Clear Message";
            case enum_type::order_executed_message: return "Order Executed Message";
            case enum_type::order_executed_with_price_size_message: return "Order Executed With Price Size Message";
            case enum_type::trade_message: return "Trade Message";
            case enum_type::auction_trade_message: return "Auction Trade Message";
            case enum_type::auction_info_message: return "Auction Info Message";
            case enum_type::statistics_message: return "Statistics Message";
            case enum_type::top_of_book_message: return "Top Of Book Message";
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
            set(enum_type::top_of_book_message);
    }

  protected:
    enum_type value;
};
}
