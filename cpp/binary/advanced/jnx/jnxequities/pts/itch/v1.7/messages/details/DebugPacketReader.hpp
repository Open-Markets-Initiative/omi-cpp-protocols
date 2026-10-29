#pragma once

#include "DebugPacketWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace jnx::jnxequities::pts::itch::v1_7 {

namespace itch_pts = ::jnx::jnxequities::pts::itch::v1_7;


inline external_var_data read_debug_text(const debug_packet& msg) {
    return { msg.tail_begin(), static_cast<std::size_t>(msg.header.packet_length.get().value() - 1), msg.tail_end() };
}

}
