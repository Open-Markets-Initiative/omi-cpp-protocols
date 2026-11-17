// Siac.Cts.Output.Cta.v2.11.b: messages/session.hpp
#pragma once

#include <cstddef>
#include <cstdint>

#include "../structs/BlockHeader.hpp"
#include "../structs/AdministrativeMessage.hpp"
#include "../types/MessageLength.hpp"
#include "dispatch.hpp"

// Forward declaration — full definition provided by callers via packet/Frame.hpp
namespace packet { struct Frame; }

namespace siac::cts::output::cta::v2_11_b {

// Sequence filter result — controls per-segment processing
enum class seq_action : std::uint8_t { process, skip };

// Process all messages in a transport segment
// Handler must implement:
// seq_action on_transport_header(const block_header&, const packet::Frame&)  — called once per segment, returns process or skip
// on_message(const <message_type>&, std::uint64_t packet_receive_time, const block_header&)  — called per message (via dispatch)

template<typename Handler>
void process_segment(Handler& handler, const std::byte* data, std::size_t length, std::uint64_t packet_receive_time, const packet::Frame& frame) {
    if (length < sizeof(block_header)) return;

    const auto* transport = block_header::parse(data);
    if (handler.on_transport_header(*transport, frame) != seq_action::process) return;

    auto count = transport->messages_in_block.get().value();

    const std::byte* cursor = data + sizeof(block_header);
    const std::byte* end = data + length;

    for (std::uint16_t i = 0; i < count && cursor + sizeof(message_length) + sizeof(administrative_message) <= end; ++i) {
        // message_length precedes the SBE header as transport framing
        auto block_size = static_cast<std::size_t>(reinterpret_cast<const message_length*>(cursor)->get().value());

        if (cursor + block_size > end) break;

        dispatch(handler, cursor, block_size, packet_receive_time, *transport);
        cursor += block_size;
    }
}

}
