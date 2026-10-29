#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/Packet.hpp"
#include "structs/Frame.hpp"
#include "enums/TemplateId.hpp"
#include "messages/HeartbeatMessage.hpp"
#include "messages/ProductSummaryMessage.hpp"
#include "messages/SnapshotOrderMessage.hpp"
#include "messages/InstrumentSummaryMessage.hpp"
#include "messages/AuctionBestBidOfferMessage.hpp"
#include "messages/AuctionClearingPriceMessage.hpp"
#include "messages/TopOfBookMessage.hpp"
#include "messages/OrderAddMessage.hpp"
#include "messages/OrderModifyMessage.hpp"
#include "messages/OrderModifySamePriorityMessage.hpp"
#include "messages/OrderDeleteMessage.hpp"
#include "messages/OrderMassDeleteMessage.hpp"
#include "messages/PartialOrderExecutionMessage.hpp"
#include "messages/FullOrderExecutionMessage.hpp"
#include "messages/TradeReversalMessage.hpp"
#include "messages/ExecutionSummaryMessage.hpp"
#include "messages/InstrumentInfoMessage.hpp"
#include "messages/LppRangeMessage.hpp"
#include "messages/ProductStateChangeMessage.hpp"
#include "messages/InstrumentStateChangeMessage.hpp"
#include "messages/AddComplexInstrumentMessage.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

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

        while (offset < bytes.size()) {
            const std::size_t start = offset;
            wire::require(Frame::name, offset + Frame::minimum_size, bytes.size());
            const Frame frame{ bytes.subspan(offset) };
            offset += frame.encoded_size();
            const std::size_t frame_size = wire::count(frame.message_header().body_len());
            wire::require(Packet::name, start + frame_size, bytes.size());
            dispatch(frame, bytes.subspan(offset, start + frame_size - offset), handler);
            offset = start + frame_size;
        }

        return offset;
    }

  private:
    template <typename Handler>
    static std::size_t dispatch(const Frame& frame, std::span<const std::byte> body, Handler& handler) {
        switch (frame.message_header().template_id()) {
            case TemplateId::HeartbeatMessage: return handle<HeartbeatMessage>(body, handler);
            case TemplateId::ProductSummaryMessage: return handle<ProductSummaryMessage>(body, handler);
            case TemplateId::SnapshotOrderMessage: return handle<SnapshotOrderMessage>(body, handler);
            case TemplateId::InstrumentSummaryMessage: return handle<InstrumentSummaryMessage>(body, handler);
            case TemplateId::AuctionBestBidOfferMessage: return handle<AuctionBestBidOfferMessage>(body, handler);
            case TemplateId::AuctionClearingPriceMessage: return handle<AuctionClearingPriceMessage>(body, handler);
            case TemplateId::TopOfBookMessage: return handle<TopOfBookMessage>(body, handler);
            case TemplateId::OrderAddMessage: return handle<OrderAddMessage>(body, handler);
            case TemplateId::OrderModifyMessage: return handle<OrderModifyMessage>(body, handler);
            case TemplateId::OrderModifySamePriorityMessage: return handle<OrderModifySamePriorityMessage>(body, handler);
            case TemplateId::OrderDeleteMessage: return handle<OrderDeleteMessage>(body, handler);
            case TemplateId::OrderMassDeleteMessage: return handle<OrderMassDeleteMessage>(body, handler);
            case TemplateId::PartialOrderExecutionMessage: return handle<PartialOrderExecutionMessage>(body, handler);
            case TemplateId::FullOrderExecutionMessage: return handle<FullOrderExecutionMessage>(body, handler);
            case TemplateId::TradeReversalMessage: return handle<TradeReversalMessage>(body, handler);
            case TemplateId::ExecutionSummaryMessage: return handle<ExecutionSummaryMessage>(body, handler);
            case TemplateId::InstrumentInfoMessage: return handle<InstrumentInfoMessage>(body, handler);
            case TemplateId::LppRangeMessage: return handle<LppRangeMessage>(body, handler);
            case TemplateId::ProductStateChangeMessage: return handle<ProductStateChangeMessage>(body, handler);
            case TemplateId::InstrumentStateChangeMessage: return handle<InstrumentStateChangeMessage>(body, handler);
            case TemplateId::AddComplexInstrumentMessage: return handle<AddComplexInstrumentMessage>(body, handler);
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

} // namespace bse::bseindia::eobi::fbe::v1_4
