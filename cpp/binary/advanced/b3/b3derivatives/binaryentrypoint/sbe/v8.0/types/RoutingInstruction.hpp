#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// routing_instruction
struct routing_instruction {

    enum class enum_type : std::uint8_t {
        retail_liquidity_taker = 1,
        waived_priority = 2,
        broker_only = 3,
        broker_only_removal = 4,
        no_value = 0
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Broker Only", enum_type::broker_only},
        {"Broker Only Removal", enum_type::broker_only_removal},
        {"No Value", enum_type::no_value},
        {"Retail Liquidity Taker", enum_type::retail_liquidity_taker},
        {"Waived Priority", enum_type::waived_priority}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::retail_liquidity_taker: return "Retail Liquidity Taker";
            case enum_type::waived_priority: return "Waived Priority";
            case enum_type::broker_only: return "Broker Only";
            case enum_type::broker_only_removal: return "Broker Only Removal";
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

    static constexpr const char* name = "routing_instruction";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<routing_instruction::enum_type>;
    using storage_type = result_type;

    constexpr routing_instruction()
     : value{ enum_type{} } {}

    constexpr routing_instruction(enum_type v)
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
