#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

// security_status
struct security_status {

    enum class enum_type : std::uint8_t {
        active = 1,
        inactive = 2,
        expired = 4,
        knocked_out = 6,
        knock_out_revoked = 7,
        suspended = 9,
        pending_deletion = 11,
        knocked_out_and_suspended = 12,
        no_value = 0xFF
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 9> from_string_map = {{
        {"Active", enum_type::active},
        {"Expired", enum_type::expired},
        {"Inactive", enum_type::inactive},
        {"Knock Out Revoked", enum_type::knock_out_revoked},
        {"Knocked Out", enum_type::knocked_out},
        {"Knocked Out And Suspended", enum_type::knocked_out_and_suspended},
        {"No Value", enum_type::no_value},
        {"Pending Deletion", enum_type::pending_deletion},
        {"Suspended", enum_type::suspended}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::active: return "Active";
            case enum_type::inactive: return "Inactive";
            case enum_type::expired: return "Expired";
            case enum_type::knocked_out: return "Knocked Out";
            case enum_type::knock_out_revoked: return "Knock Out Revoked";
            case enum_type::suspended: return "Suspended";
            case enum_type::pending_deletion: return "Pending Deletion";
            case enum_type::knocked_out_and_suspended: return "Knocked Out And Suspended";
            case enum_type::no_value: return "No Value";
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

    static constexpr const char* name = "security_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<security_status::enum_type>;
    using storage_type = result_type;

    constexpr security_status()
     : value{ enum_type{} } {}

    constexpr security_status(enum_type v)
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
            set(static_cast<enum_type>(0xFF));
    }

  protected:
    enum_type value;
};
}
