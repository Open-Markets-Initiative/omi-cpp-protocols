#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cme::mdp3::v5 {

// halt_reason
struct halt_reason {

    enum class enum_type : std::uint8_t {
        group_schedule = 0,
        surveillance_intervention = 1,
        market_event = 2,
        instrument_activation = 3,
        instrument_expiration = 4,
        unknown = 5,
        recovery_in_process = 6
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 7> from_string_map = {{
        {"Group Schedule", enum_type::group_schedule},
        {"Instrument Activation", enum_type::instrument_activation},
        {"Instrument Expiration", enum_type::instrument_expiration},
        {"Market Event", enum_type::market_event},
        {"Recovery In Process", enum_type::recovery_in_process},
        {"Surveillance Intervention", enum_type::surveillance_intervention},
        {"Unknown", enum_type::unknown}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::group_schedule: return "Group Schedule";
            case enum_type::surveillance_intervention: return "Surveillance Intervention";
            case enum_type::market_event: return "Market Event";
            case enum_type::instrument_activation: return "Instrument Activation";
            case enum_type::instrument_expiration: return "Instrument Expiration";
            case enum_type::unknown: return "Unknown";
            case enum_type::recovery_in_process: return "Recovery In Process";
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

    static constexpr const char* name = "halt_reason";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<halt_reason::enum_type>;
    using storage_type = result_type;

    constexpr halt_reason()
     : value{ enum_type{} } {}

    constexpr halt_reason(enum_type v)
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
            set(enum_type::recovery_in_process);
    }

  protected:
    enum_type value;
};
}
