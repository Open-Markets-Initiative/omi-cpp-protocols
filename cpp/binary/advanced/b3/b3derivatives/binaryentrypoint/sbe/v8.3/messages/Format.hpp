#pragma once

#include <ostream>
#include <string_view>

#include "NegotiateMessage.hpp"
#include "NegotiateResponseMessage.hpp"
#include "NegotiateRejectMessage.hpp"
#include "EstablishMessage.hpp"
#include "EstablishAckMessage.hpp"
#include "EstablishRejectMessage.hpp"
#include "TerminateMessage.hpp"
#include "NotAppliedMessage.hpp"
#include "SequenceMessage.hpp"
#include "RetransmitRequestMessage.hpp"
#include "RetransmissionMessage.hpp"
#include "RetransmitRejectMessage.hpp"
#include "SimpleNewOrderMessage.hpp"
#include "SimpleModifyOrderMessage.hpp"
#include "NewOrderSingleMessage.hpp"
#include "OrderCancelReplaceRequestMessage.hpp"
#include "OrderCancelRequestMessage.hpp"
#include "NewOrderCrossMessage.hpp"
#include "ExecutionReportNewMessage.hpp"
#include "ExecutionReportModifyMessage.hpp"
#include "ExecutionReportCancelMessage.hpp"
#include "ExecutionReportTradeMessage.hpp"
#include "ExecutionReportRejectMessage.hpp"
#include "ExecutionReportForwardMessage.hpp"
#include "BusinessMessageRejectMessage.hpp"
#include "SecurityDefinitionRequestMessage.hpp"
#include "SecurityDefinitionResponseMessage.hpp"
#include "QuoteRequestMessage.hpp"
#include "QuoteStatusReportMessage.hpp"
#include "QuoteMessage.hpp"
#include "QuoteCancelMessage.hpp"
#include "QuoteRequestRejectMessage.hpp"
#include "PositionMaintenanceCancelRequestMessage.hpp"
#include "PositionMaintenanceRequestMessage.hpp"
#include "PositionMaintenanceReportMessage.hpp"
#include "AllocationInstructionMessage.hpp"
#include "AllocationReportMessage.hpp"
#include "OrderMassActionRequestMessage.hpp"
#include "OrderMassActionReportMessage.hpp"
#include "../json/messages/negotiate_message_json.hpp"
#include "../json/messages/establish_message_json.hpp"
#include "../json/messages/simple_new_order_message_json.hpp"
#include "../json/messages/simple_modify_order_message_json.hpp"
#include "../json/messages/new_order_single_message_json.hpp"
#include "../json/messages/order_cancel_replace_request_message_json.hpp"
#include "../json/messages/order_cancel_request_message_json.hpp"
#include "../json/messages/new_order_cross_message_json.hpp"
#include "../json/messages/execution_report_new_message_json.hpp"
#include "../json/messages/execution_report_modify_message_json.hpp"
#include "../json/messages/execution_report_cancel_message_json.hpp"
#include "../json/messages/execution_report_trade_message_json.hpp"
#include "../json/messages/execution_report_reject_message_json.hpp"
#include "../json/messages/execution_report_forward_message_json.hpp"
#include "../json/messages/business_message_reject_message_json.hpp"
#include "../json/messages/security_definition_request_message_json.hpp"
#include "../json/messages/quote_request_message_json.hpp"
#include "../json/messages/quote_status_report_message_json.hpp"
#include "../json/messages/quote_message_json.hpp"
#include "../json/messages/quote_cancel_message_json.hpp"
#include "../json/messages/quote_request_reject_message_json.hpp"
#include "../json/messages/position_maintenance_request_message_json.hpp"
#include "../json/messages/position_maintenance_report_message_json.hpp"
#include "../json/messages/allocation_instruction_message_json.hpp"
#include "../json/messages/order_mass_action_report_message_json.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_3;

inline std::ostream& operator<<(std::ostream& os, const simple_open_framing_header& value) {
    os << "message_length=" << value.message_length.get().value()
       << ",encoding_type=" << value.encoding_type.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "block_length=" << value.block_length.get().value()
       << ",template_id=\"" << sbe_binaryentrypoint::template_id::to_string(value.template_id.get().value()) << '"'
       << ",schema_id=" << value.schema_id.get().value()
       << ",version=" << value.version.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const cross_sides_groups& value) {
    os << "group_size_encoding.block_length=" << value.group_size_encoding.block_length.get().value()
       << ",group_size_encoding.num_in_group=" << static_cast<unsigned>(value.group_size_encoding.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const legs_groups& value) {
    os << "group_size_encoding.block_length=" << value.group_size_encoding.block_length.get().value()
       << ",group_size_encoding.num_in_group=" << static_cast<unsigned>(value.group_size_encoding.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const sides_groups& value) {
    os << "group_size_encoding.block_length=" << value.group_size_encoding.block_length.get().value()
       << ",group_size_encoding.num_in_group=" << static_cast<unsigned>(value.group_size_encoding.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const positions_groups& value) {
    os << "group_size_encoding.block_length=" << value.group_size_encoding.block_length.get().value()
       << ",group_size_encoding.num_in_group=" << static_cast<unsigned>(value.group_size_encoding.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const negotiate_message& msg) {
    os << "session_id=" << msg.fields.session_id.get().value()
       << ",session_ver_id=" << msg.fields.session_ver_id.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",entering_firm=" << msg.fields.entering_firm.get().value()
       << ",onbehalf_firm=" << (msg.fields.onbehalf_firm.get().has_value() ? std::to_string(msg.fields.onbehalf_firm.get().value()) : std::string_view("null"))
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const negotiate_response_message& msg) {
    os << "session_id=" << msg.fields.session_id.get().value()
       << ",session_ver_id=" << msg.fields.session_ver_id.get().value()
       << ",request_timestamp=" << msg.fields.request_timestamp.get().value()
       << ",entering_firm=" << msg.fields.entering_firm.get().value()
       << ",semantic_version.major_number=" << static_cast<unsigned>(msg.fields.semantic_version.major_number.get().value())
       << ",semantic_version.minor_number=" << static_cast<unsigned>(msg.fields.semantic_version.minor_number.get().value())
       << ",semantic_version.patch_number=" << static_cast<unsigned>(msg.fields.semantic_version.patch_number.get().value())
       << ",semantic_version.build_number=" << static_cast<unsigned>(msg.fields.semantic_version.build_number.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const negotiate_reject_message& msg) {
    os << "session_id=" << msg.fields.session_id.get().value()
       << ",session_ver_id=" << msg.fields.session_ver_id.get().value()
       << ",request_timestamp=" << msg.fields.request_timestamp.get().value()
       << ",entering_firm_optional=" << (msg.fields.entering_firm_optional.get().has_value() ? std::to_string(msg.fields.entering_firm_optional.get().value()) : std::string_view("null"))
       << ",negotiation_reject_code=\"" << sbe_binaryentrypoint::negotiation_reject_code::to_string(msg.fields.negotiation_reject_code.get().value()) << '"'
       << ",current_session_ver_id=" << (msg.fields.current_session_ver_id.get().has_value() ? std::to_string(msg.fields.current_session_ver_id.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const establish_message& msg) {
    os << "session_id=" << msg.fields.session_id.get().value()
       << ",session_ver_id=" << msg.fields.session_ver_id.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",keep_alive_interval=" << msg.fields.keep_alive_interval.get().value()
       << ",next_seq_no=" << msg.fields.next_seq_no.get().value()
       << ",cancel_on_disconnect_type=\"" << sbe_binaryentrypoint::cancel_on_disconnect_type::to_string(msg.fields.cancel_on_disconnect_type.get().value()) << '"'
       << ",cod_timeout_window=" << msg.fields.cod_timeout_window.get().value()
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const establish_ack_message& msg) {
    os << "session_id=" << msg.fields.session_id.get().value()
       << ",session_ver_id=" << msg.fields.session_ver_id.get().value()
       << ",request_timestamp=" << msg.fields.request_timestamp.get().value()
       << ",keep_alive_interval=" << msg.fields.keep_alive_interval.get().value()
       << ",next_seq_no=" << msg.fields.next_seq_no.get().value()
       << ",last_incoming_seq_no=" << msg.fields.last_incoming_seq_no.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const establish_reject_message& msg) {
    os << "session_id=" << msg.fields.session_id.get().value()
       << ",session_ver_id=" << msg.fields.session_ver_id.get().value()
       << ",request_timestamp=" << msg.fields.request_timestamp.get().value()
       << ",establishment_reject_code=\"" << sbe_binaryentrypoint::establishment_reject_code::to_string(msg.fields.establishment_reject_code.get().value()) << '"'
       << ",last_incoming_seq_no_optional=" << (msg.fields.last_incoming_seq_no_optional.get().has_value() ? std::to_string(msg.fields.last_incoming_seq_no_optional.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const terminate_message& msg) {
    os << "session_id=" << msg.fields.session_id.get().value()
       << ",session_ver_id=" << msg.fields.session_ver_id.get().value()
       << ",termination_code=\"" << sbe_binaryentrypoint::termination_code::to_string(msg.fields.termination_code.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const not_applied_message& msg) {
    os << "from_seq_no=" << msg.fields.from_seq_no.get().value()
       << ",count=" << msg.fields.count.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const sequence_message& msg) {
    os << "next_seq_no=" << msg.fields.next_seq_no.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const retransmit_request_message& msg) {
    os << "session_id=" << msg.fields.session_id.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",from_seq_no=" << msg.fields.from_seq_no.get().value()
       << ",count=" << msg.fields.count.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const retransmission_message& msg) {
    os << "session_id=" << msg.fields.session_id.get().value()
       << ",request_timestamp=" << msg.fields.request_timestamp.get().value()
       << ",next_seq_no=" << msg.fields.next_seq_no.get().value()
       << ",count=" << msg.fields.count.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const retransmit_reject_message& msg) {
    os << "session_id=" << msg.fields.session_id.get().value()
       << ",request_timestamp=" << msg.fields.request_timestamp.get().value()
       << ",retransmit_reject_code=\"" << sbe_binaryentrypoint::retransmit_reject_code::to_string(msg.fields.retransmit_reject_code.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const simple_new_order_message& msg) {
    os << "inbound_business_header.session_id=" << msg.fields.inbound_business_header.session_id.get().value()
       << ",inbound_business_header.msg_seq_num=" << msg.fields.inbound_business_header.msg_seq_num.get().value()
       << ",inbound_business_header.sending_time=" << (msg.fields.inbound_business_header.sending_time.get().has_value() ? std::to_string(msg.fields.inbound_business_header.sending_time.get().value()) : std::string_view("null"))
       << ",inbound_business_header.market_segment_id=" << static_cast<unsigned>(msg.fields.inbound_business_header.market_segment_id.get().value())
       << ",inbound_business_header.padding=\"" << msg.fields.inbound_business_header.padding.get().value() << '"'
       << ",ordtagid=" << (msg.fields.ordtagid.get().has_value() ? std::to_string(msg.fields.ordtagid.get().value()) : std::string_view("null"))
       << ",mm_protection_reset=\"" << sbe_binaryentrypoint::mm_protection_reset::to_string(msg.fields.mm_protection_reset.get().value()) << '"'
       << ",clordid=" << msg.fields.clordid.get().value()
       << ",account=" << (msg.fields.account.get().has_value() ? std::to_string(msg.fields.account.get().value()) : std::string_view("null"))
       << ",sender_location=\"" << msg.fields.sender_location.get_trimmed().value() << '"'
       << ",entering_trader=\"" << msg.fields.entering_trader.get_trimmed().value() << '"'
       << ",self_trade_prevention_instruction=\"" << sbe_binaryentrypoint::self_trade_prevention_instruction::to_string(msg.fields.self_trade_prevention_instruction.get().value()) << '"'
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",side=\"" << sbe_binaryentrypoint::side::to_string(msg.fields.side.get().value()) << '"'
       << ",simple_ordtype=\"" << sbe_binaryentrypoint::simple_ordtype::to_string(msg.fields.simple_ordtype.get().value()) << '"'
       << ",time_in_force_simple=\"" << sbe_binaryentrypoint::time_in_force_simple::to_string(msg.fields.time_in_force_simple.get().value()) << '"'
       << ",routing_instruction=\"" << sbe_binaryentrypoint::routing_instruction::to_string(msg.fields.routing_instruction.get().value()) << '"'
       << ",order_qty=" << msg.fields.order_qty.get().value()
       << ",price_optional=" << (msg.fields.price_optional.get().has_value() ? std::to_string(msg.fields.price_optional.get().value()) : std::string_view("null"))
       << ",investor_id.prefix=" << msg.fields.investor_id.prefix.get().value()
       << ",investor_id.document=" << msg.fields.investor_id.document.get().value()
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const simple_modify_order_message& msg) {
    os << "inbound_business_header.session_id=" << msg.fields.inbound_business_header.session_id.get().value()
       << ",inbound_business_header.msg_seq_num=" << msg.fields.inbound_business_header.msg_seq_num.get().value()
       << ",inbound_business_header.sending_time=" << (msg.fields.inbound_business_header.sending_time.get().has_value() ? std::to_string(msg.fields.inbound_business_header.sending_time.get().value()) : std::string_view("null"))
       << ",inbound_business_header.market_segment_id=" << static_cast<unsigned>(msg.fields.inbound_business_header.market_segment_id.get().value())
       << ",inbound_business_header.padding=\"" << msg.fields.inbound_business_header.padding.get().value() << '"'
       << ",ordtagid=" << (msg.fields.ordtagid.get().has_value() ? std::to_string(msg.fields.ordtagid.get().value()) : std::string_view("null"))
       << ",mm_protection_reset=\"" << sbe_binaryentrypoint::mm_protection_reset::to_string(msg.fields.mm_protection_reset.get().value()) << '"'
       << ",clordid=" << msg.fields.clordid.get().value()
       << ",account=" << (msg.fields.account.get().has_value() ? std::to_string(msg.fields.account.get().value()) : std::string_view("null"))
       << ",sender_location=\"" << msg.fields.sender_location.get_trimmed().value() << '"'
       << ",entering_trader=\"" << msg.fields.entering_trader.get_trimmed().value() << '"'
       << ",self_trade_prevention_instruction=\"" << sbe_binaryentrypoint::self_trade_prevention_instruction::to_string(msg.fields.self_trade_prevention_instruction.get().value()) << '"'
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",side=\"" << sbe_binaryentrypoint::side::to_string(msg.fields.side.get().value()) << '"'
       << ",simple_ordtype=\"" << sbe_binaryentrypoint::simple_ordtype::to_string(msg.fields.simple_ordtype.get().value()) << '"'
       << ",time_in_force_simple=\"" << sbe_binaryentrypoint::time_in_force_simple::to_string(msg.fields.time_in_force_simple.get().value()) << '"'
       << ",routing_instruction=\"" << sbe_binaryentrypoint::routing_instruction::to_string(msg.fields.routing_instruction.get().value()) << '"'
       << ",order_qty=" << msg.fields.order_qty.get().value()
       << ",price_optional=" << (msg.fields.price_optional.get().has_value() ? std::to_string(msg.fields.price_optional.get().value()) : std::string_view("null"))
       << ",order_id_optional=" << (msg.fields.order_id_optional.get().has_value() ? std::to_string(msg.fields.order_id_optional.get().value()) : std::string_view("null"))
       << ",origclordid=" << (msg.fields.origclordid.get().has_value() ? std::to_string(msg.fields.origclordid.get().value()) : std::string_view("null"))
       << ",investor_id.prefix=" << msg.fields.investor_id.prefix.get().value()
       << ",investor_id.document=" << msg.fields.investor_id.document.get().value()
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const new_order_single_message& msg) {
    os << "inbound_business_header.session_id=" << msg.fields.inbound_business_header.session_id.get().value()
       << ",inbound_business_header.msg_seq_num=" << msg.fields.inbound_business_header.msg_seq_num.get().value()
       << ",inbound_business_header.sending_time=" << (msg.fields.inbound_business_header.sending_time.get().has_value() ? std::to_string(msg.fields.inbound_business_header.sending_time.get().value()) : std::string_view("null"))
       << ",inbound_business_header.market_segment_id=" << static_cast<unsigned>(msg.fields.inbound_business_header.market_segment_id.get().value())
       << ",inbound_business_header.padding=\"" << msg.fields.inbound_business_header.padding.get().value() << '"'
       << ",ordtagid=" << (msg.fields.ordtagid.get().has_value() ? std::to_string(msg.fields.ordtagid.get().value()) : std::string_view("null"))
       << ",mm_protection_reset=\"" << sbe_binaryentrypoint::mm_protection_reset::to_string(msg.fields.mm_protection_reset.get().value()) << '"'
       << ",clordid=" << msg.fields.clordid.get().value()
       << ",account=" << (msg.fields.account.get().has_value() ? std::to_string(msg.fields.account.get().value()) : std::string_view("null"))
       << ",sender_location=\"" << msg.fields.sender_location.get_trimmed().value() << '"'
       << ",entering_trader=\"" << msg.fields.entering_trader.get_trimmed().value() << '"'
       << ",self_trade_prevention_instruction=\"" << sbe_binaryentrypoint::self_trade_prevention_instruction::to_string(msg.fields.self_trade_prevention_instruction.get().value()) << '"'
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",side=\"" << sbe_binaryentrypoint::side::to_string(msg.fields.side.get().value()) << '"'
       << ",ordtype=\"" << sbe_binaryentrypoint::ordtype::to_string(msg.fields.ordtype.get().value()) << '"'
       << ",time_in_force=\"" << sbe_binaryentrypoint::time_in_force::to_string(msg.fields.time_in_force.get().value()) << '"'
       << ",routing_instruction=\"" << sbe_binaryentrypoint::routing_instruction::to_string(msg.fields.routing_instruction.get().value()) << '"'
       << ",order_qty=" << msg.fields.order_qty.get().value()
       << ",price_optional=" << (msg.fields.price_optional.get().has_value() ? std::to_string(msg.fields.price_optional.get().value()) : std::string_view("null"))
       << ",stop_px=" << (msg.fields.stop_px.get().has_value() ? std::to_string(msg.fields.stop_px.get().value()) : std::string_view("null"))
       << ",min_qty=" << (msg.fields.min_qty.get().has_value() ? std::to_string(msg.fields.min_qty.get().value()) : std::string_view("null"))
       << ",max_floor=" << (msg.fields.max_floor.get().has_value() ? std::to_string(msg.fields.max_floor.get().value()) : std::string_view("null"))
       << ",executing_trader_optional=\"" << (msg.fields.executing_trader_optional.get_trimmed().has_value() ? msg.fields.executing_trader_optional.get_trimmed().value() : std::string_view("null")) << '"'
       << ",expire_date=" << (msg.fields.expire_date.get().has_value() ? std::to_string(msg.fields.expire_date.get().value()) : std::string_view("null"))
       << ",custodian_info.custodian=" << msg.fields.custodian_info.custodian.get().value()
       << ",custodian_info.custody_account=" << msg.fields.custodian_info.custody_account.get().value()
       << ",custodian_info.custody_allocation_type=" << msg.fields.custodian_info.custody_allocation_type.get().value()
       << ",investor_id.prefix=" << msg.fields.investor_id.prefix.get().value()
       << ",investor_id.document=" << msg.fields.investor_id.document.get().value()
       << ",strategy_id=" << (msg.fields.strategy_id.get().has_value() ? std::to_string(msg.fields.strategy_id.get().value()) : std::string_view("null"))
       << ",trading_sub_account=" << (msg.fields.trading_sub_account.get().has_value() ? std::to_string(msg.fields.trading_sub_account.get().value()) : std::string_view("null"))
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_cancel_replace_request_message& msg) {
    os << "inbound_business_header.session_id=" << msg.fields.inbound_business_header.session_id.get().value()
       << ",inbound_business_header.msg_seq_num=" << msg.fields.inbound_business_header.msg_seq_num.get().value()
       << ",inbound_business_header.sending_time=" << (msg.fields.inbound_business_header.sending_time.get().has_value() ? std::to_string(msg.fields.inbound_business_header.sending_time.get().value()) : std::string_view("null"))
       << ",inbound_business_header.market_segment_id=" << static_cast<unsigned>(msg.fields.inbound_business_header.market_segment_id.get().value())
       << ",inbound_business_header.padding=\"" << msg.fields.inbound_business_header.padding.get().value() << '"'
       << ",ordtagid=" << (msg.fields.ordtagid.get().has_value() ? std::to_string(msg.fields.ordtagid.get().value()) : std::string_view("null"))
       << ",mm_protection_reset=\"" << sbe_binaryentrypoint::mm_protection_reset::to_string(msg.fields.mm_protection_reset.get().value()) << '"'
       << ",clordid=" << msg.fields.clordid.get().value()
       << ",account=" << (msg.fields.account.get().has_value() ? std::to_string(msg.fields.account.get().value()) : std::string_view("null"))
       << ",sender_location=\"" << msg.fields.sender_location.get_trimmed().value() << '"'
       << ",entering_trader=\"" << msg.fields.entering_trader.get_trimmed().value() << '"'
       << ",self_trade_prevention_instruction=\"" << sbe_binaryentrypoint::self_trade_prevention_instruction::to_string(msg.fields.self_trade_prevention_instruction.get().value()) << '"'
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",side=\"" << sbe_binaryentrypoint::side::to_string(msg.fields.side.get().value()) << '"'
       << ",ordtype=\"" << sbe_binaryentrypoint::ordtype::to_string(msg.fields.ordtype.get().value()) << '"'
       << ",time_in_force_optional=\"" << sbe_binaryentrypoint::time_in_force_optional::to_string(msg.fields.time_in_force_optional.get().value()) << '"'
       << ",routing_instruction=\"" << sbe_binaryentrypoint::routing_instruction::to_string(msg.fields.routing_instruction.get().value()) << '"'
       << ",order_qty=" << msg.fields.order_qty.get().value()
       << ",price_optional=" << (msg.fields.price_optional.get().has_value() ? std::to_string(msg.fields.price_optional.get().value()) : std::string_view("null"))
       << ",order_id_optional=" << (msg.fields.order_id_optional.get().has_value() ? std::to_string(msg.fields.order_id_optional.get().value()) : std::string_view("null"))
       << ",origclordid=" << (msg.fields.origclordid.get().has_value() ? std::to_string(msg.fields.origclordid.get().value()) : std::string_view("null"))
       << ",stop_px=" << (msg.fields.stop_px.get().has_value() ? std::to_string(msg.fields.stop_px.get().value()) : std::string_view("null"))
       << ",min_qty=" << (msg.fields.min_qty.get().has_value() ? std::to_string(msg.fields.min_qty.get().value()) : std::string_view("null"))
       << ",max_floor=" << (msg.fields.max_floor.get().has_value() ? std::to_string(msg.fields.max_floor.get().value()) : std::string_view("null"))
       << ",executing_trader_optional=\"" << (msg.fields.executing_trader_optional.get_trimmed().has_value() ? msg.fields.executing_trader_optional.get_trimmed().value() : std::string_view("null")) << '"'
       << ",account_type=\"" << sbe_binaryentrypoint::account_type::to_string(msg.fields.account_type.get().value()) << '"'
       << ",expire_date=" << (msg.fields.expire_date.get().has_value() ? std::to_string(msg.fields.expire_date.get().value()) : std::string_view("null"))
       << ",custodian_info.custodian=" << msg.fields.custodian_info.custodian.get().value()
       << ",custodian_info.custody_account=" << msg.fields.custodian_info.custody_account.get().value()
       << ",custodian_info.custody_allocation_type=" << msg.fields.custodian_info.custody_allocation_type.get().value()
       << ",investor_id.prefix=" << msg.fields.investor_id.prefix.get().value()
       << ",investor_id.document=" << msg.fields.investor_id.document.get().value()
       << ",strategy_id=" << (msg.fields.strategy_id.get().has_value() ? std::to_string(msg.fields.strategy_id.get().value()) : std::string_view("null"))
       << ",trading_sub_account=" << (msg.fields.trading_sub_account.get().has_value() ? std::to_string(msg.fields.trading_sub_account.get().value()) : std::string_view("null"))
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_cancel_request_message& msg) {
    os << "inbound_business_header.session_id=" << msg.fields.inbound_business_header.session_id.get().value()
       << ",inbound_business_header.msg_seq_num=" << msg.fields.inbound_business_header.msg_seq_num.get().value()
       << ",inbound_business_header.sending_time=" << (msg.fields.inbound_business_header.sending_time.get().has_value() ? std::to_string(msg.fields.inbound_business_header.sending_time.get().value()) : std::string_view("null"))
       << ",inbound_business_header.market_segment_id=" << static_cast<unsigned>(msg.fields.inbound_business_header.market_segment_id.get().value())
       << ",inbound_business_header.padding=\"" << msg.fields.inbound_business_header.padding.get().value() << '"'
       << ",clordid=" << msg.fields.clordid.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",order_id_optional=" << (msg.fields.order_id_optional.get().has_value() ? std::to_string(msg.fields.order_id_optional.get().value()) : std::string_view("null"))
       << ",origclordid=" << (msg.fields.origclordid.get().has_value() ? std::to_string(msg.fields.origclordid.get().value()) : std::string_view("null"))
       << ",side=\"" << sbe_binaryentrypoint::side::to_string(msg.fields.side.get().value()) << '"'
       << ",single_cancel_restatement_reason=\"" << sbe_binaryentrypoint::single_cancel_restatement_reason::to_string(msg.fields.single_cancel_restatement_reason.get().value()) << '"'
       << ",sender_location=\"" << msg.fields.sender_location.get_trimmed().value() << '"'
       << ",entering_trader=\"" << msg.fields.entering_trader.get_trimmed().value() << '"'
       << ",executing_trader_optional=\"" << (msg.fields.executing_trader_optional.get_trimmed().has_value() ? msg.fields.executing_trader_optional.get_trimmed().value() : std::string_view("null")) << '"'
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const new_order_cross_message& msg) {
    os << "inbound_business_header.session_id=" << msg.fields.inbound_business_header.session_id.get().value()
       << ",inbound_business_header.msg_seq_num=" << msg.fields.inbound_business_header.msg_seq_num.get().value()
       << ",inbound_business_header.sending_time=" << (msg.fields.inbound_business_header.sending_time.get().has_value() ? std::to_string(msg.fields.inbound_business_header.sending_time.get().value()) : std::string_view("null"))
       << ",inbound_business_header.market_segment_id=" << static_cast<unsigned>(msg.fields.inbound_business_header.market_segment_id.get().value())
       << ",inbound_business_header.padding=\"" << msg.fields.inbound_business_header.padding.get().value() << '"'
       << ",crossid=" << msg.fields.crossid.get().value()
       << ",sender_location=\"" << msg.fields.sender_location.get_trimmed().value() << '"'
       << ",entering_trader=\"" << msg.fields.entering_trader.get_trimmed().value() << '"'
       << ",executing_trader_optional=\"" << (msg.fields.executing_trader_optional.get_trimmed().has_value() ? msg.fields.executing_trader_optional.get_trimmed().value() : std::string_view("null")) << '"'
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",order_qty=" << msg.fields.order_qty.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",crossed_indicator=\"" << sbe_binaryentrypoint::crossed_indicator::to_string(msg.fields.crossed_indicator.get().value()) << '"'
       << ",cross_type=\"" << sbe_binaryentrypoint::cross_type::to_string(msg.fields.cross_type.get().value()) << '"'
       << ",cross_prioritization=\"" << sbe_binaryentrypoint::cross_prioritization::to_string(msg.fields.cross_prioritization.get().value()) << '"'
       << ",max_sweep_qty=" << (msg.fields.max_sweep_qty.get().has_value() ? std::to_string(msg.fields.max_sweep_qty.get().value()) : std::string_view("null"))
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const execution_report_new_message& msg) {
    os << "outbound_business_header.session_id=" << msg.fields.outbound_business_header.session_id.get().value()
       << ",outbound_business_header.msg_seq_num=" << msg.fields.outbound_business_header.msg_seq_num.get().value()
       << ",outbound_business_header.sending_time=" << (msg.fields.outbound_business_header.sending_time.get().has_value() ? std::to_string(msg.fields.outbound_business_header.sending_time.get().value()) : std::string_view("null"))
       << ",outbound_business_header.event_indicator=" << static_cast<unsigned>(msg.fields.outbound_business_header.event_indicator.get().value())
       << ",outbound_business_header.market_segment_id_optional=" << static_cast<unsigned>(msg.fields.outbound_business_header.market_segment_id_optional.get().value())
       << ",side=\"" << sbe_binaryentrypoint::side::to_string(msg.fields.side.get().value()) << '"'
       << ",ord_status=\"" << sbe_binaryentrypoint::ord_status::to_string(msg.fields.ord_status.get().value()) << '"'
       << ",clordid=" << msg.fields.clordid.get().value()
       << ",secondary_order_id=" << msg.fields.secondary_order_id.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",account=" << (msg.fields.account.get().has_value() ? std::to_string(msg.fields.account.get().value()) : std::string_view("null"))
       << ",exec_id=" << msg.fields.exec_id.get().value()
       << ",transact_time=" << msg.fields.transact_time.get().value()
       << ",market_segment_received_time=" << (msg.fields.market_segment_received_time.get().has_value() ? std::to_string(msg.fields.market_segment_received_time.get().value()) : std::string_view("null"))
       << ",protection_price=" << (msg.fields.protection_price.get().has_value() ? std::to_string(msg.fields.protection_price.get().value()) : std::string_view("null"))
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",working_indicator=\"" << sbe_binaryentrypoint::working_indicator::to_string(msg.fields.working_indicator.get().value()) << '"'
       << ",multi_leg_reporting_type=\"" << sbe_binaryentrypoint::multi_leg_reporting_type::to_string(msg.fields.multi_leg_reporting_type.get().value()) << '"'
       << ",ordtype=\"" << sbe_binaryentrypoint::ordtype::to_string(msg.fields.ordtype.get().value()) << '"'
       << ",time_in_force=\"" << sbe_binaryentrypoint::time_in_force::to_string(msg.fields.time_in_force.get().value()) << '"'
       << ",expire_date=" << (msg.fields.expire_date.get().has_value() ? std::to_string(msg.fields.expire_date.get().value()) : std::string_view("null"))
       << ",order_qty=" << msg.fields.order_qty.get().value()
       << ",price_optional=" << (msg.fields.price_optional.get().has_value() ? std::to_string(msg.fields.price_optional.get().value()) : std::string_view("null"))
       << ",stop_px=" << (msg.fields.stop_px.get().has_value() ? std::to_string(msg.fields.stop_px.get().value()) : std::string_view("null"))
       << ",min_qty=" << (msg.fields.min_qty.get().has_value() ? std::to_string(msg.fields.min_qty.get().value()) : std::string_view("null"))
       << ",max_floor=" << (msg.fields.max_floor.get().has_value() ? std::to_string(msg.fields.max_floor.get().value()) : std::string_view("null"))
       << ",crossid_optional=" << (msg.fields.crossid_optional.get().has_value() ? std::to_string(msg.fields.crossid_optional.get().value()) : std::string_view("null"))
       << ",received_time=" << (msg.fields.received_time.get().has_value() ? std::to_string(msg.fields.received_time.get().value()) : std::string_view("null"))
       << ",ordtagid=" << (msg.fields.ordtagid.get().has_value() ? std::to_string(msg.fields.ordtagid.get().value()) : std::string_view("null"))
       << ",investor_id.prefix=" << msg.fields.investor_id.prefix.get().value()
       << ",investor_id.document=" << msg.fields.investor_id.document.get().value()
       << ",cross_type=\"" << sbe_binaryentrypoint::cross_type::to_string(msg.fields.cross_type.get().value()) << '"'
       << ",cross_prioritization=\"" << sbe_binaryentrypoint::cross_prioritization::to_string(msg.fields.cross_prioritization.get().value()) << '"'
       << ",mm_protection_reset_optional=\"" << sbe_binaryentrypoint::mm_protection_reset_optional::to_string(msg.fields.mm_protection_reset_optional.get().value()) << '"'
       << ",strategy_id=" << (msg.fields.strategy_id.get().has_value() ? std::to_string(msg.fields.strategy_id.get().value()) : std::string_view("null"))
       << ",trading_sub_account=" << (msg.fields.trading_sub_account.get().has_value() ? std::to_string(msg.fields.trading_sub_account.get().value()) : std::string_view("null"))
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const execution_report_modify_message& msg) {
    os << "outbound_business_header.session_id=" << msg.fields.outbound_business_header.session_id.get().value()
       << ",outbound_business_header.msg_seq_num=" << msg.fields.outbound_business_header.msg_seq_num.get().value()
       << ",outbound_business_header.sending_time=" << (msg.fields.outbound_business_header.sending_time.get().has_value() ? std::to_string(msg.fields.outbound_business_header.sending_time.get().value()) : std::string_view("null"))
       << ",outbound_business_header.event_indicator=" << static_cast<unsigned>(msg.fields.outbound_business_header.event_indicator.get().value())
       << ",outbound_business_header.market_segment_id_optional=" << static_cast<unsigned>(msg.fields.outbound_business_header.market_segment_id_optional.get().value())
       << ",side=\"" << sbe_binaryentrypoint::side::to_string(msg.fields.side.get().value()) << '"'
       << ",ord_status=\"" << sbe_binaryentrypoint::ord_status::to_string(msg.fields.ord_status.get().value()) << '"'
       << ",clordid=" << msg.fields.clordid.get().value()
       << ",secondary_order_id=" << msg.fields.secondary_order_id.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",leaves_qty=" << msg.fields.leaves_qty.get().value()
       << ",account=" << (msg.fields.account.get().has_value() ? std::to_string(msg.fields.account.get().value()) : std::string_view("null"))
       << ",exec_id=" << msg.fields.exec_id.get().value()
       << ",transact_time=" << msg.fields.transact_time.get().value()
       << ",cum_qty=" << msg.fields.cum_qty.get().value()
       << ",market_segment_received_time=" << (msg.fields.market_segment_received_time.get().has_value() ? std::to_string(msg.fields.market_segment_received_time.get().value()) : std::string_view("null"))
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",origclordid=" << (msg.fields.origclordid.get().has_value() ? std::to_string(msg.fields.origclordid.get().value()) : std::string_view("null"))
       << ",protection_price=" << (msg.fields.protection_price.get().has_value() ? std::to_string(msg.fields.protection_price.get().value()) : std::string_view("null"))
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",working_indicator=\"" << sbe_binaryentrypoint::working_indicator::to_string(msg.fields.working_indicator.get().value()) << '"'
       << ",multi_leg_reporting_type=\"" << sbe_binaryentrypoint::multi_leg_reporting_type::to_string(msg.fields.multi_leg_reporting_type.get().value()) << '"'
       << ",ordtype=\"" << sbe_binaryentrypoint::ordtype::to_string(msg.fields.ordtype.get().value()) << '"'
       << ",time_in_force=\"" << sbe_binaryentrypoint::time_in_force::to_string(msg.fields.time_in_force.get().value()) << '"'
       << ",expire_date=" << (msg.fields.expire_date.get().has_value() ? std::to_string(msg.fields.expire_date.get().value()) : std::string_view("null"))
       << ",order_qty=" << msg.fields.order_qty.get().value()
       << ",price_optional=" << (msg.fields.price_optional.get().has_value() ? std::to_string(msg.fields.price_optional.get().value()) : std::string_view("null"))
       << ",stop_px=" << (msg.fields.stop_px.get().has_value() ? std::to_string(msg.fields.stop_px.get().value()) : std::string_view("null"))
       << ",min_qty=" << (msg.fields.min_qty.get().has_value() ? std::to_string(msg.fields.min_qty.get().value()) : std::string_view("null"))
       << ",max_floor=" << (msg.fields.max_floor.get().has_value() ? std::to_string(msg.fields.max_floor.get().value()) : std::string_view("null"))
       << ",received_time=" << (msg.fields.received_time.get().has_value() ? std::to_string(msg.fields.received_time.get().value()) : std::string_view("null"))
       << ",ordtagid=" << (msg.fields.ordtagid.get().has_value() ? std::to_string(msg.fields.ordtagid.get().value()) : std::string_view("null"))
       << ",investor_id.prefix=" << msg.fields.investor_id.prefix.get().value()
       << ",investor_id.document=" << msg.fields.investor_id.document.get().value()
       << ",mm_protection_reset_optional=\"" << sbe_binaryentrypoint::mm_protection_reset_optional::to_string(msg.fields.mm_protection_reset_optional.get().value()) << '"'
       << ",strategy_id=" << (msg.fields.strategy_id.get().has_value() ? std::to_string(msg.fields.strategy_id.get().value()) : std::string_view("null"))
       << ",trading_sub_account=" << (msg.fields.trading_sub_account.get().has_value() ? std::to_string(msg.fields.trading_sub_account.get().value()) : std::string_view("null"))
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const execution_report_cancel_message& msg) {
    os << "outbound_business_header.session_id=" << msg.fields.outbound_business_header.session_id.get().value()
       << ",outbound_business_header.msg_seq_num=" << msg.fields.outbound_business_header.msg_seq_num.get().value()
       << ",outbound_business_header.sending_time=" << (msg.fields.outbound_business_header.sending_time.get().has_value() ? std::to_string(msg.fields.outbound_business_header.sending_time.get().value()) : std::string_view("null"))
       << ",outbound_business_header.event_indicator=" << static_cast<unsigned>(msg.fields.outbound_business_header.event_indicator.get().value())
       << ",outbound_business_header.market_segment_id_optional=" << static_cast<unsigned>(msg.fields.outbound_business_header.market_segment_id_optional.get().value())
       << ",side=\"" << sbe_binaryentrypoint::side::to_string(msg.fields.side.get().value()) << '"'
       << ",ord_status=\"" << sbe_binaryentrypoint::ord_status::to_string(msg.fields.ord_status.get().value()) << '"'
       << ",clordid=" << msg.fields.clordid.get().value()
       << ",secondary_order_id=" << msg.fields.secondary_order_id.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",cum_qty=" << msg.fields.cum_qty.get().value()
       << ",account=" << (msg.fields.account.get().has_value() ? std::to_string(msg.fields.account.get().value()) : std::string_view("null"))
       << ",exec_id=" << msg.fields.exec_id.get().value()
       << ",transact_time=" << msg.fields.transact_time.get().value()
       << ",market_segment_received_time=" << (msg.fields.market_segment_received_time.get().has_value() ? std::to_string(msg.fields.market_segment_received_time.get().value()) : std::string_view("null"))
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",origclordid=" << (msg.fields.origclordid.get().has_value() ? std::to_string(msg.fields.origclordid.get().value()) : std::string_view("null"))
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",working_indicator=\"" << sbe_binaryentrypoint::working_indicator::to_string(msg.fields.working_indicator.get().value()) << '"'
       << ",exec_restatement_reason=\"" << sbe_binaryentrypoint::exec_restatement_reason::to_string(msg.fields.exec_restatement_reason.get().value()) << '"'
       << ",mass_action_report_id_optional=" << (msg.fields.mass_action_report_id_optional.get().has_value() ? std::to_string(msg.fields.mass_action_report_id_optional.get().value()) : std::string_view("null"))
       << ",ordtype=\"" << sbe_binaryentrypoint::ordtype::to_string(msg.fields.ordtype.get().value()) << '"'
       << ",time_in_force=\"" << sbe_binaryentrypoint::time_in_force::to_string(msg.fields.time_in_force.get().value()) << '"'
       << ",expire_date=" << (msg.fields.expire_date.get().has_value() ? std::to_string(msg.fields.expire_date.get().value()) : std::string_view("null"))
       << ",order_qty=" << msg.fields.order_qty.get().value()
       << ",price_optional=" << (msg.fields.price_optional.get().has_value() ? std::to_string(msg.fields.price_optional.get().value()) : std::string_view("null"))
       << ",stop_px=" << (msg.fields.stop_px.get().has_value() ? std::to_string(msg.fields.stop_px.get().value()) : std::string_view("null"))
       << ",min_qty=" << (msg.fields.min_qty.get().has_value() ? std::to_string(msg.fields.min_qty.get().value()) : std::string_view("null"))
       << ",max_floor=" << (msg.fields.max_floor.get().has_value() ? std::to_string(msg.fields.max_floor.get().value()) : std::string_view("null"))
       << ",received_time=" << (msg.fields.received_time.get().has_value() ? std::to_string(msg.fields.received_time.get().value()) : std::string_view("null"))
       << ",ordtagid=" << (msg.fields.ordtagid.get().has_value() ? std::to_string(msg.fields.ordtagid.get().value()) : std::string_view("null"))
       << ",investor_id.prefix=" << msg.fields.investor_id.prefix.get().value()
       << ",investor_id.document=" << msg.fields.investor_id.document.get().value()
       << ",strategy_id=" << (msg.fields.strategy_id.get().has_value() ? std::to_string(msg.fields.strategy_id.get().value()) : std::string_view("null"))
       << ",action_requested_from_session_id=" << (msg.fields.action_requested_from_session_id.get().has_value() ? std::to_string(msg.fields.action_requested_from_session_id.get().value()) : std::string_view("null"))
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const execution_report_trade_message& msg) {
    os << "outbound_business_header.session_id=" << msg.fields.outbound_business_header.session_id.get().value()
       << ",outbound_business_header.msg_seq_num=" << msg.fields.outbound_business_header.msg_seq_num.get().value()
       << ",outbound_business_header.sending_time=" << (msg.fields.outbound_business_header.sending_time.get().has_value() ? std::to_string(msg.fields.outbound_business_header.sending_time.get().value()) : std::string_view("null"))
       << ",outbound_business_header.event_indicator=" << static_cast<unsigned>(msg.fields.outbound_business_header.event_indicator.get().value())
       << ",outbound_business_header.market_segment_id_optional=" << static_cast<unsigned>(msg.fields.outbound_business_header.market_segment_id_optional.get().value())
       << ",side=\"" << sbe_binaryentrypoint::side::to_string(msg.fields.side.get().value()) << '"'
       << ",ord_status=\"" << sbe_binaryentrypoint::ord_status::to_string(msg.fields.ord_status.get().value()) << '"'
       << ",clordid_optional=" << (msg.fields.clordid_optional.get().has_value() ? std::to_string(msg.fields.clordid_optional.get().value()) : std::string_view("null"))
       << ",secondary_order_id=" << msg.fields.secondary_order_id.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",account=" << (msg.fields.account.get().has_value() ? std::to_string(msg.fields.account.get().value()) : std::string_view("null"))
       << ",last_qty=" << msg.fields.last_qty.get().value()
       << ",last_px=" << msg.fields.last_px.get().value()
       << ",exec_id=" << msg.fields.exec_id.get().value()
       << ",transact_time=" << msg.fields.transact_time.get().value()
       << ",leaves_qty=" << msg.fields.leaves_qty.get().value()
       << ",cum_qty=" << msg.fields.cum_qty.get().value()
       << ",aggressor_indicator=\"" << sbe_binaryentrypoint::aggressor_indicator::to_string(msg.fields.aggressor_indicator.get().value()) << '"'
       << ",exec_type=\"" << sbe_binaryentrypoint::exec_type::to_string(msg.fields.exec_type.get().value()) << '"'
       << ",order_category=\"" << sbe_binaryentrypoint::order_category::to_string(msg.fields.order_category.get().value()) << '"'
       << ",multi_leg_reporting_type=\"" << sbe_binaryentrypoint::multi_leg_reporting_type::to_string(msg.fields.multi_leg_reporting_type.get().value()) << '"'
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",contra_broker=" << msg.fields.contra_broker.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",tot_no_related_sym=" << (msg.fields.tot_no_related_sym.get().has_value() ? std::to_string(msg.fields.tot_no_related_sym.get().value()) : std::string_view("null"))
       << ",secondary_exec_id=" << (msg.fields.secondary_exec_id.get().has_value() ? std::to_string(msg.fields.secondary_exec_id.get().value()) : std::string_view("null"))
       << ",exec_ref_id=" << (msg.fields.exec_ref_id.get().has_value() ? std::to_string(msg.fields.exec_ref_id.get().value()) : std::string_view("null"))
       << ",crossid_optional=" << (msg.fields.crossid_optional.get().has_value() ? std::to_string(msg.fields.crossid_optional.get().value()) : std::string_view("null"))
       << ",crossed_indicator=\"" << sbe_binaryentrypoint::crossed_indicator::to_string(msg.fields.crossed_indicator.get().value()) << '"'
       << ",order_qty=" << msg.fields.order_qty.get().value()
       << ",trading_session_id=\"" << sbe_binaryentrypoint::trading_session_id::to_string(msg.fields.trading_session_id.get().value()) << '"'
       << ",trading_session_sub_id=\"" << sbe_binaryentrypoint::trading_session_sub_id::to_string(msg.fields.trading_session_sub_id.get().value()) << '"'
       << ",security_trading_status=\"" << sbe_binaryentrypoint::security_trading_status::to_string(msg.fields.security_trading_status.get().value()) << '"'
       << ",cross_type=\"" << sbe_binaryentrypoint::cross_type::to_string(msg.fields.cross_type.get().value()) << '"'
       << ",cross_prioritization=\"" << sbe_binaryentrypoint::cross_prioritization::to_string(msg.fields.cross_prioritization.get().value()) << '"'
       << ",strategy_id=" << (msg.fields.strategy_id.get().has_value() ? std::to_string(msg.fields.strategy_id.get().value()) : std::string_view("null"))
       << ",implied_event_id.event_id=" << msg.fields.implied_event_id.event_id.get().value()
       << ",implied_event_id.no_related_trades=" << msg.fields.implied_event_id.no_related_trades.get().value()
       << ",trading_sub_account=" << (msg.fields.trading_sub_account.get().has_value() ? std::to_string(msg.fields.trading_sub_account.get().value()) : std::string_view("null"))
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const execution_report_reject_message& msg) {
    os << "outbound_business_header.session_id=" << msg.fields.outbound_business_header.session_id.get().value()
       << ",outbound_business_header.msg_seq_num=" << msg.fields.outbound_business_header.msg_seq_num.get().value()
       << ",outbound_business_header.sending_time=" << (msg.fields.outbound_business_header.sending_time.get().has_value() ? std::to_string(msg.fields.outbound_business_header.sending_time.get().value()) : std::string_view("null"))
       << ",outbound_business_header.event_indicator=" << static_cast<unsigned>(msg.fields.outbound_business_header.event_indicator.get().value())
       << ",outbound_business_header.market_segment_id_optional=" << static_cast<unsigned>(msg.fields.outbound_business_header.market_segment_id_optional.get().value())
       << ",side=\"" << sbe_binaryentrypoint::side::to_string(msg.fields.side.get().value()) << '"'
       << ",cxl_rej_response_to=\"" << sbe_binaryentrypoint::cxl_rej_response_to::to_string(msg.fields.cxl_rej_response_to.get().value()) << '"'
       << ",clordid=" << msg.fields.clordid.get().value()
       << ",secondary_order_id_optional=" << (msg.fields.secondary_order_id_optional.get().has_value() ? std::to_string(msg.fields.secondary_order_id_optional.get().value()) : std::string_view("null"))
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",ord_rej_reason=\"" << sbe_binaryentrypoint::ord_rej_reason::to_string(msg.fields.ord_rej_reason.get().value()) << '"'
       << ",transact_time=" << msg.fields.transact_time.get().value()
       << ",exec_id=" << msg.fields.exec_id.get().value()
       << ",order_id_optional=" << (msg.fields.order_id_optional.get().has_value() ? std::to_string(msg.fields.order_id_optional.get().value()) : std::string_view("null"))
       << ",origclordid=" << (msg.fields.origclordid.get().has_value() ? std::to_string(msg.fields.origclordid.get().value()) : std::string_view("null"))
       << ",account=" << (msg.fields.account.get().has_value() ? std::to_string(msg.fields.account.get().value()) : std::string_view("null"))
       << ",ordtype=\"" << sbe_binaryentrypoint::ordtype::to_string(msg.fields.ordtype.get().value()) << '"'
       << ",time_in_force=\"" << sbe_binaryentrypoint::time_in_force::to_string(msg.fields.time_in_force.get().value()) << '"'
       << ",expire_date=" << (msg.fields.expire_date.get().has_value() ? std::to_string(msg.fields.expire_date.get().value()) : std::string_view("null"))
       << ",order_qty_optional=" << (msg.fields.order_qty_optional.get().has_value() ? std::to_string(msg.fields.order_qty_optional.get().value()) : std::string_view("null"))
       << ",price_optional=" << (msg.fields.price_optional.get().has_value() ? std::to_string(msg.fields.price_optional.get().value()) : std::string_view("null"))
       << ",stop_px=" << (msg.fields.stop_px.get().has_value() ? std::to_string(msg.fields.stop_px.get().value()) : std::string_view("null"))
       << ",min_qty=" << (msg.fields.min_qty.get().has_value() ? std::to_string(msg.fields.min_qty.get().value()) : std::string_view("null"))
       << ",max_floor=" << (msg.fields.max_floor.get().has_value() ? std::to_string(msg.fields.max_floor.get().value()) : std::string_view("null"))
       << ",crossid_optional=" << (msg.fields.crossid_optional.get().has_value() ? std::to_string(msg.fields.crossid_optional.get().value()) : std::string_view("null"))
       << ",crossed_indicator=\"" << sbe_binaryentrypoint::crossed_indicator::to_string(msg.fields.crossed_indicator.get().value()) << '"'
       << ",received_time=" << (msg.fields.received_time.get().has_value() ? std::to_string(msg.fields.received_time.get().value()) : std::string_view("null"))
       << ",ordtagid=" << (msg.fields.ordtagid.get().has_value() ? std::to_string(msg.fields.ordtagid.get().value()) : std::string_view("null"))
       << ",investor_id.prefix=" << msg.fields.investor_id.prefix.get().value()
       << ",investor_id.document=" << msg.fields.investor_id.document.get().value()
       << ",strategy_id=" << (msg.fields.strategy_id.get().has_value() ? std::to_string(msg.fields.strategy_id.get().value()) : std::string_view("null"))
       << ",trading_sub_account=" << (msg.fields.trading_sub_account.get().has_value() ? std::to_string(msg.fields.trading_sub_account.get().value()) : std::string_view("null"))
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const execution_report_forward_message& msg) {
    os << "outbound_business_header.session_id=" << msg.fields.outbound_business_header.session_id.get().value()
       << ",outbound_business_header.msg_seq_num=" << msg.fields.outbound_business_header.msg_seq_num.get().value()
       << ",outbound_business_header.sending_time=" << (msg.fields.outbound_business_header.sending_time.get().has_value() ? std::to_string(msg.fields.outbound_business_header.sending_time.get().value()) : std::string_view("null"))
       << ",outbound_business_header.event_indicator=" << static_cast<unsigned>(msg.fields.outbound_business_header.event_indicator.get().value())
       << ",outbound_business_header.market_segment_id_optional=" << static_cast<unsigned>(msg.fields.outbound_business_header.market_segment_id_optional.get().value())
       << ",side=\"" << sbe_binaryentrypoint::side::to_string(msg.fields.side.get().value()) << '"'
       << ",ord_status=\"" << sbe_binaryentrypoint::ord_status::to_string(msg.fields.ord_status.get().value()) << '"'
       << ",clordid_optional=" << (msg.fields.clordid_optional.get().has_value() ? std::to_string(msg.fields.clordid_optional.get().value()) : std::string_view("null"))
       << ",secondary_order_id=" << msg.fields.secondary_order_id.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",account=" << (msg.fields.account.get().has_value() ? std::to_string(msg.fields.account.get().value()) : std::string_view("null"))
       << ",last_qty=" << msg.fields.last_qty.get().value()
       << ",last_px=" << msg.fields.last_px.get().value()
       << ",exec_id=" << msg.fields.exec_id.get().value()
       << ",transact_time=" << msg.fields.transact_time.get().value()
       << ",leaves_qty=" << msg.fields.leaves_qty.get().value()
       << ",cum_qty=" << msg.fields.cum_qty.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",contra_broker=" << msg.fields.contra_broker.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",aggressor_indicator=\"" << sbe_binaryentrypoint::aggressor_indicator::to_string(msg.fields.aggressor_indicator.get().value()) << '"'
       << ",settl_type_optional=\"" << sbe_binaryentrypoint::settl_type_optional::to_string(msg.fields.settl_type_optional.get().value()) << '"'
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",days_to_settlement_optional=" << (msg.fields.days_to_settlement_optional.get().has_value() ? std::to_string(msg.fields.days_to_settlement_optional.get().value()) : std::string_view("null"))
       << ",secondary_exec_id=" << (msg.fields.secondary_exec_id.get().has_value() ? std::to_string(msg.fields.secondary_exec_id.get().value()) : std::string_view("null"))
       << ",exec_ref_id=" << (msg.fields.exec_ref_id.get().has_value() ? std::to_string(msg.fields.exec_ref_id.get().value()) : std::string_view("null"))
       << ",fixed_rate_percentage_8_optional=" << (msg.fields.fixed_rate_percentage_8_optional.get().has_value() ? std::to_string(msg.fields.fixed_rate_percentage_8_optional.get().value()) : std::string_view("null"))
       << ",order_qty=" << msg.fields.order_qty.get().value()
       << ",trading_session_id=\"" << sbe_binaryentrypoint::trading_session_id::to_string(msg.fields.trading_session_id.get().value()) << '"'
       << ",trading_session_sub_id=\"" << sbe_binaryentrypoint::trading_session_sub_id::to_string(msg.fields.trading_session_sub_id.get().value()) << '"'
       << ",security_trading_status=\"" << sbe_binaryentrypoint::security_trading_status::to_string(msg.fields.security_trading_status.get().value()) << '"'
       << ",trading_sub_account=" << (msg.fields.trading_sub_account.get().has_value() ? std::to_string(msg.fields.trading_sub_account.get().value()) : std::string_view("null"))
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const business_message_reject_message& msg) {
    os << "outbound_business_header.session_id=" << msg.fields.outbound_business_header.session_id.get().value()
       << ",outbound_business_header.msg_seq_num=" << msg.fields.outbound_business_header.msg_seq_num.get().value()
       << ",outbound_business_header.sending_time=" << (msg.fields.outbound_business_header.sending_time.get().has_value() ? std::to_string(msg.fields.outbound_business_header.sending_time.get().value()) : std::string_view("null"))
       << ",outbound_business_header.event_indicator=" << static_cast<unsigned>(msg.fields.outbound_business_header.event_indicator.get().value())
       << ",outbound_business_header.market_segment_id_optional=" << static_cast<unsigned>(msg.fields.outbound_business_header.market_segment_id_optional.get().value())
       << ",ref_msg_type=\"" << sbe_binaryentrypoint::ref_msg_type::to_string(msg.fields.ref_msg_type.get().value()) << '"'
       << ",ref_seq_num=" << msg.fields.ref_seq_num.get().value()
       << ",business_reject_ref_id=" << (msg.fields.business_reject_ref_id.get().has_value() ? std::to_string(msg.fields.business_reject_ref_id.get().value()) : std::string_view("null"))
       << ",business_reject_reason=" << msg.fields.business_reject_reason.get().value()
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const security_definition_request_message& msg) {
    os << "inbound_business_header.session_id=" << msg.fields.inbound_business_header.session_id.get().value()
       << ",inbound_business_header.msg_seq_num=" << msg.fields.inbound_business_header.msg_seq_num.get().value()
       << ",inbound_business_header.sending_time=" << (msg.fields.inbound_business_header.sending_time.get().has_value() ? std::to_string(msg.fields.inbound_business_header.sending_time.get().value()) : std::string_view("null"))
       << ",inbound_business_header.market_segment_id=" << static_cast<unsigned>(msg.fields.inbound_business_header.market_segment_id.get().value())
       << ",inbound_business_header.padding=\"" << msg.fields.inbound_business_header.padding.get().value() << '"'
       << ",security_req_id=" << msg.fields.security_req_id.get().value()
       << ",sender_location=\"" << msg.fields.sender_location.get_trimmed().value() << '"'
       << ",entering_trader=\"" << msg.fields.entering_trader.get_trimmed().value() << '"'
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const security_definition_response_message& msg) {
    os << "outbound_business_header.session_id=" << msg.fields.outbound_business_header.session_id.get().value()
       << ",outbound_business_header.msg_seq_num=" << msg.fields.outbound_business_header.msg_seq_num.get().value()
       << ",outbound_business_header.sending_time=" << (msg.fields.outbound_business_header.sending_time.get().has_value() ? std::to_string(msg.fields.outbound_business_header.sending_time.get().value()) : std::string_view("null"))
       << ",outbound_business_header.event_indicator=" << static_cast<unsigned>(msg.fields.outbound_business_header.event_indicator.get().value())
       << ",outbound_business_header.market_segment_id_optional=" << static_cast<unsigned>(msg.fields.outbound_business_header.market_segment_id_optional.get().value())
       << ",security_req_id=" << msg.fields.security_req_id.get().value()
       << ",security_id_optional=" << (msg.fields.security_id_optional.get().has_value() ? std::to_string(msg.fields.security_id_optional.get().value()) : std::string_view("null"))
       << ",security_response_type=\"" << sbe_binaryentrypoint::security_response_type::to_string(msg.fields.security_response_type.get().value()) << '"'
       << ",security_strategy_type=\"" << (msg.fields.security_strategy_type.get_trimmed().has_value() ? msg.fields.security_strategy_type.get_trimmed().value() : std::string_view("null")) << '"'
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",security_response_id=" << msg.fields.security_response_id.get().value()
       << ",sender_location=\"" << msg.fields.sender_location.get_trimmed().value() << '"'
       << ",entering_trader=\"" << msg.fields.entering_trader.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const quote_request_message& msg) {
    os << "bidirectional_business_header.session_id=" << msg.fields.bidirectional_business_header.session_id.get().value()
       << ",bidirectional_business_header.msg_seq_num=" << msg.fields.bidirectional_business_header.msg_seq_num.get().value()
       << ",bidirectional_business_header.sending_time=" << (msg.fields.bidirectional_business_header.sending_time.get().has_value() ? std::to_string(msg.fields.bidirectional_business_header.sending_time.get().value()) : std::string_view("null"))
       << ",bidirectional_business_header.event_indicator=" << static_cast<unsigned>(msg.fields.bidirectional_business_header.event_indicator.get().value())
       << ",bidirectional_business_header.market_segment_id_optional=" << static_cast<unsigned>(msg.fields.bidirectional_business_header.market_segment_id_optional.get().value())
       << ",bidirectional_business_header.padding=\"" << msg.fields.bidirectional_business_header.padding.get().value() << '"'
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",quote_req_id=" << msg.fields.quote_req_id.get().value()
       << ",quote_id_optional=" << (msg.fields.quote_id_optional.get().has_value() ? std::to_string(msg.fields.quote_id_optional.get().value()) : std::string_view("null"))
       << ",trade_id_optional=" << (msg.fields.trade_id_optional.get().has_value() ? std::to_string(msg.fields.trade_id_optional.get().value()) : std::string_view("null"))
       << ",contra_broker=" << msg.fields.contra_broker.get().value()
       << ",transact_time=" << msg.fields.transact_time.get().value()
       << ",price_8=" << msg.fields.price_8.get().value()
       << ",settl_type=\"" << sbe_binaryentrypoint::settl_type::to_string(msg.fields.settl_type.get().value()) << '"'
       << ",execute_underlying_trade=\"" << sbe_binaryentrypoint::execute_underlying_trade::to_string(msg.fields.execute_underlying_trade.get().value()) << '"'
       << ",order_qty=" << msg.fields.order_qty.get().value()
       << ",sender_location=\"" << msg.fields.sender_location.get_trimmed().value() << '"'
       << ",entering_trader=\"" << msg.fields.entering_trader.get_trimmed().value() << '"'
       << ",executing_trader=\"" << msg.fields.executing_trader.get_trimmed().value() << '"'
       << ",fixed_rate_percentage_8=" << msg.fields.fixed_rate_percentage_8.get().value()
       << ",days_to_settlement=" << msg.fields.days_to_settlement.get().value()
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const quote_status_report_message& msg) {
    os << "bidirectional_business_header.session_id=" << msg.fields.bidirectional_business_header.session_id.get().value()
       << ",bidirectional_business_header.msg_seq_num=" << msg.fields.bidirectional_business_header.msg_seq_num.get().value()
       << ",bidirectional_business_header.sending_time=" << (msg.fields.bidirectional_business_header.sending_time.get().has_value() ? std::to_string(msg.fields.bidirectional_business_header.sending_time.get().value()) : std::string_view("null"))
       << ",bidirectional_business_header.event_indicator=" << static_cast<unsigned>(msg.fields.bidirectional_business_header.event_indicator.get().value())
       << ",bidirectional_business_header.market_segment_id_optional=" << static_cast<unsigned>(msg.fields.bidirectional_business_header.market_segment_id_optional.get().value())
       << ",bidirectional_business_header.padding=\"" << msg.fields.bidirectional_business_header.padding.get().value() << '"'
       << ",quote_reject_reason=\"" << sbe_binaryentrypoint::quote_reject_reason::to_string(msg.fields.quote_reject_reason.get().value()) << '"'
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",quote_req_id=" << msg.fields.quote_req_id.get().value()
       << ",quote_id=" << msg.fields.quote_id.get().value()
       << ",trade_id_optional=" << (msg.fields.trade_id_optional.get().has_value() ? std::to_string(msg.fields.trade_id_optional.get().value()) : std::string_view("null"))
       << ",contra_broker=" << msg.fields.contra_broker.get().value()
       << ",transact_time=" << msg.fields.transact_time.get().value()
       << ",quote_status=\"" << sbe_binaryentrypoint::quote_status::to_string(msg.fields.quote_status.get().value()) << '"'
       << ",quote_status_response_to=\"" << sbe_binaryentrypoint::quote_status_response_to::to_string(msg.fields.quote_status_response_to.get().value()) << '"'
       << ",account=" << (msg.fields.account.get().has_value() ? std::to_string(msg.fields.account.get().value()) : std::string_view("null"))
       << ",side_optional=\"" << sbe_binaryentrypoint::side_optional::to_string(msg.fields.side_optional.get().value()) << '"'
       << ",settl_type_optional=\"" << sbe_binaryentrypoint::settl_type_optional::to_string(msg.fields.settl_type_optional.get().value()) << '"'
       << ",price_8_optional=" << (msg.fields.price_8_optional.get().has_value() ? std::to_string(msg.fields.price_8_optional.get().value()) : std::string_view("null"))
       << ",order_qty=" << msg.fields.order_qty.get().value()
       << ",sender_location=\"" << msg.fields.sender_location.get_trimmed().value() << '"'
       << ",entering_trader=\"" << msg.fields.entering_trader.get_trimmed().value() << '"'
       << ",executing_trader=\"" << msg.fields.executing_trader.get_trimmed().value() << '"'
       << ",fixed_rate_percentage_8_optional=" << (msg.fields.fixed_rate_percentage_8_optional.get().has_value() ? std::to_string(msg.fields.fixed_rate_percentage_8_optional.get().value()) : std::string_view("null"))
       << ",execute_underlying_trade=\"" << sbe_binaryentrypoint::execute_underlying_trade::to_string(msg.fields.execute_underlying_trade.get().value()) << '"'
       << ",days_to_settlement_optional=" << (msg.fields.days_to_settlement_optional.get().has_value() ? std::to_string(msg.fields.days_to_settlement_optional.get().value()) : std::string_view("null"))
       << ",trading_sub_account=" << (msg.fields.trading_sub_account.get().has_value() ? std::to_string(msg.fields.trading_sub_account.get().value()) : std::string_view("null"))
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const quote_message& msg) {
    os << "bidirectional_business_header.session_id=" << msg.fields.bidirectional_business_header.session_id.get().value()
       << ",bidirectional_business_header.msg_seq_num=" << msg.fields.bidirectional_business_header.msg_seq_num.get().value()
       << ",bidirectional_business_header.sending_time=" << (msg.fields.bidirectional_business_header.sending_time.get().has_value() ? std::to_string(msg.fields.bidirectional_business_header.sending_time.get().value()) : std::string_view("null"))
       << ",bidirectional_business_header.event_indicator=" << static_cast<unsigned>(msg.fields.bidirectional_business_header.event_indicator.get().value())
       << ",bidirectional_business_header.market_segment_id_optional=" << static_cast<unsigned>(msg.fields.bidirectional_business_header.market_segment_id_optional.get().value())
       << ",bidirectional_business_header.padding=\"" << msg.fields.bidirectional_business_header.padding.get().value() << '"'
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",quote_req_id=" << msg.fields.quote_req_id.get().value()
       << ",quote_id=" << msg.fields.quote_id.get().value()
       << ",transact_time=" << msg.fields.transact_time.get().value()
       << ",price_8_optional=" << (msg.fields.price_8_optional.get().has_value() ? std::to_string(msg.fields.price_8_optional.get().value()) : std::string_view("null"))
       << ",order_qty=" << msg.fields.order_qty.get().value()
       << ",side=\"" << sbe_binaryentrypoint::side::to_string(msg.fields.side.get().value()) << '"'
       << ",settl_type=\"" << sbe_binaryentrypoint::settl_type::to_string(msg.fields.settl_type.get().value()) << '"'
       << ",account=" << (msg.fields.account.get().has_value() ? std::to_string(msg.fields.account.get().value()) : std::string_view("null"))
       << ",sender_location=\"" << msg.fields.sender_location.get_trimmed().value() << '"'
       << ",entering_trader=\"" << msg.fields.entering_trader.get_trimmed().value() << '"'
       << ",executing_trader=\"" << msg.fields.executing_trader.get_trimmed().value() << '"'
       << ",fixed_rate_percentage_8=" << msg.fields.fixed_rate_percentage_8.get().value()
       << ",execute_underlying_trade=\"" << sbe_binaryentrypoint::execute_underlying_trade::to_string(msg.fields.execute_underlying_trade.get().value()) << '"'
       << ",days_to_settlement=" << msg.fields.days_to_settlement.get().value()
       << ",trading_sub_account=" << (msg.fields.trading_sub_account.get().has_value() ? std::to_string(msg.fields.trading_sub_account.get().value()) : std::string_view("null"))
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const quote_cancel_message& msg) {
    os << "bidirectional_business_header.session_id=" << msg.fields.bidirectional_business_header.session_id.get().value()
       << ",bidirectional_business_header.msg_seq_num=" << msg.fields.bidirectional_business_header.msg_seq_num.get().value()
       << ",bidirectional_business_header.sending_time=" << (msg.fields.bidirectional_business_header.sending_time.get().has_value() ? std::to_string(msg.fields.bidirectional_business_header.sending_time.get().value()) : std::string_view("null"))
       << ",bidirectional_business_header.event_indicator=" << static_cast<unsigned>(msg.fields.bidirectional_business_header.event_indicator.get().value())
       << ",bidirectional_business_header.market_segment_id_optional=" << static_cast<unsigned>(msg.fields.bidirectional_business_header.market_segment_id_optional.get().value())
       << ",bidirectional_business_header.padding=\"" << msg.fields.bidirectional_business_header.padding.get().value() << '"'
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",quote_req_id_optional=" << (msg.fields.quote_req_id_optional.get().has_value() ? std::to_string(msg.fields.quote_req_id_optional.get().value()) : std::string_view("null"))
       << ",quote_id_optional=" << (msg.fields.quote_id_optional.get().has_value() ? std::to_string(msg.fields.quote_id_optional.get().value()) : std::string_view("null"))
       << ",account=" << (msg.fields.account.get().has_value() ? std::to_string(msg.fields.account.get().value()) : std::string_view("null"))
       << ",sender_location=\"" << msg.fields.sender_location.get_trimmed().value() << '"'
       << ",entering_trader=\"" << msg.fields.entering_trader.get_trimmed().value() << '"'
       << ",executing_trader=\"" << msg.fields.executing_trader.get_trimmed().value() << '"'
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const quote_request_reject_message& msg) {
    os << "bidirectional_business_header.session_id=" << msg.fields.bidirectional_business_header.session_id.get().value()
       << ",bidirectional_business_header.msg_seq_num=" << msg.fields.bidirectional_business_header.msg_seq_num.get().value()
       << ",bidirectional_business_header.sending_time=" << (msg.fields.bidirectional_business_header.sending_time.get().has_value() ? std::to_string(msg.fields.bidirectional_business_header.sending_time.get().value()) : std::string_view("null"))
       << ",bidirectional_business_header.event_indicator=" << static_cast<unsigned>(msg.fields.bidirectional_business_header.event_indicator.get().value())
       << ",bidirectional_business_header.market_segment_id_optional=" << static_cast<unsigned>(msg.fields.bidirectional_business_header.market_segment_id_optional.get().value())
       << ",bidirectional_business_header.padding=\"" << msg.fields.bidirectional_business_header.padding.get().value() << '"'
       << ",quote_request_reject_reason=" << (msg.fields.quote_request_reject_reason.get().has_value() ? std::to_string(msg.fields.quote_request_reject_reason.get().value()) : std::string_view("null"))
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",quote_req_id=" << msg.fields.quote_req_id.get().value()
       << ",quote_id_optional=" << (msg.fields.quote_id_optional.get().has_value() ? std::to_string(msg.fields.quote_id_optional.get().value()) : std::string_view("null"))
       << ",trade_id_optional=" << (msg.fields.trade_id_optional.get().has_value() ? std::to_string(msg.fields.trade_id_optional.get().value()) : std::string_view("null"))
       << ",contra_broker=" << msg.fields.contra_broker.get().value()
       << ",transact_time=" << msg.fields.transact_time.get().value()
       << ",entering_trader=\"" << msg.fields.entering_trader.get_trimmed().value() << '"'
       << ",settl_type_optional=\"" << sbe_binaryentrypoint::settl_type_optional::to_string(msg.fields.settl_type_optional.get().value()) << '"'
       << ",price_8_optional=" << (msg.fields.price_8_optional.get().has_value() ? std::to_string(msg.fields.price_8_optional.get().value()) : std::string_view("null"))
       << ",order_qty_optional=" << (msg.fields.order_qty_optional.get().has_value() ? std::to_string(msg.fields.order_qty_optional.get().value()) : std::string_view("null"))
       << ",sender_location=\"" << msg.fields.sender_location.get_trimmed().value() << '"'
       << ",executing_trader=\"" << msg.fields.executing_trader.get_trimmed().value() << '"'
       << ",fixed_rate_percentage_8_optional=" << (msg.fields.fixed_rate_percentage_8_optional.get().has_value() ? std::to_string(msg.fields.fixed_rate_percentage_8_optional.get().value()) : std::string_view("null"))
       << ",days_to_settlement_optional=" << (msg.fields.days_to_settlement_optional.get().has_value() ? std::to_string(msg.fields.days_to_settlement_optional.get().value()) : std::string_view("null"))
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const position_maintenance_cancel_request_message& msg) {
    os << "inbound_business_header.session_id=" << msg.fields.inbound_business_header.session_id.get().value()
       << ",inbound_business_header.msg_seq_num=" << msg.fields.inbound_business_header.msg_seq_num.get().value()
       << ",inbound_business_header.sending_time=" << (msg.fields.inbound_business_header.sending_time.get().has_value() ? std::to_string(msg.fields.inbound_business_header.sending_time.get().value()) : std::string_view("null"))
       << ",inbound_business_header.market_segment_id=" << static_cast<unsigned>(msg.fields.inbound_business_header.market_segment_id.get().value())
       << ",inbound_business_header.padding=\"" << msg.fields.inbound_business_header.padding.get().value() << '"'
       << ",pos_req_id=" << msg.fields.pos_req_id.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",orig_pos_req_ref_id=" << (msg.fields.orig_pos_req_ref_id.get().has_value() ? std::to_string(msg.fields.orig_pos_req_ref_id.get().value()) : std::string_view("null"))
       << ",pos_maint_rpt_ref_id=" << (msg.fields.pos_maint_rpt_ref_id.get().has_value() ? std::to_string(msg.fields.pos_maint_rpt_ref_id.get().value()) : std::string_view("null"))
       << ",sender_location=\"" << msg.fields.sender_location.get_trimmed().value() << '"'
       << ",entering_trader=\"" << msg.fields.entering_trader.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const position_maintenance_request_message& msg) {
    os << "inbound_business_header.session_id=" << msg.fields.inbound_business_header.session_id.get().value()
       << ",inbound_business_header.msg_seq_num=" << msg.fields.inbound_business_header.msg_seq_num.get().value()
       << ",inbound_business_header.sending_time=" << (msg.fields.inbound_business_header.sending_time.get().has_value() ? std::to_string(msg.fields.inbound_business_header.sending_time.get().value()) : std::string_view("null"))
       << ",inbound_business_header.market_segment_id=" << static_cast<unsigned>(msg.fields.inbound_business_header.market_segment_id.get().value())
       << ",inbound_business_header.padding=\"" << msg.fields.inbound_business_header.padding.get().value() << '"'
       << ",pos_req_id=" << msg.fields.pos_req_id.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",threshold_amount=" << (msg.fields.threshold_amount.get().has_value() ? std::to_string(msg.fields.threshold_amount.get().value()) : std::string_view("null"))
       << ",account=" << (msg.fields.account.get().has_value() ? std::to_string(msg.fields.account.get().value()) : std::string_view("null"))
       << ",sender_location=\"" << msg.fields.sender_location.get_trimmed().value() << '"'
       << ",pos_trans_type=\"" << sbe_binaryentrypoint::pos_trans_type::to_string(msg.fields.pos_trans_type.get().value()) << '"'
       << ",clearing_business_date=" << msg.fields.clearing_business_date.get().value()
       << ",contrary_instruction_indicator=\"" << sbe_binaryentrypoint::contrary_instruction_indicator::to_string(msg.fields.contrary_instruction_indicator.get().value()) << '"'
       << ",entering_trader=\"" << msg.fields.entering_trader.get_trimmed().value() << '"'
       << ",long_qty=" << msg.fields.long_qty.get().value()
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const position_maintenance_report_message& msg) {
    os << "outbound_business_header.session_id=" << msg.fields.outbound_business_header.session_id.get().value()
       << ",outbound_business_header.msg_seq_num=" << msg.fields.outbound_business_header.msg_seq_num.get().value()
       << ",outbound_business_header.sending_time=" << (msg.fields.outbound_business_header.sending_time.get().has_value() ? std::to_string(msg.fields.outbound_business_header.sending_time.get().value()) : std::string_view("null"))
       << ",outbound_business_header.event_indicator=" << static_cast<unsigned>(msg.fields.outbound_business_header.event_indicator.get().value())
       << ",outbound_business_header.market_segment_id_optional=" << static_cast<unsigned>(msg.fields.outbound_business_header.market_segment_id_optional.get().value())
       << ",pos_req_id_optional=" << (msg.fields.pos_req_id_optional.get().has_value() ? std::to_string(msg.fields.pos_req_id_optional.get().value()) : std::string_view("null"))
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",pos_maint_rpt_id=" << msg.fields.pos_maint_rpt_id.get().value()
       << ",pos_trans_type=\"" << sbe_binaryentrypoint::pos_trans_type::to_string(msg.fields.pos_trans_type.get().value()) << '"'
       << ",pos_maint_action=\"" << sbe_binaryentrypoint::pos_maint_action::to_string(msg.fields.pos_maint_action.get().value()) << '"'
       << ",pos_maint_status=\"" << sbe_binaryentrypoint::pos_maint_status::to_string(msg.fields.pos_maint_status.get().value()) << '"'
       << ",trade_id_optional=" << (msg.fields.trade_id_optional.get().has_value() ? std::to_string(msg.fields.trade_id_optional.get().value()) : std::string_view("null"))
       << ",orig_pos_req_ref_id=" << (msg.fields.orig_pos_req_ref_id.get().has_value() ? std::to_string(msg.fields.orig_pos_req_ref_id.get().value()) : std::string_view("null"))
       << ",account_type=\"" << sbe_binaryentrypoint::account_type::to_string(msg.fields.account_type.get().value()) << '"'
       << ",clearing_business_date=" << msg.fields.clearing_business_date.get().value()
       << ",threshold_amount=" << (msg.fields.threshold_amount.get().has_value() ? std::to_string(msg.fields.threshold_amount.get().value()) : std::string_view("null"))
       << ",transact_time=" << msg.fields.transact_time.get().value()
       << ",account=" << (msg.fields.account.get().has_value() ? std::to_string(msg.fields.account.get().value()) : std::string_view("null"))
       << ",sender_location=\"" << msg.fields.sender_location.get_trimmed().value() << '"'
       << ",pos_maint_result=" << (msg.fields.pos_maint_result.get().has_value() ? std::to_string(msg.fields.pos_maint_result.get().value()) : std::string_view("null"))
       << ",contrary_instruction_indicator=\"" << sbe_binaryentrypoint::contrary_instruction_indicator::to_string(msg.fields.contrary_instruction_indicator.get().value()) << '"'
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const allocation_instruction_message& msg) {
    os << "inbound_business_header.session_id=" << msg.fields.inbound_business_header.session_id.get().value()
       << ",inbound_business_header.msg_seq_num=" << msg.fields.inbound_business_header.msg_seq_num.get().value()
       << ",inbound_business_header.sending_time=" << (msg.fields.inbound_business_header.sending_time.get().has_value() ? std::to_string(msg.fields.inbound_business_header.sending_time.get().value()) : std::string_view("null"))
       << ",inbound_business_header.market_segment_id=" << static_cast<unsigned>(msg.fields.inbound_business_header.market_segment_id.get().value())
       << ",inbound_business_header.padding=\"" << msg.fields.inbound_business_header.padding.get().value() << '"'
       << ",alloc_id=" << msg.fields.alloc_id.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",alloc_trans_type=\"" << sbe_binaryentrypoint::alloc_trans_type::to_string(msg.fields.alloc_trans_type.get().value()) << '"'
       << ",alloc_type=\"" << sbe_binaryentrypoint::alloc_type::to_string(msg.fields.alloc_type.get().value()) << '"'
       << ",alloc_no_orders_type=\"" << sbe_binaryentrypoint::alloc_no_orders_type::to_string(msg.fields.alloc_no_orders_type.get().value()) << '"'
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",sender_location=\"" << msg.fields.sender_location.get_trimmed().value() << '"'
       << ",entering_trader=\"" << msg.fields.entering_trader.get_trimmed().value() << '"'
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",trade_date_optional=" << (msg.fields.trade_date_optional.get().has_value() ? std::to_string(msg.fields.trade_date_optional.get().value()) : std::string_view("null"))
       << ",individual_alloc_id=" << msg.fields.individual_alloc_id.get().value()
       << ",alloc_account=" << msg.fields.alloc_account.get().value()
       << ",alloc_qty=" << msg.fields.alloc_qty.get().value()
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const allocation_report_message& msg) {
    os << "outbound_business_header.session_id=" << msg.fields.outbound_business_header.session_id.get().value()
       << ",outbound_business_header.msg_seq_num=" << msg.fields.outbound_business_header.msg_seq_num.get().value()
       << ",outbound_business_header.sending_time=" << (msg.fields.outbound_business_header.sending_time.get().has_value() ? std::to_string(msg.fields.outbound_business_header.sending_time.get().value()) : std::string_view("null"))
       << ",outbound_business_header.event_indicator=" << static_cast<unsigned>(msg.fields.outbound_business_header.event_indicator.get().value())
       << ",outbound_business_header.market_segment_id_optional=" << static_cast<unsigned>(msg.fields.outbound_business_header.market_segment_id_optional.get().value())
       << ",alloc_id=" << msg.fields.alloc_id.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",alloc_report_id=" << msg.fields.alloc_report_id.get().value()
       << ",alloc_trans_type=\"" << sbe_binaryentrypoint::alloc_trans_type::to_string(msg.fields.alloc_trans_type.get().value()) << '"'
       << ",alloc_report_type=\"" << sbe_binaryentrypoint::alloc_report_type::to_string(msg.fields.alloc_report_type.get().value()) << '"'
       << ",alloc_no_orders_type=\"" << sbe_binaryentrypoint::alloc_no_orders_type::to_string(msg.fields.alloc_no_orders_type.get().value()) << '"'
       << ",alloc_rej_code=" << (msg.fields.alloc_rej_code.get().has_value() ? std::to_string(msg.fields.alloc_rej_code.get().value()) : std::string_view("null"))
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",alloc_status=\"" << sbe_binaryentrypoint::alloc_status::to_string(msg.fields.alloc_status.get().value()) << '"'
       << ",trade_date_optional=" << (msg.fields.trade_date_optional.get().has_value() ? std::to_string(msg.fields.trade_date_optional.get().value()) : std::string_view("null"))
       << ",transact_time=" << msg.fields.transact_time.get().value()
       << ",side=\"" << sbe_binaryentrypoint::side::to_string(msg.fields.side.get().value()) << '"'
       << ",sender_location=\"" << msg.fields.sender_location.get_trimmed().value() << '"'
       << ",entering_trader=\"" << msg.fields.entering_trader.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_mass_action_request_message& msg) {
    os << "inbound_business_header.session_id=" << msg.fields.inbound_business_header.session_id.get().value()
       << ",inbound_business_header.msg_seq_num=" << msg.fields.inbound_business_header.msg_seq_num.get().value()
       << ",inbound_business_header.sending_time=" << (msg.fields.inbound_business_header.sending_time.get().has_value() ? std::to_string(msg.fields.inbound_business_header.sending_time.get().value()) : std::string_view("null"))
       << ",inbound_business_header.market_segment_id=" << static_cast<unsigned>(msg.fields.inbound_business_header.market_segment_id.get().value())
       << ",inbound_business_header.padding=\"" << msg.fields.inbound_business_header.padding.get().value() << '"'
       << ",mass_action_type=\"" << sbe_binaryentrypoint::mass_action_type::to_string(msg.fields.mass_action_type.get().value()) << '"'
       << ",mass_action_scope=\"" << sbe_binaryentrypoint::mass_action_scope::to_string(msg.fields.mass_action_scope.get().value()) << '"'
       << ",clordid=" << msg.fields.clordid.get().value()
       << ",mass_cancel_restatement_reason=\"" << sbe_binaryentrypoint::mass_cancel_restatement_reason::to_string(msg.fields.mass_cancel_restatement_reason.get().value()) << '"'
       << ",ordtagid=" << (msg.fields.ordtagid.get().has_value() ? std::to_string(msg.fields.ordtagid.get().value()) : std::string_view("null"))
       << ",side_optional=\"" << sbe_binaryentrypoint::side_optional::to_string(msg.fields.side_optional.get().value()) << '"'
       << ",asset=\"" << (msg.fields.asset.get_trimmed().has_value() ? msg.fields.asset.get_trimmed().value() : std::string_view("null")) << '"'
       << ",security_id_optional=" << (msg.fields.security_id_optional.get().has_value() ? std::to_string(msg.fields.security_id_optional.get().value()) : std::string_view("null"))
       << ",investor_id.prefix=" << msg.fields.investor_id.prefix.get().value()
       << ",investor_id.document=" << msg.fields.investor_id.document.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_mass_action_report_message& msg) {
    os << "outbound_business_header.session_id=" << msg.fields.outbound_business_header.session_id.get().value()
       << ",outbound_business_header.msg_seq_num=" << msg.fields.outbound_business_header.msg_seq_num.get().value()
       << ",outbound_business_header.sending_time=" << (msg.fields.outbound_business_header.sending_time.get().has_value() ? std::to_string(msg.fields.outbound_business_header.sending_time.get().value()) : std::string_view("null"))
       << ",outbound_business_header.event_indicator=" << static_cast<unsigned>(msg.fields.outbound_business_header.event_indicator.get().value())
       << ",outbound_business_header.market_segment_id_optional=" << static_cast<unsigned>(msg.fields.outbound_business_header.market_segment_id_optional.get().value())
       << ",mass_action_type=\"" << sbe_binaryentrypoint::mass_action_type::to_string(msg.fields.mass_action_type.get().value()) << '"'
       << ",mass_action_scope=\"" << sbe_binaryentrypoint::mass_action_scope::to_string(msg.fields.mass_action_scope.get().value()) << '"'
       << ",clordid=" << msg.fields.clordid.get().value()
       << ",mass_action_report_id=" << msg.fields.mass_action_report_id.get().value()
       << ",transact_time=" << msg.fields.transact_time.get().value()
       << ",mass_action_response=\"" << sbe_binaryentrypoint::mass_action_response::to_string(msg.fields.mass_action_response.get().value()) << '"'
       << ",mass_action_reject_reason=\"" << sbe_binaryentrypoint::mass_action_reject_reason::to_string(msg.fields.mass_action_reject_reason.get().value()) << '"'
       << ",mass_cancel_restatement_reason=\"" << sbe_binaryentrypoint::mass_cancel_restatement_reason::to_string(msg.fields.mass_cancel_restatement_reason.get().value()) << '"'
       << ",ordtagid=" << (msg.fields.ordtagid.get().has_value() ? std::to_string(msg.fields.ordtagid.get().value()) : std::string_view("null"))
       << ",side_optional=\"" << sbe_binaryentrypoint::side_optional::to_string(msg.fields.side_optional.get().value()) << '"'
       << ",asset=\"" << (msg.fields.asset.get_trimmed().has_value() ? msg.fields.asset.get_trimmed().value() : std::string_view("null")) << '"'
       << ",security_id_optional=" << (msg.fields.security_id_optional.get().has_value() ? std::to_string(msg.fields.security_id_optional.get().value()) : std::string_view("null"))
       << ",investor_id.prefix=" << msg.fields.investor_id.prefix.get().value()
       << ",investor_id.document=" << msg.fields.investor_id.document.get().value()
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

}
