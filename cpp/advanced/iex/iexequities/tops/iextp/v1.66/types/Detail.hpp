#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace iex::iexequities::tops::iextp::v1_66 {

// detail
struct detail {

    enum class enum_type : char {
        no_price_test_in_place = ' ',
        activated = 'A',
        continued = 'C',
        deactivated = 'D',
        not_available = 'N'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Activated", enum_type::activated},
        {"Continued", enum_type::continued},
        {"Deactivated", enum_type::deactivated},
        {"No Price Test In Place", enum_type::no_price_test_in_place},
        {"Not Available", enum_type::not_available}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::no_price_test_in_place: return "No Price Test In Place";
            case enum_type::activated: return "Activated";
            case enum_type::continued: return "Continued";
            case enum_type::deactivated: return "Deactivated";
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

    static constexpr const char* name = "detail";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<detail::enum_type>;
    using storage_type = result_type;

    constexpr detail()
     : value{ enum_type::no_price_test_in_place } {}

    constexpr detail(enum_type v)
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
