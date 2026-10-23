#pragma once

#include "RefreshResponseMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

namespace mach_topofmarket = ::miax::miaxoptions::topofmarket::mach::v2_5;


inline external_var_data read_application_message(const refresh_response_message& msg) {
    return { msg.tail_begin(), static_cast<std::size_t>(msg.header.sesm_packet_length.get().value() - 12), msg.tail_end() };
}

}
