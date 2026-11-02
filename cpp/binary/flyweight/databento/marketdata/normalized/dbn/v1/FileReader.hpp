#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/File.hpp"
#include "structs/Frame.hpp"
#include "enums/Rtype.hpp"
#include "messages/TradeMsg.hpp"
#include "messages/Mbp1Msg.hpp"
#include "messages/Mbp10Msg.hpp"
#include "messages/OhlcvMsg.hpp"
#include "messages/StatusMsg.hpp"
#include "messages/InstrumentDefMsg.hpp"
#include "messages/ImbalanceMsg.hpp"
#include "messages/ErrorMsg.hpp"
#include "messages/SymbolMappingMsg.hpp"
#include "messages/SystemMsg.hpp"
#include "messages/StatMsg.hpp"
#include "messages/OhlcvMsg.hpp"
#include "messages/OhlcvMsg.hpp"
#include "messages/OhlcvMsg.hpp"
#include "messages/OhlcvMsg.hpp"
#include "messages/OhlcvMsg.hpp"
#include "messages/MboMsg.hpp"
#include "messages/Cmbp1Msg.hpp"
#include "messages/CbboMsg.hpp"
#include "messages/CbboMsg.hpp"
#include "messages/Cmbp1Msg.hpp"
#include "messages/BboMsg.hpp"
#include "messages/BboMsg.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

// Reads a File in place: its headers, then each message its frames carry, handed to the
// handler as a view of its bytes. A handler declares an on() for each view it wants; a view it
// declares none for is passed over, and a code no message answers to goes to on_unknown(code,
// body) when it declares one.
struct FileReader {
    // Read one packet; what it returns is how many of the bytes the packet took.
    template <typename Handler>
    static std::size_t read(std::span<const std::byte> bytes, Handler& handler) {
        wire::require(File::name, File::minimum_size, bytes.size());
        const File packet{ bytes };
        if constexpr (requires { handler.on(packet); }) { handler.on(packet); }

        std::size_t offset = packet.encoded_size();

        while (offset < bytes.size()) {
            const std::size_t start = offset;

            // A frame the bytes do not hold in full is the caller's tail, not a fault: stop short of
            // it and leave it out of what this read took.
            if (bytes.size() - offset < Frame::minimum_size) { break; }

            const Frame frame{ bytes.subspan(offset) };
            offset += frame.encoded_size();
            const std::size_t frame_size = wire::count(frame.record_header().record_length()) * 4;
            if (frame_size < Frame::minimum_size) { throw DecodeError(File::name, Frame::minimum_size, frame_size); }
            if (start + frame_size > bytes.size()) { offset = start; break; }
            dispatch(frame, bytes.subspan(offset, start + frame_size - offset), handler);
            offset = start + frame_size;
        }

        return offset;
    }

  private:
    template <typename Handler>
    static std::size_t dispatch(const Frame& frame, std::span<const std::byte> body, Handler& handler) {
        switch (frame.record_header().rtype()) {
            case Rtype::MarketByPrice0: return handle<TradeMsg>(body, handler);
            case Rtype::MarketByPrice1: return handle<Mbp1Msg>(body, handler);
            case Rtype::MarketByPrice10: return handle<Mbp10Msg>(body, handler);
            case Rtype::OhlcvEndOfDay: return handle<OhlcvMsg>(body, handler);
            case Rtype::Status: return handle<StatusMsg>(body, handler);
            case Rtype::InstrumentDefinition: return handle<InstrumentDefMsg>(body, handler);
            case Rtype::Imbalance: return handle<ImbalanceMsg>(body, handler);
            case Rtype::Error: return handle<ErrorMsg>(body, handler);
            case Rtype::SymbolMapping: return handle<SymbolMappingMsg>(body, handler);
            case Rtype::System: return handle<SystemMsg>(body, handler);
            case Rtype::Statistics: return handle<StatMsg>(body, handler);
            case Rtype::MarketByOrder: return handle<MboMsg>(body, handler);
            case Rtype::TradeWithConsolidatedBbo: return handle<Cmbp1Msg>(body, handler);
            case Rtype::ConsolidatedBbo1Minute: return handle<CbboMsg>(body, handler);
            case Rtype::Bbo1Minute: return handle<BboMsg>(body, handler);
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
