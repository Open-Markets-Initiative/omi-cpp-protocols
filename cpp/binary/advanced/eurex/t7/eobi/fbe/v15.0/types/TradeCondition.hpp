#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

// trade_condition
struct trade_condition {

    enum class enum_type : std::uint16_t {
        implied_trade = 1,
        out_of_sequence = 107,
        midpoint_price = 155,
        trading_on_terms_of_issue = 156,
        special_auction = 596,
        trade_at_close = 624,
        retail = 743,
        auction_volume_discovery = 206,
        no_value = 0xFFFF
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 9> from_string_map = {{
        {"Auction Volume Discovery", enum_type::auction_volume_discovery},
        {"Implied Trade", enum_type::implied_trade},
        {"Midpoint Price", enum_type::midpoint_price},
        {"No Value", enum_type::no_value},
        {"Out Of Sequence", enum_type::out_of_sequence},
        {"Retail", enum_type::retail},
        {"Special Auction", enum_type::special_auction},
        {"Trade At Close", enum_type::trade_at_close},
        {"Trading On Terms Of Issue", enum_type::trading_on_terms_of_issue}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::implied_trade: return "Implied Trade";
            case enum_type::out_of_sequence: return "Out Of Sequence";
            case enum_type::midpoint_price: return "Midpoint Price";
            case enum_type::trading_on_terms_of_issue: return "Trading On Terms Of Issue";
            case enum_type::special_auction: return "Special Auction";
            case enum_type::trade_at_close: return "Trade At Close";
            case enum_type::retail: return "Retail";
            case enum_type::auction_volume_discovery: return "Auction Volume Discovery";
            case enum_type::no_value: return "No Value";
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

    static constexpr const char* name = "trade_condition";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;

    using result_type = required<trade_condition::enum_type>;
    using storage_type = result_type;

    constexpr trade_condition()
     : value{ enum_type{} } {}

    constexpr trade_condition(enum_type v)
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
            set(static_cast<enum_type>(0xFFFF));
    }

  protected:
    enum_type value;
};
}
