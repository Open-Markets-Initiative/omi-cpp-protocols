#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// security_trading_status
struct security_trading_status {

    enum class enum_type : std::uint8_t {
        trading_halt = 2,
        no_open = 4,
        ready_to_trade = 17,
        forbidden = 18,
        unknown_or_invalid = 20,
        pre_open = 21,
        final_closing_call = 101,
        reserved = 110,
        no_value = 0
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 9> from_string_map = {{
        {"Final Closing Call", enum_type::final_closing_call},
        {"Forbidden", enum_type::forbidden},
        {"No Open", enum_type::no_open},
        {"No Value", enum_type::no_value},
        {"Pre Open", enum_type::pre_open},
        {"Ready To Trade", enum_type::ready_to_trade},
        {"Reserved", enum_type::reserved},
        {"Trading Halt", enum_type::trading_halt},
        {"Unknown Or Invalid", enum_type::unknown_or_invalid}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::trading_halt: return "Trading Halt";
            case enum_type::no_open: return "No Open";
            case enum_type::ready_to_trade: return "Ready To Trade";
            case enum_type::forbidden: return "Forbidden";
            case enum_type::unknown_or_invalid: return "Unknown Or Invalid";
            case enum_type::pre_open: return "Pre Open";
            case enum_type::final_closing_call: return "Final Closing Call";
            case enum_type::reserved: return "Reserved";
            case enum_type::no_value: return "No Value";
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

    static constexpr const char* name = "security_trading_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<security_trading_status::enum_type>;
    using storage_type = result_type;

    constexpr security_trading_status()
     : value{ enum_type{} } {}

    constexpr security_trading_status(enum_type v)
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
            set(static_cast<enum_type>(0));
    }

  protected:
    enum_type value;
};
}
