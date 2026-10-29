#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v1_91 {

// trade_reporting_facility_id
struct trade_reporting_facility_id {

    enum class enum_type : char {
        not_applicable = ' ',
        inactive_value_a = 'A',
        finra_nasdaq_chicago = 'B',
        inactive_value_c = 'C',
        inactive_value_d = 'D',
        inactive_value_i = 'I',
        inactive_value_j = 'J',
        inactive_value_k = 'K',
        inactive_value_m = 'M',
        finra_nyse = 'N',
        inactive_value_p = 'P',
        finra_nasdaq_carteret = 'T',
        inactive_value_v = 'V',
        inactive_value_w = 'W',
        inactive_value_x = 'X',
        inactive_value_y = 'Y',
        inactive_value_z = 'Z'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 17> from_string_map = {{
        {"Finra Nasdaq Carteret", enum_type::finra_nasdaq_carteret},
        {"Finra Nasdaq Chicago", enum_type::finra_nasdaq_chicago},
        {"Finra Nyse", enum_type::finra_nyse},
        {"Inactive Value A", enum_type::inactive_value_a},
        {"Inactive Value C", enum_type::inactive_value_c},
        {"Inactive Value D", enum_type::inactive_value_d},
        {"Inactive Value I", enum_type::inactive_value_i},
        {"Inactive Value J", enum_type::inactive_value_j},
        {"Inactive Value K", enum_type::inactive_value_k},
        {"Inactive Value M", enum_type::inactive_value_m},
        {"Inactive Value P", enum_type::inactive_value_p},
        {"Inactive Value V", enum_type::inactive_value_v},
        {"Inactive Value W", enum_type::inactive_value_w},
        {"Inactive Value X", enum_type::inactive_value_x},
        {"Inactive Value Y", enum_type::inactive_value_y},
        {"Inactive Value Z", enum_type::inactive_value_z},
        {"Not Applicable", enum_type::not_applicable}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::not_applicable: return "Not Applicable";
            case enum_type::inactive_value_a: return "Inactive Value A";
            case enum_type::finra_nasdaq_chicago: return "Finra Nasdaq Chicago";
            case enum_type::inactive_value_c: return "Inactive Value C";
            case enum_type::inactive_value_d: return "Inactive Value D";
            case enum_type::inactive_value_i: return "Inactive Value I";
            case enum_type::inactive_value_j: return "Inactive Value J";
            case enum_type::inactive_value_k: return "Inactive Value K";
            case enum_type::inactive_value_m: return "Inactive Value M";
            case enum_type::finra_nyse: return "Finra Nyse";
            case enum_type::inactive_value_p: return "Inactive Value P";
            case enum_type::finra_nasdaq_carteret: return "Finra Nasdaq Carteret";
            case enum_type::inactive_value_v: return "Inactive Value V";
            case enum_type::inactive_value_w: return "Inactive Value W";
            case enum_type::inactive_value_x: return "Inactive Value X";
            case enum_type::inactive_value_y: return "Inactive Value Y";
            case enum_type::inactive_value_z: return "Inactive Value Z";
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

    static constexpr const char* name = "trade_reporting_facility_id";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<trade_reporting_facility_id::enum_type>;
    using storage_type = result_type;

    constexpr trade_reporting_facility_id()
     : value{ enum_type{} } {}

    constexpr trade_reporting_facility_id(enum_type v)
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
            set(enum_type::inactive_value_z);
    }

  protected:
    enum_type value;
};
}
