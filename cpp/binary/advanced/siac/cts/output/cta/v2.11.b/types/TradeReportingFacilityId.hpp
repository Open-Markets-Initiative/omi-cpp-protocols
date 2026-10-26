#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_11_b {

// trade_reporting_facility_id
struct trade_reporting_facility_id {

    enum class enum_type : char {
        trf_not_applicable = ' ',
        not_currently_active_a = 'A',
        finra_nasdaq_trf_chicago = 'B',
        not_currently_active_c = 'C',
        not_currently_active_d = 'D',
        not_currently_active_i = 'I',
        not_currently_active_j = 'J',
        not_currently_active_k = 'K',
        not_currently_active_m = 'M',
        finra_nyse_trf = 'N',
        not_currently_active_p = 'P',
        finra_nasdaq_trf_carteret = 'T',
        not_currently_active_v = 'V',
        not_currently_active_w = 'W',
        not_currently_active_x = 'X',
        not_currently_active_y = 'Y',
        not_currently_active_z = 'Z'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 17> from_string_map = {{
        {"Finra Nasdaq Trf Carteret", enum_type::finra_nasdaq_trf_carteret},
        {"Finra Nasdaq Trf Chicago", enum_type::finra_nasdaq_trf_chicago},
        {"Finra Nyse Trf", enum_type::finra_nyse_trf},
        {"Not Currently Active A", enum_type::not_currently_active_a},
        {"Not Currently Active C", enum_type::not_currently_active_c},
        {"Not Currently Active D", enum_type::not_currently_active_d},
        {"Not Currently Active I", enum_type::not_currently_active_i},
        {"Not Currently Active J", enum_type::not_currently_active_j},
        {"Not Currently Active K", enum_type::not_currently_active_k},
        {"Not Currently Active M", enum_type::not_currently_active_m},
        {"Not Currently Active P", enum_type::not_currently_active_p},
        {"Not Currently Active V", enum_type::not_currently_active_v},
        {"Not Currently Active W", enum_type::not_currently_active_w},
        {"Not Currently Active X", enum_type::not_currently_active_x},
        {"Not Currently Active Y", enum_type::not_currently_active_y},
        {"Not Currently Active Z", enum_type::not_currently_active_z},
        {"Trf Not Applicable", enum_type::trf_not_applicable}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::trf_not_applicable: return "Trf Not Applicable";
            case enum_type::not_currently_active_a: return "Not Currently Active A";
            case enum_type::finra_nasdaq_trf_chicago: return "Finra Nasdaq Trf Chicago";
            case enum_type::not_currently_active_c: return "Not Currently Active C";
            case enum_type::not_currently_active_d: return "Not Currently Active D";
            case enum_type::not_currently_active_i: return "Not Currently Active I";
            case enum_type::not_currently_active_j: return "Not Currently Active J";
            case enum_type::not_currently_active_k: return "Not Currently Active K";
            case enum_type::not_currently_active_m: return "Not Currently Active M";
            case enum_type::finra_nyse_trf: return "Finra Nyse Trf";
            case enum_type::not_currently_active_p: return "Not Currently Active P";
            case enum_type::finra_nasdaq_trf_carteret: return "Finra Nasdaq Trf Carteret";
            case enum_type::not_currently_active_v: return "Not Currently Active V";
            case enum_type::not_currently_active_w: return "Not Currently Active W";
            case enum_type::not_currently_active_x: return "Not Currently Active X";
            case enum_type::not_currently_active_y: return "Not Currently Active Y";
            case enum_type::not_currently_active_z: return "Not Currently Active Z";
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
            set(enum_type::not_currently_active_z);
    }

  protected:
    enum_type value;
};
}
