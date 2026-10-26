#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/ServerTcpPacket.hpp"
#include "structs/ServerTcpFrame.hpp"
#include "enums/TemplateId.hpp"
#include "messages/ServerPayloadChannelReset.hpp"
#include "messages/ServerPayloadAdminLogin.hpp"
#include "messages/ServerPayloadAdminLogout.hpp"
#include "messages/ServerPayloadMdInstrumentDefinitionFuture.hpp"
#include "messages/ServerPayloadMdInstrumentDefinitionSpread.hpp"
#include "messages/ServerPayloadSecurityStatus.hpp"
#include "messages/ServerPayloadMdIncrementalRefreshBook.hpp"
#include "messages/ServerPayloadMdIncrementalRefreshDailyStatistics.hpp"
#include "messages/ServerPayloadMdIncrementalRefreshLimitsBanding.hpp"
#include "messages/ServerPayloadMdIncrementalRefreshSessionStatistics.hpp"
#include "messages/ServerPayloadMdIncrementalRefreshTrade.hpp"
#include "messages/ServerPayloadMdIncrementalRefreshVolume.hpp"
#include "messages/ServerPayloadSnapshotFullRefresh.hpp"
#include "messages/ServerPayloadQuoteRequest.hpp"
#include "messages/ServerPayloadMdInstrumentDefinitionOption.hpp"
#include "messages/ServerPayloadMdIncrementalRefreshTradeSummary.hpp"
#include "messages/ServerPayloadMdIncrementalRefreshOrderBook.hpp"
#include "messages/ServerPayloadSnapshotFullRefreshOrderBook.hpp"
#include "messages/ServerPayloadNegotiationReject.hpp"
#include "messages/ServerPayloadNegotiationResponse.hpp"
#include "messages/ServerPayloadTerminate.hpp"
#include "messages/ServerPayloadRequestAck.hpp"
#include "messages/ServerPayloadRequestReject.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

// Reads a Server Tcp Packet in place: its headers, then each message its frames carry, handed
// to the handler as a view of its bytes. A handler declares an on() for each view it wants; a
// view it declares none for is passed over, and a code no message answers to goes to
// on_unknown(code, body) when it declares one.
struct ServerTcpPacketReader {
    // Read one packet; what it returns is how many of the bytes the packet took.
    template <typename Handler>
    static std::size_t read(std::span<const std::byte> bytes, Handler& handler) {
        wire::require(ServerTcpPacket::name, ServerTcpPacket::minimum_size, bytes.size());
        const ServerTcpPacket packet{ bytes };
        if constexpr (requires { handler.on(packet); }) { handler.on(packet); }

        std::size_t offset = packet.encoded_size();

        while (offset < bytes.size()) {
            const std::size_t start = offset;

            // A frame the bytes do not hold in full is the caller's tail, not a fault: stop short of
            // it and leave it out of what this read took.
            if (bytes.size() - offset < ServerTcpFrame::minimum_size) { break; }

            const ServerTcpFrame frame{ bytes.subspan(offset) };
            offset += frame.encoded_size();
            const std::size_t frame_size = wire::count(frame.message_header().message_size()) + 14;
            if (frame_size < ServerTcpFrame::minimum_size) { throw DecodeError(ServerTcpPacket::name, ServerTcpFrame::minimum_size, frame_size); }
            if (start + frame_size > bytes.size()) { offset = start; break; }
            dispatch(frame, bytes.subspan(offset, start + frame_size - offset), handler);
            offset = start + frame_size;
        }

        return offset;
    }

  private:
    template <typename Handler>
    static std::size_t dispatch(const ServerTcpFrame& frame, std::span<const std::byte> body, Handler& handler) {
        switch (frame.message_header().simple_binary_header().template_id()) {
            case TemplateId::ChannelReset: return handle<ServerPayloadChannelReset>(body, handler);
            case TemplateId::AdminLogin: return handle<ServerPayloadAdminLogin>(body, handler);
            case TemplateId::AdminLogout: return handle<ServerPayloadAdminLogout>(body, handler);
            case TemplateId::MdInstrumentDefinitionFuture: return handle<ServerPayloadMdInstrumentDefinitionFuture>(body, handler);
            case TemplateId::MdInstrumentDefinitionSpread: return handle<ServerPayloadMdInstrumentDefinitionSpread>(body, handler);
            case TemplateId::SecurityStatus: return handle<ServerPayloadSecurityStatus>(body, handler);
            case TemplateId::MdIncrementalRefreshBook: return handle<ServerPayloadMdIncrementalRefreshBook>(body, handler);
            case TemplateId::MdIncrementalRefreshDailyStatistics: return handle<ServerPayloadMdIncrementalRefreshDailyStatistics>(body, handler);
            case TemplateId::MdIncrementalRefreshLimitsBanding: return handle<ServerPayloadMdIncrementalRefreshLimitsBanding>(body, handler);
            case TemplateId::MdIncrementalRefreshSessionStatistics: return handle<ServerPayloadMdIncrementalRefreshSessionStatistics>(body, handler);
            case TemplateId::MdIncrementalRefreshTrade: return handle<ServerPayloadMdIncrementalRefreshTrade>(body, handler);
            case TemplateId::MdIncrementalRefreshVolume: return handle<ServerPayloadMdIncrementalRefreshVolume>(body, handler);
            case TemplateId::SnapshotFullRefresh: return handle<ServerPayloadSnapshotFullRefresh>(body, handler);
            case TemplateId::QuoteRequest: return handle<ServerPayloadQuoteRequest>(body, handler);
            case TemplateId::MdInstrumentDefinitionOption: return handle<ServerPayloadMdInstrumentDefinitionOption>(body, handler);
            case TemplateId::MdIncrementalRefreshTradeSummary: return handle<ServerPayloadMdIncrementalRefreshTradeSummary>(body, handler);
            case TemplateId::MdIncrementalRefreshOrderBook: return handle<ServerPayloadMdIncrementalRefreshOrderBook>(body, handler);
            case TemplateId::SnapshotFullRefreshOrderBook: return handle<ServerPayloadSnapshotFullRefreshOrderBook>(body, handler);
            case TemplateId::NegotiationReject: return handle<ServerPayloadNegotiationReject>(body, handler);
            case TemplateId::NegotiationResponse: return handle<ServerPayloadNegotiationResponse>(body, handler);
            case TemplateId::Terminate: return handle<ServerPayloadTerminate>(body, handler);
            case TemplateId::RequestAck: return handle<ServerPayloadRequestAck>(body, handler);
            case TemplateId::RequestReject: return handle<ServerPayloadRequestReject>(body, handler);
            default:
                if constexpr (requires { handler.on_unknown(frame.message_header().simple_binary_header().template_id(), body); }) { handler.on_unknown(frame.message_header().simple_binary_header().template_id(), body); }
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

} // namespace cme::globex::mdp3::sbe::v1_8
