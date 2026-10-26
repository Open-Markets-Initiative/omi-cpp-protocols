#pragma once

#include "UnsequencedDataPacketWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v5_0_2017;


inline external_var_data read_unsequenced_message(const unsequenced_data_packet& msg) {
    return { msg.tail_begin(), static_cast<std::size_t>(msg.header.packet_length.get().value() - 2), msg.tail_end() };
}

}
