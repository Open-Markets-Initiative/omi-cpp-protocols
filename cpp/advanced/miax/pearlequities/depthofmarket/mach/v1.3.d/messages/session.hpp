#pragma once

#include <cstddef>
#include <cstdint>

#include "../structs/MachMessage.hpp"
#include "dispatch.hpp"

// Forward declaration — full definition provided by callers via packet/Frame.hpp
namespace packet { struct Frame; }

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Sequence filter result — controls per-packet processing
enum class seq_action : std::uint8_t { process, skip };

// Process concatenated sub-packets in a UDP payload (size-based iteration)
// Handler must implement:
// seq_action on_transport_header(const mach_message&, const packet::Frame&)  — called per sub-packet
// on_message(const <message_type>&, std::uint64_t packet_receive_time, const mach_message&)  — called per application message (via dispatch)

template<typename Handler>
void process_segment(Handler& handler, const std::byte* data, std::size_t length, std::uint64_t packet_receive_time, const packet::Frame& frame) {
    const std::byte* cursor = data;
    const std::byte* end = data + length;

    while (cursor + sizeof(mach_message) <= end) {
        const auto* hdr = mach_message::parse(cursor);
        auto mach_packet_length = hdr->mach_packet_length.get().value();

        if (mach_packet_length < sizeof(mach_message) || cursor + mach_packet_length > end) break;

        if (handler.on_transport_header(*hdr, frame) == seq_action::process) {
            // Only dispatch application messages (packet_type == 0)
            if (static_cast<int>(hdr->mach_packet_type.get().value()) == 0) {
                const std::byte* msg_start = cursor + sizeof(mach_message);
                auto msg_size = static_cast<std::size_t>(mach_packet_length) - sizeof(mach_message);
                dispatch(handler, msg_start, msg_size, packet_receive_time, *hdr);
            }
        }

        cursor += mach_packet_length;
    }
}

}
