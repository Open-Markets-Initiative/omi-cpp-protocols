#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace iex::iexequities::deep::snap::v1_6 {

// reject_reason_code
struct reject_reason_code {

    enum class enum_type : char {
        authentication_failure = 'A',
        incorrect_channel_id = 'C',
        snapshot_request_already_active = 'E',
        quota_exceeded = 'Q',
        snapshot_not_yet_available = 'R',
        incorrect_session_id = 'S',
        unknown_message = 'U'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 7> from_string_map = {{
        {"Authentication Failure", enum_type::authentication_failure},
        {"Incorrect Channel Id", enum_type::incorrect_channel_id},
        {"Incorrect Session Id", enum_type::incorrect_session_id},
        {"Quota Exceeded", enum_type::quota_exceeded},
        {"Snapshot Not Yet Available", enum_type::snapshot_not_yet_available},
        {"Snapshot Request Already Active", enum_type::snapshot_request_already_active},
        {"Unknown Message", enum_type::unknown_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::authentication_failure: return "Authentication Failure";
            case enum_type::incorrect_channel_id: return "Incorrect Channel Id";
            case enum_type::snapshot_request_already_active: return "Snapshot Request Already Active";
            case enum_type::quota_exceeded: return "Quota Exceeded";
            case enum_type::snapshot_not_yet_available: return "Snapshot Not Yet Available";
            case enum_type::incorrect_session_id: return "Incorrect Session Id";
            case enum_type::unknown_message: return "Unknown Message";
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

    static constexpr const char* name = "reject_reason_code";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<reject_reason_code::enum_type>;
    using storage_type = result_type;

    constexpr reject_reason_code()
     : value{ enum_type::authentication_failure } {}

    constexpr reject_reason_code(enum_type v)
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
            set(enum_type::unknown_message);
    }

  protected:
    enum_type value;
};
}
