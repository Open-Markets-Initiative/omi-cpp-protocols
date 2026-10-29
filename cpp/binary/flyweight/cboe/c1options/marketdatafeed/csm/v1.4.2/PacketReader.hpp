#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/Packet.hpp"
#include "structs/Frame.hpp"
#include "enums/TemplateId.hpp"
#include "messages/SecurityDefinitionMessage.hpp"
#include "messages/CurrentMarketRefreshMessage.hpp"
#include "messages/MarketDataRefreshMessage.hpp"
#include "messages/CurrentMarketUpdateMessage.hpp"
#include "messages/RecapUpdateMessage.hpp"
#include "messages/TickerMessage.hpp"
#include "messages/ExpectedOpeningPriceAndSizeMessage.hpp"
#include "messages/IndexValueMessage.hpp"
#include "messages/SettlementValueMessage.hpp"
#include "messages/SummaryMessage.hpp"
#include "messages/MarketDataControlMessage.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

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
        const std::size_t count = wire::count(packet.packet_header().message_count());

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
        switch (frame.message_header().template_id()) {
            case TemplateId::SecurityDefinitionMessage: return handle<SecurityDefinitionMessage>(body, handler);
            case TemplateId::CurrentMarketRefreshMessage: return handle<CurrentMarketRefreshMessage>(body, handler);
            case TemplateId::MarketDataRefreshMessage: return handle<MarketDataRefreshMessage>(body, handler);
            case TemplateId::CurrentMarketUpdateMessage: return handle<CurrentMarketUpdateMessage>(body, handler);
            case TemplateId::RecapUpdateMessage: return handle<RecapUpdateMessage>(body, handler);
            case TemplateId::TickerMessage: return handle<TickerMessage>(body, handler);
            case TemplateId::ExpectedOpeningPriceAndSizeMessage: return handle<ExpectedOpeningPriceAndSizeMessage>(body, handler);
            case TemplateId::IndexValueMessage: return handle<IndexValueMessage>(body, handler);
            case TemplateId::SettlementValueMessage: return handle<SettlementValueMessage>(body, handler);
            case TemplateId::SummaryMessage: return handle<SummaryMessage>(body, handler);
            case TemplateId::MarketDataControlMessage: return handle<MarketDataControlMessage>(body, handler);
            default:
                if constexpr (requires { handler.on_unknown(frame.message_header().template_id(), body); }) { handler.on_unknown(frame.message_header().template_id(), body); }
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

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
