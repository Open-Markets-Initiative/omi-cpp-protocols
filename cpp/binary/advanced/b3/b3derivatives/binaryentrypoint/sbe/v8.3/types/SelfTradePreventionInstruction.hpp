#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// self_trade_prevention_instruction
struct self_trade_prevention_instruction {

    enum class enum_type : std::uint8_t {
        none = 0,
        cancel_aggressor_order = 1,
        cancel_resting_order = 2,
        cancel_both_orders = 3
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Cancel Aggressor Order", enum_type::cancel_aggressor_order},
        {"Cancel Both Orders", enum_type::cancel_both_orders},
        {"Cancel Resting Order", enum_type::cancel_resting_order},
        {"None", enum_type::none}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::none: return "None";
            case enum_type::cancel_aggressor_order: return "Cancel Aggressor Order";
            case enum_type::cancel_resting_order: return "Cancel Resting Order";
            case enum_type::cancel_both_orders: return "Cancel Both Orders";
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

    static constexpr const char* name = "self_trade_prevention_instruction";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<self_trade_prevention_instruction::enum_type>;
    using storage_type = result_type;

    constexpr self_trade_prevention_instruction()
     : value{ enum_type{} } {}

    constexpr self_trade_prevention_instruction(enum_type v)
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
            set(enum_type::cancel_both_orders);
    }

  protected:
    enum_type value;
};
}
