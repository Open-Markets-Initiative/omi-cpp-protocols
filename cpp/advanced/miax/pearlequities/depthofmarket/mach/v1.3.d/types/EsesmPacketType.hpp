#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// esesm_packet_type
struct esesm_packet_type {

    enum class enum_type : char {
        sequenced_data_packet = 's',
        unsequenced_data_packet = 'U',
        login_request = 'l',
        login_response = 'r',
        synchronization_complete = 'c',
        retransmission_request = 'a',
        logout_request = 'X',
        goodbye_packet = 'G',
        trading_session_update = 'u',
        server_heartbeat = '0',
        client_heartbeat = '1',
        test_packet = 'T'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 12> from_string_map = {{
        {"Client Heartbeat", enum_type::client_heartbeat},
        {"Goodbye Packet", enum_type::goodbye_packet},
        {"Login Request", enum_type::login_request},
        {"Login Response", enum_type::login_response},
        {"Logout Request", enum_type::logout_request},
        {"Retransmission Request", enum_type::retransmission_request},
        {"Sequenced Data Packet", enum_type::sequenced_data_packet},
        {"Server Heartbeat", enum_type::server_heartbeat},
        {"Synchronization Complete", enum_type::synchronization_complete},
        {"Test Packet", enum_type::test_packet},
        {"Trading Session Update", enum_type::trading_session_update},
        {"Unsequenced Data Packet", enum_type::unsequenced_data_packet}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::sequenced_data_packet: return "Sequenced Data Packet";
            case enum_type::unsequenced_data_packet: return "Unsequenced Data Packet";
            case enum_type::login_request: return "Login Request";
            case enum_type::login_response: return "Login Response";
            case enum_type::synchronization_complete: return "Synchronization Complete";
            case enum_type::retransmission_request: return "Retransmission Request";
            case enum_type::logout_request: return "Logout Request";
            case enum_type::goodbye_packet: return "Goodbye Packet";
            case enum_type::trading_session_update: return "Trading Session Update";
            case enum_type::server_heartbeat: return "Server Heartbeat";
            case enum_type::client_heartbeat: return "Client Heartbeat";
            case enum_type::test_packet: return "Test Packet";
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

    static constexpr const char* name = "esesm_packet_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<esesm_packet_type::enum_type>;
    using storage_type = result_type;

    constexpr esesm_packet_type()
     : value{ enum_type{} } {}

    constexpr esesm_packet_type(enum_type v)
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
            set(enum_type::test_packet);
    }

  protected:
    enum_type value;
};
}
