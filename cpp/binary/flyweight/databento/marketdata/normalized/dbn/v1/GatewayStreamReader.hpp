// Databento.MarketData.Normalized.Dbn.v1: GatewayStreamReader.hpp
#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/GatewayStream.hpp"
#include "structs/GatewayFrame.hpp"
#include "enums/Rtype.hpp"
#include "messages/RecordBodyTradeMsg.hpp"
#include "messages/RecordBodyMbp1Msg.hpp"
#include "messages/RecordBodyMbp10Msg.hpp"
#include "messages/RecordBodyOhlcvMsg.hpp"
#include "messages/RecordBodyStatusMsg.hpp"
#include "messages/RecordBodyInstrumentDefMsg.hpp"
#include "messages/RecordBodyImbalanceMsg.hpp"
#include "messages/RecordBodyErrorMsg.hpp"
#include "messages/RecordBodySymbolMappingMsg.hpp"
#include "messages/RecordBodySystemMsg.hpp"
#include "messages/RecordBodyStatMsg.hpp"
#include "messages/RecordBodyOhlcvMsg.hpp"
#include "messages/RecordBodyOhlcvMsg.hpp"
#include "messages/RecordBodyOhlcvMsg.hpp"
#include "messages/RecordBodyOhlcvMsg.hpp"
#include "messages/RecordBodyOhlcvMsg.hpp"
#include "messages/RecordBodyMboMsg.hpp"
#include "messages/RecordBodyCmbp1Msg.hpp"
#include "messages/RecordBodyCbboMsg.hpp"
#include "messages/RecordBodyCbboMsg.hpp"
#include "messages/RecordBodyCmbp1Msg.hpp"
#include "messages/RecordBodyBboMsg.hpp"
#include "messages/RecordBodyBboMsg.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

// Reads a Gateway Stream in place: its headers, then each message its frames carry, handed to
// the handler as a view of its bytes. A handler declares an on() for each view it wants; a
// view it declares none for is passed over, and a code no message answers to goes to
// on_unknown(code, body) when it declares one.
struct GatewayStreamReader {
    // Read one packet; what it returns is how many of the bytes the packet took.
    template <typename Handler>
    static std::size_t read(std::span<const std::byte> bytes, Handler& handler) {
        wire::require(GatewayStream::name, GatewayStream::minimum_size, bytes.size());
        const GatewayStream packet{ bytes };
        if constexpr (requires { handler.on(packet); }) { handler.on(packet); }

        std::size_t offset = packet.encoded_size();

        while (offset < bytes.size()) {
            const std::size_t start = offset;

            // A frame the bytes do not hold in full is the caller's tail, not a fault: stop short of
            // it and leave it out of what this read took.
            if (bytes.size() - offset < GatewayFrame::minimum_size) { break; }

            const GatewayFrame frame{ bytes.subspan(offset) };
            offset += frame.encoded_size();
            const std::size_t frame_size = wire::count(frame.record_header().record_length()) * 4;
            if (frame_size < GatewayFrame::minimum_size) { throw DecodeError(GatewayStream::name, GatewayFrame::minimum_size, frame_size); }
            if (start + frame_size > bytes.size()) { offset = start; break; }
            dispatch(frame, bytes.subspan(offset, start + frame_size - offset), handler);
            offset = start + frame_size;
        }

        return offset;
    }

  private:
    template <typename Handler>
    static std::size_t dispatch(const GatewayFrame& frame, std::span<const std::byte> body, Handler& handler) {
        switch (frame.record_header().rtype()) {
            case Rtype::MarketByPrice0: return handle<RecordBodyTradeMsg>(body, handler);
            case Rtype::MarketByPrice1: return handle<RecordBodyMbp1Msg>(body, handler);
            case Rtype::MarketByPrice10: return handle<RecordBodyMbp10Msg>(body, handler);
            case Rtype::OhlcvEndOfDay: return handle<RecordBodyOhlcvMsg>(body, handler);
            case Rtype::Status: return handle<RecordBodyStatusMsg>(body, handler);
            case Rtype::InstrumentDefinition: return handle<RecordBodyInstrumentDefMsg>(body, handler);
            case Rtype::Imbalance: return handle<RecordBodyImbalanceMsg>(body, handler);
            case Rtype::Error: return handle<RecordBodyErrorMsg>(body, handler);
            case Rtype::SymbolMapping: return handle<RecordBodySymbolMappingMsg>(body, handler);
            case Rtype::System: return handle<RecordBodySystemMsg>(body, handler);
            case Rtype::Statistics: return handle<RecordBodyStatMsg>(body, handler);
            case Rtype::MarketByOrder: return handle<RecordBodyMboMsg>(body, handler);
            case Rtype::TradeWithConsolidatedBbo: return handle<RecordBodyCmbp1Msg>(body, handler);
            case Rtype::ConsolidatedBbo1Minute: return handle<RecordBodyCbboMsg>(body, handler);
            case Rtype::Bbo1Minute: return handle<RecordBodyBboMsg>(body, handler);
            default:
                if constexpr (requires { handler.on_unknown(frame.record_header().rtype(), body); }) { handler.on_unknown(frame.record_header().rtype(), body); }
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

} // namespace databento::marketdata::normalized::dbn::v1
