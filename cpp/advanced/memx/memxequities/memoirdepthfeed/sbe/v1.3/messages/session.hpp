#pragma once

#include <cstddef>
#include <cstdint>

#include "../structs/CommonHeader.hpp"
#include "../types/MessageCount.hpp"
#include "../types/MessageLength.hpp"
#include "dispatch.hpp"

// Forward declaration — full definition provided by callers via packet/Frame.hpp
namespace packet { struct Frame; }

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// Sequence filter result — controls per-segment processing
enum class seq_action : std::uint8_t { process, skip };

// Process messages in a gated count-based transport segment
// Gate: message_type == 2 selects sequenced messages (skips heartbeats/shutdown)
// Count: message_count controls inner message loop
// Handler must implement:
// seq_action on_transport_header(const common_header&, const packet::Frame&)  — called once per segment, returns process or skip
// on_message(const <message_type>&, std::uint64_t packet_receive_time, const common_header&)  — called per message (via dispatch)

template<typename Handler>
void process_segment(Handler& handler, const std::byte* data, std::size_t length, std::uint64_t packet_receive_time, const packet::Frame& frame) {
    const std::byte* cursor = data;
    const std::byte* end = data + length;

    if (cursor + sizeof(common_header) > end) return;
    const auto* hdr = common_header::parse(cursor);

    if (handler.on_transport_header(*hdr, frame) != seq_action::process) return;

    // Gate: only process sequenced messages (message_type == 2)
    if (static_cast<int>(hdr->message_type.get().value()) != 2) return;

    cursor += sizeof(common_header);

    // Read message count (type used directly — framing struct not generated)
    if (cursor + sizeof(message_count) > end) return;
    auto count = reinterpret_cast<const message_count*>(cursor)->get().value();
    cursor += sizeof(message_count);

    // Iterate messages
    for (decltype(count) i = 0; i < count && cursor + sizeof(message_length) <= end; ++i) {
        auto msg_len = reinterpret_cast<const message_length*>(cursor)->get().value();
        // msg_len excludes the length field; total block = value + 2
        auto block_size = static_cast<std::size_t>(msg_len) + 2;

        if (cursor + block_size > end) break;

        // Dispatch from after the message length field (pointing to dispatch struct)
        dispatch(handler, cursor + sizeof(message_length), msg_len, packet_receive_time, *hdr);
        cursor += block_size;
    }
}

}
