#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

// auction_info
struct auction_info {

    enum class enum_type : char {
        not_applicable = '0',
        buy_imbalance = 'B',
        no_imbalance = 'N',
        insufficient_orders_for_auction = 'O',
        sell_imbalance = 'S'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Buy Imbalance", enum_type::buy_imbalance},
        {"Insufficient Orders For Auction", enum_type::insufficient_orders_for_auction},
        {"No Imbalance", enum_type::no_imbalance},
        {"Not Applicable", enum_type::not_applicable},
        {"Sell Imbalance", enum_type::sell_imbalance}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::not_applicable: return "Not Applicable";
            case enum_type::buy_imbalance: return "Buy Imbalance";
            case enum_type::no_imbalance: return "No Imbalance";
            case enum_type::insufficient_orders_for_auction: return "Insufficient Orders For Auction";
            case enum_type::sell_imbalance: return "Sell Imbalance";
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

    static constexpr const char* name = "auction_info";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<auction_info::enum_type>;
    using storage_type = result_type;

    constexpr auction_info()
     : value{ enum_type{} } {}

    constexpr auction_info(enum_type v)
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
            set(enum_type::sell_imbalance);
    }

  protected:
    enum_type value;
};
}
