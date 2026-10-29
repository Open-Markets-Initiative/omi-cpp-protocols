// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.3 canonical values of 'packet', through the Modern iterator: every value
// Modern reads from each side of each connection the tree is sent from, at its address, held to what the model reads.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "TcpReassembler.hpp"
#include "tests/canonical/Canonical.hpp"
#include "cpp/binary/modern/b3/b3derivatives/binaryentrypoint/sbe/v8.3/definitions.hpp"

namespace protocol = ::b3::b3derivatives::binaryentrypoint::sbe::v8_3;

namespace {

// The values the Modern iterator reads from one stream of 'packet', by indexed address
canonical::Listing read(const std::byte* data, std::size_t length) {
    canonical::Listing values;
    protocol::SimpleOpenFrameIterator iterator;
    iterator.initialize(data, length);

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "packet.simpleopenframe[" + std::to_string(index++) + "]";

        // the iterator steps past a record the bytes end inside; its values are not read
        if (iterator.current > iterator.end) {
            values[entry] = "(ends inside the record)";
            break;
        }

        values[entry + ".simpleopenframingheader.messagelength"] = canonical::number(iterator.simple_open_framing_header->message_length.get());
        values[entry + ".simpleopenframingheader.encodingtype"] = canonical::number(iterator.simple_open_framing_header->encoding_type.get());
        values[entry + ".messageheader.blocklength"] = canonical::number(iterator.message_header->block_length.get());
        values[entry + ".messageheader.templateid"] = canonical::number(iterator.message_header->template_id.get());
        values[entry + ".messageheader.schemaid"] = canonical::number(iterator.message_header->schema_id.get());
        values[entry + ".messageheader.version"] = canonical::number(iterator.message_header->version.get());

        if (iterator.template_id == 1) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.negotiatemessage";
            [[maybe_unused]] const auto* message = protocol::NegotiateMessage::parse(iterator.message);
            values[entry + ".payload.negotiatemessage.sessionid"] = canonical::number(message->session_id.get());
            values[entry + ".payload.negotiatemessage.sessionverid"] = canonical::number(message->session_ver_id.get());
            values[entry + ".payload.negotiatemessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.negotiatemessage.enteringfirm"] = canonical::number(message->entering_firm.get());
            values[entry + ".payload.negotiatemessage.onbehalffirm"] = (static_cast<std::uint32_t>(message->onbehalf_firm.get()) != 0x0U ? canonical::number(message->onbehalf_firm.get()) : canonical::absent());
        } else if (iterator.template_id == 2) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.negotiateresponsemessage";
            [[maybe_unused]] const auto* message = protocol::NegotiateResponseMessage::parse(iterator.message);
            values[entry + ".payload.negotiateresponsemessage.sessionid"] = canonical::number(message->session_id.get());
            values[entry + ".payload.negotiateresponsemessage.sessionverid"] = canonical::number(message->session_ver_id.get());
            values[entry + ".payload.negotiateresponsemessage.requesttimestamp"] = canonical::number(message->request_timestamp.get());
            values[entry + ".payload.negotiateresponsemessage.enteringfirm"] = canonical::number(message->entering_firm.get());
            values[entry + ".payload.negotiateresponsemessage.semanticversion.majornumber"] = canonical::number(message->semantic_version.major_number.get());
            values[entry + ".payload.negotiateresponsemessage.semanticversion.minornumber"] = canonical::number(message->semantic_version.minor_number.get());
            values[entry + ".payload.negotiateresponsemessage.semanticversion.patchnumber"] = canonical::number(message->semantic_version.patch_number.get());
            values[entry + ".payload.negotiateresponsemessage.semanticversion.buildnumber"] = canonical::number(message->semantic_version.build_number.get());
        } else if (iterator.template_id == 3) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.negotiaterejectmessage";
            [[maybe_unused]] const auto* message = protocol::NegotiateRejectMessage::parse(iterator.message);
            values[entry + ".payload.negotiaterejectmessage.sessionid"] = canonical::number(message->session_id.get());
            values[entry + ".payload.negotiaterejectmessage.sessionverid"] = canonical::number(message->session_ver_id.get());
            values[entry + ".payload.negotiaterejectmessage.requesttimestamp"] = canonical::number(message->request_timestamp.get());
            values[entry + ".payload.negotiaterejectmessage.enteringfirmoptional"] = (static_cast<std::uint32_t>(message->entering_firm_optional.get()) != 0x0U ? canonical::number(message->entering_firm_optional.get()) : canonical::absent());
            values[entry + ".payload.negotiaterejectmessage.negotiationrejectcode"] = canonical::number(message->negotiation_reject_code.get());
            values[entry + ".payload.negotiaterejectmessage.currentsessionverid"] = (static_cast<std::uint64_t>(message->current_session_ver_id.get()) != 0x0ULL ? canonical::number(message->current_session_ver_id.get()) : canonical::absent());
        } else if (iterator.template_id == 4) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.establishmessage";
            [[maybe_unused]] const auto* message = protocol::EstablishMessage::parse(iterator.message);
            values[entry + ".payload.establishmessage.sessionid"] = canonical::number(message->session_id.get());
            values[entry + ".payload.establishmessage.sessionverid"] = canonical::number(message->session_ver_id.get());
            values[entry + ".payload.establishmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.establishmessage.keepaliveinterval"] = canonical::number(message->keep_alive_interval.get());
            values[entry + ".payload.establishmessage.nextseqno"] = canonical::number(message->next_seq_no.get());
            values[entry + ".payload.establishmessage.cancelondisconnecttype"] = canonical::number(message->cancel_on_disconnect_type.get());
            values[entry + ".payload.establishmessage.codtimeoutwindow"] = canonical::number(message->cod_timeout_window.get());
        } else if (iterator.template_id == 5) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.establishackmessage";
            [[maybe_unused]] const auto* message = protocol::EstablishAckMessage::parse(iterator.message);
            values[entry + ".payload.establishackmessage.sessionid"] = canonical::number(message->session_id.get());
            values[entry + ".payload.establishackmessage.sessionverid"] = canonical::number(message->session_ver_id.get());
            values[entry + ".payload.establishackmessage.requesttimestamp"] = canonical::number(message->request_timestamp.get());
            values[entry + ".payload.establishackmessage.keepaliveinterval"] = canonical::number(message->keep_alive_interval.get());
            values[entry + ".payload.establishackmessage.nextseqno"] = canonical::number(message->next_seq_no.get());
            values[entry + ".payload.establishackmessage.lastincomingseqno"] = canonical::number(message->last_incoming_seq_no.get());
        } else if (iterator.template_id == 6) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.establishrejectmessage";
            [[maybe_unused]] const auto* message = protocol::EstablishRejectMessage::parse(iterator.message);
            values[entry + ".payload.establishrejectmessage.sessionid"] = canonical::number(message->session_id.get());
            values[entry + ".payload.establishrejectmessage.sessionverid"] = canonical::number(message->session_ver_id.get());
            values[entry + ".payload.establishrejectmessage.requesttimestamp"] = canonical::number(message->request_timestamp.get());
            values[entry + ".payload.establishrejectmessage.establishmentrejectcode"] = canonical::number(message->establishment_reject_code.get());
            values[entry + ".payload.establishrejectmessage.lastincomingseqnooptional"] = (static_cast<std::uint32_t>(message->last_incoming_seq_no_optional.get()) != 0x0U ? canonical::number(message->last_incoming_seq_no_optional.get()) : canonical::absent());
        } else if (iterator.template_id == 7) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.terminatemessage";
            [[maybe_unused]] const auto* message = protocol::TerminateMessage::parse(iterator.message);
            values[entry + ".payload.terminatemessage.sessionid"] = canonical::number(message->session_id.get());
            values[entry + ".payload.terminatemessage.sessionverid"] = canonical::number(message->session_ver_id.get());
            values[entry + ".payload.terminatemessage.terminationcode"] = canonical::number(message->termination_code.get());
        } else if (iterator.template_id == 8) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.notappliedmessage";
            [[maybe_unused]] const auto* message = protocol::NotAppliedMessage::parse(iterator.message);
            values[entry + ".payload.notappliedmessage.fromseqno"] = canonical::number(message->from_seq_no.get());
            values[entry + ".payload.notappliedmessage.count"] = canonical::number(message->count.get());
        } else if (iterator.template_id == 9) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.sequencemessage";
            [[maybe_unused]] const auto* message = protocol::SequenceMessage::parse(iterator.message);
            values[entry + ".payload.sequencemessage.nextseqno"] = canonical::number(message->next_seq_no.get());
        } else if (iterator.template_id == 12) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.retransmitrequestmessage";
            [[maybe_unused]] const auto* message = protocol::RetransmitRequestMessage::parse(iterator.message);
            values[entry + ".payload.retransmitrequestmessage.sessionid"] = canonical::number(message->session_id.get());
            values[entry + ".payload.retransmitrequestmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.retransmitrequestmessage.fromseqno"] = canonical::number(message->from_seq_no.get());
            values[entry + ".payload.retransmitrequestmessage.count"] = canonical::number(message->count.get());
        } else if (iterator.template_id == 13) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.retransmissionmessage";
            [[maybe_unused]] const auto* message = protocol::RetransmissionMessage::parse(iterator.message);
            values[entry + ".payload.retransmissionmessage.sessionid"] = canonical::number(message->session_id.get());
            values[entry + ".payload.retransmissionmessage.requesttimestamp"] = canonical::number(message->request_timestamp.get());
            values[entry + ".payload.retransmissionmessage.nextseqno"] = canonical::number(message->next_seq_no.get());
            values[entry + ".payload.retransmissionmessage.count"] = canonical::number(message->count.get());
        } else if (iterator.template_id == 14) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.retransmitrejectmessage";
            [[maybe_unused]] const auto* message = protocol::RetransmitRejectMessage::parse(iterator.message);
            values[entry + ".payload.retransmitrejectmessage.sessionid"] = canonical::number(message->session_id.get());
            values[entry + ".payload.retransmitrejectmessage.requesttimestamp"] = canonical::number(message->request_timestamp.get());
            values[entry + ".payload.retransmitrejectmessage.retransmitrejectcode"] = canonical::number(message->retransmit_reject_code.get());
        } else if (iterator.template_id == 100) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.simplenewordermessage";
            [[maybe_unused]] const auto* message = protocol::SimpleNewOrderMessage::parse(iterator.message);
            values[entry + ".payload.simplenewordermessage.inboundbusinessheader.sessionid"] = canonical::number(message->inbound_business_header.session_id.get());
            values[entry + ".payload.simplenewordermessage.inboundbusinessheader.msgseqnum"] = canonical::number(message->inbound_business_header.msg_seq_num.get());
            values[entry + ".payload.simplenewordermessage.inboundbusinessheader.sendingtime"] = (static_cast<std::uint64_t>(message->inbound_business_header.sending_time.get()) != 0x0ULL ? canonical::number(message->inbound_business_header.sending_time.get()) : canonical::absent());
            values[entry + ".payload.simplenewordermessage.inboundbusinessheader.marketsegmentid"] = canonical::number(message->inbound_business_header.market_segment_id.get());
            values[entry + ".payload.simplenewordermessage.inboundbusinessheader.padding"] = canonical::text(canonical::character(message->inbound_business_header.padding.get()));
            values[entry + ".payload.simplenewordermessage.ordtagid"] = (static_cast<std::uint8_t>(message->ordtagid.get()) != 0x0U ? canonical::number(message->ordtagid.get()) : canonical::absent());
            values[entry + ".payload.simplenewordermessage.mmprotectionreset"] = canonical::number(message->mm_protection_reset.get());
            values[entry + ".payload.simplenewordermessage.clordid"] = canonical::number(message->clordid.get());
            values[entry + ".payload.simplenewordermessage.account"] = (static_cast<std::uint32_t>(message->account.get()) != 0x0U ? canonical::number(message->account.get()) : canonical::absent());
            values[entry + ".payload.simplenewordermessage.senderlocation"] = canonical::text(std::string(message->sender_location.get()), '\0', false);
            values[entry + ".payload.simplenewordermessage.enteringtrader"] = canonical::text(std::string(message->entering_trader.get()), '\0', false);
            values[entry + ".payload.simplenewordermessage.selftradepreventioninstruction"] = canonical::number(message->self_trade_prevention_instruction.get());
            values[entry + ".payload.simplenewordermessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.simplenewordermessage.side"] = canonical::text(canonical::character(message->side.get()));
            values[entry + ".payload.simplenewordermessage.simpleordtype"] = canonical::text(canonical::character(message->simple_ordtype.get()));
            values[entry + ".payload.simplenewordermessage.timeinforcesimple"] = canonical::text(canonical::character(message->time_in_force_simple.get()));
            values[entry + ".payload.simplenewordermessage.routinginstruction"] = (static_cast<std::uint8_t>(message->routing_instruction.get()) != 0x0U ? canonical::number(message->routing_instruction.get()) : canonical::absent());
            values[entry + ".payload.simplenewordermessage.orderqty"] = canonical::number(message->order_qty.get());
            values[entry + ".payload.simplenewordermessage.priceoptional"] = (static_cast<std::uint64_t>(message->price_optional.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->price_optional.integer(), -4) : canonical::absent());
            values[entry + ".payload.simplenewordermessage.investorid.prefix"] = canonical::number(message->investor_id.prefix.get());
            values[entry + ".payload.simplenewordermessage.investorid.document"] = canonical::number(message->investor_id.document.get());
        } else if (iterator.template_id == 101) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.simplemodifyordermessage";
            [[maybe_unused]] const auto* message = protocol::SimpleModifyOrderMessage::parse(iterator.message);
            values[entry + ".payload.simplemodifyordermessage.inboundbusinessheader.sessionid"] = canonical::number(message->inbound_business_header.session_id.get());
            values[entry + ".payload.simplemodifyordermessage.inboundbusinessheader.msgseqnum"] = canonical::number(message->inbound_business_header.msg_seq_num.get());
            values[entry + ".payload.simplemodifyordermessage.inboundbusinessheader.sendingtime"] = (static_cast<std::uint64_t>(message->inbound_business_header.sending_time.get()) != 0x0ULL ? canonical::number(message->inbound_business_header.sending_time.get()) : canonical::absent());
            values[entry + ".payload.simplemodifyordermessage.inboundbusinessheader.marketsegmentid"] = canonical::number(message->inbound_business_header.market_segment_id.get());
            values[entry + ".payload.simplemodifyordermessage.inboundbusinessheader.padding"] = canonical::text(canonical::character(message->inbound_business_header.padding.get()));
            values[entry + ".payload.simplemodifyordermessage.ordtagid"] = (static_cast<std::uint8_t>(message->ordtagid.get()) != 0x0U ? canonical::number(message->ordtagid.get()) : canonical::absent());
            values[entry + ".payload.simplemodifyordermessage.mmprotectionreset"] = canonical::number(message->mm_protection_reset.get());
            values[entry + ".payload.simplemodifyordermessage.clordid"] = canonical::number(message->clordid.get());
            values[entry + ".payload.simplemodifyordermessage.account"] = (static_cast<std::uint32_t>(message->account.get()) != 0x0U ? canonical::number(message->account.get()) : canonical::absent());
            values[entry + ".payload.simplemodifyordermessage.senderlocation"] = canonical::text(std::string(message->sender_location.get()), '\0', false);
            values[entry + ".payload.simplemodifyordermessage.enteringtrader"] = canonical::text(std::string(message->entering_trader.get()), '\0', false);
            values[entry + ".payload.simplemodifyordermessage.selftradepreventioninstruction"] = canonical::number(message->self_trade_prevention_instruction.get());
            values[entry + ".payload.simplemodifyordermessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.simplemodifyordermessage.side"] = canonical::text(canonical::character(message->side.get()));
            values[entry + ".payload.simplemodifyordermessage.simpleordtype"] = canonical::text(canonical::character(message->simple_ordtype.get()));
            values[entry + ".payload.simplemodifyordermessage.timeinforcesimple"] = canonical::text(canonical::character(message->time_in_force_simple.get()));
            values[entry + ".payload.simplemodifyordermessage.routinginstruction"] = (static_cast<std::uint8_t>(message->routing_instruction.get()) != 0x0U ? canonical::number(message->routing_instruction.get()) : canonical::absent());
            values[entry + ".payload.simplemodifyordermessage.orderqty"] = canonical::number(message->order_qty.get());
            values[entry + ".payload.simplemodifyordermessage.priceoptional"] = (static_cast<std::uint64_t>(message->price_optional.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->price_optional.integer(), -4) : canonical::absent());
            values[entry + ".payload.simplemodifyordermessage.orderidoptional"] = (static_cast<std::uint64_t>(message->order_id_optional.get()) != 0x0ULL ? canonical::number(message->order_id_optional.get()) : canonical::absent());
            values[entry + ".payload.simplemodifyordermessage.origclordid"] = (static_cast<std::uint64_t>(message->origclordid.get()) != 0x0ULL ? canonical::number(message->origclordid.get()) : canonical::absent());
            values[entry + ".payload.simplemodifyordermessage.investorid.prefix"] = canonical::number(message->investor_id.prefix.get());
            values[entry + ".payload.simplemodifyordermessage.investorid.document"] = canonical::number(message->investor_id.document.get());
        } else if (iterator.template_id == 102) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.newordersinglemessage";
            [[maybe_unused]] const auto* message = protocol::NewOrderSingleMessage::parse(iterator.message);
            values[entry + ".payload.newordersinglemessage.inboundbusinessheader.sessionid"] = canonical::number(message->inbound_business_header.session_id.get());
            values[entry + ".payload.newordersinglemessage.inboundbusinessheader.msgseqnum"] = canonical::number(message->inbound_business_header.msg_seq_num.get());
            values[entry + ".payload.newordersinglemessage.inboundbusinessheader.sendingtime"] = (static_cast<std::uint64_t>(message->inbound_business_header.sending_time.get()) != 0x0ULL ? canonical::number(message->inbound_business_header.sending_time.get()) : canonical::absent());
            values[entry + ".payload.newordersinglemessage.inboundbusinessheader.marketsegmentid"] = canonical::number(message->inbound_business_header.market_segment_id.get());
            values[entry + ".payload.newordersinglemessage.inboundbusinessheader.padding"] = canonical::text(canonical::character(message->inbound_business_header.padding.get()));
            values[entry + ".payload.newordersinglemessage.ordtagid"] = (static_cast<std::uint8_t>(message->ordtagid.get()) != 0x0U ? canonical::number(message->ordtagid.get()) : canonical::absent());
            values[entry + ".payload.newordersinglemessage.mmprotectionreset"] = canonical::number(message->mm_protection_reset.get());
            values[entry + ".payload.newordersinglemessage.clordid"] = canonical::number(message->clordid.get());
            values[entry + ".payload.newordersinglemessage.account"] = (static_cast<std::uint32_t>(message->account.get()) != 0x0U ? canonical::number(message->account.get()) : canonical::absent());
            values[entry + ".payload.newordersinglemessage.senderlocation"] = canonical::text(std::string(message->sender_location.get()), '\0', false);
            values[entry + ".payload.newordersinglemessage.enteringtrader"] = canonical::text(std::string(message->entering_trader.get()), '\0', false);
            values[entry + ".payload.newordersinglemessage.selftradepreventioninstruction"] = canonical::number(message->self_trade_prevention_instruction.get());
            values[entry + ".payload.newordersinglemessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.newordersinglemessage.side"] = canonical::text(canonical::character(message->side.get()));
            values[entry + ".payload.newordersinglemessage.ordtype"] = canonical::text(canonical::character(message->ordtype.get()));
            values[entry + ".payload.newordersinglemessage.timeinforce"] = canonical::text(canonical::character(message->time_in_force.get()));
            values[entry + ".payload.newordersinglemessage.routinginstruction"] = (static_cast<std::uint8_t>(message->routing_instruction.get()) != 0x0U ? canonical::number(message->routing_instruction.get()) : canonical::absent());
            values[entry + ".payload.newordersinglemessage.orderqty"] = canonical::number(message->order_qty.get());
            values[entry + ".payload.newordersinglemessage.priceoptional"] = (static_cast<std::uint64_t>(message->price_optional.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->price_optional.integer(), -4) : canonical::absent());
            values[entry + ".payload.newordersinglemessage.stoppx"] = (static_cast<std::uint64_t>(message->stop_px.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->stop_px.integer(), -4) : canonical::absent());
            values[entry + ".payload.newordersinglemessage.minqty"] = (static_cast<std::uint64_t>(message->min_qty.get()) != 0x0ULL ? canonical::number(message->min_qty.get()) : canonical::absent());
            values[entry + ".payload.newordersinglemessage.maxfloor"] = (static_cast<std::uint64_t>(message->max_floor.get()) != 0x0ULL ? canonical::number(message->max_floor.get()) : canonical::absent());
            values[entry + ".payload.newordersinglemessage.expiredate"] = (static_cast<std::uint16_t>(message->expire_date.get()) != 0x0U ? canonical::number(message->expire_date.get()) : canonical::absent());
            values[entry + ".payload.newordersinglemessage.custodianinfo.custodian"] = canonical::number(message->custodian_info.custodian.get());
            values[entry + ".payload.newordersinglemessage.custodianinfo.custodyaccount"] = canonical::number(message->custodian_info.custody_account.get());
            values[entry + ".payload.newordersinglemessage.custodianinfo.custodyallocationtype"] = canonical::number(message->custodian_info.custody_allocation_type.get());
            values[entry + ".payload.newordersinglemessage.investorid.prefix"] = canonical::number(message->investor_id.prefix.get());
            values[entry + ".payload.newordersinglemessage.investorid.document"] = canonical::number(message->investor_id.document.get());
            values[entry + ".payload.newordersinglemessage.strategyid"] = (static_cast<std::uint32_t>(message->strategy_id.get()) != 0x0U ? canonical::number(message->strategy_id.get()) : canonical::absent());
            values[entry + ".payload.newordersinglemessage.tradingsubaccount"] = (static_cast<std::uint32_t>(message->trading_sub_account.get()) != 0x0U ? canonical::number(message->trading_sub_account.get()) : canonical::absent());
        } else if (iterator.template_id == 104) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.ordercancelreplacerequestmessage";
            [[maybe_unused]] const auto* message = protocol::OrderCancelReplaceRequestMessage::parse(iterator.message);
            values[entry + ".payload.ordercancelreplacerequestmessage.inboundbusinessheader.sessionid"] = canonical::number(message->inbound_business_header.session_id.get());
            values[entry + ".payload.ordercancelreplacerequestmessage.inboundbusinessheader.msgseqnum"] = canonical::number(message->inbound_business_header.msg_seq_num.get());
            values[entry + ".payload.ordercancelreplacerequestmessage.inboundbusinessheader.sendingtime"] = (static_cast<std::uint64_t>(message->inbound_business_header.sending_time.get()) != 0x0ULL ? canonical::number(message->inbound_business_header.sending_time.get()) : canonical::absent());
            values[entry + ".payload.ordercancelreplacerequestmessage.inboundbusinessheader.marketsegmentid"] = canonical::number(message->inbound_business_header.market_segment_id.get());
            values[entry + ".payload.ordercancelreplacerequestmessage.inboundbusinessheader.padding"] = canonical::text(canonical::character(message->inbound_business_header.padding.get()));
            values[entry + ".payload.ordercancelreplacerequestmessage.ordtagid"] = (static_cast<std::uint8_t>(message->ordtagid.get()) != 0x0U ? canonical::number(message->ordtagid.get()) : canonical::absent());
            values[entry + ".payload.ordercancelreplacerequestmessage.mmprotectionreset"] = canonical::number(message->mm_protection_reset.get());
            values[entry + ".payload.ordercancelreplacerequestmessage.clordid"] = canonical::number(message->clordid.get());
            values[entry + ".payload.ordercancelreplacerequestmessage.account"] = (static_cast<std::uint32_t>(message->account.get()) != 0x0U ? canonical::number(message->account.get()) : canonical::absent());
            values[entry + ".payload.ordercancelreplacerequestmessage.senderlocation"] = canonical::text(std::string(message->sender_location.get()), '\0', false);
            values[entry + ".payload.ordercancelreplacerequestmessage.enteringtrader"] = canonical::text(std::string(message->entering_trader.get()), '\0', false);
            values[entry + ".payload.ordercancelreplacerequestmessage.selftradepreventioninstruction"] = canonical::number(message->self_trade_prevention_instruction.get());
            values[entry + ".payload.ordercancelreplacerequestmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.ordercancelreplacerequestmessage.side"] = canonical::text(canonical::character(message->side.get()));
            values[entry + ".payload.ordercancelreplacerequestmessage.ordtype"] = canonical::text(canonical::character(message->ordtype.get()));
            values[entry + ".payload.ordercancelreplacerequestmessage.routinginstruction"] = (static_cast<std::uint8_t>(message->routing_instruction.get()) != 0x0U ? canonical::number(message->routing_instruction.get()) : canonical::absent());
            values[entry + ".payload.ordercancelreplacerequestmessage.orderqty"] = canonical::number(message->order_qty.get());
            values[entry + ".payload.ordercancelreplacerequestmessage.priceoptional"] = (static_cast<std::uint64_t>(message->price_optional.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->price_optional.integer(), -4) : canonical::absent());
            values[entry + ".payload.ordercancelreplacerequestmessage.orderidoptional"] = (static_cast<std::uint64_t>(message->order_id_optional.get()) != 0x0ULL ? canonical::number(message->order_id_optional.get()) : canonical::absent());
            values[entry + ".payload.ordercancelreplacerequestmessage.origclordid"] = (static_cast<std::uint64_t>(message->origclordid.get()) != 0x0ULL ? canonical::number(message->origclordid.get()) : canonical::absent());
            values[entry + ".payload.ordercancelreplacerequestmessage.stoppx"] = (static_cast<std::uint64_t>(message->stop_px.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->stop_px.integer(), -4) : canonical::absent());
            values[entry + ".payload.ordercancelreplacerequestmessage.minqty"] = (static_cast<std::uint64_t>(message->min_qty.get()) != 0x0ULL ? canonical::number(message->min_qty.get()) : canonical::absent());
            values[entry + ".payload.ordercancelreplacerequestmessage.maxfloor"] = (static_cast<std::uint64_t>(message->max_floor.get()) != 0x0ULL ? canonical::number(message->max_floor.get()) : canonical::absent());
            values[entry + ".payload.ordercancelreplacerequestmessage.accounttype"] = (static_cast<std::uint8_t>(message->account_type.get()) != 0x0U ? canonical::number(message->account_type.get()) : canonical::absent());
            values[entry + ".payload.ordercancelreplacerequestmessage.expiredate"] = (static_cast<std::uint16_t>(message->expire_date.get()) != 0x0U ? canonical::number(message->expire_date.get()) : canonical::absent());
            values[entry + ".payload.ordercancelreplacerequestmessage.custodianinfo.custodian"] = canonical::number(message->custodian_info.custodian.get());
            values[entry + ".payload.ordercancelreplacerequestmessage.custodianinfo.custodyaccount"] = canonical::number(message->custodian_info.custody_account.get());
            values[entry + ".payload.ordercancelreplacerequestmessage.custodianinfo.custodyallocationtype"] = canonical::number(message->custodian_info.custody_allocation_type.get());
            values[entry + ".payload.ordercancelreplacerequestmessage.investorid.prefix"] = canonical::number(message->investor_id.prefix.get());
            values[entry + ".payload.ordercancelreplacerequestmessage.investorid.document"] = canonical::number(message->investor_id.document.get());
            values[entry + ".payload.ordercancelreplacerequestmessage.strategyid"] = (static_cast<std::uint32_t>(message->strategy_id.get()) != 0x0U ? canonical::number(message->strategy_id.get()) : canonical::absent());
            values[entry + ".payload.ordercancelreplacerequestmessage.tradingsubaccount"] = (static_cast<std::uint32_t>(message->trading_sub_account.get()) != 0x0U ? canonical::number(message->trading_sub_account.get()) : canonical::absent());
        } else if (iterator.template_id == 105) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.ordercancelrequestmessage";
            [[maybe_unused]] const auto* message = protocol::OrderCancelRequestMessage::parse(iterator.message);
            values[entry + ".payload.ordercancelrequestmessage.inboundbusinessheader.sessionid"] = canonical::number(message->inbound_business_header.session_id.get());
            values[entry + ".payload.ordercancelrequestmessage.inboundbusinessheader.msgseqnum"] = canonical::number(message->inbound_business_header.msg_seq_num.get());
            values[entry + ".payload.ordercancelrequestmessage.inboundbusinessheader.sendingtime"] = (static_cast<std::uint64_t>(message->inbound_business_header.sending_time.get()) != 0x0ULL ? canonical::number(message->inbound_business_header.sending_time.get()) : canonical::absent());
            values[entry + ".payload.ordercancelrequestmessage.inboundbusinessheader.marketsegmentid"] = canonical::number(message->inbound_business_header.market_segment_id.get());
            values[entry + ".payload.ordercancelrequestmessage.inboundbusinessheader.padding"] = canonical::text(canonical::character(message->inbound_business_header.padding.get()));
            values[entry + ".payload.ordercancelrequestmessage.clordid"] = canonical::number(message->clordid.get());
            values[entry + ".payload.ordercancelrequestmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.ordercancelrequestmessage.orderidoptional"] = (static_cast<std::uint64_t>(message->order_id_optional.get()) != 0x0ULL ? canonical::number(message->order_id_optional.get()) : canonical::absent());
            values[entry + ".payload.ordercancelrequestmessage.origclordid"] = (static_cast<std::uint64_t>(message->origclordid.get()) != 0x0ULL ? canonical::number(message->origclordid.get()) : canonical::absent());
            values[entry + ".payload.ordercancelrequestmessage.side"] = canonical::text(canonical::character(message->side.get()));
            values[entry + ".payload.ordercancelrequestmessage.singlecancelrestatementreason"] = (static_cast<std::uint8_t>(message->single_cancel_restatement_reason.get()) != 0x0U ? canonical::number(message->single_cancel_restatement_reason.get()) : canonical::absent());
            values[entry + ".payload.ordercancelrequestmessage.senderlocation"] = canonical::text(std::string(message->sender_location.get()), '\0', false);
            values[entry + ".payload.ordercancelrequestmessage.enteringtrader"] = canonical::text(std::string(message->entering_trader.get()), '\0', false);
        } else if (iterator.template_id == 106) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.newordercrossmessage";
            [[maybe_unused]] const auto* message = protocol::NewOrderCrossMessage::parse(iterator.message);
            values[entry + ".payload.newordercrossmessage.inboundbusinessheader.sessionid"] = canonical::number(message->inbound_business_header.session_id.get());
            values[entry + ".payload.newordercrossmessage.inboundbusinessheader.msgseqnum"] = canonical::number(message->inbound_business_header.msg_seq_num.get());
            values[entry + ".payload.newordercrossmessage.inboundbusinessheader.sendingtime"] = (static_cast<std::uint64_t>(message->inbound_business_header.sending_time.get()) != 0x0ULL ? canonical::number(message->inbound_business_header.sending_time.get()) : canonical::absent());
            values[entry + ".payload.newordercrossmessage.inboundbusinessheader.marketsegmentid"] = canonical::number(message->inbound_business_header.market_segment_id.get());
            values[entry + ".payload.newordercrossmessage.inboundbusinessheader.padding"] = canonical::text(canonical::character(message->inbound_business_header.padding.get()));
            values[entry + ".payload.newordercrossmessage.crossid"] = canonical::number(message->crossid.get());
            values[entry + ".payload.newordercrossmessage.senderlocation"] = canonical::text(std::string(message->sender_location.get()), '\0', false);
            values[entry + ".payload.newordercrossmessage.enteringtrader"] = canonical::text(std::string(message->entering_trader.get()), '\0', false);
            values[entry + ".payload.newordercrossmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.newordercrossmessage.orderqty"] = canonical::number(message->order_qty.get());
            values[entry + ".payload.newordercrossmessage.price"] = canonical::scaled(message->price.integer(), -4);
            values[entry + ".payload.newordercrossmessage.crossedindicator"] = (static_cast<std::uint16_t>(message->crossed_indicator.get()) != 0x0U ? canonical::number(message->crossed_indicator.get()) : canonical::absent());
            values[entry + ".payload.newordercrossmessage.crosstype"] = (static_cast<std::uint8_t>(message->cross_type.get()) != 0x0U ? canonical::number(message->cross_type.get()) : canonical::absent());
            values[entry + ".payload.newordercrossmessage.crossprioritization"] = (static_cast<std::uint8_t>(message->cross_prioritization.get()) != 0x0FFU ? canonical::number(message->cross_prioritization.get()) : canonical::absent());
            values[entry + ".payload.newordercrossmessage.maxsweepqty"] = (static_cast<std::uint64_t>(message->max_sweep_qty.get()) != 0x0ULL ? canonical::number(message->max_sweep_qty.get()) : canonical::absent());
        } else if (iterator.template_id == 200) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.executionreportnewmessage";
            [[maybe_unused]] const auto* message = protocol::ExecutionReportNewMessage::parse(iterator.message);
            values[entry + ".payload.executionreportnewmessage.outboundbusinessheader.sessionid"] = canonical::number(message->outbound_business_header.session_id.get());
            values[entry + ".payload.executionreportnewmessage.outboundbusinessheader.msgseqnum"] = canonical::number(message->outbound_business_header.msg_seq_num.get());
            values[entry + ".payload.executionreportnewmessage.outboundbusinessheader.sendingtime"] = (static_cast<std::uint64_t>(message->outbound_business_header.sending_time.get()) != 0x0ULL ? canonical::number(message->outbound_business_header.sending_time.get()) : canonical::absent());
            values[entry + ".payload.executionreportnewmessage.outboundbusinessheader.eventindicator"] = canonical::number(message->outbound_business_header.event_indicator.get());
            values[entry + ".payload.executionreportnewmessage.outboundbusinessheader.marketsegmentidoptional"] = canonical::number(message->outbound_business_header.market_segment_id_optional.get());
            values[entry + ".payload.executionreportnewmessage.side"] = canonical::text(canonical::character(message->side.get()));
            values[entry + ".payload.executionreportnewmessage.ordstatus"] = canonical::text(canonical::character(message->ord_status.get()));
            values[entry + ".payload.executionreportnewmessage.clordid"] = canonical::number(message->clordid.get());
            values[entry + ".payload.executionreportnewmessage.secondaryorderid"] = canonical::number(message->secondary_order_id.get());
            values[entry + ".payload.executionreportnewmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.executionreportnewmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.executionreportnewmessage.account"] = (static_cast<std::uint32_t>(message->account.get()) != 0x0U ? canonical::number(message->account.get()) : canonical::absent());
            values[entry + ".payload.executionreportnewmessage.execid"] = canonical::number(message->exec_id.get());
            values[entry + ".payload.executionreportnewmessage.transacttime"] = canonical::number(message->transact_time.get());
            values[entry + ".payload.executionreportnewmessage.marketsegmentreceivedtime"] = (static_cast<std::uint64_t>(message->market_segment_received_time.get()) != 0x0ULL ? canonical::number(message->market_segment_received_time.get()) : canonical::absent());
            values[entry + ".payload.executionreportnewmessage.protectionprice"] = (static_cast<std::uint64_t>(message->protection_price.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->protection_price.integer(), -4) : canonical::absent());
            values[entry + ".payload.executionreportnewmessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.executionreportnewmessage.workingindicator"] = canonical::number(message->working_indicator.get());
            values[entry + ".payload.executionreportnewmessage.ordtype"] = canonical::text(canonical::character(message->ordtype.get()));
            values[entry + ".payload.executionreportnewmessage.timeinforce"] = canonical::text(canonical::character(message->time_in_force.get()));
            values[entry + ".payload.executionreportnewmessage.expiredate"] = (static_cast<std::uint16_t>(message->expire_date.get()) != 0x0U ? canonical::number(message->expire_date.get()) : canonical::absent());
            values[entry + ".payload.executionreportnewmessage.orderqty"] = canonical::number(message->order_qty.get());
            values[entry + ".payload.executionreportnewmessage.priceoptional"] = (static_cast<std::uint64_t>(message->price_optional.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->price_optional.integer(), -4) : canonical::absent());
            values[entry + ".payload.executionreportnewmessage.stoppx"] = (static_cast<std::uint64_t>(message->stop_px.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->stop_px.integer(), -4) : canonical::absent());
            values[entry + ".payload.executionreportnewmessage.minqty"] = (static_cast<std::uint64_t>(message->min_qty.get()) != 0x0ULL ? canonical::number(message->min_qty.get()) : canonical::absent());
            values[entry + ".payload.executionreportnewmessage.maxfloor"] = (static_cast<std::uint64_t>(message->max_floor.get()) != 0x0ULL ? canonical::number(message->max_floor.get()) : canonical::absent());
            values[entry + ".payload.executionreportnewmessage.crossidoptional"] = (static_cast<std::uint64_t>(message->crossid_optional.get()) != 0x0ULL ? canonical::number(message->crossid_optional.get()) : canonical::absent());
            values[entry + ".payload.executionreportnewmessage.receivedtime"] = (static_cast<std::uint64_t>(message->received_time.get()) != 0x0ULL ? canonical::number(message->received_time.get()) : canonical::absent());
            values[entry + ".payload.executionreportnewmessage.ordtagid"] = (static_cast<std::uint8_t>(message->ordtagid.get()) != 0x0U ? canonical::number(message->ordtagid.get()) : canonical::absent());
            values[entry + ".payload.executionreportnewmessage.investorid.prefix"] = canonical::number(message->investor_id.prefix.get());
            values[entry + ".payload.executionreportnewmessage.investorid.document"] = canonical::number(message->investor_id.document.get());
            values[entry + ".payload.executionreportnewmessage.crosstype"] = (static_cast<std::uint8_t>(message->cross_type.get()) != 0x0U ? canonical::number(message->cross_type.get()) : canonical::absent());
            values[entry + ".payload.executionreportnewmessage.crossprioritization"] = (static_cast<std::uint8_t>(message->cross_prioritization.get()) != 0x0FFU ? canonical::number(message->cross_prioritization.get()) : canonical::absent());
            values[entry + ".payload.executionreportnewmessage.mmprotectionresetoptional"] = (static_cast<std::uint8_t>(message->mm_protection_reset_optional.get()) != 0x0FFU ? canonical::number(message->mm_protection_reset_optional.get()) : canonical::absent());
            values[entry + ".payload.executionreportnewmessage.strategyid"] = (static_cast<std::uint32_t>(message->strategy_id.get()) != 0x0U ? canonical::number(message->strategy_id.get()) : canonical::absent());
            values[entry + ".payload.executionreportnewmessage.tradingsubaccount"] = (static_cast<std::uint32_t>(message->trading_sub_account.get()) != 0x0U ? canonical::number(message->trading_sub_account.get()) : canonical::absent());
        } else if (iterator.template_id == 201) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.executionreportmodifymessage";
            [[maybe_unused]] const auto* message = protocol::ExecutionReportModifyMessage::parse(iterator.message);
            values[entry + ".payload.executionreportmodifymessage.outboundbusinessheader.sessionid"] = canonical::number(message->outbound_business_header.session_id.get());
            values[entry + ".payload.executionreportmodifymessage.outboundbusinessheader.msgseqnum"] = canonical::number(message->outbound_business_header.msg_seq_num.get());
            values[entry + ".payload.executionreportmodifymessage.outboundbusinessheader.sendingtime"] = (static_cast<std::uint64_t>(message->outbound_business_header.sending_time.get()) != 0x0ULL ? canonical::number(message->outbound_business_header.sending_time.get()) : canonical::absent());
            values[entry + ".payload.executionreportmodifymessage.outboundbusinessheader.eventindicator"] = canonical::number(message->outbound_business_header.event_indicator.get());
            values[entry + ".payload.executionreportmodifymessage.outboundbusinessheader.marketsegmentidoptional"] = canonical::number(message->outbound_business_header.market_segment_id_optional.get());
            values[entry + ".payload.executionreportmodifymessage.side"] = canonical::text(canonical::character(message->side.get()));
            values[entry + ".payload.executionreportmodifymessage.ordstatus"] = canonical::text(canonical::character(message->ord_status.get()));
            values[entry + ".payload.executionreportmodifymessage.clordid"] = canonical::number(message->clordid.get());
            values[entry + ".payload.executionreportmodifymessage.secondaryorderid"] = canonical::number(message->secondary_order_id.get());
            values[entry + ".payload.executionreportmodifymessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.executionreportmodifymessage.leavesqty"] = canonical::number(message->leaves_qty.get());
            values[entry + ".payload.executionreportmodifymessage.account"] = (static_cast<std::uint32_t>(message->account.get()) != 0x0U ? canonical::number(message->account.get()) : canonical::absent());
            values[entry + ".payload.executionreportmodifymessage.execid"] = canonical::number(message->exec_id.get());
            values[entry + ".payload.executionreportmodifymessage.transacttime"] = canonical::number(message->transact_time.get());
            values[entry + ".payload.executionreportmodifymessage.cumqty"] = canonical::number(message->cum_qty.get());
            values[entry + ".payload.executionreportmodifymessage.marketsegmentreceivedtime"] = (static_cast<std::uint64_t>(message->market_segment_received_time.get()) != 0x0ULL ? canonical::number(message->market_segment_received_time.get()) : canonical::absent());
            values[entry + ".payload.executionreportmodifymessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.executionreportmodifymessage.origclordid"] = (static_cast<std::uint64_t>(message->origclordid.get()) != 0x0ULL ? canonical::number(message->origclordid.get()) : canonical::absent());
            values[entry + ".payload.executionreportmodifymessage.protectionprice"] = (static_cast<std::uint64_t>(message->protection_price.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->protection_price.integer(), -4) : canonical::absent());
            values[entry + ".payload.executionreportmodifymessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.executionreportmodifymessage.workingindicator"] = canonical::number(message->working_indicator.get());
            values[entry + ".payload.executionreportmodifymessage.ordtype"] = canonical::text(canonical::character(message->ordtype.get()));
            values[entry + ".payload.executionreportmodifymessage.timeinforce"] = canonical::text(canonical::character(message->time_in_force.get()));
            values[entry + ".payload.executionreportmodifymessage.expiredate"] = (static_cast<std::uint16_t>(message->expire_date.get()) != 0x0U ? canonical::number(message->expire_date.get()) : canonical::absent());
            values[entry + ".payload.executionreportmodifymessage.orderqty"] = canonical::number(message->order_qty.get());
            values[entry + ".payload.executionreportmodifymessage.priceoptional"] = (static_cast<std::uint64_t>(message->price_optional.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->price_optional.integer(), -4) : canonical::absent());
            values[entry + ".payload.executionreportmodifymessage.stoppx"] = (static_cast<std::uint64_t>(message->stop_px.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->stop_px.integer(), -4) : canonical::absent());
            values[entry + ".payload.executionreportmodifymessage.minqty"] = (static_cast<std::uint64_t>(message->min_qty.get()) != 0x0ULL ? canonical::number(message->min_qty.get()) : canonical::absent());
            values[entry + ".payload.executionreportmodifymessage.maxfloor"] = (static_cast<std::uint64_t>(message->max_floor.get()) != 0x0ULL ? canonical::number(message->max_floor.get()) : canonical::absent());
            values[entry + ".payload.executionreportmodifymessage.receivedtime"] = (static_cast<std::uint64_t>(message->received_time.get()) != 0x0ULL ? canonical::number(message->received_time.get()) : canonical::absent());
            values[entry + ".payload.executionreportmodifymessage.ordtagid"] = (static_cast<std::uint8_t>(message->ordtagid.get()) != 0x0U ? canonical::number(message->ordtagid.get()) : canonical::absent());
            values[entry + ".payload.executionreportmodifymessage.investorid.prefix"] = canonical::number(message->investor_id.prefix.get());
            values[entry + ".payload.executionreportmodifymessage.investorid.document"] = canonical::number(message->investor_id.document.get());
            values[entry + ".payload.executionreportmodifymessage.mmprotectionresetoptional"] = (static_cast<std::uint8_t>(message->mm_protection_reset_optional.get()) != 0x0FFU ? canonical::number(message->mm_protection_reset_optional.get()) : canonical::absent());
            values[entry + ".payload.executionreportmodifymessage.strategyid"] = (static_cast<std::uint32_t>(message->strategy_id.get()) != 0x0U ? canonical::number(message->strategy_id.get()) : canonical::absent());
            values[entry + ".payload.executionreportmodifymessage.tradingsubaccount"] = (static_cast<std::uint32_t>(message->trading_sub_account.get()) != 0x0U ? canonical::number(message->trading_sub_account.get()) : canonical::absent());
        } else if (iterator.template_id == 202) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.executionreportcancelmessage";
            [[maybe_unused]] const auto* message = protocol::ExecutionReportCancelMessage::parse(iterator.message);
            values[entry + ".payload.executionreportcancelmessage.outboundbusinessheader.sessionid"] = canonical::number(message->outbound_business_header.session_id.get());
            values[entry + ".payload.executionreportcancelmessage.outboundbusinessheader.msgseqnum"] = canonical::number(message->outbound_business_header.msg_seq_num.get());
            values[entry + ".payload.executionreportcancelmessage.outboundbusinessheader.sendingtime"] = (static_cast<std::uint64_t>(message->outbound_business_header.sending_time.get()) != 0x0ULL ? canonical::number(message->outbound_business_header.sending_time.get()) : canonical::absent());
            values[entry + ".payload.executionreportcancelmessage.outboundbusinessheader.eventindicator"] = canonical::number(message->outbound_business_header.event_indicator.get());
            values[entry + ".payload.executionreportcancelmessage.outboundbusinessheader.marketsegmentidoptional"] = canonical::number(message->outbound_business_header.market_segment_id_optional.get());
            values[entry + ".payload.executionreportcancelmessage.side"] = canonical::text(canonical::character(message->side.get()));
            values[entry + ".payload.executionreportcancelmessage.ordstatus"] = canonical::text(canonical::character(message->ord_status.get()));
            values[entry + ".payload.executionreportcancelmessage.clordid"] = canonical::number(message->clordid.get());
            values[entry + ".payload.executionreportcancelmessage.secondaryorderid"] = canonical::number(message->secondary_order_id.get());
            values[entry + ".payload.executionreportcancelmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.executionreportcancelmessage.cumqty"] = canonical::number(message->cum_qty.get());
            values[entry + ".payload.executionreportcancelmessage.account"] = (static_cast<std::uint32_t>(message->account.get()) != 0x0U ? canonical::number(message->account.get()) : canonical::absent());
            values[entry + ".payload.executionreportcancelmessage.execid"] = canonical::number(message->exec_id.get());
            values[entry + ".payload.executionreportcancelmessage.transacttime"] = canonical::number(message->transact_time.get());
            values[entry + ".payload.executionreportcancelmessage.marketsegmentreceivedtime"] = (static_cast<std::uint64_t>(message->market_segment_received_time.get()) != 0x0ULL ? canonical::number(message->market_segment_received_time.get()) : canonical::absent());
            values[entry + ".payload.executionreportcancelmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.executionreportcancelmessage.origclordid"] = (static_cast<std::uint64_t>(message->origclordid.get()) != 0x0ULL ? canonical::number(message->origclordid.get()) : canonical::absent());
            values[entry + ".payload.executionreportcancelmessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.executionreportcancelmessage.workingindicator"] = canonical::number(message->working_indicator.get());
            values[entry + ".payload.executionreportcancelmessage.execrestatementreason"] = (static_cast<std::uint8_t>(message->exec_restatement_reason.get()) != 0x0U ? canonical::number(message->exec_restatement_reason.get()) : canonical::absent());
            values[entry + ".payload.executionreportcancelmessage.massactionreportidoptional"] = (static_cast<std::uint64_t>(message->mass_action_report_id_optional.get()) != 0x0ULL ? canonical::number(message->mass_action_report_id_optional.get()) : canonical::absent());
            values[entry + ".payload.executionreportcancelmessage.ordtype"] = canonical::text(canonical::character(message->ordtype.get()));
            values[entry + ".payload.executionreportcancelmessage.timeinforce"] = canonical::text(canonical::character(message->time_in_force.get()));
            values[entry + ".payload.executionreportcancelmessage.expiredate"] = (static_cast<std::uint16_t>(message->expire_date.get()) != 0x0U ? canonical::number(message->expire_date.get()) : canonical::absent());
            values[entry + ".payload.executionreportcancelmessage.orderqty"] = canonical::number(message->order_qty.get());
            values[entry + ".payload.executionreportcancelmessage.priceoptional"] = (static_cast<std::uint64_t>(message->price_optional.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->price_optional.integer(), -4) : canonical::absent());
            values[entry + ".payload.executionreportcancelmessage.stoppx"] = (static_cast<std::uint64_t>(message->stop_px.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->stop_px.integer(), -4) : canonical::absent());
            values[entry + ".payload.executionreportcancelmessage.minqty"] = (static_cast<std::uint64_t>(message->min_qty.get()) != 0x0ULL ? canonical::number(message->min_qty.get()) : canonical::absent());
            values[entry + ".payload.executionreportcancelmessage.maxfloor"] = (static_cast<std::uint64_t>(message->max_floor.get()) != 0x0ULL ? canonical::number(message->max_floor.get()) : canonical::absent());
            values[entry + ".payload.executionreportcancelmessage.receivedtime"] = (static_cast<std::uint64_t>(message->received_time.get()) != 0x0ULL ? canonical::number(message->received_time.get()) : canonical::absent());
            values[entry + ".payload.executionreportcancelmessage.ordtagid"] = (static_cast<std::uint8_t>(message->ordtagid.get()) != 0x0U ? canonical::number(message->ordtagid.get()) : canonical::absent());
            values[entry + ".payload.executionreportcancelmessage.investorid.prefix"] = canonical::number(message->investor_id.prefix.get());
            values[entry + ".payload.executionreportcancelmessage.investorid.document"] = canonical::number(message->investor_id.document.get());
            values[entry + ".payload.executionreportcancelmessage.strategyid"] = (static_cast<std::uint32_t>(message->strategy_id.get()) != 0x0U ? canonical::number(message->strategy_id.get()) : canonical::absent());
            values[entry + ".payload.executionreportcancelmessage.actionrequestedfromsessionid"] = (static_cast<std::uint32_t>(message->action_requested_from_session_id.get()) != 0x0U ? canonical::number(message->action_requested_from_session_id.get()) : canonical::absent());
        } else if (iterator.template_id == 203) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.executionreporttrademessage";
            [[maybe_unused]] const auto* message = protocol::ExecutionReportTradeMessage::parse(iterator.message);
            values[entry + ".payload.executionreporttrademessage.outboundbusinessheader.sessionid"] = canonical::number(message->outbound_business_header.session_id.get());
            values[entry + ".payload.executionreporttrademessage.outboundbusinessheader.msgseqnum"] = canonical::number(message->outbound_business_header.msg_seq_num.get());
            values[entry + ".payload.executionreporttrademessage.outboundbusinessheader.sendingtime"] = (static_cast<std::uint64_t>(message->outbound_business_header.sending_time.get()) != 0x0ULL ? canonical::number(message->outbound_business_header.sending_time.get()) : canonical::absent());
            values[entry + ".payload.executionreporttrademessage.outboundbusinessheader.eventindicator"] = canonical::number(message->outbound_business_header.event_indicator.get());
            values[entry + ".payload.executionreporttrademessage.outboundbusinessheader.marketsegmentidoptional"] = canonical::number(message->outbound_business_header.market_segment_id_optional.get());
            values[entry + ".payload.executionreporttrademessage.side"] = canonical::text(canonical::character(message->side.get()));
            values[entry + ".payload.executionreporttrademessage.ordstatus"] = canonical::text(canonical::character(message->ord_status.get()));
            values[entry + ".payload.executionreporttrademessage.clordidoptional"] = (static_cast<std::uint64_t>(message->clordid_optional.get()) != 0x0ULL ? canonical::number(message->clordid_optional.get()) : canonical::absent());
            values[entry + ".payload.executionreporttrademessage.secondaryorderid"] = canonical::number(message->secondary_order_id.get());
            values[entry + ".payload.executionreporttrademessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.executionreporttrademessage.account"] = (static_cast<std::uint32_t>(message->account.get()) != 0x0U ? canonical::number(message->account.get()) : canonical::absent());
            values[entry + ".payload.executionreporttrademessage.lastqty"] = canonical::number(message->last_qty.get());
            values[entry + ".payload.executionreporttrademessage.lastpx"] = canonical::scaled(message->last_px.integer(), -4);
            values[entry + ".payload.executionreporttrademessage.execid"] = canonical::number(message->exec_id.get());
            values[entry + ".payload.executionreporttrademessage.transacttime"] = canonical::number(message->transact_time.get());
            values[entry + ".payload.executionreporttrademessage.leavesqty"] = canonical::number(message->leaves_qty.get());
            values[entry + ".payload.executionreporttrademessage.cumqty"] = canonical::number(message->cum_qty.get());
            values[entry + ".payload.executionreporttrademessage.aggressorindicator"] = canonical::number(message->aggressor_indicator.get());
            values[entry + ".payload.executionreporttrademessage.exectype"] = canonical::text(canonical::character(message->exec_type.get()));
            values[entry + ".payload.executionreporttrademessage.tradeid"] = canonical::number(message->trade_id.get());
            values[entry + ".payload.executionreporttrademessage.contrabroker"] = canonical::number(message->contra_broker.get());
            values[entry + ".payload.executionreporttrademessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.executionreporttrademessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.executionreporttrademessage.totnorelatedsym"] = (static_cast<std::uint8_t>(message->tot_no_related_sym.get()) != 0x0U ? canonical::number(message->tot_no_related_sym.get()) : canonical::absent());
            values[entry + ".payload.executionreporttrademessage.secondaryexecid"] = (static_cast<std::uint64_t>(message->secondary_exec_id.get()) != 0x0ULL ? canonical::number(message->secondary_exec_id.get()) : canonical::absent());
            values[entry + ".payload.executionreporttrademessage.execrefid"] = (static_cast<std::uint64_t>(message->exec_ref_id.get()) != 0x0ULL ? canonical::number(message->exec_ref_id.get()) : canonical::absent());
            values[entry + ".payload.executionreporttrademessage.crossidoptional"] = (static_cast<std::uint64_t>(message->crossid_optional.get()) != 0x0ULL ? canonical::number(message->crossid_optional.get()) : canonical::absent());
            values[entry + ".payload.executionreporttrademessage.crossedindicator"] = (static_cast<std::uint16_t>(message->crossed_indicator.get()) != 0x0U ? canonical::number(message->crossed_indicator.get()) : canonical::absent());
            values[entry + ".payload.executionreporttrademessage.orderqty"] = canonical::number(message->order_qty.get());
            values[entry + ".payload.executionreporttrademessage.tradingsessionid"] = (static_cast<std::uint8_t>(message->trading_session_id.get()) != 0x0U ? canonical::number(message->trading_session_id.get()) : canonical::absent());
            values[entry + ".payload.executionreporttrademessage.tradingsessionsubid"] = (static_cast<std::uint8_t>(message->trading_session_sub_id.get()) != 0x0U ? canonical::number(message->trading_session_sub_id.get()) : canonical::absent());
            values[entry + ".payload.executionreporttrademessage.securitytradingstatus"] = (static_cast<std::uint8_t>(message->security_trading_status.get()) != 0x0U ? canonical::number(message->security_trading_status.get()) : canonical::absent());
            values[entry + ".payload.executionreporttrademessage.crosstype"] = (static_cast<std::uint8_t>(message->cross_type.get()) != 0x0U ? canonical::number(message->cross_type.get()) : canonical::absent());
            values[entry + ".payload.executionreporttrademessage.crossprioritization"] = (static_cast<std::uint8_t>(message->cross_prioritization.get()) != 0x0FFU ? canonical::number(message->cross_prioritization.get()) : canonical::absent());
            values[entry + ".payload.executionreporttrademessage.strategyid"] = (static_cast<std::uint32_t>(message->strategy_id.get()) != 0x0U ? canonical::number(message->strategy_id.get()) : canonical::absent());
            values[entry + ".payload.executionreporttrademessage.impliedeventid.eventid"] = canonical::number(message->implied_event_id.event_id.get());
            values[entry + ".payload.executionreporttrademessage.impliedeventid.norelatedtrades"] = canonical::number(message->implied_event_id.no_related_trades.get());
            values[entry + ".payload.executionreporttrademessage.tradingsubaccount"] = (static_cast<std::uint32_t>(message->trading_sub_account.get()) != 0x0U ? canonical::number(message->trading_sub_account.get()) : canonical::absent());
        } else if (iterator.template_id == 204) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.executionreportrejectmessage";
            [[maybe_unused]] const auto* message = protocol::ExecutionReportRejectMessage::parse(iterator.message);
            values[entry + ".payload.executionreportrejectmessage.outboundbusinessheader.sessionid"] = canonical::number(message->outbound_business_header.session_id.get());
            values[entry + ".payload.executionreportrejectmessage.outboundbusinessheader.msgseqnum"] = canonical::number(message->outbound_business_header.msg_seq_num.get());
            values[entry + ".payload.executionreportrejectmessage.outboundbusinessheader.sendingtime"] = (static_cast<std::uint64_t>(message->outbound_business_header.sending_time.get()) != 0x0ULL ? canonical::number(message->outbound_business_header.sending_time.get()) : canonical::absent());
            values[entry + ".payload.executionreportrejectmessage.outboundbusinessheader.eventindicator"] = canonical::number(message->outbound_business_header.event_indicator.get());
            values[entry + ".payload.executionreportrejectmessage.outboundbusinessheader.marketsegmentidoptional"] = canonical::number(message->outbound_business_header.market_segment_id_optional.get());
            values[entry + ".payload.executionreportrejectmessage.side"] = canonical::text(canonical::character(message->side.get()));
            values[entry + ".payload.executionreportrejectmessage.cxlrejresponseto"] = canonical::number(message->cxl_rej_response_to.get());
            values[entry + ".payload.executionreportrejectmessage.clordid"] = canonical::number(message->clordid.get());
            values[entry + ".payload.executionreportrejectmessage.secondaryorderidoptional"] = (static_cast<std::uint64_t>(message->secondary_order_id_optional.get()) != 0x0ULL ? canonical::number(message->secondary_order_id_optional.get()) : canonical::absent());
            values[entry + ".payload.executionreportrejectmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.executionreportrejectmessage.ordrejreason"] = canonical::number(message->ord_rej_reason.get());
            values[entry + ".payload.executionreportrejectmessage.transacttime"] = canonical::number(message->transact_time.get());
            values[entry + ".payload.executionreportrejectmessage.execid"] = canonical::number(message->exec_id.get());
            values[entry + ".payload.executionreportrejectmessage.orderidoptional"] = (static_cast<std::uint64_t>(message->order_id_optional.get()) != 0x0ULL ? canonical::number(message->order_id_optional.get()) : canonical::absent());
            values[entry + ".payload.executionreportrejectmessage.origclordid"] = (static_cast<std::uint64_t>(message->origclordid.get()) != 0x0ULL ? canonical::number(message->origclordid.get()) : canonical::absent());
            values[entry + ".payload.executionreportrejectmessage.account"] = (static_cast<std::uint32_t>(message->account.get()) != 0x0U ? canonical::number(message->account.get()) : canonical::absent());
            values[entry + ".payload.executionreportrejectmessage.ordtype"] = canonical::text(canonical::character(message->ordtype.get()));
            values[entry + ".payload.executionreportrejectmessage.timeinforce"] = canonical::text(canonical::character(message->time_in_force.get()));
            values[entry + ".payload.executionreportrejectmessage.expiredate"] = (static_cast<std::uint16_t>(message->expire_date.get()) != 0x0U ? canonical::number(message->expire_date.get()) : canonical::absent());
            values[entry + ".payload.executionreportrejectmessage.orderqtyoptional"] = (static_cast<std::uint64_t>(message->order_qty_optional.get()) != 0x0ULL ? canonical::number(message->order_qty_optional.get()) : canonical::absent());
            values[entry + ".payload.executionreportrejectmessage.priceoptional"] = (static_cast<std::uint64_t>(message->price_optional.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->price_optional.integer(), -4) : canonical::absent());
            values[entry + ".payload.executionreportrejectmessage.stoppx"] = (static_cast<std::uint64_t>(message->stop_px.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->stop_px.integer(), -4) : canonical::absent());
            values[entry + ".payload.executionreportrejectmessage.minqty"] = (static_cast<std::uint64_t>(message->min_qty.get()) != 0x0ULL ? canonical::number(message->min_qty.get()) : canonical::absent());
            values[entry + ".payload.executionreportrejectmessage.maxfloor"] = (static_cast<std::uint64_t>(message->max_floor.get()) != 0x0ULL ? canonical::number(message->max_floor.get()) : canonical::absent());
            values[entry + ".payload.executionreportrejectmessage.crossidoptional"] = (static_cast<std::uint64_t>(message->crossid_optional.get()) != 0x0ULL ? canonical::number(message->crossid_optional.get()) : canonical::absent());
            values[entry + ".payload.executionreportrejectmessage.crossedindicator"] = (static_cast<std::uint16_t>(message->crossed_indicator.get()) != 0x0U ? canonical::number(message->crossed_indicator.get()) : canonical::absent());
            values[entry + ".payload.executionreportrejectmessage.receivedtime"] = (static_cast<std::uint64_t>(message->received_time.get()) != 0x0ULL ? canonical::number(message->received_time.get()) : canonical::absent());
            values[entry + ".payload.executionreportrejectmessage.ordtagid"] = (static_cast<std::uint8_t>(message->ordtagid.get()) != 0x0U ? canonical::number(message->ordtagid.get()) : canonical::absent());
            values[entry + ".payload.executionreportrejectmessage.investorid.prefix"] = canonical::number(message->investor_id.prefix.get());
            values[entry + ".payload.executionreportrejectmessage.investorid.document"] = canonical::number(message->investor_id.document.get());
            values[entry + ".payload.executionreportrejectmessage.strategyid"] = (static_cast<std::uint32_t>(message->strategy_id.get()) != 0x0U ? canonical::number(message->strategy_id.get()) : canonical::absent());
            values[entry + ".payload.executionreportrejectmessage.tradingsubaccount"] = (static_cast<std::uint32_t>(message->trading_sub_account.get()) != 0x0U ? canonical::number(message->trading_sub_account.get()) : canonical::absent());
        } else if (iterator.template_id == 205) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.executionreportforwardmessage";
            [[maybe_unused]] const auto* message = protocol::ExecutionReportForwardMessage::parse(iterator.message);
            values[entry + ".payload.executionreportforwardmessage.outboundbusinessheader.sessionid"] = canonical::number(message->outbound_business_header.session_id.get());
            values[entry + ".payload.executionreportforwardmessage.outboundbusinessheader.msgseqnum"] = canonical::number(message->outbound_business_header.msg_seq_num.get());
            values[entry + ".payload.executionreportforwardmessage.outboundbusinessheader.sendingtime"] = (static_cast<std::uint64_t>(message->outbound_business_header.sending_time.get()) != 0x0ULL ? canonical::number(message->outbound_business_header.sending_time.get()) : canonical::absent());
            values[entry + ".payload.executionreportforwardmessage.outboundbusinessheader.eventindicator"] = canonical::number(message->outbound_business_header.event_indicator.get());
            values[entry + ".payload.executionreportforwardmessage.outboundbusinessheader.marketsegmentidoptional"] = canonical::number(message->outbound_business_header.market_segment_id_optional.get());
            values[entry + ".payload.executionreportforwardmessage.side"] = canonical::text(canonical::character(message->side.get()));
            values[entry + ".payload.executionreportforwardmessage.ordstatus"] = canonical::text(canonical::character(message->ord_status.get()));
            values[entry + ".payload.executionreportforwardmessage.clordidoptional"] = (static_cast<std::uint64_t>(message->clordid_optional.get()) != 0x0ULL ? canonical::number(message->clordid_optional.get()) : canonical::absent());
            values[entry + ".payload.executionreportforwardmessage.secondaryorderid"] = canonical::number(message->secondary_order_id.get());
            values[entry + ".payload.executionreportforwardmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.executionreportforwardmessage.account"] = (static_cast<std::uint32_t>(message->account.get()) != 0x0U ? canonical::number(message->account.get()) : canonical::absent());
            values[entry + ".payload.executionreportforwardmessage.lastqty"] = canonical::number(message->last_qty.get());
            values[entry + ".payload.executionreportforwardmessage.lastpx"] = canonical::scaled(message->last_px.integer(), -4);
            values[entry + ".payload.executionreportforwardmessage.execid"] = canonical::number(message->exec_id.get());
            values[entry + ".payload.executionreportforwardmessage.transacttime"] = canonical::number(message->transact_time.get());
            values[entry + ".payload.executionreportforwardmessage.leavesqty"] = canonical::number(message->leaves_qty.get());
            values[entry + ".payload.executionreportforwardmessage.cumqty"] = canonical::number(message->cum_qty.get());
            values[entry + ".payload.executionreportforwardmessage.tradeid"] = canonical::number(message->trade_id.get());
            values[entry + ".payload.executionreportforwardmessage.contrabroker"] = canonical::number(message->contra_broker.get());
            values[entry + ".payload.executionreportforwardmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.executionreportforwardmessage.aggressorindicator"] = canonical::number(message->aggressor_indicator.get());
            values[entry + ".payload.executionreportforwardmessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.executionreportforwardmessage.daystosettlementoptional"] = (static_cast<std::uint16_t>(message->days_to_settlement_optional.get()) != 0x0FFFFU ? canonical::number(message->days_to_settlement_optional.get()) : canonical::absent());
            values[entry + ".payload.executionreportforwardmessage.secondaryexecid"] = (static_cast<std::uint64_t>(message->secondary_exec_id.get()) != 0x0ULL ? canonical::number(message->secondary_exec_id.get()) : canonical::absent());
            values[entry + ".payload.executionreportforwardmessage.execrefid"] = (static_cast<std::uint64_t>(message->exec_ref_id.get()) != 0x0ULL ? canonical::number(message->exec_ref_id.get()) : canonical::absent());
            values[entry + ".payload.executionreportforwardmessage.fixedratepercentage8optional"] = (static_cast<std::uint64_t>(message->fixed_rate_percentage_8_optional.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->fixed_rate_percentage_8_optional.integer(), -8) : canonical::absent());
            values[entry + ".payload.executionreportforwardmessage.orderqty"] = canonical::number(message->order_qty.get());
            values[entry + ".payload.executionreportforwardmessage.tradingsessionid"] = (static_cast<std::uint8_t>(message->trading_session_id.get()) != 0x0U ? canonical::number(message->trading_session_id.get()) : canonical::absent());
            values[entry + ".payload.executionreportforwardmessage.tradingsessionsubid"] = (static_cast<std::uint8_t>(message->trading_session_sub_id.get()) != 0x0U ? canonical::number(message->trading_session_sub_id.get()) : canonical::absent());
            values[entry + ".payload.executionreportforwardmessage.securitytradingstatus"] = (static_cast<std::uint8_t>(message->security_trading_status.get()) != 0x0U ? canonical::number(message->security_trading_status.get()) : canonical::absent());
            values[entry + ".payload.executionreportforwardmessage.tradingsubaccount"] = (static_cast<std::uint32_t>(message->trading_sub_account.get()) != 0x0U ? canonical::number(message->trading_sub_account.get()) : canonical::absent());
        } else if (iterator.template_id == 206) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.businessmessagerejectmessage";
            [[maybe_unused]] const auto* message = protocol::BusinessMessageRejectMessage::parse(iterator.message);
            values[entry + ".payload.businessmessagerejectmessage.outboundbusinessheader.sessionid"] = canonical::number(message->outbound_business_header.session_id.get());
            values[entry + ".payload.businessmessagerejectmessage.outboundbusinessheader.msgseqnum"] = canonical::number(message->outbound_business_header.msg_seq_num.get());
            values[entry + ".payload.businessmessagerejectmessage.outboundbusinessheader.sendingtime"] = (static_cast<std::uint64_t>(message->outbound_business_header.sending_time.get()) != 0x0ULL ? canonical::number(message->outbound_business_header.sending_time.get()) : canonical::absent());
            values[entry + ".payload.businessmessagerejectmessage.outboundbusinessheader.eventindicator"] = canonical::number(message->outbound_business_header.event_indicator.get());
            values[entry + ".payload.businessmessagerejectmessage.outboundbusinessheader.marketsegmentidoptional"] = canonical::number(message->outbound_business_header.market_segment_id_optional.get());
            values[entry + ".payload.businessmessagerejectmessage.refmsgtype"] = canonical::number(message->ref_msg_type.get());
            values[entry + ".payload.businessmessagerejectmessage.refseqnum"] = canonical::number(message->ref_seq_num.get());
            values[entry + ".payload.businessmessagerejectmessage.businessrejectrefid"] = (static_cast<std::uint64_t>(message->business_reject_ref_id.get()) != 0x0ULL ? canonical::number(message->business_reject_ref_id.get()) : canonical::absent());
            values[entry + ".payload.businessmessagerejectmessage.businessrejectreason"] = canonical::number(message->business_reject_reason.get());
        } else if (iterator.template_id == 300) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.securitydefinitionrequestmessage";
            [[maybe_unused]] const auto* message = protocol::SecurityDefinitionRequestMessage::parse(iterator.message);
            values[entry + ".payload.securitydefinitionrequestmessage.inboundbusinessheader.sessionid"] = canonical::number(message->inbound_business_header.session_id.get());
            values[entry + ".payload.securitydefinitionrequestmessage.inboundbusinessheader.msgseqnum"] = canonical::number(message->inbound_business_header.msg_seq_num.get());
            values[entry + ".payload.securitydefinitionrequestmessage.inboundbusinessheader.sendingtime"] = (static_cast<std::uint64_t>(message->inbound_business_header.sending_time.get()) != 0x0ULL ? canonical::number(message->inbound_business_header.sending_time.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionrequestmessage.inboundbusinessheader.marketsegmentid"] = canonical::number(message->inbound_business_header.market_segment_id.get());
            values[entry + ".payload.securitydefinitionrequestmessage.inboundbusinessheader.padding"] = canonical::text(canonical::character(message->inbound_business_header.padding.get()));
            values[entry + ".payload.securitydefinitionrequestmessage.securityreqid"] = canonical::number(message->security_req_id.get());
            values[entry + ".payload.securitydefinitionrequestmessage.senderlocation"] = canonical::text(std::string(message->sender_location.get()), '\0', false);
            values[entry + ".payload.securitydefinitionrequestmessage.enteringtrader"] = canonical::text(std::string(message->entering_trader.get()), '\0', false);
        } else if (iterator.template_id == 301) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.securitydefinitionresponsemessage";
            [[maybe_unused]] const auto* message = protocol::SecurityDefinitionResponseMessage::parse(iterator.message);
            values[entry + ".payload.securitydefinitionresponsemessage.outboundbusinessheader.sessionid"] = canonical::number(message->outbound_business_header.session_id.get());
            values[entry + ".payload.securitydefinitionresponsemessage.outboundbusinessheader.msgseqnum"] = canonical::number(message->outbound_business_header.msg_seq_num.get());
            values[entry + ".payload.securitydefinitionresponsemessage.outboundbusinessheader.sendingtime"] = (static_cast<std::uint64_t>(message->outbound_business_header.sending_time.get()) != 0x0ULL ? canonical::number(message->outbound_business_header.sending_time.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionresponsemessage.outboundbusinessheader.eventindicator"] = canonical::number(message->outbound_business_header.event_indicator.get());
            values[entry + ".payload.securitydefinitionresponsemessage.outboundbusinessheader.marketsegmentidoptional"] = canonical::number(message->outbound_business_header.market_segment_id_optional.get());
            values[entry + ".payload.securitydefinitionresponsemessage.securityreqid"] = canonical::number(message->security_req_id.get());
            values[entry + ".payload.securitydefinitionresponsemessage.securityidoptional"] = (static_cast<std::uint64_t>(message->security_id_optional.get()) != 0x0ULL ? canonical::number(message->security_id_optional.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionresponsemessage.securityresponsetype"] = canonical::number(message->security_response_type.get());
            values[entry + ".payload.securitydefinitionresponsemessage.symbol"] = canonical::text(std::string(message->symbol.get()), '\0', false);
            values[entry + ".payload.securitydefinitionresponsemessage.securityresponseid"] = canonical::number(message->security_response_id.get());
            values[entry + ".payload.securitydefinitionresponsemessage.senderlocation"] = canonical::text(std::string(message->sender_location.get()), '\0', false);
            values[entry + ".payload.securitydefinitionresponsemessage.enteringtrader"] = canonical::text(std::string(message->entering_trader.get()), '\0', false);
        } else if (iterator.template_id == 401) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.quoterequestmessage";
            [[maybe_unused]] const auto* message = protocol::QuoteRequestMessage::parse(iterator.message);
            values[entry + ".payload.quoterequestmessage.bidirectionalbusinessheader.sessionid"] = canonical::number(message->bidirectional_business_header.session_id.get());
            values[entry + ".payload.quoterequestmessage.bidirectionalbusinessheader.msgseqnum"] = canonical::number(message->bidirectional_business_header.msg_seq_num.get());
            values[entry + ".payload.quoterequestmessage.bidirectionalbusinessheader.sendingtime"] = (static_cast<std::uint64_t>(message->bidirectional_business_header.sending_time.get()) != 0x0ULL ? canonical::number(message->bidirectional_business_header.sending_time.get()) : canonical::absent());
            values[entry + ".payload.quoterequestmessage.bidirectionalbusinessheader.eventindicator"] = canonical::number(message->bidirectional_business_header.event_indicator.get());
            values[entry + ".payload.quoterequestmessage.bidirectionalbusinessheader.marketsegmentidoptional"] = canonical::number(message->bidirectional_business_header.market_segment_id_optional.get());
            values[entry + ".payload.quoterequestmessage.bidirectionalbusinessheader.padding"] = canonical::text(canonical::character(message->bidirectional_business_header.padding.get()));
            values[entry + ".payload.quoterequestmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.quoterequestmessage.quotereqid"] = canonical::number(message->quote_req_id.get());
            values[entry + ".payload.quoterequestmessage.quoteidoptional"] = (static_cast<std::uint64_t>(message->quote_id_optional.get()) != 0x0ULL ? canonical::number(message->quote_id_optional.get()) : canonical::absent());
            values[entry + ".payload.quoterequestmessage.tradeidoptional"] = (static_cast<std::uint32_t>(message->trade_id_optional.get()) != 0x0U ? canonical::number(message->trade_id_optional.get()) : canonical::absent());
            values[entry + ".payload.quoterequestmessage.contrabroker"] = canonical::number(message->contra_broker.get());
            values[entry + ".payload.quoterequestmessage.transacttime"] = canonical::number(message->transact_time.get());
            values[entry + ".payload.quoterequestmessage.price8"] = canonical::scaled(message->price_8.integer(), -8);
            values[entry + ".payload.quoterequestmessage.settltype"] = canonical::text(canonical::character(message->settl_type.get()));
            values[entry + ".payload.quoterequestmessage.orderqty"] = canonical::number(message->order_qty.get());
            values[entry + ".payload.quoterequestmessage.senderlocation"] = canonical::text(std::string(message->sender_location.get()), '\0', false);
            values[entry + ".payload.quoterequestmessage.enteringtrader"] = canonical::text(std::string(message->entering_trader.get()), '\0', false);
            values[entry + ".payload.quoterequestmessage.executingtrader"] = canonical::text(std::string(message->executing_trader.get()), '\0', false);
            values[entry + ".payload.quoterequestmessage.fixedratepercentage8"] = canonical::scaled(message->fixed_rate_percentage_8.integer(), -8);
            values[entry + ".payload.quoterequestmessage.daystosettlement"] = canonical::number(message->days_to_settlement.get());
        } else if (iterator.template_id == 402) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.quotestatusreportmessage";
            [[maybe_unused]] const auto* message = protocol::QuoteStatusReportMessage::parse(iterator.message);
            values[entry + ".payload.quotestatusreportmessage.bidirectionalbusinessheader.sessionid"] = canonical::number(message->bidirectional_business_header.session_id.get());
            values[entry + ".payload.quotestatusreportmessage.bidirectionalbusinessheader.msgseqnum"] = canonical::number(message->bidirectional_business_header.msg_seq_num.get());
            values[entry + ".payload.quotestatusreportmessage.bidirectionalbusinessheader.sendingtime"] = (static_cast<std::uint64_t>(message->bidirectional_business_header.sending_time.get()) != 0x0ULL ? canonical::number(message->bidirectional_business_header.sending_time.get()) : canonical::absent());
            values[entry + ".payload.quotestatusreportmessage.bidirectionalbusinessheader.eventindicator"] = canonical::number(message->bidirectional_business_header.event_indicator.get());
            values[entry + ".payload.quotestatusreportmessage.bidirectionalbusinessheader.marketsegmentidoptional"] = canonical::number(message->bidirectional_business_header.market_segment_id_optional.get());
            values[entry + ".payload.quotestatusreportmessage.bidirectionalbusinessheader.padding"] = canonical::text(canonical::character(message->bidirectional_business_header.padding.get()));
            values[entry + ".payload.quotestatusreportmessage.quoterejectreason"] = (static_cast<std::uint32_t>(message->quote_reject_reason.get()) != 0x0U ? canonical::number(message->quote_reject_reason.get()) : canonical::absent());
            values[entry + ".payload.quotestatusreportmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.quotestatusreportmessage.quotereqid"] = canonical::number(message->quote_req_id.get());
            values[entry + ".payload.quotestatusreportmessage.quoteid"] = canonical::number(message->quote_id.get());
            values[entry + ".payload.quotestatusreportmessage.tradeidoptional"] = (static_cast<std::uint32_t>(message->trade_id_optional.get()) != 0x0U ? canonical::number(message->trade_id_optional.get()) : canonical::absent());
            values[entry + ".payload.quotestatusreportmessage.contrabroker"] = canonical::number(message->contra_broker.get());
            values[entry + ".payload.quotestatusreportmessage.transacttime"] = canonical::number(message->transact_time.get());
            values[entry + ".payload.quotestatusreportmessage.quotestatus"] = canonical::number(message->quote_status.get());
            values[entry + ".payload.quotestatusreportmessage.account"] = (static_cast<std::uint32_t>(message->account.get()) != 0x0U ? canonical::number(message->account.get()) : canonical::absent());
            values[entry + ".payload.quotestatusreportmessage.price8optional"] = (static_cast<std::uint64_t>(message->price_8_optional.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->price_8_optional.integer(), -8) : canonical::absent());
            values[entry + ".payload.quotestatusreportmessage.orderqty"] = canonical::number(message->order_qty.get());
            values[entry + ".payload.quotestatusreportmessage.senderlocation"] = canonical::text(std::string(message->sender_location.get()), '\0', false);
            values[entry + ".payload.quotestatusreportmessage.enteringtrader"] = canonical::text(std::string(message->entering_trader.get()), '\0', false);
            values[entry + ".payload.quotestatusreportmessage.executingtrader"] = canonical::text(std::string(message->executing_trader.get()), '\0', false);
            values[entry + ".payload.quotestatusreportmessage.fixedratepercentage8optional"] = (static_cast<std::uint64_t>(message->fixed_rate_percentage_8_optional.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->fixed_rate_percentage_8_optional.integer(), -8) : canonical::absent());
            values[entry + ".payload.quotestatusreportmessage.daystosettlementoptional"] = (static_cast<std::uint16_t>(message->days_to_settlement_optional.get()) != 0x0FFFFU ? canonical::number(message->days_to_settlement_optional.get()) : canonical::absent());
            values[entry + ".payload.quotestatusreportmessage.tradingsubaccount"] = (static_cast<std::uint32_t>(message->trading_sub_account.get()) != 0x0U ? canonical::number(message->trading_sub_account.get()) : canonical::absent());
        } else if (iterator.template_id == 403) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.quotemessage";
            [[maybe_unused]] const auto* message = protocol::QuoteMessage::parse(iterator.message);
            values[entry + ".payload.quotemessage.bidirectionalbusinessheader.sessionid"] = canonical::number(message->bidirectional_business_header.session_id.get());
            values[entry + ".payload.quotemessage.bidirectionalbusinessheader.msgseqnum"] = canonical::number(message->bidirectional_business_header.msg_seq_num.get());
            values[entry + ".payload.quotemessage.bidirectionalbusinessheader.sendingtime"] = (static_cast<std::uint64_t>(message->bidirectional_business_header.sending_time.get()) != 0x0ULL ? canonical::number(message->bidirectional_business_header.sending_time.get()) : canonical::absent());
            values[entry + ".payload.quotemessage.bidirectionalbusinessheader.eventindicator"] = canonical::number(message->bidirectional_business_header.event_indicator.get());
            values[entry + ".payload.quotemessage.bidirectionalbusinessheader.marketsegmentidoptional"] = canonical::number(message->bidirectional_business_header.market_segment_id_optional.get());
            values[entry + ".payload.quotemessage.bidirectionalbusinessheader.padding"] = canonical::text(canonical::character(message->bidirectional_business_header.padding.get()));
            values[entry + ".payload.quotemessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.quotemessage.quotereqid"] = canonical::number(message->quote_req_id.get());
            values[entry + ".payload.quotemessage.quoteid"] = canonical::number(message->quote_id.get());
            values[entry + ".payload.quotemessage.transacttime"] = canonical::number(message->transact_time.get());
            values[entry + ".payload.quotemessage.price8optional"] = (static_cast<std::uint64_t>(message->price_8_optional.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->price_8_optional.integer(), -8) : canonical::absent());
            values[entry + ".payload.quotemessage.orderqty"] = canonical::number(message->order_qty.get());
            values[entry + ".payload.quotemessage.side"] = canonical::text(canonical::character(message->side.get()));
            values[entry + ".payload.quotemessage.settltype"] = canonical::text(canonical::character(message->settl_type.get()));
            values[entry + ".payload.quotemessage.account"] = (static_cast<std::uint32_t>(message->account.get()) != 0x0U ? canonical::number(message->account.get()) : canonical::absent());
            values[entry + ".payload.quotemessage.senderlocation"] = canonical::text(std::string(message->sender_location.get()), '\0', false);
            values[entry + ".payload.quotemessage.enteringtrader"] = canonical::text(std::string(message->entering_trader.get()), '\0', false);
            values[entry + ".payload.quotemessage.executingtrader"] = canonical::text(std::string(message->executing_trader.get()), '\0', false);
            values[entry + ".payload.quotemessage.fixedratepercentage8"] = canonical::scaled(message->fixed_rate_percentage_8.integer(), -8);
            values[entry + ".payload.quotemessage.daystosettlement"] = canonical::number(message->days_to_settlement.get());
            values[entry + ".payload.quotemessage.tradingsubaccount"] = (static_cast<std::uint32_t>(message->trading_sub_account.get()) != 0x0U ? canonical::number(message->trading_sub_account.get()) : canonical::absent());
        } else if (iterator.template_id == 404) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.quotecancelmessage";
            [[maybe_unused]] const auto* message = protocol::QuoteCancelMessage::parse(iterator.message);
            values[entry + ".payload.quotecancelmessage.bidirectionalbusinessheader.sessionid"] = canonical::number(message->bidirectional_business_header.session_id.get());
            values[entry + ".payload.quotecancelmessage.bidirectionalbusinessheader.msgseqnum"] = canonical::number(message->bidirectional_business_header.msg_seq_num.get());
            values[entry + ".payload.quotecancelmessage.bidirectionalbusinessheader.sendingtime"] = (static_cast<std::uint64_t>(message->bidirectional_business_header.sending_time.get()) != 0x0ULL ? canonical::number(message->bidirectional_business_header.sending_time.get()) : canonical::absent());
            values[entry + ".payload.quotecancelmessage.bidirectionalbusinessheader.eventindicator"] = canonical::number(message->bidirectional_business_header.event_indicator.get());
            values[entry + ".payload.quotecancelmessage.bidirectionalbusinessheader.marketsegmentidoptional"] = canonical::number(message->bidirectional_business_header.market_segment_id_optional.get());
            values[entry + ".payload.quotecancelmessage.bidirectionalbusinessheader.padding"] = canonical::text(canonical::character(message->bidirectional_business_header.padding.get()));
            values[entry + ".payload.quotecancelmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.quotecancelmessage.quotereqidoptional"] = (static_cast<std::uint64_t>(message->quote_req_id_optional.get()) != 0x0ULL ? canonical::number(message->quote_req_id_optional.get()) : canonical::absent());
            values[entry + ".payload.quotecancelmessage.quoteidoptional"] = (static_cast<std::uint64_t>(message->quote_id_optional.get()) != 0x0ULL ? canonical::number(message->quote_id_optional.get()) : canonical::absent());
            values[entry + ".payload.quotecancelmessage.account"] = (static_cast<std::uint32_t>(message->account.get()) != 0x0U ? canonical::number(message->account.get()) : canonical::absent());
            values[entry + ".payload.quotecancelmessage.senderlocation"] = canonical::text(std::string(message->sender_location.get()), '\0', false);
            values[entry + ".payload.quotecancelmessage.enteringtrader"] = canonical::text(std::string(message->entering_trader.get()), '\0', false);
            values[entry + ".payload.quotecancelmessage.executingtrader"] = canonical::text(std::string(message->executing_trader.get()), '\0', false);
        } else if (iterator.template_id == 405) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.quoterequestrejectmessage";
            [[maybe_unused]] const auto* message = protocol::QuoteRequestRejectMessage::parse(iterator.message);
            values[entry + ".payload.quoterequestrejectmessage.bidirectionalbusinessheader.sessionid"] = canonical::number(message->bidirectional_business_header.session_id.get());
            values[entry + ".payload.quoterequestrejectmessage.bidirectionalbusinessheader.msgseqnum"] = canonical::number(message->bidirectional_business_header.msg_seq_num.get());
            values[entry + ".payload.quoterequestrejectmessage.bidirectionalbusinessheader.sendingtime"] = (static_cast<std::uint64_t>(message->bidirectional_business_header.sending_time.get()) != 0x0ULL ? canonical::number(message->bidirectional_business_header.sending_time.get()) : canonical::absent());
            values[entry + ".payload.quoterequestrejectmessage.bidirectionalbusinessheader.eventindicator"] = canonical::number(message->bidirectional_business_header.event_indicator.get());
            values[entry + ".payload.quoterequestrejectmessage.bidirectionalbusinessheader.marketsegmentidoptional"] = canonical::number(message->bidirectional_business_header.market_segment_id_optional.get());
            values[entry + ".payload.quoterequestrejectmessage.bidirectionalbusinessheader.padding"] = canonical::text(canonical::character(message->bidirectional_business_header.padding.get()));
            values[entry + ".payload.quoterequestrejectmessage.quoterequestrejectreason"] = (static_cast<std::uint32_t>(message->quote_request_reject_reason.get()) != 0x0U ? canonical::number(message->quote_request_reject_reason.get()) : canonical::absent());
            values[entry + ".payload.quoterequestrejectmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.quoterequestrejectmessage.quotereqid"] = canonical::number(message->quote_req_id.get());
            values[entry + ".payload.quoterequestrejectmessage.quoteidoptional"] = (static_cast<std::uint64_t>(message->quote_id_optional.get()) != 0x0ULL ? canonical::number(message->quote_id_optional.get()) : canonical::absent());
            values[entry + ".payload.quoterequestrejectmessage.tradeidoptional"] = (static_cast<std::uint32_t>(message->trade_id_optional.get()) != 0x0U ? canonical::number(message->trade_id_optional.get()) : canonical::absent());
            values[entry + ".payload.quoterequestrejectmessage.contrabroker"] = canonical::number(message->contra_broker.get());
            values[entry + ".payload.quoterequestrejectmessage.transacttime"] = canonical::number(message->transact_time.get());
            values[entry + ".payload.quoterequestrejectmessage.enteringtrader"] = canonical::text(std::string(message->entering_trader.get()), '\0', false);
            values[entry + ".payload.quoterequestrejectmessage.price8optional"] = (static_cast<std::uint64_t>(message->price_8_optional.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->price_8_optional.integer(), -8) : canonical::absent());
            values[entry + ".payload.quoterequestrejectmessage.orderqtyoptional"] = (static_cast<std::uint64_t>(message->order_qty_optional.get()) != 0x0ULL ? canonical::number(message->order_qty_optional.get()) : canonical::absent());
            values[entry + ".payload.quoterequestrejectmessage.senderlocation"] = canonical::text(std::string(message->sender_location.get()), '\0', false);
            values[entry + ".payload.quoterequestrejectmessage.executingtrader"] = canonical::text(std::string(message->executing_trader.get()), '\0', false);
            values[entry + ".payload.quoterequestrejectmessage.fixedratepercentage8optional"] = (static_cast<std::uint64_t>(message->fixed_rate_percentage_8_optional.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->fixed_rate_percentage_8_optional.integer(), -8) : canonical::absent());
            values[entry + ".payload.quoterequestrejectmessage.daystosettlementoptional"] = (static_cast<std::uint16_t>(message->days_to_settlement_optional.get()) != 0x0FFFFU ? canonical::number(message->days_to_settlement_optional.get()) : canonical::absent());
        } else if (iterator.template_id == 501) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.positionmaintenancecancelrequestmessage";
            [[maybe_unused]] const auto* message = protocol::PositionMaintenanceCancelRequestMessage::parse(iterator.message);
            values[entry + ".payload.positionmaintenancecancelrequestmessage.inboundbusinessheader.sessionid"] = canonical::number(message->inbound_business_header.session_id.get());
            values[entry + ".payload.positionmaintenancecancelrequestmessage.inboundbusinessheader.msgseqnum"] = canonical::number(message->inbound_business_header.msg_seq_num.get());
            values[entry + ".payload.positionmaintenancecancelrequestmessage.inboundbusinessheader.sendingtime"] = (static_cast<std::uint64_t>(message->inbound_business_header.sending_time.get()) != 0x0ULL ? canonical::number(message->inbound_business_header.sending_time.get()) : canonical::absent());
            values[entry + ".payload.positionmaintenancecancelrequestmessage.inboundbusinessheader.marketsegmentid"] = canonical::number(message->inbound_business_header.market_segment_id.get());
            values[entry + ".payload.positionmaintenancecancelrequestmessage.inboundbusinessheader.padding"] = canonical::text(canonical::character(message->inbound_business_header.padding.get()));
            values[entry + ".payload.positionmaintenancecancelrequestmessage.posreqid"] = canonical::number(message->pos_req_id.get());
            values[entry + ".payload.positionmaintenancecancelrequestmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.positionmaintenancecancelrequestmessage.origposreqrefid"] = (static_cast<std::uint64_t>(message->orig_pos_req_ref_id.get()) != 0x0ULL ? canonical::number(message->orig_pos_req_ref_id.get()) : canonical::absent());
            values[entry + ".payload.positionmaintenancecancelrequestmessage.posmaintrptrefid"] = (static_cast<std::uint64_t>(message->pos_maint_rpt_ref_id.get()) != 0x0ULL ? canonical::number(message->pos_maint_rpt_ref_id.get()) : canonical::absent());
            values[entry + ".payload.positionmaintenancecancelrequestmessage.senderlocation"] = canonical::text(std::string(message->sender_location.get()), '\0', false);
            values[entry + ".payload.positionmaintenancecancelrequestmessage.enteringtrader"] = canonical::text(std::string(message->entering_trader.get()), '\0', false);
        } else if (iterator.template_id == 502) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.positionmaintenancerequestmessage";
            [[maybe_unused]] const auto* message = protocol::PositionMaintenanceRequestMessage::parse(iterator.message);
            values[entry + ".payload.positionmaintenancerequestmessage.inboundbusinessheader.sessionid"] = canonical::number(message->inbound_business_header.session_id.get());
            values[entry + ".payload.positionmaintenancerequestmessage.inboundbusinessheader.msgseqnum"] = canonical::number(message->inbound_business_header.msg_seq_num.get());
            values[entry + ".payload.positionmaintenancerequestmessage.inboundbusinessheader.sendingtime"] = (static_cast<std::uint64_t>(message->inbound_business_header.sending_time.get()) != 0x0ULL ? canonical::number(message->inbound_business_header.sending_time.get()) : canonical::absent());
            values[entry + ".payload.positionmaintenancerequestmessage.inboundbusinessheader.marketsegmentid"] = canonical::number(message->inbound_business_header.market_segment_id.get());
            values[entry + ".payload.positionmaintenancerequestmessage.inboundbusinessheader.padding"] = canonical::text(canonical::character(message->inbound_business_header.padding.get()));
            values[entry + ".payload.positionmaintenancerequestmessage.posreqid"] = canonical::number(message->pos_req_id.get());
            values[entry + ".payload.positionmaintenancerequestmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.positionmaintenancerequestmessage.thresholdamount"] = (static_cast<std::uint64_t>(message->threshold_amount.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->threshold_amount.integer(), -4) : canonical::absent());
            values[entry + ".payload.positionmaintenancerequestmessage.account"] = (static_cast<std::uint32_t>(message->account.get()) != 0x0U ? canonical::number(message->account.get()) : canonical::absent());
            values[entry + ".payload.positionmaintenancerequestmessage.senderlocation"] = canonical::text(std::string(message->sender_location.get()), '\0', false);
            values[entry + ".payload.positionmaintenancerequestmessage.postranstype"] = canonical::number(message->pos_trans_type.get());
            values[entry + ".payload.positionmaintenancerequestmessage.clearingbusinessdate"] = canonical::number(message->clearing_business_date.get());
            values[entry + ".payload.positionmaintenancerequestmessage.contraryinstructionindicator"] = canonical::number(message->contrary_instruction_indicator.get());
            values[entry + ".payload.positionmaintenancerequestmessage.enteringtrader"] = canonical::text(std::string(message->entering_trader.get()), '\0', false);
            values[entry + ".payload.positionmaintenancerequestmessage.longqty"] = canonical::number(message->long_qty.get());
        } else if (iterator.template_id == 503) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.positionmaintenancereportmessage";
            [[maybe_unused]] const auto* message = protocol::PositionMaintenanceReportMessage::parse(iterator.message);
            values[entry + ".payload.positionmaintenancereportmessage.outboundbusinessheader.sessionid"] = canonical::number(message->outbound_business_header.session_id.get());
            values[entry + ".payload.positionmaintenancereportmessage.outboundbusinessheader.msgseqnum"] = canonical::number(message->outbound_business_header.msg_seq_num.get());
            values[entry + ".payload.positionmaintenancereportmessage.outboundbusinessheader.sendingtime"] = (static_cast<std::uint64_t>(message->outbound_business_header.sending_time.get()) != 0x0ULL ? canonical::number(message->outbound_business_header.sending_time.get()) : canonical::absent());
            values[entry + ".payload.positionmaintenancereportmessage.outboundbusinessheader.eventindicator"] = canonical::number(message->outbound_business_header.event_indicator.get());
            values[entry + ".payload.positionmaintenancereportmessage.outboundbusinessheader.marketsegmentidoptional"] = canonical::number(message->outbound_business_header.market_segment_id_optional.get());
            values[entry + ".payload.positionmaintenancereportmessage.posreqidoptional"] = (static_cast<std::uint64_t>(message->pos_req_id_optional.get()) != 0x0ULL ? canonical::number(message->pos_req_id_optional.get()) : canonical::absent());
            values[entry + ".payload.positionmaintenancereportmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.positionmaintenancereportmessage.posmaintrptid"] = canonical::number(message->pos_maint_rpt_id.get());
            values[entry + ".payload.positionmaintenancereportmessage.postranstype"] = canonical::number(message->pos_trans_type.get());
            values[entry + ".payload.positionmaintenancereportmessage.posmaintaction"] = canonical::text(canonical::character(message->pos_maint_action.get()));
            values[entry + ".payload.positionmaintenancereportmessage.posmaintstatus"] = canonical::text(canonical::character(message->pos_maint_status.get()));
            values[entry + ".payload.positionmaintenancereportmessage.tradeidoptional"] = (static_cast<std::uint32_t>(message->trade_id_optional.get()) != 0x0U ? canonical::number(message->trade_id_optional.get()) : canonical::absent());
            values[entry + ".payload.positionmaintenancereportmessage.origposreqrefid"] = (static_cast<std::uint64_t>(message->orig_pos_req_ref_id.get()) != 0x0ULL ? canonical::number(message->orig_pos_req_ref_id.get()) : canonical::absent());
            values[entry + ".payload.positionmaintenancereportmessage.accounttype"] = (static_cast<std::uint8_t>(message->account_type.get()) != 0x0U ? canonical::number(message->account_type.get()) : canonical::absent());
            values[entry + ".payload.positionmaintenancereportmessage.clearingbusinessdate"] = canonical::number(message->clearing_business_date.get());
            values[entry + ".payload.positionmaintenancereportmessage.thresholdamount"] = (static_cast<std::uint64_t>(message->threshold_amount.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->threshold_amount.integer(), -4) : canonical::absent());
            values[entry + ".payload.positionmaintenancereportmessage.transacttime"] = canonical::number(message->transact_time.get());
            values[entry + ".payload.positionmaintenancereportmessage.account"] = (static_cast<std::uint32_t>(message->account.get()) != 0x0U ? canonical::number(message->account.get()) : canonical::absent());
            values[entry + ".payload.positionmaintenancereportmessage.senderlocation"] = canonical::text(std::string(message->sender_location.get()), '\0', false);
            values[entry + ".payload.positionmaintenancereportmessage.posmaintresult"] = (static_cast<std::uint32_t>(message->pos_maint_result.get()) != 0x0U ? canonical::number(message->pos_maint_result.get()) : canonical::absent());
            values[entry + ".payload.positionmaintenancereportmessage.contraryinstructionindicator"] = canonical::number(message->contrary_instruction_indicator.get());
        } else if (iterator.template_id == 601) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.allocationinstructionmessage";
            [[maybe_unused]] const auto* message = protocol::AllocationInstructionMessage::parse(iterator.message);
            values[entry + ".payload.allocationinstructionmessage.inboundbusinessheader.sessionid"] = canonical::number(message->inbound_business_header.session_id.get());
            values[entry + ".payload.allocationinstructionmessage.inboundbusinessheader.msgseqnum"] = canonical::number(message->inbound_business_header.msg_seq_num.get());
            values[entry + ".payload.allocationinstructionmessage.inboundbusinessheader.sendingtime"] = (static_cast<std::uint64_t>(message->inbound_business_header.sending_time.get()) != 0x0ULL ? canonical::number(message->inbound_business_header.sending_time.get()) : canonical::absent());
            values[entry + ".payload.allocationinstructionmessage.inboundbusinessheader.marketsegmentid"] = canonical::number(message->inbound_business_header.market_segment_id.get());
            values[entry + ".payload.allocationinstructionmessage.inboundbusinessheader.padding"] = canonical::text(canonical::character(message->inbound_business_header.padding.get()));
            values[entry + ".payload.allocationinstructionmessage.allocid"] = canonical::number(message->alloc_id.get());
            values[entry + ".payload.allocationinstructionmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.allocationinstructionmessage.alloctranstype"] = canonical::text(canonical::character(message->alloc_trans_type.get()));
            values[entry + ".payload.allocationinstructionmessage.alloctype"] = canonical::text(canonical::character(message->alloc_type.get()));
            values[entry + ".payload.allocationinstructionmessage.allocnoorderstype"] = canonical::text(canonical::character(message->alloc_no_orders_type.get()));
            values[entry + ".payload.allocationinstructionmessage.quantity"] = canonical::number(message->quantity.get());
            values[entry + ".payload.allocationinstructionmessage.senderlocation"] = canonical::text(std::string(message->sender_location.get()), '\0', false);
            values[entry + ".payload.allocationinstructionmessage.enteringtrader"] = canonical::text(std::string(message->entering_trader.get()), '\0', false);
            values[entry + ".payload.allocationinstructionmessage.tradeid"] = canonical::number(message->trade_id.get());
            values[entry + ".payload.allocationinstructionmessage.tradedateoptional"] = (static_cast<std::uint16_t>(message->trade_date_optional.get()) != 0x0U ? canonical::number(message->trade_date_optional.get()) : canonical::absent());
            values[entry + ".payload.allocationinstructionmessage.individualallocid"] = canonical::number(message->individual_alloc_id.get());
            values[entry + ".payload.allocationinstructionmessage.allocaccount"] = canonical::number(message->alloc_account.get());
            values[entry + ".payload.allocationinstructionmessage.allocqty"] = canonical::number(message->alloc_qty.get());
        } else if (iterator.template_id == 602) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.allocationreportmessage";
            [[maybe_unused]] const auto* message = protocol::AllocationReportMessage::parse(iterator.message);
            values[entry + ".payload.allocationreportmessage.outboundbusinessheader.sessionid"] = canonical::number(message->outbound_business_header.session_id.get());
            values[entry + ".payload.allocationreportmessage.outboundbusinessheader.msgseqnum"] = canonical::number(message->outbound_business_header.msg_seq_num.get());
            values[entry + ".payload.allocationreportmessage.outboundbusinessheader.sendingtime"] = (static_cast<std::uint64_t>(message->outbound_business_header.sending_time.get()) != 0x0ULL ? canonical::number(message->outbound_business_header.sending_time.get()) : canonical::absent());
            values[entry + ".payload.allocationreportmessage.outboundbusinessheader.eventindicator"] = canonical::number(message->outbound_business_header.event_indicator.get());
            values[entry + ".payload.allocationreportmessage.outboundbusinessheader.marketsegmentidoptional"] = canonical::number(message->outbound_business_header.market_segment_id_optional.get());
            values[entry + ".payload.allocationreportmessage.allocid"] = canonical::number(message->alloc_id.get());
            values[entry + ".payload.allocationreportmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.allocationreportmessage.allocreportid"] = canonical::number(message->alloc_report_id.get());
            values[entry + ".payload.allocationreportmessage.alloctranstype"] = canonical::text(canonical::character(message->alloc_trans_type.get()));
            values[entry + ".payload.allocationreportmessage.allocreporttype"] = canonical::text(canonical::character(message->alloc_report_type.get()));
            values[entry + ".payload.allocationreportmessage.allocnoorderstype"] = canonical::text(canonical::character(message->alloc_no_orders_type.get()));
            values[entry + ".payload.allocationreportmessage.allocrejcode"] = (static_cast<std::uint32_t>(message->alloc_rej_code.get()) != 0x0U ? canonical::number(message->alloc_rej_code.get()) : canonical::absent());
            values[entry + ".payload.allocationreportmessage.quantity"] = canonical::number(message->quantity.get());
            values[entry + ".payload.allocationreportmessage.allocstatus"] = canonical::text(canonical::character(message->alloc_status.get()));
            values[entry + ".payload.allocationreportmessage.tradedateoptional"] = (static_cast<std::uint16_t>(message->trade_date_optional.get()) != 0x0U ? canonical::number(message->trade_date_optional.get()) : canonical::absent());
            values[entry + ".payload.allocationreportmessage.transacttime"] = canonical::number(message->transact_time.get());
            values[entry + ".payload.allocationreportmessage.side"] = canonical::text(canonical::character(message->side.get()));
            values[entry + ".payload.allocationreportmessage.senderlocation"] = canonical::text(std::string(message->sender_location.get()), '\0', false);
            values[entry + ".payload.allocationreportmessage.enteringtrader"] = canonical::text(std::string(message->entering_trader.get()), '\0', false);
        } else if (iterator.template_id == 701) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.ordermassactionrequestmessage";
            [[maybe_unused]] const auto* message = protocol::OrderMassActionRequestMessage::parse(iterator.message);
            values[entry + ".payload.ordermassactionrequestmessage.inboundbusinessheader.sessionid"] = canonical::number(message->inbound_business_header.session_id.get());
            values[entry + ".payload.ordermassactionrequestmessage.inboundbusinessheader.msgseqnum"] = canonical::number(message->inbound_business_header.msg_seq_num.get());
            values[entry + ".payload.ordermassactionrequestmessage.inboundbusinessheader.sendingtime"] = (static_cast<std::uint64_t>(message->inbound_business_header.sending_time.get()) != 0x0ULL ? canonical::number(message->inbound_business_header.sending_time.get()) : canonical::absent());
            values[entry + ".payload.ordermassactionrequestmessage.inboundbusinessheader.marketsegmentid"] = canonical::number(message->inbound_business_header.market_segment_id.get());
            values[entry + ".payload.ordermassactionrequestmessage.inboundbusinessheader.padding"] = canonical::text(canonical::character(message->inbound_business_header.padding.get()));
            values[entry + ".payload.ordermassactionrequestmessage.massactiontype"] = canonical::number(message->mass_action_type.get());
            values[entry + ".payload.ordermassactionrequestmessage.massactionscope"] = (static_cast<std::uint8_t>(message->mass_action_scope.get()) != 0x0U ? canonical::number(message->mass_action_scope.get()) : canonical::absent());
            values[entry + ".payload.ordermassactionrequestmessage.clordid"] = canonical::number(message->clordid.get());
            values[entry + ".payload.ordermassactionrequestmessage.masscancelrestatementreason"] = (static_cast<std::uint8_t>(message->mass_cancel_restatement_reason.get()) != 0x0U ? canonical::number(message->mass_cancel_restatement_reason.get()) : canonical::absent());
            values[entry + ".payload.ordermassactionrequestmessage.ordtagid"] = (static_cast<std::uint8_t>(message->ordtagid.get()) != 0x0U ? canonical::number(message->ordtagid.get()) : canonical::absent());
            values[entry + ".payload.ordermassactionrequestmessage.securityidoptional"] = (static_cast<std::uint64_t>(message->security_id_optional.get()) != 0x0ULL ? canonical::number(message->security_id_optional.get()) : canonical::absent());
            values[entry + ".payload.ordermassactionrequestmessage.investorid.prefix"] = canonical::number(message->investor_id.prefix.get());
            values[entry + ".payload.ordermassactionrequestmessage.investorid.document"] = canonical::number(message->investor_id.document.get());
        } else if (iterator.template_id == 702) {
            values[entry + ".payload"] = "packet.simpleopenframe.payload.ordermassactionreportmessage";
            [[maybe_unused]] const auto* message = protocol::OrderMassActionReportMessage::parse(iterator.message);
            values[entry + ".payload.ordermassactionreportmessage.outboundbusinessheader.sessionid"] = canonical::number(message->outbound_business_header.session_id.get());
            values[entry + ".payload.ordermassactionreportmessage.outboundbusinessheader.msgseqnum"] = canonical::number(message->outbound_business_header.msg_seq_num.get());
            values[entry + ".payload.ordermassactionreportmessage.outboundbusinessheader.sendingtime"] = (static_cast<std::uint64_t>(message->outbound_business_header.sending_time.get()) != 0x0ULL ? canonical::number(message->outbound_business_header.sending_time.get()) : canonical::absent());
            values[entry + ".payload.ordermassactionreportmessage.outboundbusinessheader.eventindicator"] = canonical::number(message->outbound_business_header.event_indicator.get());
            values[entry + ".payload.ordermassactionreportmessage.outboundbusinessheader.marketsegmentidoptional"] = canonical::number(message->outbound_business_header.market_segment_id_optional.get());
            values[entry + ".payload.ordermassactionreportmessage.massactiontype"] = canonical::number(message->mass_action_type.get());
            values[entry + ".payload.ordermassactionreportmessage.massactionscope"] = (static_cast<std::uint8_t>(message->mass_action_scope.get()) != 0x0U ? canonical::number(message->mass_action_scope.get()) : canonical::absent());
            values[entry + ".payload.ordermassactionreportmessage.clordid"] = canonical::number(message->clordid.get());
            values[entry + ".payload.ordermassactionreportmessage.massactionreportid"] = canonical::number(message->mass_action_report_id.get());
            values[entry + ".payload.ordermassactionreportmessage.transacttime"] = canonical::number(message->transact_time.get());
            values[entry + ".payload.ordermassactionreportmessage.massactionresponse"] = canonical::text(canonical::character(message->mass_action_response.get()));
            values[entry + ".payload.ordermassactionreportmessage.massactionrejectreason"] = (static_cast<std::uint8_t>(message->mass_action_reject_reason.get()) != 0x0FFU ? canonical::number(message->mass_action_reject_reason.get()) : canonical::absent());
            values[entry + ".payload.ordermassactionreportmessage.masscancelrestatementreason"] = (static_cast<std::uint8_t>(message->mass_cancel_restatement_reason.get()) != 0x0U ? canonical::number(message->mass_cancel_restatement_reason.get()) : canonical::absent());
            values[entry + ".payload.ordermassactionreportmessage.ordtagid"] = (static_cast<std::uint8_t>(message->ordtagid.get()) != 0x0U ? canonical::number(message->ordtagid.get()) : canonical::absent());
            values[entry + ".payload.ordermassactionreportmessage.securityidoptional"] = (static_cast<std::uint64_t>(message->security_id_optional.get()) != 0x0ULL ? canonical::number(message->security_id_optional.get()) : canonical::absent());
            values[entry + ".payload.ordermassactionreportmessage.investorid.prefix"] = canonical::number(message->investor_id.prefix.get());
            values[entry + ".payload.ordermassactionreportmessage.investorid.document"] = canonical::number(message->investor_id.document.get());
        }
    }

    return values;
}

// Reassemble each side of a sample's connections, read each side with Modern and hold it to the model's values
int check(const char* name, const char* capture, const char* expected) {
    const char* packets = std::getenv("OMI_PACKETS_DIR");

    if (packets == nullptr) {
        std::printf("FAIL: OMI_PACKETS_DIR is not set\n");
        return 1;
    }

    const auto model = canonical::load(canonical::root() + "/" + expected);

    std::vector<packet::TcpFlowKey> order;
    std::unordered_map<packet::TcpFlowKey, std::vector<std::byte>, packet::TcpFlowKey::hash> sides;
    packet::TcpReassembler reassembler;
    bool dialled = false;
    std::uint32_t client_ip = 0;
    std::uint16_t client_port = 0;

    reassembler.on_data = [&](const packet::TcpFlowKey& key, const std::byte* data, std::size_t length) {
        auto& side = sides[key];
        side.insert(side.end(), data, data + length);
    };

    std::vector<std::pair<std::string, std::int64_t>> sources;
    sources.emplace_back(std::string{packets} + "/" + capture, 0);
    packet::PcapIterator captures(sources);

    while (captures.advance()) {
        const packet::Frame frame(captures.data(), captures.length());

        if (!frame.valid() || !frame.is_tcp()) { continue; }

        const packet::TcpFlowKey key{ frame.src_ip, frame.dst_ip, frame.src_port, frame.dst_port };

        if (sides.find(key) == sides.end()) {
            sides[key];
            order.push_back(key);
        }

        if (!dialled && (frame.tcp_flags & 0x02) != 0 && (frame.tcp_flags & 0x10) == 0) {
            dialled = true;
            client_ip = frame.src_ip;
            client_port = frame.src_port;
        }

        reassembler.process(frame);
    }

    std::size_t stream = 0;
    std::size_t read_values = 0;
    int differences = 0;

    for (const auto& key : order) {
        [[maybe_unused]] const bool from_client = dialled && key.src_ip == client_ip && key.src_port == client_port;
        [[maybe_unused]] const bool to_client = dialled && key.dst_ip == client_ip && key.dst_port == client_port;

        if (!(true)) { continue; }

        if (stream >= model.size()) {
            std::printf("FAIL %s: more streams than the model read\n", name);
            return 1;
        }

        const auto& bytes = sides[key];
        const auto values = read(bytes.data(), bytes.size());

        if (values.empty() && !model[stream].empty()) {
            std::printf("FAIL %s: no value read from stream %zu, %zu bytes\n", name, stream, bytes.size());
            return 1;
        }

        read_values += values.size();
        differences += canonical::compare(name, stream, model[stream], values);
        ++stream;
    }

    if (stream != model.size()) {
        std::printf("FAIL %s: %zu streams, the model read %zu\n", name, stream, model.size());
        return 1;
    }

    if (differences == 0) {
        std::printf("ok   %s: %zu values of %zu streams\n", name, read_values, stream);
    }

    return differences == 0 ? 0 : 1;
}

}

int main() {
    std::printf("== B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.3 (modern 'packet' values)\n");
    int failures = 0;
    failures += check("BusinessMessageRejectMessage", "B3/B3Derivatives.BinaryEntryPoint.Sbe.v8.3/BusinessMessageRejectMessage.pcap", "b3/b3derivatives/binaryentrypoint/sbe/v8.3/packet/BusinessMessageRejectMessage.values");
    failures += check("EstablishAckMessage", "B3/B3Derivatives.BinaryEntryPoint.Sbe.v8.3/EstablishAckMessage.pcap", "b3/b3derivatives/binaryentrypoint/sbe/v8.3/packet/EstablishAckMessage.values");
    failures += check("EstablishMessage", "B3/B3Derivatives.BinaryEntryPoint.Sbe.v8.3/EstablishMessage.pcap", "b3/b3derivatives/binaryentrypoint/sbe/v8.3/packet/EstablishMessage.values");
    failures += check("EstablishRejectMessage", "B3/B3Derivatives.BinaryEntryPoint.Sbe.v8.3/EstablishRejectMessage.pcap", "b3/b3derivatives/binaryentrypoint/sbe/v8.3/packet/EstablishRejectMessage.values");
    failures += check("ExecutionReportCancelMessage", "B3/B3Derivatives.BinaryEntryPoint.Sbe.v8.3/ExecutionReportCancelMessage.pcap", "b3/b3derivatives/binaryentrypoint/sbe/v8.3/packet/ExecutionReportCancelMessage.values");
    failures += check("ExecutionReportRejectMessage", "B3/B3Derivatives.BinaryEntryPoint.Sbe.v8.3/ExecutionReportRejectMessage.pcap", "b3/b3derivatives/binaryentrypoint/sbe/v8.3/packet/ExecutionReportRejectMessage.values");
    failures += check("NegotiateMessage", "B3/B3Derivatives.BinaryEntryPoint.Sbe.v8.3/NegotiateMessage.pcap", "b3/b3derivatives/binaryentrypoint/sbe/v8.3/packet/NegotiateMessage.values");
    failures += check("NegotiateRejectMessage", "B3/B3Derivatives.BinaryEntryPoint.Sbe.v8.3/NegotiateRejectMessage.pcap", "b3/b3derivatives/binaryentrypoint/sbe/v8.3/packet/NegotiateRejectMessage.values");
    failures += check("NewOrderCrossMessage", "B3/B3Derivatives.BinaryEntryPoint.Sbe.v8.3/NewOrderCrossMessage.pcap", "b3/b3derivatives/binaryentrypoint/sbe/v8.3/packet/NewOrderCrossMessage.values");
    failures += check("NewOrderSingleMessage", "B3/B3Derivatives.BinaryEntryPoint.Sbe.v8.3/NewOrderSingleMessage.pcap", "b3/b3derivatives/binaryentrypoint/sbe/v8.3/packet/NewOrderSingleMessage.values");
    failures += check("OrderCancelRequestMessage", "B3/B3Derivatives.BinaryEntryPoint.Sbe.v8.3/OrderCancelRequestMessage.pcap", "b3/b3derivatives/binaryentrypoint/sbe/v8.3/packet/OrderCancelRequestMessage.values");
    failures += check("RetransmissionMessage", "B3/B3Derivatives.BinaryEntryPoint.Sbe.v8.3/RetransmissionMessage.pcap", "b3/b3derivatives/binaryentrypoint/sbe/v8.3/packet/RetransmissionMessage.values");
    failures += check("RetransmitRejectMessage", "B3/B3Derivatives.BinaryEntryPoint.Sbe.v8.3/RetransmitRejectMessage.pcap", "b3/b3derivatives/binaryentrypoint/sbe/v8.3/packet/RetransmitRejectMessage.values");
    failures += check("RetransmitRequestMessage", "B3/B3Derivatives.BinaryEntryPoint.Sbe.v8.3/RetransmitRequestMessage.pcap", "b3/b3derivatives/binaryentrypoint/sbe/v8.3/packet/RetransmitRequestMessage.values");
    failures += check("SequenceMessage", "B3/B3Derivatives.BinaryEntryPoint.Sbe.v8.3/SequenceMessage.pcap", "b3/b3derivatives/binaryentrypoint/sbe/v8.3/packet/SequenceMessage.values");
    failures += check("SimpleModifyOrderMessage", "B3/B3Derivatives.BinaryEntryPoint.Sbe.v8.3/SimpleModifyOrderMessage.pcap", "b3/b3derivatives/binaryentrypoint/sbe/v8.3/packet/SimpleModifyOrderMessage.values");
    failures += check("SimpleNewOrderMessage", "B3/B3Derivatives.BinaryEntryPoint.Sbe.v8.3/SimpleNewOrderMessage.pcap", "b3/b3derivatives/binaryentrypoint/sbe/v8.3/packet/SimpleNewOrderMessage.values");
    failures += check("TerminateMessage", "B3/B3Derivatives.BinaryEntryPoint.Sbe.v8.3/TerminateMessage.pcap", "b3/b3derivatives/binaryentrypoint/sbe/v8.3/packet/TerminateMessage.values");
    return failures == 0 ? 0 : 1;
}
