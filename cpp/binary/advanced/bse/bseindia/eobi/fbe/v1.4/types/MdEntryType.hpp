#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// md_entry_type
struct md_entry_type {

    enum class enum_type : std::uint8_t {
        trade = 2,
        opening_price = 4,
        closing_price = 5,
        high_price = 7,
        low_price = 8,
        previous_closing_price = 101,
        opening_auction = 200,
        intraday_auction = 201,
        circuit_breaker_auction = 202,
        closing_auction = 203,
        upper_ckt_limit = 204,
        lower_ckt_limit = 205,
        gross_trade_amt = 206,
        upper_exec_limit = 208,
        lower_exec_limit = 209
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 15> from_string_map = {{
        {"Circuit Breaker Auction", enum_type::circuit_breaker_auction},
        {"Closing Auction", enum_type::closing_auction},
        {"Closing Price", enum_type::closing_price},
        {"Gross Trade Amt", enum_type::gross_trade_amt},
        {"High Price", enum_type::high_price},
        {"Intraday Auction", enum_type::intraday_auction},
        {"Low Price", enum_type::low_price},
        {"Lower Ckt Limit", enum_type::lower_ckt_limit},
        {"Lower Exec Limit", enum_type::lower_exec_limit},
        {"Opening Auction", enum_type::opening_auction},
        {"Opening Price", enum_type::opening_price},
        {"Previous Closing Price", enum_type::previous_closing_price},
        {"Trade", enum_type::trade},
        {"Upper Ckt Limit", enum_type::upper_ckt_limit},
        {"Upper Exec Limit", enum_type::upper_exec_limit}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::trade: return "Trade";
            case enum_type::opening_price: return "Opening Price";
            case enum_type::closing_price: return "Closing Price";
            case enum_type::high_price: return "High Price";
            case enum_type::low_price: return "Low Price";
            case enum_type::previous_closing_price: return "Previous Closing Price";
            case enum_type::opening_auction: return "Opening Auction";
            case enum_type::intraday_auction: return "Intraday Auction";
            case enum_type::circuit_breaker_auction: return "Circuit Breaker Auction";
            case enum_type::closing_auction: return "Closing Auction";
            case enum_type::upper_ckt_limit: return "Upper Ckt Limit";
            case enum_type::lower_ckt_limit: return "Lower Ckt Limit";
            case enum_type::gross_trade_amt: return "Gross Trade Amt";
            case enum_type::upper_exec_limit: return "Upper Exec Limit";
            case enum_type::lower_exec_limit: return "Lower Exec Limit";
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

    static constexpr const char* name = "md_entry_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<md_entry_type::enum_type>;
    using storage_type = result_type;

    constexpr md_entry_type()
     : value{ enum_type{} } {}

    constexpr md_entry_type(enum_type v)
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
            set(enum_type::lower_exec_limit);
    }

  protected:
    enum_type value;
};
}
