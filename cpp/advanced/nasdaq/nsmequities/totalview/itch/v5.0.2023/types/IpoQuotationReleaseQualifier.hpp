#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// ipo_quotation_release_qualifier
struct ipo_quotation_release_qualifier {

    enum class enum_type : char {
        anticipated_quotation_release_time = 'A',
        ipo_release_canceled_or_postponed = 'C'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Anticipated Quotation Release Time", enum_type::anticipated_quotation_release_time},
        {"Ipo Release Canceled Or Postponed", enum_type::ipo_release_canceled_or_postponed}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::anticipated_quotation_release_time: return "Anticipated Quotation Release Time";
            case enum_type::ipo_release_canceled_or_postponed: return "Ipo Release Canceled Or Postponed";
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

    static constexpr const char* name = "ipo_quotation_release_qualifier";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<ipo_quotation_release_qualifier::enum_type>;
    using storage_type = result_type;

    constexpr ipo_quotation_release_qualifier()
     : value{ enum_type::anticipated_quotation_release_time } {}

    constexpr ipo_quotation_release_qualifier(enum_type v)
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
            set(enum_type::ipo_release_canceled_or_postponed);
    }

  protected:
    enum_type value;
};
}
