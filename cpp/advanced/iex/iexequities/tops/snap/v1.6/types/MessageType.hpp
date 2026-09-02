#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace iex::iexequities::tops::snap::v1_6 {

// message_type
struct message_type {

    enum class enum_type : char {
        snapshot_request_message = 'r',
        error_response_message = 'e',
        snapshot_start_message = 's',
        snapshot_data_message = 'd',
        snapshot_end_message = 'x'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Error Response Message", enum_type::error_response_message},
        {"Snapshot Data Message", enum_type::snapshot_data_message},
        {"Snapshot End Message", enum_type::snapshot_end_message},
        {"Snapshot Request Message", enum_type::snapshot_request_message},
        {"Snapshot Start Message", enum_type::snapshot_start_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::snapshot_request_message: return "Snapshot Request Message";
            case enum_type::error_response_message: return "Error Response Message";
            case enum_type::snapshot_start_message: return "Snapshot Start Message";
            case enum_type::snapshot_data_message: return "Snapshot Data Message";
            case enum_type::snapshot_end_message: return "Snapshot End Message";
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

    static constexpr const char* name = "message_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<message_type::enum_type>;
    using storage_type = result_type;

    constexpr message_type()
     : value{ enum_type::snapshot_request_message } {}

    constexpr message_type(enum_type v)
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
            set(enum_type::snapshot_end_message);
    }

  protected:
    enum_type value;
};
}
