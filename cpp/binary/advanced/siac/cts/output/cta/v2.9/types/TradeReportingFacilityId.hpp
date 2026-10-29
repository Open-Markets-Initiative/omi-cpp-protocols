#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_9 {

// trade_reporting_facility_id
struct trade_reporting_facility_id {

    enum class enum_type : char {
        not_applicable = ' ',
        finra_nasdaq_chicago = 'B',
        finra_nyse = 'N',
        finra_nasdaq_carteret = 'T'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Finra Nasdaq Carteret", enum_type::finra_nasdaq_carteret},
        {"Finra Nasdaq Chicago", enum_type::finra_nasdaq_chicago},
        {"Finra Nyse", enum_type::finra_nyse},
        {"Not Applicable", enum_type::not_applicable}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::not_applicable: return "Not Applicable";
            case enum_type::finra_nasdaq_chicago: return "Finra Nasdaq Chicago";
            case enum_type::finra_nyse: return "Finra Nyse";
            case enum_type::finra_nasdaq_carteret: return "Finra Nasdaq Carteret";
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
            set(enum_type::finra_nasdaq_carteret);
    }

  protected:
    enum_type value;
};
}
