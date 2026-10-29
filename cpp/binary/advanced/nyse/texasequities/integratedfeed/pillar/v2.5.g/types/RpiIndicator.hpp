#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::texasequities::integratedfeed::pillar::v2_5_g {

// rpi_indicator
struct rpi_indicator {

    enum class enum_type : char {
        no_retail_interest_default = ' ',
        retail_interest_on_the_bid_side = 'A',
        retail_interest_on_the_offer_side = 'B',
        retail_interest_on_the_bid_and_offer_sides = 'C'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"No Retail Interest Default", enum_type::no_retail_interest_default},
        {"Retail Interest On The Bid And Offer Sides", enum_type::retail_interest_on_the_bid_and_offer_sides},
        {"Retail Interest On The Bid Side", enum_type::retail_interest_on_the_bid_side},
        {"Retail Interest On The Offer Side", enum_type::retail_interest_on_the_offer_side}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::no_retail_interest_default: return "No Retail Interest Default";
            case enum_type::retail_interest_on_the_bid_side: return "Retail Interest On The Bid Side";
            case enum_type::retail_interest_on_the_offer_side: return "Retail Interest On The Offer Side";
            case enum_type::retail_interest_on_the_bid_and_offer_sides: return "Retail Interest On The Bid And Offer Sides";
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

    static constexpr const char* name = "rpi_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<rpi_indicator::enum_type>;
    using storage_type = result_type;

    constexpr rpi_indicator()
     : value{ enum_type{} } {}

    constexpr rpi_indicator(enum_type v)
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
            set(enum_type::retail_interest_on_the_bid_and_offer_sides);
    }

  protected:
    enum_type value;
};
}
