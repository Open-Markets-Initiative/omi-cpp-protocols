#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// offer_condition
struct offer_condition {

    enum class enum_type : char {
        regular = 'A',
        public_customer_interest = 'B',
        not_firm = 'C',
        reserved = 'R',
        trading_halt = 'T'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Not Firm", enum_type::not_firm},
        {"Public Customer Interest", enum_type::public_customer_interest},
        {"Regular", enum_type::regular},
        {"Reserved", enum_type::reserved},
        {"Trading Halt", enum_type::trading_halt}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::regular: return "Regular";
            case enum_type::public_customer_interest: return "Public Customer Interest";
            case enum_type::not_firm: return "Not Firm";
            case enum_type::reserved: return "Reserved";
            case enum_type::trading_halt: return "Trading Halt";
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
            set(enum_type::trading_halt);
    }

  protected:
    enum_type value;
};
}
