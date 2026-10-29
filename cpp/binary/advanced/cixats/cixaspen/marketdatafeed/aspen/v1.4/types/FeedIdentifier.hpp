#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// feed_identifier
struct feed_identifier {

    enum class enum_type : char {
        aspen = 'A',
        aspen_vert = 'V',
        midpoint = 'M',
        aspen_uat = 'B',
        aspen_vert_uat = 'W',
        midpoint_uat = 'N'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 6> from_string_map = {{
        {"Aspen", enum_type::aspen},
        {"Aspen Uat", enum_type::aspen_uat},
        {"Aspen Vert", enum_type::aspen_vert},
        {"Aspen Vert Uat", enum_type::aspen_vert_uat},
        {"Midpoint", enum_type::midpoint},
        {"Midpoint Uat", enum_type::midpoint_uat}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::aspen: return "Aspen";
            case enum_type::aspen_vert: return "Aspen Vert";
            case enum_type::midpoint: return "Midpoint";
            case enum_type::aspen_uat: return "Aspen Uat";
            case enum_type::aspen_vert_uat: return "Aspen Vert Uat";
            case enum_type::midpoint_uat: return "Midpoint Uat";
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

    static constexpr const char* name = "feed_identifier";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<feed_identifier::enum_type>;
    using storage_type = result_type;

    constexpr feed_identifier()
     : value{ enum_type{} } {}

    constexpr feed_identifier(enum_type v)
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
            set(enum_type::midpoint_uat);
    }

  protected:
    enum_type value;
};
}
