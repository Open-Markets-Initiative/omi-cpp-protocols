#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// retransmit_reject_code
struct retransmit_reject_code {

    enum class enum_type : std::uint8_t {
        out_of_range = 0,
        invalid_session = 1,
        request_limit_exceeded = 2,
        retransmit_in_progress = 3,
        invalid_timestamp = 4,
        invalid_fromseqno = 5,
        invalid_count = 9,
        throttle_reject = 10,
        system_busy = 11
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 9> from_string_map = {{
        {"Invalid Count", enum_type::invalid_count},
        {"Invalid Fromseqno", enum_type::invalid_fromseqno},
        {"Invalid Session", enum_type::invalid_session},
        {"Invalid Timestamp", enum_type::invalid_timestamp},
        {"Out Of Range", enum_type::out_of_range},
        {"Request Limit Exceeded", enum_type::request_limit_exceeded},
        {"Retransmit In Progress", enum_type::retransmit_in_progress},
        {"System Busy", enum_type::system_busy},
        {"Throttle Reject", enum_type::throttle_reject}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::out_of_range: return "Out Of Range";
            case enum_type::invalid_session: return "Invalid Session";
            case enum_type::request_limit_exceeded: return "Request Limit Exceeded";
            case enum_type::retransmit_in_progress: return "Retransmit In Progress";
            case enum_type::invalid_timestamp: return "Invalid Timestamp";
            case enum_type::invalid_fromseqno: return "Invalid Fromseqno";
            case enum_type::invalid_count: return "Invalid Count";
            case enum_type::throttle_reject: return "Throttle Reject";
            case enum_type::system_busy: return "System Busy";
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

    static constexpr const char* name = "retransmit_reject_code";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<retransmit_reject_code::enum_type>;
    using storage_type = result_type;

    constexpr retransmit_reject_code()
     : value{ enum_type{} } {}

    constexpr retransmit_reject_code(enum_type v)
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
            set(enum_type::system_busy);
    }

  protected:
    enum_type value;
};
}
