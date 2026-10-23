#pragma once

#include "DebugPacketWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

namespace itch_itto = ::nasdaq::nomoptions::itto::itch::v4_0_2025;


inline external_var_data read_debug_text(const debug_packet& msg) {
    return { msg.tail_begin(), static_cast<std::size_t>(msg.header.packet_length.get().value() - 1), msg.tail_end() };
}

}
