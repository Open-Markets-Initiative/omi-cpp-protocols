// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: types/OfferCondition.hpp
#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// offer_condition
struct offer_condition {

    enum class enum_type : char {
        regular = 'A',
        trading_halt = 'T',
        wide = 'W',
        simple_auction = 'S',
        complex_auction = 'C',
        simple_market_protection = 'M',
        leg_market_protection = 'L'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 7> from_string_map = {{
        {"Complex Auction", enum_type::complex_auction},
        {"Leg Market Protection", enum_type::leg_market_protection},
        {"Regular", enum_type::regular},
        {"Simple Auction", enum_type::simple_auction},
        {"Simple Market Protection", enum_type::simple_market_protection},
        {"Trading Halt", enum_type::trading_halt},
        {"Wide", enum_type::wide}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::regular: return "Regular";
            case enum_type::trading_halt: return "Trading Halt";
            case enum_type::wide: return "Wide";
            case enum_type::simple_auction: return "Simple Auction";
            case enum_type::complex_auction: return "Complex Auction";
            case enum_type::simple_market_protection: return "Simple Market Protection";
            case enum_type::leg_market_protection: return "Leg Market Protection";
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

    static constexpr const char* name = "offer_condition";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<offer_condition::enum_type>;
    using storage_type = result_type;

    constexpr offer_condition()
     : value{ enum_type{} } {}

    constexpr offer_condition(enum_type v)
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
            set(enum_type::leg_market_protection);
    }

  protected:
    enum_type value;
};
}
