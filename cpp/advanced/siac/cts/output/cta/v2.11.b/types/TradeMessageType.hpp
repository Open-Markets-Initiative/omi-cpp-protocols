#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_11_b {

// trade_message_type
struct trade_message_type {

    enum class enum_type : char {
        auction_status = 'A',
        trade_correction = 'C',
        fractional_trade_correction = 'O',
        long_trade = 'L',
        fractional_long_trade = 'R',
        trading_status = 'S',
        short_trade = 'T',
        fractional_short_trade = 'H',
        trade_cancel_error = 'X',
        fractional_trade_cancel_error = 'E'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 10> from_string_map = {{
        {"Auction Status", enum_type::auction_status},
        {"Fractional Long Trade", enum_type::fractional_long_trade},
        {"Fractional Short Trade", enum_type::fractional_short_trade},
        {"Fractional Trade Cancel Error", enum_type::fractional_trade_cancel_error},
        {"Fractional Trade Correction", enum_type::fractional_trade_correction},
        {"Long Trade", enum_type::long_trade},
        {"Short Trade", enum_type::short_trade},
        {"Trade Cancel Error", enum_type::trade_cancel_error},
        {"Trade Correction", enum_type::trade_correction},
        {"Trading Status", enum_type::trading_status}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::auction_status: return "Auction Status";
            case enum_type::trade_correction: return "Trade Correction";
            case enum_type::fractional_trade_correction: return "Fractional Trade Correction";
            case enum_type::long_trade: return "Long Trade";
            case enum_type::fractional_long_trade: return "Fractional Long Trade";
            case enum_type::trading_status: return "Trading Status";
            case enum_type::short_trade: return "Short Trade";
            case enum_type::fractional_short_trade: return "Fractional Short Trade";
            case enum_type::trade_cancel_error: return "Trade Cancel Error";
            case enum_type::fractional_trade_cancel_error: return "Fractional Trade Cancel Error";
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
            set(enum_type::fractional_trade_cancel_error);
    }

  protected:
    enum_type value;
};
}
