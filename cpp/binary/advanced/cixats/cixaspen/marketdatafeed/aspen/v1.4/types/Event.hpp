#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// event
struct event {

    enum class enum_type : char {
        start_of_session = 'O',
        market_accepting_orders = 'S',
        market_open_for_trading = 'Q',
        market_closed_for_trading = 'E',
        end_of_session = 'C'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"End Of Session", enum_type::end_of_session},
        {"Market Accepting Orders", enum_type::market_accepting_orders},
        {"Market Closed For Trading", enum_type::market_closed_for_trading},
        {"Market Open For Trading", enum_type::market_open_for_trading},
        {"Start Of Session", enum_type::start_of_session}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::start_of_session: return "Start Of Session";
            case enum_type::market_accepting_orders: return "Market Accepting Orders";
            case enum_type::market_open_for_trading: return "Market Open For Trading";
            case enum_type::market_closed_for_trading: return "Market Closed For Trading";
            case enum_type::end_of_session: return "End Of Session";
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

    static constexpr const char* name = "event";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<event::enum_type>;
    using storage_type = result_type;

    constexpr event()
     : value{ enum_type{} } {}

    constexpr event(enum_type v)
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
            set(enum_type::end_of_session);
    }

  protected:
    enum_type value;
};
}
