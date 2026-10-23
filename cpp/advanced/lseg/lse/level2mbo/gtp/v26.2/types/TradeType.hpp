#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

// trade_type
struct trade_type {

    enum class enum_type : std::uint8_t {
        regular_or_continuous_trade = 0,
        auction_trade_bulk = 1,
        auction_trade_individual = 2,
        onbook_trade_cancellation = 9,
        trade_correction = 11,
        rfq_trade = 22,
        rfq_trade_cancellation = 23,
        rfq_trade_correction = 24
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 8> from_string_map = {{
        {"Auction Trade Bulk", enum_type::auction_trade_bulk},
        {"Auction Trade Individual", enum_type::auction_trade_individual},
        {"Onbook Trade Cancellation", enum_type::onbook_trade_cancellation},
        {"Regular Or Continuous Trade", enum_type::regular_or_continuous_trade},
        {"Rfq Trade", enum_type::rfq_trade},
        {"Rfq Trade Cancellation", enum_type::rfq_trade_cancellation},
        {"Rfq Trade Correction", enum_type::rfq_trade_correction},
        {"Trade Correction", enum_type::trade_correction}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::regular_or_continuous_trade: return "Regular Or Continuous Trade";
            case enum_type::auction_trade_bulk: return "Auction Trade Bulk";
            case enum_type::auction_trade_individual: return "Auction Trade Individual";
            case enum_type::onbook_trade_cancellation: return "Onbook Trade Cancellation";
            case enum_type::trade_correction: return "Trade Correction";
            case enum_type::rfq_trade: return "Rfq Trade";
            case enum_type::rfq_trade_cancellation: return "Rfq Trade Cancellation";
            case enum_type::rfq_trade_correction: return "Rfq Trade Correction";
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

    static constexpr const char* name = "trade_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<trade_type::enum_type>;
    using storage_type = result_type;

    constexpr trade_type()
     : value{ enum_type{} } {}

    constexpr trade_type(enum_type v)
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
            set(enum_type::rfq_trade_correction);
    }

  protected:
    enum_type value;
};
}
