#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// login_status
struct login_status {

    enum class enum_type : char {
        successful = ' ',
        invalid_trading_session_requested = 'S',
        no_active_trading_session_exists = 'U',
        rejected = 'X',
        invalid_start_sequence_number_requested = 'N',
        incompatible_session_protocol_version = 'I',
        incompatible_application_protocol_version = 'A',
        request_rejected_because_client_already_logged_in = 'L'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 8> from_string_map = {{
        {"Incompatible Application Protocol Version", enum_type::incompatible_application_protocol_version},
        {"Incompatible Session Protocol Version", enum_type::incompatible_session_protocol_version},
        {"Invalid Start Sequence Number Requested", enum_type::invalid_start_sequence_number_requested},
        {"Invalid Trading Session Requested", enum_type::invalid_trading_session_requested},
        {"No Active Trading Session Exists", enum_type::no_active_trading_session_exists},
        {"Rejected", enum_type::rejected},
        {"Request Rejected Because Client Already Logged In", enum_type::request_rejected_because_client_already_logged_in},
        {"Successful", enum_type::successful}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::successful: return "Successful";
            case enum_type::invalid_trading_session_requested: return "Invalid Trading Session Requested";
            case enum_type::no_active_trading_session_exists: return "No Active Trading Session Exists";
            case enum_type::rejected: return "Rejected";
            case enum_type::invalid_start_sequence_number_requested: return "Invalid Start Sequence Number Requested";
            case enum_type::incompatible_session_protocol_version: return "Incompatible Session Protocol Version";
            case enum_type::incompatible_application_protocol_version: return "Incompatible Application Protocol Version";
            case enum_type::request_rejected_because_client_already_logged_in: return "Request Rejected Because Client Already Logged In";
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

    static constexpr const char* name = "login_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<login_status::enum_type>;
    using storage_type = result_type;

    constexpr login_status()
     : value{ enum_type{} } {}

    constexpr login_status(enum_type v)
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
            set(enum_type::request_rejected_because_client_already_logged_in);
    }

  protected:
    enum_type value;
};
}
