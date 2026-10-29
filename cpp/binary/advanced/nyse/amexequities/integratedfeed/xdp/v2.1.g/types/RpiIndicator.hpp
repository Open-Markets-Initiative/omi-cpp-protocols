#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

// rpi_indicator
struct rpi_indicator {

    enum class enum_type : char {
        no_retail_interest = ' ',
        interest_on_bid = 'A',
        interest_on_offer = 'B',
        interest_on_bid_and_offer = 'C'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Interest On Bid", enum_type::interest_on_bid},
        {"Interest On Bid And Offer", enum_type::interest_on_bid_and_offer},
        {"Interest On Offer", enum_type::interest_on_offer},
        {"No Retail Interest", enum_type::no_retail_interest}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::no_retail_interest: return "No Retail Interest";
            case enum_type::interest_on_bid: return "Interest On Bid";
            case enum_type::interest_on_offer: return "Interest On Offer";
            case enum_type::interest_on_bid_and_offer: return "Interest On Bid And Offer";
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
            set(enum_type::interest_on_bid_and_offer);
    }

  protected:
    enum_type value;
};
}
