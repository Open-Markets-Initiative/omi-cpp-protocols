#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// mach_packet_type
struct mach_packet_type {

    enum class enum_type : std::uint8_t {
        heartbeat = 0,
        start_of_session = 1,
        end_of_session = 2,
        application_message = 3
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Application Message", enum_type::application_message},
        {"End Of Session", enum_type::end_of_session},
        {"Heartbeat", enum_type::heartbeat},
        {"Start Of Session", enum_type::start_of_session}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::heartbeat: return "Heartbeat";
            case enum_type::start_of_session: return "Start Of Session";
            case enum_type::end_of_session: return "End Of Session";
            case enum_type::application_message: return "Application Message";
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

    static constexpr const char* name = "mach_packet_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<mach_packet_type::enum_type>;
    using storage_type = result_type;

    constexpr mach_packet_type()
     : value{ enum_type{} } {}

    constexpr mach_packet_type(enum_type v)
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
            set(enum_type::application_message);
    }

  protected:
    enum_type value;
};
}
