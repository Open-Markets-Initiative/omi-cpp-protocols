#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace iex::iexequities::deep::iextp::v1_08 {

// operational_halt_status
struct operational_halt_status {

    enum class enum_type : char {
        iex_specific_operational_trading_halt = 'O',
        not_operationally_halted_on_iex = 'N'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Iex Specific Operational Trading Halt", enum_type::iex_specific_operational_trading_halt},
        {"Not Operationally Halted On Iex", enum_type::not_operationally_halted_on_iex}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::iex_specific_operational_trading_halt: return "Iex Specific Operational Trading Halt";
            case enum_type::not_operationally_halted_on_iex: return "Not Operationally Halted On Iex";
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

    static constexpr const char* name = "operational_halt_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<operational_halt_status::enum_type>;
    using storage_type = result_type;

    constexpr operational_halt_status()
     : value{ enum_type::iex_specific_operational_trading_halt } {}

    constexpr operational_halt_status(enum_type v)
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
            set(enum_type::not_operationally_halted_on_iex);
    }

  protected:
    enum_type value;
};
}
