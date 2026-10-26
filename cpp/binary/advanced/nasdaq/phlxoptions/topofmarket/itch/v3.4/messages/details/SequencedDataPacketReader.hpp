#pragma once

#include "SequencedDataPacketWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

namespace itch_topofmarket = ::nasdaq::phlxoptions::topofmarket::itch::v3_4;


inline external_var_data read_sequenced_message(const sequenced_data_packet& msg) {
    return { msg.tail_begin(), static_cast<std::size_t>(msg.header.packet_length.get().value() - 2), msg.tail_end() };
}

}
