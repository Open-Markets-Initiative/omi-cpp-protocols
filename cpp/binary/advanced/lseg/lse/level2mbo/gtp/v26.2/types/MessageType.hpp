#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

// message_type
struct message_type {

    enum class enum_type : std::uint8_t {
        system_event_message = 0x53,
        instrument_directory_message = 0x70,
        instrument_status_message = 0x48,
        add_order_mbo_message = 0x41,
        add_order_short_mbo_message = 0x65,
        order_book_clear_message = 0x79,
        trade_message = 0x50,
        statistics_message = 0x77,
        statistics_update_message = 0x6A
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 9> from_string_map = {{
        {"Add Order Mbo Message", enum_type::add_order_mbo_message},
        {"Add Order Short Mbo Message", enum_type::add_order_short_mbo_message},
        {"Instrument Directory Message", enum_type::instrument_directory_message},
        {"Instrument Status Message", enum_type::instrument_status_message},
        {"Order Book Clear Message", enum_type::order_book_clear_message},
        {"Statistics Message", enum_type::statistics_message},
        {"Statistics Update Message", enum_type::statistics_update_message},
        {"System Event Message", enum_type::system_event_message},
        {"Trade Message", enum_type::trade_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::system_event_message: return "System Event Message";
            case enum_type::instrument_directory_message: return "Instrument Directory Message";
            case enum_type::instrument_status_message: return "Instrument Status Message";
            case enum_type::add_order_mbo_message: return "Add Order Mbo Message";
            case enum_type::add_order_short_mbo_message: return "Add Order Short Mbo Message";
            case enum_type::order_book_clear_message: return "Order Book Clear Message";
            case enum_type::trade_message: return "Trade Message";
            case enum_type::statistics_message: return "Statistics Message";
            case enum_type::statistics_update_message: return "Statistics Update Message";
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
            set(enum_type::statistics_update_message);
    }

  protected:
    enum_type value;
};
}
