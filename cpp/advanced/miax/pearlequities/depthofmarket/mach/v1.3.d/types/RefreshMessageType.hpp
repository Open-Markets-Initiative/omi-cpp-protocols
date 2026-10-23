#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// refresh_message_type
struct refresh_message_type {

    enum class enum_type : char {
        symbol_update_refresh = 'S',
        security_trading_status_refresh = 't',
        system_state_refresh = 's',
        order_book_refresh = 'O'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Order Book Refresh", enum_type::order_book_refresh},
        {"Security Trading Status Refresh", enum_type::security_trading_status_refresh},
        {"Symbol Update Refresh", enum_type::symbol_update_refresh},
        {"System State Refresh", enum_type::system_state_refresh}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::symbol_update_refresh: return "Symbol Update Refresh";
            case enum_type::security_trading_status_refresh: return "Security Trading Status Refresh";
            case enum_type::system_state_refresh: return "System State Refresh";
            case enum_type::order_book_refresh: return "Order Book Refresh";
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

    static constexpr const char* name = "refresh_message_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<refresh_message_type::enum_type>;
    using storage_type = result_type;

    constexpr refresh_message_type()
     : value{ enum_type{} } {}

    constexpr refresh_message_type(enum_type v)
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
            set(enum_type::order_book_refresh);
    }

  protected:
    enum_type value;
};
}
