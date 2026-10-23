#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// message_type
struct message_type {

    enum class enum_type : char {
        system_time_message = '1',
        simple_series_update_message = 'P',
        system_state_message = 'S',
        simple_top_of_market_best_bid_or_offer_compact_bid_message = 'B',
        simple_top_of_market_best_bid_or_offer_compact_offer_message = 'O',
        simple_top_of_market_best_bid_or_offer_wide_bid_message = 'b',
        simple_top_of_market_best_bid_or_offer_wide_offer_message = 'o',
        simple_double_sided_top_of_market_best_bid_or_offer_compact_message = 'd',
        simple_double_sided_top_of_market_best_bid_or_offer_wide_message = 'D',
        last_sale_message = 'T',
        trade_cancel_message = 'X',
        underlying_trading_status_notification_message = 'H'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 12> from_string_map = {{
        {"Last Sale Message", enum_type::last_sale_message},
        {"Simple Double Sided Top Of Market Best Bid Or Offer Compact Message", enum_type::simple_double_sided_top_of_market_best_bid_or_offer_compact_message},
        {"Simple Double Sided Top Of Market Best Bid Or Offer Wide Message", enum_type::simple_double_sided_top_of_market_best_bid_or_offer_wide_message},
        {"Simple Series Update Message", enum_type::simple_series_update_message},
        {"Simple Top Of Market Best Bid Or Offer Compact Bid Message", enum_type::simple_top_of_market_best_bid_or_offer_compact_bid_message},
        {"Simple Top Of Market Best Bid Or Offer Compact Offer Message", enum_type::simple_top_of_market_best_bid_or_offer_compact_offer_message},
        {"Simple Top Of Market Best Bid Or Offer Wide Bid Message", enum_type::simple_top_of_market_best_bid_or_offer_wide_bid_message},
        {"Simple Top Of Market Best Bid Or Offer Wide Offer Message", enum_type::simple_top_of_market_best_bid_or_offer_wide_offer_message},
        {"System State Message", enum_type::system_state_message},
        {"System Time Message", enum_type::system_time_message},
        {"Trade Cancel Message", enum_type::trade_cancel_message},
        {"Underlying Trading Status Notification Message", enum_type::underlying_trading_status_notification_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::system_time_message: return "System Time Message";
            case enum_type::simple_series_update_message: return "Simple Series Update Message";
            case enum_type::system_state_message: return "System State Message";
            case enum_type::simple_top_of_market_best_bid_or_offer_compact_bid_message: return "Simple Top Of Market Best Bid Or Offer Compact Bid Message";
            case enum_type::simple_top_of_market_best_bid_or_offer_compact_offer_message: return "Simple Top Of Market Best Bid Or Offer Compact Offer Message";
            case enum_type::simple_top_of_market_best_bid_or_offer_wide_bid_message: return "Simple Top Of Market Best Bid Or Offer Wide Bid Message";
            case enum_type::simple_top_of_market_best_bid_or_offer_wide_offer_message: return "Simple Top Of Market Best Bid Or Offer Wide Offer Message";
            case enum_type::simple_double_sided_top_of_market_best_bid_or_offer_compact_message: return "Simple Double Sided Top Of Market Best Bid Or Offer Compact Message";
            case enum_type::simple_double_sided_top_of_market_best_bid_or_offer_wide_message: return "Simple Double Sided Top Of Market Best Bid Or Offer Wide Message";
            case enum_type::last_sale_message: return "Last Sale Message";
            case enum_type::trade_cancel_message: return "Trade Cancel Message";
            case enum_type::underlying_trading_status_notification_message: return "Underlying Trading Status Notification Message";
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

    static constexpr const char* name = "message_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<message_type::enum_type>;
    using storage_type = result_type;

    constexpr message_type()
     : value{ enum_type{} } {}

    constexpr message_type(enum_type v)
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
            set(enum_type::underlying_trading_status_notification_message);
    }

  protected:
    enum_type value;
};
}
