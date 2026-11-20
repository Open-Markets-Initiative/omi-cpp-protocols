// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: messages/details/HeartbeatBodyReader.hpp
#pragma once

#include "HeartbeatBodyWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

namespace xmt_quantumfeedlevel2 = ::tmx::tsx::quantumfeedlevel2::xmt::v2_10;


inline external_count_iterator<heartbeat_body_admin_body_entry> read_admin_body(const heartbeat_body& msg) {
    return { msg.tail_begin(), msg.header.num_body.get().value(), msg.tail_end() };
}

}
