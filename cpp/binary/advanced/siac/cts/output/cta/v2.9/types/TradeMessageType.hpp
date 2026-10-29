#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_9 {

// trade_message_type
struct trade_message_type {

    enum class enum_type : char {
        auction_status_message = 'A',
        trade_correction_message = 'C',
        long_trade_message = 'L',
        trading_status_message = 'S',
        short_trade_message = 'T',
        trade_cancel_error_message = 'X'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 6> from_string_map = {{
        {"Auction Status Message", enum_type::auction_status_message},
        {"Long Trade Message", enum_type::long_trade_message},
        {"Short Trade Message", enum_type::short_trade_message},
        {"Trade Cancel Error Message", enum_type::trade_cancel_error_message},
        {"Trade Correction Message", enum_type::trade_correction_message},
        {"Trading Status Message", enum_type::trading_status_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::auction_status_message: return "Auction Status Message";
            case enum_type::trade_correction_message: return "Trade Correction Message";
            case enum_type::long_trade_message: return "Long Trade Message";
            case enum_type::trading_status_message: return "Trading Status Message";
            case enum_type::short_trade_message: return "Short Trade Message";
            case enum_type::trade_cancel_error_message: return "Trade Cancel Error Message";
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

    static constexpr const char* name = "trade_message_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<trade_message_type::enum_type>;
    using storage_type = result_type;

    constexpr trade_message_type()
     : value{ enum_type{} } {}

    constexpr trade_message_type(enum_type v)
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
            set(enum_type::trade_cancel_error_message);
    }

  protected:
    enum_type value;
};
}
