#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// delivery_flag
struct delivery_flag {

    enum class enum_type : std::uint8_t {
        heartbeat = 1,
        contains_original_and_refresh_msgs = 2,
        contains_only_refresh_messages = 3,
        xdp_failover = 10,
        contains_only_original_messages = 11,
        sequence_number_reset_message = 12
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 6> from_string_map = {{
        {"Contains Only Original Messages", enum_type::contains_only_original_messages},
        {"Contains Only Refresh Messages", enum_type::contains_only_refresh_messages},
        {"Contains Original And Refresh Msgs", enum_type::contains_original_and_refresh_msgs},
        {"Heartbeat", enum_type::heartbeat},
        {"Sequence Number Reset Message", enum_type::sequence_number_reset_message},
        {"XDP Failover", enum_type::xdp_failover}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::heartbeat: return "Heartbeat";
            case enum_type::contains_original_and_refresh_msgs: return "Contains Original And Refresh Msgs";
            case enum_type::contains_only_refresh_messages: return "Contains Only Refresh Messages";
            case enum_type::xdp_failover: return "XDP Failover";
            case enum_type::contains_only_original_messages: return "Contains Only Original Messages";
            case enum_type::sequence_number_reset_message: return "Sequence Number Reset Message";
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

    static constexpr const char* name = "delivery_flag";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<delivery_flag::enum_type>;
    using storage_type = result_type;

    constexpr delivery_flag()
     : value{ enum_type{} } {}

    constexpr delivery_flag(enum_type v)
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
            set(enum_type::sequence_number_reset_message);
    }

  protected:
    enum_type value;
};
}
