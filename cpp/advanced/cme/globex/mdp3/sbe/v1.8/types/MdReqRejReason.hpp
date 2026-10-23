#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cme::mdp3::v8 {

// md_req_rej_reason
struct md_req_rej_reason {

    enum class enum_type : std::uint8_t {
        unknown_security = 0,
        unknown_message = 1,
        unsupported_scope = 2,
        other = 3
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Other", enum_type::other},
        {"Unknown Message", enum_type::unknown_message},
        {"Unknown Security", enum_type::unknown_security},
        {"Unsupported Scope", enum_type::unsupported_scope}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::unknown_security: return "Unknown Security";
            case enum_type::unknown_message: return "Unknown Message";
            case enum_type::unsupported_scope: return "Unsupported Scope";
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

    static constexpr const char* name = "md_req_rej_reason";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<md_req_rej_reason::enum_type>;
    using storage_type = result_type;

    constexpr md_req_rej_reason()
     : value{ enum_type{} } {}

    constexpr md_req_rej_reason(enum_type v)
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
