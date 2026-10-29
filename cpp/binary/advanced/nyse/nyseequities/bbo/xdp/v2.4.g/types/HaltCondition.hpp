#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::nyseequities::bbo::xdp::v2_4_g {

// halt_condition
struct halt_condition {

    enum class enum_type : char {
        security_not_delayedhalted = '~',
        not_delayedhalted_nyse_tape_a_only = ' ',
        news_dissemination = 'D',
        order_imbalance = 'I',
        news_pending = 'P',
        luld_pause = 'M',
        related_security_not_used = 'S',
        equipment_changeover = 'X',
        no_open_no_resume = 'Z',
        market_wide_circuit_breaker_halt_level_1 = '1',
        market_wide_circuit_breaker_halt_level_2 = '2',
        market_wide_circuit_breaker_halt_level_3 = '3'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 12> from_string_map = {{
        {"Equipment Changeover", enum_type::equipment_changeover},
        {"Luld Pause", enum_type::luld_pause},
        {"Market Wide Circuit Breaker Halt Level 1", enum_type::market_wide_circuit_breaker_halt_level_1},
        {"Market Wide Circuit Breaker Halt Level 2", enum_type::market_wide_circuit_breaker_halt_level_2},
        {"Market Wide Circuit Breaker Halt Level 3", enum_type::market_wide_circuit_breaker_halt_level_3},
        {"News Dissemination", enum_type::news_dissemination},
        {"News Pending", enum_type::news_pending},
        {"No Open No Resume", enum_type::no_open_no_resume},
        {"Not Delayedhalted Nyse Tape A Only", enum_type::not_delayedhalted_nyse_tape_a_only},
        {"Order Imbalance", enum_type::order_imbalance},
        {"Related Security Not Used", enum_type::related_security_not_used},
        {"Security Not Delayedhalted", enum_type::security_not_delayedhalted}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::security_not_delayedhalted: return "Security Not Delayedhalted";
            case enum_type::not_delayedhalted_nyse_tape_a_only: return "Not Delayedhalted Nyse Tape A Only";
            case enum_type::news_dissemination: return "News Dissemination";
            case enum_type::order_imbalance: return "Order Imbalance";
            case enum_type::news_pending: return "News Pending";
            case enum_type::luld_pause: return "Luld Pause";
            case enum_type::related_security_not_used: return "Related Security Not Used";
            case enum_type::equipment_changeover: return "Equipment Changeover";
            case enum_type::no_open_no_resume: return "No Open No Resume";
            case enum_type::market_wide_circuit_breaker_halt_level_1: return "Market Wide Circuit Breaker Halt Level 1";
            case enum_type::market_wide_circuit_breaker_halt_level_2: return "Market Wide Circuit Breaker Halt Level 2";
            case enum_type::market_wide_circuit_breaker_halt_level_3: return "Market Wide Circuit Breaker Halt Level 3";
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

    static constexpr const char* name = "halt_condition";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<halt_condition::enum_type>;
    using storage_type = result_type;

    constexpr halt_condition()
     : value{ enum_type{} } {}

    constexpr halt_condition(enum_type v)
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
            set(enum_type::market_wide_circuit_breaker_halt_level_3);
    }

  protected:
    enum_type value;
};
}
