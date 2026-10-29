#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// cancel_on_disconnect_type
struct cancel_on_disconnect_type {

    enum class enum_type : std::uint8_t {
        do_not_cancel_on_disconnect_or_terminate = 0,
        cancel_on_disconnect_only = 1,
        cancel_on_terminate_only = 2,
        cancel_on_disconnect_or_terminate = 3
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Cancel On Disconnect Only", enum_type::cancel_on_disconnect_only},
        {"Cancel On Disconnect Or Terminate", enum_type::cancel_on_disconnect_or_terminate},
        {"Cancel On Terminate Only", enum_type::cancel_on_terminate_only},
        {"Do Not Cancel On Disconnect Or Terminate", enum_type::do_not_cancel_on_disconnect_or_terminate}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::do_not_cancel_on_disconnect_or_terminate: return "Do Not Cancel On Disconnect Or Terminate";
            case enum_type::cancel_on_disconnect_only: return "Cancel On Disconnect Only";
            case enum_type::cancel_on_terminate_only: return "Cancel On Terminate Only";
            case enum_type::cancel_on_disconnect_or_terminate: return "Cancel On Disconnect Or Terminate";
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

    static constexpr const char* name = "cancel_on_disconnect_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<cancel_on_disconnect_type::enum_type>;
    using storage_type = result_type;

    constexpr cancel_on_disconnect_type()
     : value{ enum_type{} } {}

    constexpr cancel_on_disconnect_type(enum_type v)
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
            set(enum_type::cancel_on_disconnect_or_terminate);
    }

  protected:
    enum_type value;
};
}
