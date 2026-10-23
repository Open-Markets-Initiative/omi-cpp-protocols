#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

// statistic_type
struct statistic_type {

    enum class enum_type : std::uint16_t {
        indicative_auction_uncrossing_data = 1,
        official_opening_price = 2,
        official_closing_price = 3,
        trade_high_on_book = 4,
        trade_low_on_book = 5,
        trade_high_all_trades = 6,
        trade_low_all_trades = 7,
        fifty_two_week_trade_high_all_trades = 8,
        fifty_two_week_trade_low_all_trades = 9,
        best_closing_bid = 10,
        best_closing_ask = 11,
        static_reference_price = 16,
        dynamic_reference_price = 17
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 13> from_string_map = {{
        {"Best Closing Ask", enum_type::best_closing_ask},
        {"Best Closing Bid", enum_type::best_closing_bid},
        {"Dynamic Reference Price", enum_type::dynamic_reference_price},
        {"Fifty Two Week Trade High All Trades", enum_type::fifty_two_week_trade_high_all_trades},
        {"Fifty Two Week Trade Low All Trades", enum_type::fifty_two_week_trade_low_all_trades},
        {"Indicative Auction Uncrossing Data", enum_type::indicative_auction_uncrossing_data},
        {"Official Closing Price", enum_type::official_closing_price},
        {"Official Opening Price", enum_type::official_opening_price},
        {"Static Reference Price", enum_type::static_reference_price},
        {"Trade High All Trades", enum_type::trade_high_all_trades},
        {"Trade High On Book", enum_type::trade_high_on_book},
        {"Trade Low All Trades", enum_type::trade_low_all_trades},
        {"Trade Low On Book", enum_type::trade_low_on_book}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::indicative_auction_uncrossing_data: return "Indicative Auction Uncrossing Data";
            case enum_type::official_opening_price: return "Official Opening Price";
            case enum_type::official_closing_price: return "Official Closing Price";
            case enum_type::trade_high_on_book: return "Trade High On Book";
            case enum_type::trade_low_on_book: return "Trade Low On Book";
            case enum_type::trade_high_all_trades: return "Trade High All Trades";
            case enum_type::trade_low_all_trades: return "Trade Low All Trades";
            case enum_type::fifty_two_week_trade_high_all_trades: return "Fifty Two Week Trade High All Trades";
            case enum_type::fifty_two_week_trade_low_all_trades: return "Fifty Two Week Trade Low All Trades";
            case enum_type::best_closing_bid: return "Best Closing Bid";
            case enum_type::best_closing_ask: return "Best Closing Ask";
            case enum_type::static_reference_price: return "Static Reference Price";
            case enum_type::dynamic_reference_price: return "Dynamic Reference Price";
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

    static constexpr const char* name = "statistic_type";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;

    using result_type = required<statistic_type::enum_type>;
    using storage_type = result_type;

    constexpr statistic_type()
     : value{ enum_type{} } {}

    constexpr statistic_type(enum_type v)
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
            set(enum_type::dynamic_reference_price);
    }

  protected:
    enum_type value;
};
}
