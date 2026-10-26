#pragma once

#include <cstddef>
#include <cstdint>

#include "../structs/BinaryPacketHeader.hpp"
#include "../structs/SimpleBinaryHeader.hpp"
#include "../types/MessageSize.hpp"
#include "dispatch.hpp"

// Forward declaration — full definition provided by callers via packet/Frame.hpp
namespace packet { struct Frame; }

namespace cme::mdp3::v13 {

// Sequence filter result — controls per-segment processing
enum class seq_action : std::uint8_t { process, skip };

// Process message-delimited transport segment
// Messages are self-describing (each carries its own size) — iterate until end of payload
// Handler must implement:
// seq_action on_transport_header(const binary_packet_header&, const packet::Frame&)  — called once per segment, returns process or skip
// on_message(const <message_type>&, std::uint64_t packet_receive_time, const binary_packet_header&)  — called per message (via dispatch)

template<typename Handler>
void process_segment(Handler& handler, const std::byte* data, std::size_t length, std::uint64_t packet_receive_time, const packet::Frame& frame) {
    if (length < sizeof(binary_packet_header)) return;

    const auto* transport = binary_packet_header::parse(data);
    if (handler.on_transport_header(*transport, frame) != seq_action::process) return;

    const std::byte* cursor = data + sizeof(binary_packet_header);
    const std::byte* end = data + length;

    while (cursor + sizeof(message_size) + sizeof(simple_binary_header) <= end) {
        // message_size precedes the SBE header as transport framing
        auto block_size = static_cast<std::size_t>(reinterpret_cast<const message_size*>(cursor)->get().value());

        if (block_size == 0 || cursor + block_size > end) break;

        dispatch(handler, cursor, block_size, packet_receive_time, *transport);
        cursor += block_size;
    }
}

}
