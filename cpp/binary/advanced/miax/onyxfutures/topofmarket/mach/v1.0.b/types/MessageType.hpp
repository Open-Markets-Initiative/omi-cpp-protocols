// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: types/MessageType.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// message_type
struct message_type {

    enum class enum_type : std::uint8_t {
        simple_instrument_definition_message = 1,
        complex_instrument_definition_message = 2,
        system_state_message = 3,
        instrument_trading_status_notification_message = 4,
        best_bid_and_offer_message = 15,
        last_sale_message = 16,
        trade_cancel_message = 14
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 7> from_string_map = {{
        {"Best Bid And Offer Message", enum_type::best_bid_and_offer_message},
        {"Complex Instrument Definition Message", enum_type::complex_instrument_definition_message},
        {"Instrument Trading Status Notification Message", enum_type::instrument_trading_status_notification_message},
        {"Last Sale Message", enum_type::last_sale_message},
        {"Simple Instrument Definition Message", enum_type::simple_instrument_definition_message},
        {"System State Message", enum_type::system_state_message},
        {"Trade Cancel Message", enum_type::trade_cancel_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::simple_instrument_definition_message: return "Simple Instrument Definition Message";
            case enum_type::complex_instrument_definition_message: return "Complex Instrument Definition Message";
            case enum_type::system_state_message: return "System State Message";
            case enum_type::instrument_trading_status_notification_message: return "Instrument Trading Status Notification Message";
            case enum_type::best_bid_and_offer_message: return "Best Bid And Offer Message";
            case enum_type::last_sale_message: return "Last Sale Message";
            case enum_type::trade_cancel_message: return "Trade Cancel Message";
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
            set(enum_type::trade_cancel_message);
    }

  protected:
    enum_type value;
};
}
