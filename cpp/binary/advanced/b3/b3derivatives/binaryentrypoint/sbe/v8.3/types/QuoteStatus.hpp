#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// quote_status
struct quote_status {

    enum class enum_type : std::uint8_t {
        expired = 7,
        accepted = 0,
        rejected = 5,
        quote_not_found = 9,
        pending = 10,
        pass = 11,
        canceled = 17
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 7> from_string_map = {{
        {"Accepted", enum_type::accepted},
        {"Canceled", enum_type::canceled},
        {"Expired", enum_type::expired},
        {"Pass", enum_type::pass},
        {"Pending", enum_type::pending},
        {"Quote Not Found", enum_type::quote_not_found},
        {"Rejected", enum_type::rejected}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::expired: return "Expired";
            case enum_type::accepted: return "Accepted";
            case enum_type::rejected: return "Rejected";
            case enum_type::quote_not_found: return "Quote Not Found";
            case enum_type::pending: return "Pending";
            case enum_type::pass: return "Pass";
            case enum_type::canceled: return "Canceled";
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

    static constexpr const char* name = "quote_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<quote_status::enum_type>;
    using storage_type = result_type;

    constexpr quote_status()
     : value{ enum_type{} } {}

    constexpr quote_status(enum_type v)
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
            set(enum_type::canceled);
    }

  protected:
    enum_type value;
};
}
