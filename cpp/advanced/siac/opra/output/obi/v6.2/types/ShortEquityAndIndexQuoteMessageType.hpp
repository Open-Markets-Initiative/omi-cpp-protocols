#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::opra::output::obi::v6_2 {

// short_equity_and_index_quote_message_type
struct short_equity_and_index_quote_message_type {

    enum class enum_type : char {
        regular_trading = ' ',
        non_firm_quote = 'F',
        indicative_value = 'I',
        rotation = 'R',
        trading_halted = 'T',
        eligible_for_automatic_execution = 'A',
        bid_contains_customer_trading_interest = 'B',
        offer_contains_customer_trading_interest = 'O',
        both_bid_and_offer_contain_customer_trading_interest = 'C',
        offer_side_of_quote_not_firm_bid_side_firm = 'X',
        bid_side_of_quote_not_firm_offer_side_firm = 'Y'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 11> from_string_map = {{
        {"Bid Contains Customer Trading Interest", enum_type::bid_contains_customer_trading_interest},
        {"Bid Side Of Quote Not Firm Offer Side Firm", enum_type::bid_side_of_quote_not_firm_offer_side_firm},
        {"Both Bid And Offer Contain Customer Trading Interest", enum_type::both_bid_and_offer_contain_customer_trading_interest},
        {"Eligible For Automatic Execution", enum_type::eligible_for_automatic_execution},
        {"Indicative Value", enum_type::indicative_value},
        {"Non Firm Quote", enum_type::non_firm_quote},
        {"Offer Contains Customer Trading Interest", enum_type::offer_contains_customer_trading_interest},
        {"Offer Side Of Quote Not Firm Bid Side Firm", enum_type::offer_side_of_quote_not_firm_bid_side_firm},
        {"Regular Trading", enum_type::regular_trading},
        {"Rotation", enum_type::rotation},
        {"Trading Halted", enum_type::trading_halted}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::regular_trading: return "Regular Trading";
            case enum_type::non_firm_quote: return "Non Firm Quote";
            case enum_type::indicative_value: return "Indicative Value";
            case enum_type::rotation: return "Rotation";
            case enum_type::trading_halted: return "Trading Halted";
            case enum_type::eligible_for_automatic_execution: return "Eligible For Automatic Execution";
            case enum_type::bid_contains_customer_trading_interest: return "Bid Contains Customer Trading Interest";
            case enum_type::offer_contains_customer_trading_interest: return "Offer Contains Customer Trading Interest";
            case enum_type::both_bid_and_offer_contain_customer_trading_interest: return "Both Bid And Offer Contain Customer Trading Interest";
            case enum_type::offer_side_of_quote_not_firm_bid_side_firm: return "Offer Side Of Quote Not Firm Bid Side Firm";
            case enum_type::bid_side_of_quote_not_firm_offer_side_firm: return "Bid Side Of Quote Not Firm Offer Side Firm";
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

    static constexpr const char* name = "short_equity_and_index_quote_message_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<short_equity_and_index_quote_message_type::enum_type>;
    using storage_type = result_type;

    constexpr short_equity_and_index_quote_message_type()
     : value{ enum_type{} } {}

    constexpr short_equity_and_index_quote_message_type(enum_type v)
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
            set(enum_type::bid_side_of_quote_not_firm_offer_side_firm);
    }

  protected:
    enum_type value;
};
}
