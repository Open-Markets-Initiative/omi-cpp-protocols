#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_11_b {

// held_trade_indicator
struct held_trade_indicator {

    enum class enum_type : char {
        held_trade_indicator_not_applicable = ' ',
        held_trade_not_a_last_sale_for_participant_or_consolidated = 'A',
        held_trade_last_sale_for_participant_but_not_consolidated = 'B',
        held_trade_last_sale_for_participant_and_consolidated = 'C'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Held Trade Indicator Not Applicable", enum_type::held_trade_indicator_not_applicable},
        {"Held Trade Last Sale For Participant And Consolidated", enum_type::held_trade_last_sale_for_participant_and_consolidated},
        {"Held Trade Last Sale For Participant But Not Consolidated", enum_type::held_trade_last_sale_for_participant_but_not_consolidated},
        {"Held Trade Not A Last Sale For Participant Or Consolidated", enum_type::held_trade_not_a_last_sale_for_participant_or_consolidated}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::held_trade_indicator_not_applicable: return "Held Trade Indicator Not Applicable";
            case enum_type::held_trade_not_a_last_sale_for_participant_or_consolidated: return "Held Trade Not A Last Sale For Participant Or Consolidated";
            case enum_type::held_trade_last_sale_for_participant_but_not_consolidated: return "Held Trade Last Sale For Participant But Not Consolidated";
            case enum_type::held_trade_last_sale_for_participant_and_consolidated: return "Held Trade Last Sale For Participant And Consolidated";
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

    static constexpr const char* name = "held_trade_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<held_trade_indicator::enum_type>;
    using storage_type = result_type;

    constexpr held_trade_indicator()
     : value{ enum_type{} } {}

    constexpr held_trade_indicator(enum_type v)
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
            set(enum_type::held_trade_last_sale_for_participant_and_consolidated);
    }

  protected:
    enum_type value;
};
}
