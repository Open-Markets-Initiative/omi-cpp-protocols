#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::nyseequities::bbo::xdp::v2_4_g {

// quote_condition
struct quote_condition {

    enum class enum_type : char {
        closing = 'C',
        opening_quote = 'O',
        regular_quote = 'R',
        slow_on_the_bid_and_ask = 'W'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Closing", enum_type::closing},
        {"Opening Quote", enum_type::opening_quote},
        {"Regular Quote", enum_type::regular_quote},
        {"Slow On The Bid And Ask", enum_type::slow_on_the_bid_and_ask}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::closing: return "Closing";
            case enum_type::opening_quote: return "Opening Quote";
            case enum_type::regular_quote: return "Regular Quote";
            case enum_type::slow_on_the_bid_and_ask: return "Slow On The Bid And Ask";
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
            set(enum_type::slow_on_the_bid_and_ask);
    }

  protected:
    enum_type value;
};
}
