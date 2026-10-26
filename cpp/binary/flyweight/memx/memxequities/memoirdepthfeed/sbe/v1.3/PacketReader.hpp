#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/Packet.hpp"
#include "enums/MessageType.hpp"
#include "messages/SequencedMessage.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// Reads a Packet in place: its headers, then each message its frames carry, handed to the
// handler as a view of its bytes. A handler declares an on() for each view it wants; a view it
// declares none for is passed over, and a code no message answers to goes to on_unknown(code,
// body) when it declares one.
struct PacketReader {
    // Read one packet; what it returns is how many of the bytes the packet took.
    template <typename Handler>
    static std::size_t read(std::span<const std::byte> bytes, Handler& handler) {
        wire::require(Packet::name, Packet::minimum_size, bytes.size());
        const Packet packet{ bytes };
        if constexpr (requires { handler.on(packet); }) { handler.on(packet); }

        const std::size_t offset = packet.encoded_size();
        return offset + dispatch(packet, bytes.subspan(offset), handler);
    }

  private:
    template <typename Handler>
    static std::size_t dispatch(const Packet& packet, std::span<const std::byte> body, Handler& handler) {
        switch (packet.common_header().message_type()) {
            case MessageType::SequencedMessage: return handle<SequencedMessage>(body, handler);
            default:
                if constexpr (requires { handler.on_unknown(packet.common_header().message_type(), body); }) { handler.on_unknown(packet.common_header().message_type(), body); }
                return body.size();
        }
    }

    template <typename Message, typename Handler, typename... Handed>
    static std::size_t handle(std::span<const std::byte> body, Handler& handler, Handed... handed) {
        wire::require(Message::name, Message::minimum_size, body.size());
        const Message message{ body, handed... };
        if constexpr (requires { handler.on(message); }) { handler.on(message); }
        return message.encoded_size();
    }
};

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
