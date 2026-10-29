#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

// quote_condition
struct quote_condition {

    enum class enum_type : char {
        regular_trading = '1',
        rotation = '2',
        trading_halted = '3',
        pre_open = '4',
        rotation_legal_width_quote_pending = '5'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Pre Open", enum_type::pre_open},
        {"Regular Trading", enum_type::regular_trading},
        {"Rotation", enum_type::rotation},
        {"Rotation Legal Width Quote Pending", enum_type::rotation_legal_width_quote_pending},
        {"Trading Halted", enum_type::trading_halted}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::regular_trading: return "Regular Trading";
            case enum_type::rotation: return "Rotation";
            case enum_type::trading_halted: return "Trading Halted";
            case enum_type::pre_open: return "Pre Open";
            case enum_type::rotation_legal_width_quote_pending: return "Rotation Legal Width Quote Pending";
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
            set(enum_type::rotation_legal_width_quote_pending);
    }

  protected:
    enum_type value;
};
}
