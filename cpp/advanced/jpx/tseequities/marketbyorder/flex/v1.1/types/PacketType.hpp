#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// packet_type
struct packet_type {

    enum class enum_type : char {
        login_request_message = 'R',
        login_result_message = 'A',
        message_response_message = 'S',
        end_of_message_message = 'G'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"End Of Message Message", enum_type::end_of_message_message},
        {"Login Request Message", enum_type::login_request_message},
        {"Login Result Message", enum_type::login_result_message},
        {"Message Response Message", enum_type::message_response_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::login_request_message: return "Login Request Message";
            case enum_type::login_result_message: return "Login Result Message";
            case enum_type::message_response_message: return "Message Response Message";
            case enum_type::end_of_message_message: return "End Of Message Message";
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

    static constexpr const char* name = "packet_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<packet_type::enum_type>;
    using storage_type = result_type;

    constexpr packet_type()
     : value{ enum_type::login_request_message } {}

    constexpr packet_type(enum_type v)
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
            set(enum_type::end_of_message_message);
    }

  protected:
    enum_type value;
};
}
