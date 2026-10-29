#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// negotiation_reject_code
struct negotiation_reject_code {

    enum class enum_type : std::uint8_t {
        unspecified = 0,
        credentials = 1,
        flowtype_not_supported = 2,
        already_negotiated = 3,
        session_blocked = 4,
        invalid_sessionid = 5,
        invalid_sessionverid = 6,
        invalid_timestamp = 7,
        invalid_firm = 8,
        negotiate_not_allowed = 20,
        duplicate_session_connection = 21,
        authentication_in_progress = 22,
        protocol_version_not_supported = 23
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 13> from_string_map = {{
        {"Already Negotiated", enum_type::already_negotiated},
        {"Authentication In Progress", enum_type::authentication_in_progress},
        {"Credentials", enum_type::credentials},
        {"Duplicate Session Connection", enum_type::duplicate_session_connection},
        {"Flowtype Not Supported", enum_type::flowtype_not_supported},
        {"Invalid Firm", enum_type::invalid_firm},
        {"Invalid Sessionid", enum_type::invalid_sessionid},
        {"Invalid Sessionverid", enum_type::invalid_sessionverid},
        {"Invalid Timestamp", enum_type::invalid_timestamp},
        {"Negotiate Not Allowed", enum_type::negotiate_not_allowed},
        {"Protocol Version Not Supported", enum_type::protocol_version_not_supported},
        {"Session Blocked", enum_type::session_blocked},
        {"Unspecified", enum_type::unspecified}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::unspecified: return "Unspecified";
            case enum_type::credentials: return "Credentials";
            case enum_type::flowtype_not_supported: return "Flowtype Not Supported";
            case enum_type::already_negotiated: return "Already Negotiated";
            case enum_type::session_blocked: return "Session Blocked";
            case enum_type::invalid_sessionid: return "Invalid Sessionid";
            case enum_type::invalid_sessionverid: return "Invalid Sessionverid";
            case enum_type::invalid_timestamp: return "Invalid Timestamp";
            case enum_type::invalid_firm: return "Invalid Firm";
            case enum_type::negotiate_not_allowed: return "Negotiate Not Allowed";
            case enum_type::duplicate_session_connection: return "Duplicate Session Connection";
            case enum_type::authentication_in_progress: return "Authentication In Progress";
            case enum_type::protocol_version_not_supported: return "Protocol Version Not Supported";
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

    static constexpr const char* name = "negotiation_reject_code";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<negotiation_reject_code::enum_type>;
    using storage_type = result_type;

    constexpr negotiation_reject_code()
     : value{ enum_type{} } {}

    constexpr negotiation_reject_code(enum_type v)
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
            set(enum_type::protocol_version_not_supported);
    }

  protected:
    enum_type value;
};
}
