#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/Packet.hpp"
#include "structs/Frame.hpp"
#include "enums/TemplateId.hpp"
#include "messages/NegotiateMessage.hpp"
#include "messages/NegotiateResponseMessage.hpp"
#include "messages/NegotiateRejectMessage.hpp"
#include "messages/EstablishMessage.hpp"
#include "messages/EstablishAckMessage.hpp"
#include "messages/EstablishRejectMessage.hpp"
#include "messages/TerminateMessage.hpp"
#include "messages/NotAppliedMessage.hpp"
#include "messages/SequenceMessage.hpp"
#include "messages/RetransmitRequestMessage.hpp"
#include "messages/RetransmissionMessage.hpp"
#include "messages/RetransmitRejectMessage.hpp"
#include "messages/SimpleNewOrderMessage.hpp"
#include "messages/SimpleModifyOrderMessage.hpp"
#include "messages/NewOrderSingleMessage.hpp"
#include "messages/OrderCancelReplaceRequestMessage.hpp"
#include "messages/OrderCancelRequestMessage.hpp"
#include "messages/NewOrderCrossMessage.hpp"
#include "messages/ExecutionReportNewMessage.hpp"
#include "messages/ExecutionReportModifyMessage.hpp"
#include "messages/ExecutionReportCancelMessage.hpp"
#include "messages/ExecutionReportTradeMessage.hpp"
#include "messages/ExecutionReportRejectMessage.hpp"
#include "messages/ExecutionReportForwardMessage.hpp"
#include "messages/BusinessMessageRejectMessage.hpp"
#include "messages/SecurityDefinitionRequestMessage.hpp"
#include "messages/SecurityDefinitionResponseMessage.hpp"
#include "messages/QuoteRequestMessage.hpp"
#include "messages/QuoteStatusReportMessage.hpp"
#include "messages/QuoteMessage.hpp"
#include "messages/QuoteCancelMessage.hpp"
#include "messages/QuoteRequestRejectMessage.hpp"
#include "messages/PositionMaintenanceCancelRequestMessage.hpp"
#include "messages/PositionMaintenanceRequestMessage.hpp"
#include "messages/PositionMaintenanceReportMessage.hpp"
#include "messages/AllocationInstructionMessage.hpp"
#include "messages/AllocationReportMessage.hpp"
#include "messages/OrderMassActionRequestMessage.hpp"
#include "messages/OrderMassActionReportMessage.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// Reads a Packet in place: its headers, then each message its frames carry, handed to the
// handler as a view of its bytes. A handler declares an on() for each view it wants; a view it
// declares none for is passed over, and a code no message answers to goes to on_unknown(code,
// body) when it declares one.
struct StreamReader {
    // Read one packet; what it returns is how many of the bytes the packet took.
    template <typename Handler>
    static std::size_t read(std::span<const std::byte> bytes, Handler& handler) {
        wire::require(Packet::name, Packet::minimum_size, bytes.size());
        const Packet packet{ bytes };
        if constexpr (requires { handler.on(packet); }) { handler.on(packet); }

        std::size_t offset = packet.encoded_size();

        while (offset < bytes.size()) {
            const std::size_t start = offset;

            // A frame the bytes do not hold in full is the caller's tail, not a fault: stop short of
            // it and leave it out of what this read took.
            if (bytes.size() - offset < Frame::minimum_size) { break; }

            const Frame frame{ bytes.subspan(offset) };
            offset += frame.encoded_size();
            const std::size_t frame_size = wire::count(frame.simple_open_framing_header().message_length());
            if (frame_size < Frame::minimum_size) { throw DecodeError(Packet::name, Frame::minimum_size, frame_size); }
            if (start + frame_size > bytes.size()) { offset = start; break; }
            dispatch(frame, bytes.subspan(offset, start + frame_size - offset), handler);
            offset = start + frame_size;
        }

        return offset;
    }

  private:
    template <typename Handler>
    static std::size_t dispatch(const Frame& frame, std::span<const std::byte> body, Handler& handler) {
        switch (frame.message_header().template_id()) {
            case TemplateId::NegotiateMessage: return handle<NegotiateMessage>(body, handler);
            case TemplateId::NegotiateResponseMessage: return handle<NegotiateResponseMessage>(body, handler);
            case TemplateId::NegotiateRejectMessage: return handle<NegotiateRejectMessage>(body, handler);
            case TemplateId::EstablishMessage: return handle<EstablishMessage>(body, handler);
            case TemplateId::EstablishAckMessage: return handle<EstablishAckMessage>(body, handler);
            case TemplateId::EstablishRejectMessage: return handle<EstablishRejectMessage>(body, handler);
            case TemplateId::TerminateMessage: return handle<TerminateMessage>(body, handler);
            case TemplateId::NotAppliedMessage: return handle<NotAppliedMessage>(body, handler);
            case TemplateId::SequenceMessage: return handle<SequenceMessage>(body, handler);
            case TemplateId::RetransmitRequestMessage: return handle<RetransmitRequestMessage>(body, handler);
            case TemplateId::RetransmissionMessage: return handle<RetransmissionMessage>(body, handler);
            case TemplateId::RetransmitRejectMessage: return handle<RetransmitRejectMessage>(body, handler);
            case TemplateId::SimpleNewOrderMessage: return handle<SimpleNewOrderMessage>(body, handler);
            case TemplateId::SimpleModifyOrderMessage: return handle<SimpleModifyOrderMessage>(body, handler);
            case TemplateId::NewOrderSingleMessage: return handle<NewOrderSingleMessage>(body, handler);
            case TemplateId::OrderCancelReplaceRequestMessage: return handle<OrderCancelReplaceRequestMessage>(body, handler);
            case TemplateId::OrderCancelRequestMessage: return handle<OrderCancelRequestMessage>(body, handler);
            case TemplateId::NewOrderCrossMessage: return handle<NewOrderCrossMessage>(body, handler);
            case TemplateId::ExecutionReportNewMessage: return handle<ExecutionReportNewMessage>(body, handler);
            case TemplateId::ExecutionReportModifyMessage: return handle<ExecutionReportModifyMessage>(body, handler);
            case TemplateId::ExecutionReportCancelMessage: return handle<ExecutionReportCancelMessage>(body, handler);
            case TemplateId::ExecutionReportTradeMessage: return handle<ExecutionReportTradeMessage>(body, handler);
            case TemplateId::ExecutionReportRejectMessage: return handle<ExecutionReportRejectMessage>(body, handler);
            case TemplateId::ExecutionReportForwardMessage: return handle<ExecutionReportForwardMessage>(body, handler);
            case TemplateId::BusinessMessageRejectMessage: return handle<BusinessMessageRejectMessage>(body, handler);
            case TemplateId::SecurityDefinitionRequestMessage: return handle<SecurityDefinitionRequestMessage>(body, handler);
            case TemplateId::SecurityDefinitionResponseMessage: return handle<SecurityDefinitionResponseMessage>(body, handler);
            case TemplateId::QuoteRequestMessage: return handle<QuoteRequestMessage>(body, handler);
            case TemplateId::QuoteStatusReportMessage: return handle<QuoteStatusReportMessage>(body, handler);
            case TemplateId::QuoteMessage: return handle<QuoteMessage>(body, handler);
            case TemplateId::QuoteCancelMessage: return handle<QuoteCancelMessage>(body, handler);
            case TemplateId::QuoteRequestRejectMessage: return handle<QuoteRequestRejectMessage>(body, handler);
            case TemplateId::PositionMaintenanceCancelRequestMessage: return handle<PositionMaintenanceCancelRequestMessage>(body, handler);
            case TemplateId::PositionMaintenanceRequestMessage: return handle<PositionMaintenanceRequestMessage>(body, handler);
            case TemplateId::PositionMaintenanceReportMessage: return handle<PositionMaintenanceReportMessage>(body, handler);
            case TemplateId::AllocationInstructionMessage: return handle<AllocationInstructionMessage>(body, handler);
            case TemplateId::AllocationReportMessage: return handle<AllocationReportMessage>(body, handler);
            case TemplateId::OrderMassActionRequestMessage: return handle<OrderMassActionRequestMessage>(body, handler);
            case TemplateId::OrderMassActionReportMessage: return handle<OrderMassActionReportMessage>(body, handler);
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

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
