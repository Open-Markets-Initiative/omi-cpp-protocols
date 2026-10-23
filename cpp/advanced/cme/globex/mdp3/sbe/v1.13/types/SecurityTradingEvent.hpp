#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cme::mdp3::v13 {

// security_trading_event
struct security_trading_event {

    enum class enum_type : std::uint8_t {
        no_event = 0,
        no_cancel = 1,
        reset_statistics = 4,
        implied_matching_on = 5,
        implied_matching_off = 6,
        end_of_workup = 7
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 6> from_string_map = {{
        {"End Of Workup", enum_type::end_of_workup},
        {"Implied Matching Off", enum_type::implied_matching_off},
        {"Implied Matching On", enum_type::implied_matching_on},
        {"No Cancel", enum_type::no_cancel},
        {"No Event", enum_type::no_event},
        {"Reset Statistics", enum_type::reset_statistics}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::no_event: return "No Event";
            case enum_type::no_cancel: return "No Cancel";
            case enum_type::reset_statistics: return "Reset Statistics";
            case enum_type::implied_matching_on: return "Implied Matching On";
            case enum_type::implied_matching_off: return "Implied Matching Off";
            case enum_type::end_of_workup: return "End Of Workup";
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

    static constexpr const char* name = "security_trading_event";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<security_trading_event::enum_type>;
    using storage_type = result_type;

    constexpr security_trading_event()
     : value{ enum_type{} } {}

    constexpr security_trading_event(enum_type v)
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
            set(enum_type::end_of_workup);
    }

  protected:
    enum_type value;
};
}
