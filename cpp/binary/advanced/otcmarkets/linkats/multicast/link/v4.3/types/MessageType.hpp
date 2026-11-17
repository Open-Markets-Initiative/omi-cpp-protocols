// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/MessageType.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// message_type
struct message_type {

    enum class enum_type : std::uint8_t {
        start_of_spin_message = 11,
        end_of_spin_message = 12,
        market_open_message = 13,
        market_close_message = 14,
        security_message = 9,
        quote_message = 1,
        quote_update_message = 2,
        inside_message = 3,
        inside_update_message = 4,
        reference_price_message = 7,
        reference_price_update_message = 8,
        extended_security_message = 15,
        extended_security_no_cusip_message = 16,
        trade_message = 17
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 14> from_string_map = {{
        {"End Of Spin Message", enum_type::end_of_spin_message},
        {"Extended Security Message", enum_type::extended_security_message},
        {"Extended Security No Cusip Message", enum_type::extended_security_no_cusip_message},
        {"Inside Message", enum_type::inside_message},
        {"Inside Update Message", enum_type::inside_update_message},
        {"Market Close Message", enum_type::market_close_message},
        {"Market Open Message", enum_type::market_open_message},
        {"Quote Message", enum_type::quote_message},
        {"Quote Update Message", enum_type::quote_update_message},
        {"Reference Price Message", enum_type::reference_price_message},
        {"Reference Price Update Message", enum_type::reference_price_update_message},
        {"Security Message", enum_type::security_message},
        {"Start Of Spin Message", enum_type::start_of_spin_message},
        {"Trade Message", enum_type::trade_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::start_of_spin_message: return "Start Of Spin Message";
            case enum_type::end_of_spin_message: return "End Of Spin Message";
            case enum_type::market_open_message: return "Market Open Message";
            case enum_type::market_close_message: return "Market Close Message";
            case enum_type::security_message: return "Security Message";
            case enum_type::quote_message: return "Quote Message";
            case enum_type::quote_update_message: return "Quote Update Message";
            case enum_type::inside_message: return "Inside Message";
            case enum_type::inside_update_message: return "Inside Update Message";
            case enum_type::reference_price_message: return "Reference Price Message";
            case enum_type::reference_price_update_message: return "Reference Price Update Message";
            case enum_type::extended_security_message: return "Extended Security Message";
            case enum_type::extended_security_no_cusip_message: return "Extended Security No Cusip Message";
            case enum_type::trade_message: return "Trade Message";
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
            set(enum_type::trade_message);
    }

  protected:
    enum_type value;
};
}
