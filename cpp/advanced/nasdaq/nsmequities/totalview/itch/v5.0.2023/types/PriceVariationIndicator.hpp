#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// price_variation_indicator
struct price_variation_indicator {

    enum class enum_type : char {
        less_than_1_percent = 'L',
        less_than_2_percent = '1',
        less_than_3_percent = '2',
        less_than_4_percent = '3',
        less_than_5_percent = '4',
        less_than_6_percent = '5',
        less_than_7_percent = '6',
        less_than_8_percent = '7',
        less_than_9_percent = '8',
        less_than_10_percent = '9',
        less_than_20_percent = 'A',
        less_than_30_percent = 'B',
        more_than_30_percent = 'C',
        not_available = ' '
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 14> from_string_map = {{
        {"Less Than 1 Percent", enum_type::less_than_1_percent},
        {"Less Than 10 Percent", enum_type::less_than_10_percent},
        {"Less Than 2 Percent", enum_type::less_than_2_percent},
        {"Less Than 20 Percent", enum_type::less_than_20_percent},
        {"Less Than 3 Percent", enum_type::less_than_3_percent},
        {"Less Than 30 Percent", enum_type::less_than_30_percent},
        {"Less Than 4 Percent", enum_type::less_than_4_percent},
        {"Less Than 5 Percent", enum_type::less_than_5_percent},
        {"Less Than 6 Percent", enum_type::less_than_6_percent},
        {"Less Than 7 Percent", enum_type::less_than_7_percent},
        {"Less Than 8 Percent", enum_type::less_than_8_percent},
        {"Less Than 9 Percent", enum_type::less_than_9_percent},
        {"More Than 30 Percent", enum_type::more_than_30_percent},
        {"Not Available", enum_type::not_available}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::less_than_1_percent: return "Less Than 1 Percent";
            case enum_type::less_than_2_percent: return "Less Than 2 Percent";
            case enum_type::less_than_3_percent: return "Less Than 3 Percent";
            case enum_type::less_than_4_percent: return "Less Than 4 Percent";
            case enum_type::less_than_5_percent: return "Less Than 5 Percent";
            case enum_type::less_than_6_percent: return "Less Than 6 Percent";
            case enum_type::less_than_7_percent: return "Less Than 7 Percent";
            case enum_type::less_than_8_percent: return "Less Than 8 Percent";
            case enum_type::less_than_9_percent: return "Less Than 9 Percent";
            case enum_type::less_than_10_percent: return "Less Than 10 Percent";
            case enum_type::less_than_20_percent: return "Less Than 20 Percent";
            case enum_type::less_than_30_percent: return "Less Than 30 Percent";
            case enum_type::more_than_30_percent: return "More Than 30 Percent";
            case enum_type::not_available: return "Not Available";
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
     : value{ enum_type::less_than_1_percent } {}

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
            set(enum_type::not_available);
    }

  protected:
    enum_type value;
};
}
