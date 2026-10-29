#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cqs::output::cta::v1_91 {

// finra_bbo_indicator
struct finra_bbo_indicator {

    enum class enum_type : char {
        not_applicable = ' ',
        no_finra_bbo_change = 'A',
        no_finra_bbo_exists = 'B'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"No Finra Bbo Change", enum_type::no_finra_bbo_change},
        {"No Finra Bbo Exists", enum_type::no_finra_bbo_exists},
        {"Not Applicable", enum_type::not_applicable}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::not_applicable: return "Not Applicable";
            case enum_type::no_finra_bbo_change: return "No Finra Bbo Change";
            case enum_type::no_finra_bbo_exists: return "No Finra Bbo Exists";
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

    static constexpr const char* name = "finra_bbo_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<finra_bbo_indicator::enum_type>;
    using storage_type = result_type;

    constexpr finra_bbo_indicator()
     : value{ enum_type{} } {}

    constexpr finra_bbo_indicator(enum_type v)
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
            set(enum_type::no_finra_bbo_exists);
    }

  protected:
    enum_type value;
};
}
