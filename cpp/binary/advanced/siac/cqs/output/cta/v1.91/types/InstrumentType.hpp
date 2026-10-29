#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cqs::output::cta::v1_91 {

// instrument_type
struct instrument_type {

    enum class enum_type : char {
        cta_eligible_equity = '0',
        local_issue = '1',
        corporate_bond = '2',
        government_bond = '3'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Corporate Bond", enum_type::corporate_bond},
        {"Cta Eligible Equity", enum_type::cta_eligible_equity},
        {"Government Bond", enum_type::government_bond},
        {"Local Issue", enum_type::local_issue}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::cta_eligible_equity: return "Cta Eligible Equity";
            case enum_type::local_issue: return "Local Issue";
            case enum_type::corporate_bond: return "Corporate Bond";
            case enum_type::government_bond: return "Government Bond";
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

    static constexpr const char* name = "instrument_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<instrument_type::enum_type>;
    using storage_type = result_type;

    constexpr instrument_type()
     : value{ enum_type{} } {}

    constexpr instrument_type(enum_type v)
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
            set(enum_type::government_bond);
    }

  protected:
    enum_type value;
};
}
