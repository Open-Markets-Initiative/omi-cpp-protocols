// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/SecurityStatus.hpp
#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// security_status
struct security_status {

    enum class enum_type : char {
        active = 'A',
        quote_only = 'Q',
        suspended = 'S',
        halted = 'H',
        internal_halt = 'I',
        revoked = 'R',
        deleted = 'D'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 7> from_string_map = {{
        {"Active", enum_type::active},
        {"Deleted", enum_type::deleted},
        {"Halted", enum_type::halted},
        {"Internal Halt", enum_type::internal_halt},
        {"Quote Only", enum_type::quote_only},
        {"Revoked", enum_type::revoked},
        {"Suspended", enum_type::suspended}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::active: return "Active";
            case enum_type::quote_only: return "Quote Only";
            case enum_type::suspended: return "Suspended";
            case enum_type::halted: return "Halted";
            case enum_type::internal_halt: return "Internal Halt";
            case enum_type::revoked: return "Revoked";
            case enum_type::deleted: return "Deleted";
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
            set(enum_type::deleted);
    }

  protected:
    enum_type value;
};
}
