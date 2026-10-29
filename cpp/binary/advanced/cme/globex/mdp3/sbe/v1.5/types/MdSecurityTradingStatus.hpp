#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cme::mdp3::v5 {

// md_security_trading_status
struct md_security_trading_status {

    enum class enum_type : std::uint8_t {
        no_value = 255,
        trading_halt = 2,
        close = 4,
        new_price_indication = 15,
        ready_to_trade = 17,
        not_available_for_trading = 18,
        unknown_or_invalid = 20,
        pre_open = 21,
        pre_cross = 24,
        cross = 25,
        post_close = 26,
        no_change = 103
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 12> from_string_map = {{
        {"Close", enum_type::close},
        {"Cross", enum_type::cross},
        {"New Price Indication", enum_type::new_price_indication},
        {"No Change", enum_type::no_change},
        {"No Value", enum_type::no_value},
        {"Not Available For Trading", enum_type::not_available_for_trading},
        {"Post Close", enum_type::post_close},
        {"Pre Cross", enum_type::pre_cross},
        {"Pre Open", enum_type::pre_open},
        {"Ready To Trade", enum_type::ready_to_trade},
        {"Trading Halt", enum_type::trading_halt},
        {"Unknown Or Invalid", enum_type::unknown_or_invalid}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::no_value: return "No Value";
            case enum_type::trading_halt: return "Trading Halt";
            case enum_type::close: return "Close";
            case enum_type::new_price_indication: return "New Price Indication";
            case enum_type::ready_to_trade: return "Ready To Trade";
            case enum_type::not_available_for_trading: return "Not Available For Trading";
            case enum_type::unknown_or_invalid: return "Unknown Or Invalid";
            case enum_type::pre_open: return "Pre Open";
            case enum_type::pre_cross: return "Pre Cross";
            case enum_type::cross: return "Cross";
            case enum_type::post_close: return "Post Close";
            case enum_type::no_change: return "No Change";
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

    static constexpr const char* name = "md_security_trading_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<md_security_trading_status::enum_type>;
    using storage_type = result_type;

    constexpr md_security_trading_status()
     : value{ enum_type{} } {}

    constexpr md_security_trading_status(enum_type v)
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
            set(static_cast<enum_type>(255));
    }

  protected:
    enum_type value;
};
}
