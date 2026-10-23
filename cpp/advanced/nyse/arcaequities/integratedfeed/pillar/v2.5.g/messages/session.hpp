#pragma once

#include <cstddef>
#include <cstdint>

#include "../structs/PacketHeader.hpp"
#include "../structs/MessageHeader.hpp"
#include "dispatch.hpp"

// Forward declaration — full definition provided by callers via packet/Frame.hpp
namespace packet { struct Frame; }

namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g {

// Sequence filter result — controls per-segment processing
enum class seq_action : std::uint8_t { process, skip };

// Process all messages in a transport segment
// Handler must implement:
// seq_action on_transport_header(const packet_header&, const packet::Frame&)  — called once per segment, returns process or skip
// on_message(const <message_type>&, std::uint64_t packet_receive_time, const packet_header&)  — called per message (via dispatch)

template<typename Handler>
void process_segment(Handler& handler, const std::byte* data, std::size_t length, std::uint64_t packet_receive_time, const packet::Frame& frame) {
    if (length < sizeof(packet_header)) return;

    const auto* transport = packet_header::parse(data);
    if (handler.on_transport_header(*transport, frame) != seq_action::process) return;

    auto count = transport->number_msgs.get().value();

    const std::byte* cursor = data + sizeof(packet_header);
    const std::byte* end = data + length;

    for (std::uint16_t i = 0; i < count && cursor + sizeof(message_header) <= end; ++i) {
        const auto* msg_hdr = message_header::parse(cursor);
        // message_size is the total block size (inclusive of header)
        auto block_size = static_cast<std::size_t>(msg_hdr->message_size.get().value());

        if (cursor + block_size > end) break;

        dispatch(handler, cursor, block_size, packet_receive_time, *transport);
        cursor += block_size;
    }
}

}
