#pragma once

#include "NegotiateMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_1;


inline sbe_var_data read_credentials(const negotiate_message& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

inline sbe_var_data read_client_ip(const std::byte* pos, const negotiate_message& msg) {
    return { pos, msg.tail_end() };
}

inline sbe_var_data read_client_app_name(const std::byte* pos, const negotiate_message& msg) {
    return { pos, msg.tail_end() };
}

inline sbe_var_data read_client_app_version(const std::byte* pos, const negotiate_message& msg) {
    return { pos, msg.tail_end() };
}

}
