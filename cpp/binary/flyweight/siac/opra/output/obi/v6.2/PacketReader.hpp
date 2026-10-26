#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/Packet.hpp"
#include "structs/Frame.hpp"
#include "enums/MessageCategory.hpp"
#include "messages/AdministrativeCategory.hpp"
#include "messages/ControlCategory.hpp"
#include "messages/EquityAndIndexLastSaleCategory.hpp"
#include "messages/OpenInterestCategory.hpp"
#include "messages/EquityAndIndexEndOfDaySummaryCategory.hpp"
#include "messages/LongEquityAndIndexQuoteCategory.hpp"
#include "messages/ShortEquityAndIndexQuoteCategory.hpp"
#include "messages/UnderlyingValueCategory.hpp"

namespace siac::opra::output::obi::v6_2 {

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

        std::size_t offset = packet.encoded_size();
        const std::size_t count = wire::count(packet.block_header().messages_in_block());

        for (std::size_t index = 0; index < count; ++index) {
            wire::require(Frame::name, offset + Frame::minimum_size, bytes.size());
            const Frame frame{ bytes.subspan(offset) };
            offset += frame.encoded_size();
            offset += dispatch(frame, bytes.subspan(offset), handler);
        }

        return offset;
    }

  private:
    template <typename Handler>
    static std::size_t dispatch(const Frame& frame, std::span<const std::byte> body, Handler& handler) {
        switch (frame.message_header().message_category()) {
            case MessageCategory::Administrative: return handle<AdministrativeCategory>(body, handler);
            case MessageCategory::Control: return handle<ControlCategory>(body, handler);
            case MessageCategory::EquityAndIndexLastSale: return handle<EquityAndIndexLastSaleCategory>(body, handler);
            case MessageCategory::OpenInterest: return handle<OpenInterestCategory>(body, handler);
            case MessageCategory::EquityAndIndexEndOfDaySummary: return handle<EquityAndIndexEndOfDaySummaryCategory>(body, handler);
            case MessageCategory::LongEquityAndIndexQuote: return handle<LongEquityAndIndexQuoteCategory>(body, handler);
            case MessageCategory::ShortEquityAndIndexQuote: return handle<ShortEquityAndIndexQuoteCategory>(body, handler);
            case MessageCategory::UnderlyingValue: return handle<UnderlyingValueCategory>(body, handler);
            default:
                if constexpr (requires { handler.on_unknown(frame.message_header().message_category(), body); }) { handler.on_unknown(frame.message_header().message_category(), body); }
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

} // namespace siac::opra::output::obi::v6_2
