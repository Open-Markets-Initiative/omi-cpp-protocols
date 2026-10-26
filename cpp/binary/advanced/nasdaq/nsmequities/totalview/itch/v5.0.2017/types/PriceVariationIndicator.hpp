#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

// price_variation_indicator
struct price_variation_indicator {

    enum class enum_type : char {
        less = 'L',
        one_to_one_point_nine_nine_percent = '1',
        two_to_two_point_nine_nine_percent = '2',
        three_to_three_point_nine_nine_percent = '3',
        four_to_four_point_nine_nine_percent = '4',
        five_to_five_point_nine_nine_percent = '5',
        six_to_six_point_nine_nine_percent = '6',
        seven_to_seven_point_nine_nine_percent = '7',
        eight_to_eight_point_nine_nine_percent = '8',
        nine_to_nine_point_nine_nine_percent = '9',
        ten_to_nineteen_point_nine_nine_percent = 'A',
        twenty_to_twenty_nine_point_nine_nine_percent = 'B',
        thirty_percent_or_greater = 'C',
        no_calculation = ' '
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 14> from_string_map = {{
        {"Eight To Eight Point Nine Nine Percent", enum_type::eight_to_eight_point_nine_nine_percent},
        {"Five To Five Point Nine Nine Percent", enum_type::five_to_five_point_nine_nine_percent},
        {"Four To Four Point Nine Nine Percent", enum_type::four_to_four_point_nine_nine_percent},
        {"Less", enum_type::less},
        {"Nine To Nine Point Nine Nine Percent", enum_type::nine_to_nine_point_nine_nine_percent},
        {"No Calculation", enum_type::no_calculation},
        {"One To One Point Nine Nine Percent", enum_type::one_to_one_point_nine_nine_percent},
        {"Seven To Seven Point Nine Nine Percent", enum_type::seven_to_seven_point_nine_nine_percent},
        {"Six To Six Point Nine Nine Percent", enum_type::six_to_six_point_nine_nine_percent},
        {"Ten To Nineteen Point Nine Nine Percent", enum_type::ten_to_nineteen_point_nine_nine_percent},
        {"Thirty Percent Or Greater", enum_type::thirty_percent_or_greater},
        {"Three To Three Point Nine Nine Percent", enum_type::three_to_three_point_nine_nine_percent},
        {"Twenty To Twenty Nine Point Nine Nine Percent", enum_type::twenty_to_twenty_nine_point_nine_nine_percent},
        {"Two To Two Point Nine Nine Percent", enum_type::two_to_two_point_nine_nine_percent}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::less: return "Less";
            case enum_type::one_to_one_point_nine_nine_percent: return "One To One Point Nine Nine Percent";
            case enum_type::two_to_two_point_nine_nine_percent: return "Two To Two Point Nine Nine Percent";
            case enum_type::three_to_three_point_nine_nine_percent: return "Three To Three Point Nine Nine Percent";
            case enum_type::four_to_four_point_nine_nine_percent: return "Four To Four Point Nine Nine Percent";
            case enum_type::five_to_five_point_nine_nine_percent: return "Five To Five Point Nine Nine Percent";
            case enum_type::six_to_six_point_nine_nine_percent: return "Six To Six Point Nine Nine Percent";
            case enum_type::seven_to_seven_point_nine_nine_percent: return "Seven To Seven Point Nine Nine Percent";
            case enum_type::eight_to_eight_point_nine_nine_percent: return "Eight To Eight Point Nine Nine Percent";
            case enum_type::nine_to_nine_point_nine_nine_percent: return "Nine To Nine Point Nine Nine Percent";
            case enum_type::ten_to_nineteen_point_nine_nine_percent: return "Ten To Nineteen Point Nine Nine Percent";
            case enum_type::twenty_to_twenty_nine_point_nine_nine_percent: return "Twenty To Twenty Nine Point Nine Nine Percent";
            case enum_type::thirty_percent_or_greater: return "Thirty Percent Or Greater";
            case enum_type::no_calculation: return "No Calculation";
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

    static constexpr const char* name = "price_variation_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<price_variation_indicator::enum_type>;
    using storage_type = result_type;

    constexpr price_variation_indicator()
     : value{ enum_type{} } {}

    constexpr price_variation_indicator(enum_type v)
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
            set(enum_type::no_calculation);
    }

  protected:
    enum_type value;
};
}
