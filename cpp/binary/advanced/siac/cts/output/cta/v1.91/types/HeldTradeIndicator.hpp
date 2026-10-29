#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v1_91 {

// held_trade_indicator
struct held_trade_indicator {

    enum class enum_type : char {
        not_applicable = ' ',
        cannot_be_used_as_a_last_sale_for_both_participant_and_consolidated_basis = 'A',
        can_be_used_as_a_last_sale_for_participant_but_not_consolidated_basis = 'B',
        can_be_used_as_a_last_sale_for_participant_and_consolidated_basis = 'C'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Can Be Used As A Last Sale For Participant And Consolidated Basis", enum_type::can_be_used_as_a_last_sale_for_participant_and_consolidated_basis},
        {"Can Be Used As A Last Sale For Participant But Not Consolidated Basis", enum_type::can_be_used_as_a_last_sale_for_participant_but_not_consolidated_basis},
        {"Cannot Be Used As A Last Sale For Both Participant And Consolidated Basis", enum_type::cannot_be_used_as_a_last_sale_for_both_participant_and_consolidated_basis},
        {"Not Applicable", enum_type::not_applicable}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::not_applicable: return "Not Applicable";
            case enum_type::cannot_be_used_as_a_last_sale_for_both_participant_and_consolidated_basis: return "Cannot Be Used As A Last Sale For Both Participant And Consolidated Basis";
            case enum_type::can_be_used_as_a_last_sale_for_participant_but_not_consolidated_basis: return "Can Be Used As A Last Sale For Participant But Not Consolidated Basis";
            case enum_type::can_be_used_as_a_last_sale_for_participant_and_consolidated_basis: return "Can Be Used As A Last Sale For Participant And Consolidated Basis";
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
            set(enum_type::can_be_used_as_a_last_sale_for_participant_and_consolidated_basis);
    }

  protected:
    enum_type value;
};
}
