// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/InitiatedBy.hpp
#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// initiated_by
struct initiated_by {

    enum class enum_type : char {
        buy = 'B',
        sell = 'S',
        both = 'C'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Both", enum_type::both},
        {"Buy", enum_type::buy},
        {"Sell", enum_type::sell}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::buy: return "Buy";
            case enum_type::sell: return "Sell";
            case enum_type::both: return "Both";
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

    static constexpr const char* name = "initiated_by";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<initiated_by::enum_type>;
    using storage_type = result_type;

    constexpr initiated_by()
     : value{ enum_type{} } {}

    constexpr initiated_by(enum_type v)
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
            set(enum_type::both);
    }

  protected:
    enum_type value;
};
}
