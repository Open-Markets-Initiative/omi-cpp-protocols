#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// client_packet_type
struct client_packet_type {

    enum class enum_type : char {
        debug_packet = '+',
        login_request_packet = 'L',
        unsequenced_data_packet = 'U',
        client_heartbeat_packet = 'R',
        logout_request_packet = 'O'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Client Heartbeat Packet", enum_type::client_heartbeat_packet},
        {"Debug Packet", enum_type::debug_packet},
        {"Login Request Packet", enum_type::login_request_packet},
        {"Logout Request Packet", enum_type::logout_request_packet},
        {"Unsequenced Data Packet", enum_type::unsequenced_data_packet}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::debug_packet: return "Debug Packet";
            case enum_type::login_request_packet: return "Login Request Packet";
            case enum_type::unsequenced_data_packet: return "Unsequenced Data Packet";
            case enum_type::client_heartbeat_packet: return "Client Heartbeat Packet";
            case enum_type::logout_request_packet: return "Logout Request Packet";
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

    static constexpr const char* name = "client_packet_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<client_packet_type::enum_type>;
    using storage_type = result_type;

    constexpr client_packet_type()
     : value{ enum_type::debug_packet } {}

    constexpr client_packet_type(enum_type v)
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
            set(enum_type::logout_request_packet);
    }

  protected:
    enum_type value;
};
}
