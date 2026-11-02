#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

// instrument_class
struct instrument_class {

    enum class enum_type : char {
        bond = 'B',
        call = 'C',
        future = 'F',
        index = 'I',
        stock = 'K',
        mixed_spread = 'M',
        put = 'P',
        future_spread = 'S',
        option_spread = 'T',
        fx_spot = 'X',
        commodity_spot = 'Y'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 11> from_string_map = {{
        {"Bond", enum_type::bond},
        {"Call", enum_type::call},
        {"Commodity Spot", enum_type::commodity_spot},
        {"Future", enum_type::future},
        {"Future Spread", enum_type::future_spread},
        {"Fx Spot", enum_type::fx_spot},
        {"Index", enum_type::index},
        {"Mixed Spread", enum_type::mixed_spread},
        {"Option Spread", enum_type::option_spread},
        {"Put", enum_type::put},
        {"Stock", enum_type::stock}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::bond: return "Bond";
            case enum_type::call: return "Call";
            case enum_type::future: return "Future";
            case enum_type::index: return "Index";
            case enum_type::stock: return "Stock";
            case enum_type::mixed_spread: return "Mixed Spread";
            case enum_type::put: return "Put";
            case enum_type::future_spread: return "Future Spread";
            case enum_type::option_spread: return "Option Spread";
            case enum_type::fx_spot: return "Fx Spot";
            case enum_type::commodity_spot: return "Commodity Spot";
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

    static constexpr const char* name = "instrument_class";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<instrument_class::enum_type>;
    using storage_type = result_type;

    constexpr instrument_class()
     : value{ enum_type{} } {}

    constexpr instrument_class(enum_type v)
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
            set(enum_type::commodity_spot);
    }

  protected:
    enum_type value;
};
}
