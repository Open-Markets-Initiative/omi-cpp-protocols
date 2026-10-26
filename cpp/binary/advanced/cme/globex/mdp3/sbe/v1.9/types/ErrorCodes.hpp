#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cme::mdp3::v9 {

// error_codes
struct error_codes {

    enum class enum_type : std::uint8_t {
        hmac_reject = 0,
        invalid_value = 1,
        slow_connection = 2,
        other = 3
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Hmac Reject", enum_type::hmac_reject},
        {"Invalid Value", enum_type::invalid_value},
        {"Other", enum_type::other},
        {"Slow Connection", enum_type::slow_connection}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::hmac_reject: return "Hmac Reject";
            case enum_type::invalid_value: return "Invalid Value";
            case enum_type::slow_connection: return "Slow Connection";
            case enum_type::other: return "Other";
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

    static constexpr const char* name = "error_codes";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<error_codes::enum_type>;
    using storage_type = result_type;

    constexpr error_codes()
     : value{ enum_type{} } {}

    constexpr error_codes(enum_type v)
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
            set(enum_type::other);
    }

  protected:
    enum_type value;
};
}
