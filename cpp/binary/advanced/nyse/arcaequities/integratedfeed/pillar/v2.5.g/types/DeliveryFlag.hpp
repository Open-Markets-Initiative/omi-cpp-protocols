#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g {

// delivery_flag
struct delivery_flag {

    enum class enum_type : std::uint8_t {
        heartbeat = 1,
        pillar_failover = 10,
        original_message = 11,
        sequence_number_reset_message = 12,
        one_retransmission_packet = 13,
        retransmission_sequence_message = 15,
        one_refresh_packet = 17,
        refresh_sequence_start = 18,
        refresh_sequence_message = 19,
        refresh_sequence_end = 20,
        message_unavailable = 21
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 11> from_string_map = {{
        {"Heartbeat", enum_type::heartbeat},
        {"Message Unavailable", enum_type::message_unavailable},
        {"One Refresh Packet", enum_type::one_refresh_packet},
        {"One Retransmission Packet", enum_type::one_retransmission_packet},
        {"Original Message", enum_type::original_message},
        {"Pillar Failover", enum_type::pillar_failover},
        {"Refresh Sequence End", enum_type::refresh_sequence_end},
        {"Refresh Sequence Message", enum_type::refresh_sequence_message},
        {"Refresh Sequence Start", enum_type::refresh_sequence_start},
        {"Retransmission Sequence Message", enum_type::retransmission_sequence_message},
        {"Sequence Number Reset Message", enum_type::sequence_number_reset_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::heartbeat: return "Heartbeat";
            case enum_type::pillar_failover: return "Pillar Failover";
            case enum_type::original_message: return "Original Message";
            case enum_type::sequence_number_reset_message: return "Sequence Number Reset Message";
            case enum_type::one_retransmission_packet: return "One Retransmission Packet";
            case enum_type::retransmission_sequence_message: return "Retransmission Sequence Message";
            case enum_type::one_refresh_packet: return "One Refresh Packet";
            case enum_type::refresh_sequence_start: return "Refresh Sequence Start";
            case enum_type::refresh_sequence_message: return "Refresh Sequence Message";
            case enum_type::refresh_sequence_end: return "Refresh Sequence End";
            case enum_type::message_unavailable: return "Message Unavailable";
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
            set(enum_type::message_unavailable);
    }

  protected:
    enum_type value;
};
}
