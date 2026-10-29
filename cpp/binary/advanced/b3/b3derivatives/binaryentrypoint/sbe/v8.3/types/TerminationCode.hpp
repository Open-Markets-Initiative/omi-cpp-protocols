#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// termination_code
struct termination_code {

    enum class enum_type : std::uint8_t {
        unspecified = 0,
        finished = 1,
        unnegotiated = 2,
        not_established = 3,
        session_blocked = 4,
        negotiation_in_progress = 5,
        establish_in_progress = 6,
        keepalive_interval_lapsed = 10,
        invalid_sessionid = 11,
        invalid_sessionverid = 12,
        invalid_timestamp = 13,
        invalid_nextseqno = 14,
        unrecognized_message = 15,
        invalid_sofh = 16,
        decoding_error = 17,
        terminate_not_allowed = 20,
        terminate_in_progress = 21,
        protocol_version_not_supported = 23,
        backup_takeover_in_progress = 30
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 19> from_string_map = {{
        {"Backup Takeover In Progress", enum_type::backup_takeover_in_progress},
        {"Decoding Error", enum_type::decoding_error},
        {"Establish In Progress", enum_type::establish_in_progress},
        {"Finished", enum_type::finished},
        {"Invalid Nextseqno", enum_type::invalid_nextseqno},
        {"Invalid Sessionid", enum_type::invalid_sessionid},
        {"Invalid Sessionverid", enum_type::invalid_sessionverid},
        {"Invalid Sofh", enum_type::invalid_sofh},
        {"Invalid Timestamp", enum_type::invalid_timestamp},
        {"Keepalive Interval Lapsed", enum_type::keepalive_interval_lapsed},
        {"Negotiation In Progress", enum_type::negotiation_in_progress},
        {"Not Established", enum_type::not_established},
        {"Protocol Version Not Supported", enum_type::protocol_version_not_supported},
        {"Session Blocked", enum_type::session_blocked},
        {"Terminate In Progress", enum_type::terminate_in_progress},
        {"Terminate Not Allowed", enum_type::terminate_not_allowed},
        {"Unnegotiated", enum_type::unnegotiated},
        {"Unrecognized Message", enum_type::unrecognized_message},
        {"Unspecified", enum_type::unspecified}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::unspecified: return "Unspecified";
            case enum_type::finished: return "Finished";
            case enum_type::unnegotiated: return "Unnegotiated";
            case enum_type::not_established: return "Not Established";
            case enum_type::session_blocked: return "Session Blocked";
            case enum_type::negotiation_in_progress: return "Negotiation In Progress";
            case enum_type::establish_in_progress: return "Establish In Progress";
            case enum_type::keepalive_interval_lapsed: return "Keepalive Interval Lapsed";
            case enum_type::invalid_sessionid: return "Invalid Sessionid";
            case enum_type::invalid_sessionverid: return "Invalid Sessionverid";
            case enum_type::invalid_timestamp: return "Invalid Timestamp";
            case enum_type::invalid_nextseqno: return "Invalid Nextseqno";
            case enum_type::unrecognized_message: return "Unrecognized Message";
            case enum_type::invalid_sofh: return "Invalid Sofh";
            case enum_type::decoding_error: return "Decoding Error";
            case enum_type::terminate_not_allowed: return "Terminate Not Allowed";
            case enum_type::terminate_in_progress: return "Terminate In Progress";
            case enum_type::protocol_version_not_supported: return "Protocol Version Not Supported";
            case enum_type::backup_takeover_in_progress: return "Backup Takeover In Progress";
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

    static constexpr const char* name = "termination_code";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<termination_code::enum_type>;
    using storage_type = result_type;

    constexpr termination_code()
     : value{ enum_type{} } {}

    constexpr termination_code(enum_type v)
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
            set(enum_type::backup_takeover_in_progress);
    }

  protected:
    enum_type value;
};
}
