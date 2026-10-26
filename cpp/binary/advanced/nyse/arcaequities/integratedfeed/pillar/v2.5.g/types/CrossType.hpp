#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g {

// cross_type
struct cross_type {

    enum class enum_type : char {
        market_center_early_opening_auction = 'E',
        market_center_opening_auction = 'O',
        market_center_reopening_auction = '5',
        market_center_closing_auction = '6'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Market Center Closing Auction", enum_type::market_center_closing_auction},
        {"Market Center Early Opening Auction", enum_type::market_center_early_opening_auction},
        {"Market Center Opening Auction", enum_type::market_center_opening_auction},
        {"Market Center Reopening Auction", enum_type::market_center_reopening_auction}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::market_center_early_opening_auction: return "Market Center Early Opening Auction";
            case enum_type::market_center_opening_auction: return "Market Center Opening Auction";
            case enum_type::market_center_reopening_auction: return "Market Center Reopening Auction";
            case enum_type::market_center_closing_auction: return "Market Center Closing Auction";
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

    static constexpr const char* name = "cross_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<cross_type::enum_type>;
    using storage_type = result_type;

    constexpr cross_type()
     : value{ enum_type{} } {}

    constexpr cross_type(enum_type v)
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
            set(enum_type::market_center_closing_auction);
    }

  protected:
    enum_type value;
};
}
