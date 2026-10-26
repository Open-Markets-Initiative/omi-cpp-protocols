#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// symbol_state
struct symbol_state {

    enum class enum_type : char {
        closed = 'C',
        pre_open = 'P',
        opening_auction = 'O',
        continuous_trading = 'T',
        scheduled_intraday_auction = 'I',
        closing_auction = 'L',
        post_trade = 'S',
        halted = 'H',
        auction_period = 'Q',
        trading_at_closing_price = 'A'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 10> from_string_map = {{
        {"Auction Period", enum_type::auction_period},
        {"Closed", enum_type::closed},
        {"Closing Auction", enum_type::closing_auction},
        {"Continuous Trading", enum_type::continuous_trading},
        {"Halted", enum_type::halted},
        {"Opening Auction", enum_type::opening_auction},
        {"Post Trade", enum_type::post_trade},
        {"Pre Open", enum_type::pre_open},
        {"Scheduled Intraday Auction", enum_type::scheduled_intraday_auction},
        {"Trading At Closing Price", enum_type::trading_at_closing_price}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::closed: return "Closed";
            case enum_type::pre_open: return "Pre Open";
            case enum_type::opening_auction: return "Opening Auction";
            case enum_type::continuous_trading: return "Continuous Trading";
            case enum_type::scheduled_intraday_auction: return "Scheduled Intraday Auction";
            case enum_type::closing_auction: return "Closing Auction";
            case enum_type::post_trade: return "Post Trade";
            case enum_type::halted: return "Halted";
            case enum_type::auction_period: return "Auction Period";
            case enum_type::trading_at_closing_price: return "Trading At Closing Price";
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

    static constexpr const char* name = "symbol_state";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<symbol_state::enum_type>;
    using storage_type = result_type;

    constexpr symbol_state()
     : value{ enum_type{} } {}

    constexpr symbol_state(enum_type v)
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
            set(enum_type::trading_at_closing_price);
    }

  protected:
    enum_type value;
};
}
