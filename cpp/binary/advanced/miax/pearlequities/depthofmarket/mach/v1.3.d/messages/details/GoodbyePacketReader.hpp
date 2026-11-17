// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/details/GoodbyePacketReader.hpp
#pragma once

#include "GoodbyePacketWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;


inline external_var_data read_logout_text(const goodbye_packet& msg) {
    return { msg.tail_begin(), static_cast<std::size_t>(msg.header.esesm_packet_length.get().value() - 2), msg.tail_end() };
}

}
