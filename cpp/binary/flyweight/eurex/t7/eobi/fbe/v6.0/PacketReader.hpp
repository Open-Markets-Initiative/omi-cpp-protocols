#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/Packet.hpp"
#include "structs/Frame.hpp"
#include "enums/TemplateId.hpp"
#include "messages/AddComplexInstrument.hpp"
#include "messages/AuctionBbo.hpp"
#include "messages/AuctionClearingPrice.hpp"
#include "messages/CrossRequest.hpp"
#include "messages/ExecutionSummary.hpp"
#include "messages/FullOrderExecution.hpp"
#include "messages/Heartbeat.hpp"
#include "messages/InstrumentStateChange.hpp"
#include "messages/InstrumentSummary.hpp"
#include "messages/OrderAdd.hpp"
#include "messages/OrderDelete.hpp"
#include "messages/OrderMassDelete.hpp"
#include "messages/OrderModify.hpp"
#include "messages/OrderModifySamePrio.hpp"
#include "messages/PartialOrderExecution.hpp"
#include "messages/ProductStateChange.hpp"
#include "messages/ProductSummary.hpp"
#include "messages/QuoteRequest.hpp"
#include "messages/SnapshotOrder.hpp"
#include "messages/TopOfBook.hpp"
#include "messages/TradeReport.hpp"
#include "messages/TradeReversal.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

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
            const std::size_t frame_size = wire::count(frame.message_header_comp().body_len());
            wire::require(Packet::name, start + frame_size, bytes.size());
            dispatch(frame, bytes.subspan(offset, start + frame_size - offset), handler);
            offset = start + frame_size;
        }

        return offset;
    }

  private:
    template <typename Handler>
    static std::size_t dispatch(const Frame& frame, std::span<const std::byte> body, Handler& handler) {
        switch (frame.message_header_comp().template_id()) {
            case TemplateId::AddComplexInstrument: return handle<AddComplexInstrument>(body, handler);
            case TemplateId::AuctionBbo: return handle<AuctionBbo>(body, handler);
            case TemplateId::AuctionClearingPrice: return handle<AuctionClearingPrice>(body, handler);
            case TemplateId::CrossRequest: return handle<CrossRequest>(body, handler);
            case TemplateId::ExecutionSummary: return handle<ExecutionSummary>(body, handler);
            case TemplateId::FullOrderExecution: return handle<FullOrderExecution>(body, handler);
            case TemplateId::Heartbeat: return handle<Heartbeat>(body, handler);
            case TemplateId::InstrumentStateChange: return handle<InstrumentStateChange>(body, handler);
            case TemplateId::InstrumentSummary: return handle<InstrumentSummary>(body, handler);
            case TemplateId::OrderAdd: return handle<OrderAdd>(body, handler);
            case TemplateId::OrderDelete: return handle<OrderDelete>(body, handler);
            case TemplateId::OrderMassDelete: return handle<OrderMassDelete>(body, handler);
            case TemplateId::OrderModify: return handle<OrderModify>(body, handler);
            case TemplateId::OrderModifySamePrio: return handle<OrderModifySamePrio>(body, handler);
            case TemplateId::PartialOrderExecution: return handle<PartialOrderExecution>(body, handler);
            case TemplateId::ProductStateChange: return handle<ProductStateChange>(body, handler);
            case TemplateId::ProductSummary: return handle<ProductSummary>(body, handler);
            case TemplateId::QuoteRequest: return handle<QuoteRequest>(body, handler);
            case TemplateId::SnapshotOrder: return handle<SnapshotOrder>(body, handler);
            case TemplateId::TopOfBook: return handle<TopOfBook>(body, handler);
            case TemplateId::TradeReport: return handle<TradeReport>(body, handler);
            case TemplateId::TradeReversal: return handle<TradeReversal>(body, handler);
            default:
                if constexpr (requires { handler.on_unknown(frame.message_header_comp().template_id(), body); }) { handler.on_unknown(frame.message_header_comp().template_id(), body); }
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

} // namespace eurex::t7::eobi::fbe::v6_0
