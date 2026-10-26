#pragma once

#include <cstddef>
#include <cstdint>

#include "../structs/BlockHeader.hpp"
#include "dispatch.hpp"

// Forward declaration — full definition provided by callers via packet/Frame.hpp
namespace packet { struct Frame; }

namespace siac::opra::output::obi::v6_2 {

// Sequence filter result — controls per-segment processing
enum class seq_action : std::uint8_t { process, skip };

// Process all messages in a transport segment (branch-dispatched sizing)
// Handler must implement:
// seq_action on_transport_header(const block_header&, const packet::Frame&)  — called once per segment
// on_message(const <message_type>&, std::uint64_t packet_receive_time, const block_header&)  — called per message (via dispatch)
// dispatch() returns the number of bytes consumed per message

template<typename Handler>
void process_segment(Handler& handler, const std::byte* data, std::size_t length, std::uint64_t packet_receive_time, const packet::Frame& frame) {
    if (length < sizeof(block_header)) return;

    const auto* transport = block_header::parse(data);
    if (handler.on_transport_header(*transport, frame) != seq_action::process) return;

    auto count = transport->messages_in_block.get().value();

    const std::byte* cursor = data + sizeof(block_header);
    const std::byte* end = data + length;

    for (decltype(count) i = 0; i < count && cursor < end; ++i) {
        auto consumed = dispatch(handler, cursor, static_cast<std::size_t>(end - cursor), packet_receive_time, *transport);
        if (consumed == 0) break;
        cursor += consumed;
    }
}

}
