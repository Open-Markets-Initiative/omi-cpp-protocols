#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cqs::output::cta::v1_91 {

// quote_condition
struct quote_condition {

    enum class enum_type : char {
        quote_condition_not_applicable = ' ',
        slow_quote_on_offer_side = 'A',
        slow_quote_on_bid_side = 'B',
        closing = 'C',
        slow_quote_due_to_lrp_or_gap_quote_on_the_bid_side = 'E',
        slow_quote_due_to_lrp_or_gap_quote_on_the_offer_side = 'F',
        slow_quote_on_the_bid_and_offer_sides = 'H',
        closed_market_maker = 'L',
        non_firm_quote = 'N',
        opening_quote = 'O',
        regular_finra_open = 'R',
        slow_quote_due_to_liquidity_replenishment_point_or_gap_quote_on_both_the_bid_and_offer_sides = 'U',
        slow_quote_due_to_set_slow_list_on_both_the_bid_and_offer_sides = 'W',
        on_demand_intra_day_auction = '4'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 14> from_string_map = {{
        {"Closed Market Maker", enum_type::closed_market_maker},
        {"Closing", enum_type::closing},
        {"Non Firm Quote", enum_type::non_firm_quote},
        {"On Demand Intra Day Auction", enum_type::on_demand_intra_day_auction},
        {"Opening Quote", enum_type::opening_quote},
        {"Quote Condition Not Applicable", enum_type::quote_condition_not_applicable},
        {"Regular Finra Open", enum_type::regular_finra_open},
        {"Slow Quote Due To Liquidity Replenishment Point Or Gap Quote On Both The Bid And Offer Sides", enum_type::slow_quote_due_to_liquidity_replenishment_point_or_gap_quote_on_both_the_bid_and_offer_sides},
        {"Slow Quote Due To Lrp Or Gap Quote On The Bid Side", enum_type::slow_quote_due_to_lrp_or_gap_quote_on_the_bid_side},
        {"Slow Quote Due To Lrp Or Gap Quote On The Offer Side", enum_type::slow_quote_due_to_lrp_or_gap_quote_on_the_offer_side},
        {"Slow Quote Due To Set Slow List On Both The Bid And Offer Sides", enum_type::slow_quote_due_to_set_slow_list_on_both_the_bid_and_offer_sides},
        {"Slow Quote On Bid Side", enum_type::slow_quote_on_bid_side},
        {"Slow Quote On Offer Side", enum_type::slow_quote_on_offer_side},
        {"Slow Quote On The Bid And Offer Sides", enum_type::slow_quote_on_the_bid_and_offer_sides}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::quote_condition_not_applicable: return "Quote Condition Not Applicable";
            case enum_type::slow_quote_on_offer_side: return "Slow Quote On Offer Side";
            case enum_type::slow_quote_on_bid_side: return "Slow Quote On Bid Side";
            case enum_type::closing: return "Closing";
            case enum_type::slow_quote_due_to_lrp_or_gap_quote_on_the_bid_side: return "Slow Quote Due To Lrp Or Gap Quote On The Bid Side";
            case enum_type::slow_quote_due_to_lrp_or_gap_quote_on_the_offer_side: return "Slow Quote Due To Lrp Or Gap Quote On The Offer Side";
            case enum_type::slow_quote_on_the_bid_and_offer_sides: return "Slow Quote On The Bid And Offer Sides";
            case enum_type::closed_market_maker: return "Closed Market Maker";
            case enum_type::non_firm_quote: return "Non Firm Quote";
            case enum_type::opening_quote: return "Opening Quote";
            case enum_type::regular_finra_open: return "Regular Finra Open";
            case enum_type::slow_quote_due_to_liquidity_replenishment_point_or_gap_quote_on_both_the_bid_and_offer_sides: return "Slow Quote Due To Liquidity Replenishment Point Or Gap Quote On Both The Bid And Offer Sides";
            case enum_type::slow_quote_due_to_set_slow_list_on_both_the_bid_and_offer_sides: return "Slow Quote Due To Set Slow List On Both The Bid And Offer Sides";
            case enum_type::on_demand_intra_day_auction: return "On Demand Intra Day Auction";
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

    static constexpr const char* name = "quote_condition";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<quote_condition::enum_type>;
    using storage_type = result_type;

    constexpr quote_condition()
     : value{ enum_type{} } {}

    constexpr quote_condition(enum_type v)
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
            set(enum_type::on_demand_intra_day_auction);
    }

  protected:
    enum_type value;
};
}
