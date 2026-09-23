#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// server_packet_type
struct server_packet_type {

    enum class enum_type : char {
        debug_packet = '+',
        login_accepted_packet = 'A',
        login_rejected_packet = 'J',
        sequenced_data_packet = 'S',
        server_heartbeat_packet = 'H',
        end_of_session_packet = 'Z'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 6> from_string_map = {{
        {"Debug Packet", enum_type::debug_packet},
        {"End Of Session Packet", enum_type::end_of_session_packet},
        {"Login Accepted Packet", enum_type::login_accepted_packet},
        {"Login Rejected Packet", enum_type::login_rejected_packet},
        {"Sequenced Data Packet", enum_type::sequenced_data_packet},
        {"Server Heartbeat Packet", enum_type::server_heartbeat_packet}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::debug_packet: return "Debug Packet";
            case enum_type::login_accepted_packet: return "Login Accepted Packet";
            case enum_type::login_rejected_packet: return "Login Rejected Packet";
            case enum_type::sequenced_data_packet: return "Sequenced Data Packet";
            case enum_type::server_heartbeat_packet: return "Server Heartbeat Packet";
            case enum_type::end_of_session_packet: return "End Of Session Packet";
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

    static constexpr const char* name = "server_packet_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<server_packet_type::enum_type>;
    using storage_type = result_type;

    constexpr server_packet_type()
     : value{ enum_type::debug_packet } {}

    constexpr server_packet_type(enum_type v)
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
            set(enum_type::end_of_session_packet);
    }

  protected:
    enum_type value;
};
}
