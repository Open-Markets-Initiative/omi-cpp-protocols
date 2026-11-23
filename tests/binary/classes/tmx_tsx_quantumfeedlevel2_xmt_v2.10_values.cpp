// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10 canonical values, through the Classes Packet: every value Classes decodes from
// each sample, at its address, held to what the model reads.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "tests/canonical/Canonical.hpp"
#include "cpp/binary/classes/tmx/tsx/quantumfeedlevel2/xmt/v2.10/definitions.hpp"

namespace protocol = ::tmx::tsx::quantumfeedlevel2::xmt::v2_10;

namespace {

// The values the Classes Packet decodes from one datagram, by indexed address. A datagram it cannot
// decode is a value the model never reads, so it fails rather than passing with nothing compared.
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::Packet packet;

    try {
        packet.decode(frame.payload, frame.payload_len);
    } catch (const protocol::DecodeError& error) {
        values["(does not decode)"] = error.what();
        return values;
    }

    values["packet.frameheader.startofframe"] = canonical::number(packet.frame_header().start_of_frame());
    values["packet.frameheader.protocolname"] = canonical::text(canonical::character(packet.frame_header().protocol_name()));
    values["packet.frameheader.protocolversion"] = canonical::numeric(canonical::character(packet.frame_header().protocol_version()));
    values["packet.frameheader.messagelength"] = canonical::number(packet.frame_header().message_length());
    values["packet.frameheader.sessionid"] = canonical::number(packet.frame_header().session_id());
    values["packet.frameheader.ackrequiredpossdup"] = canonical::text(canonical::character(packet.frame_header().ack_required_poss_dup()));
    values["packet.frameheader.numbody"] = canonical::number(packet.frame_header().num_body());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        const std::string entry = "packet.packetbody.businessbodies.body[" + std::to_string(index++) + "]";
        values[entry + ".bodyheader.msglength"] = canonical::number(each.body_header().msg_length());
        values[entry + ".bodyheader.msgtype"] = canonical::text(canonical::character(each.body_header().msg_type()));
        values[entry + ".bodymessage.businessheader.msgversion"] = canonical::number(each.business_header().msg_version());
        values[entry + ".bodymessage.businessheader.sourceid"] = canonical::text(canonical::character(each.business_header().source_id()));
        values[entry + ".bodymessage.businessheader.streamid"] = canonical::number(each.business_header().stream_id());
        values[entry + ".bodymessage.businessheader.sequence0"] = canonical::number(each.business_header().sequence_0());
        values[entry + ".bodymessage.businessheader.sequence1"] = canonical::number(each.business_header().sequence_1());

        if (const auto* message = dynamic_cast<const protocol::SymbolStatusMessage*>(each.message())) {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.symbolstatusmessage";
            values[entry + ".bodymessage.businessmessage.symbolstatusmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".bodymessage.businessmessage.symbolstatusmessage.stockgroup"] = ((*message).stock_group().has_value() ? canonical::number((*(*message).stock_group())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.symbolstatusmessage.cusip"] = canonical::text(std::string((*message).cusip()), ' ', false);
            values[entry + ".bodymessage.businessmessage.symbolstatusmessage.boardlot"] = ((*message).board_lot().has_value() ? canonical::number((*(*message).board_lot())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.symbolstatusmessage.currency"] = canonical::text(canonical::character((*message).currency()), ' ', false);
            values[entry + ".bodymessage.businessmessage.symbolstatusmessage.facevalue"] = ((*message).face_value().has_value() ? canonical::scaled((*(*message).face_value()).mantissa(), (*(*message).face_value()).exponent()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.symbolstatusmessage.lastsale"] = ((*message).last_sale().has_value() ? canonical::scaled((*(*message).last_sale()).mantissa(), (*(*message).last_sale()).exponent()) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::OrderBookMessage*>(each.message())) {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.orderbookmessage";
            values[entry + ".bodymessage.businessmessage.orderbookmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderbookmessage.brokernumber"] = ((*message).broker_number().has_value() ? canonical::number((*(*message).broker_number())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookmessage.orderside"] = canonical::text(canonical::character((*message).order_side()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderbookmessage.orderid"] = ((*message).order_id().has_value() ? canonical::number((*(*message).order_id())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookmessage.price"] = ((*message).price().has_value() ? canonical::scaled((*(*message).price()).mantissa(), (*(*message).price()).exponent()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookmessage.volume"] = ((*message).volume().has_value() ? canonical::number((*(*message).volume())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookmessage.prioritytimestamp"] = ((*message).priority_time_stamp().has_value() ? canonical::number((*(*message).priority_time_stamp())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::OrderBookTermsMessage*>(each.message())) {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.orderbooktermsmessage";
            values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.brokernumber"] = ((*message).broker_number().has_value() ? canonical::number((*(*message).broker_number())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.orderside"] = canonical::text(canonical::character((*message).order_side()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.orderid"] = ((*message).order_id().has_value() ? canonical::number((*(*message).order_id())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.price"] = ((*message).price().has_value() ? canonical::scaled((*(*message).price()).mantissa(), (*(*message).price()).exponent()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.volume"] = ((*message).volume().has_value() ? canonical::number((*(*message).volume())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.nonresident"] = canonical::text(canonical::character((*message).non_resident()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.settlementterms"] = canonical::text(canonical::character((*message).settlement_terms()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.settlementdate"] = ((*message).settlement_date().has_value() ? canonical::number((*(*message).settlement_date())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.prioritytimestamp"] = ((*message).priority_time_stamp().has_value() ? canonical::number((*(*message).priority_time_stamp())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::AssignCopOrdersMessage*>(each.message())) {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.assigncopordersmessage";
            values[entry + ".bodymessage.businessmessage.assigncopordersmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".bodymessage.businessmessage.assigncopordersmessage.calculatedopeningprice"] = ((*message).calculated_opening_price().has_value() ? canonical::scaled((*(*message).calculated_opening_price()).mantissa(), (*(*message).calculated_opening_price()).exponent()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.assigncopordersmessage.orderside"] = canonical::text(canonical::character((*message).order_side()), ' ', false);
            for (std::size_t cop_order_index = 0; const auto& cop_order_entry : (*message).cop_order()) {
                const std::string cop_order_at = std::string{entry + ".bodymessage.businessmessage.assigncopordersmessage.coporder"} + "[" + std::to_string(cop_order_index++) + "]";
                values[cop_order_at + ".brokernumber"] = (cop_order_entry.broker_number().has_value() ? canonical::number((*cop_order_entry.broker_number())) : canonical::absent());
                values[cop_order_at + ".orderid"] = (cop_order_entry.order_id().has_value() ? canonical::number((*cop_order_entry.order_id())) : canonical::absent());
            }
            values[entry + ".bodymessage.businessmessage.assigncopordersmessage.tradingsystemtimestamp"] = ((*message).trading_system_time_stamp().has_value() ? canonical::number((*(*message).trading_system_time_stamp())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::AssignCopNoOrdersMessage*>(each.message())) {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.assigncopnoordersmessage";
            values[entry + ".bodymessage.businessmessage.assigncopnoordersmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".bodymessage.businessmessage.assigncopnoordersmessage.calculatedopeningprice"] = ((*message).calculated_opening_price().has_value() ? canonical::scaled((*(*message).calculated_opening_price()).mantissa(), (*(*message).calculated_opening_price()).exponent()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.assigncopnoordersmessage.tradingsystemtimestamp"] = ((*message).trading_system_time_stamp().has_value() ? canonical::number((*(*message).trading_system_time_stamp())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::AssignLimitMessage*>(each.message())) {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.assignlimitmessage";
            values[entry + ".bodymessage.businessmessage.assignlimitmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".bodymessage.businessmessage.assignlimitmessage.calculatedopeningprice"] = ((*message).calculated_opening_price().has_value() ? canonical::scaled((*(*message).calculated_opening_price()).mantissa(), (*(*message).calculated_opening_price()).exponent()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.assignlimitmessage.orderside"] = canonical::text(canonical::character((*message).order_side()), ' ', false);
            for (std::size_t cop_limit_index = 0; const auto& cop_limit_entry : (*message).cop_limit()) {
                const std::string cop_limit_at = std::string{entry + ".bodymessage.businessmessage.assignlimitmessage.coplimit"} + "[" + std::to_string(cop_limit_index++) + "]";
                values[cop_limit_at + ".brokernumber"] = (cop_limit_entry.broker_number().has_value() ? canonical::number((*cop_limit_entry.broker_number())) : canonical::absent());
                values[cop_limit_at + ".orderid"] = (cop_limit_entry.order_id().has_value() ? canonical::number((*cop_limit_entry.order_id())) : canonical::absent());
                values[cop_limit_at + ".price"] = (cop_limit_entry.price().has_value() ? canonical::scaled((*cop_limit_entry.price()).mantissa(), (*cop_limit_entry.price()).exponent()) : canonical::absent());
            }
            values[entry + ".bodymessage.businessmessage.assignlimitmessage.tradingsystemtimestamp"] = ((*message).trading_system_time_stamp().has_value() ? canonical::number((*(*message).trading_system_time_stamp())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::MarketStateUpdateMessage*>(each.message())) {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.marketstateupdatemessage";
            values[entry + ".bodymessage.businessmessage.marketstateupdatemessage.marketstate"] = canonical::text(canonical::character((*message).market_state()), ' ', false);
            values[entry + ".bodymessage.businessmessage.marketstateupdatemessage.stockgroup"] = ((*message).stock_group().has_value() ? canonical::number((*(*message).stock_group())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.marketstateupdatemessage.tradingsystemtimestamp"] = ((*message).trading_system_time_stamp().has_value() ? canonical::number((*(*message).trading_system_time_stamp())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::MocImbalanceMessage*>(each.message())) {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.mocimbalancemessage";
            values[entry + ".bodymessage.businessmessage.mocimbalancemessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".bodymessage.businessmessage.mocimbalancemessage.imbalanceside"] = canonical::text(canonical::character((*message).imbalance_side()), ' ', false, {std::string_view(" ", 1), std::string_view("", 0)});
            values[entry + ".bodymessage.businessmessage.mocimbalancemessage.imbalancevolume"] = ((*message).imbalance_volume().has_value() ? canonical::number((*(*message).imbalance_volume())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.mocimbalancemessage.tradingsystemtimestamp"] = ((*message).trading_system_time_stamp().has_value() ? canonical::number((*(*message).trading_system_time_stamp())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.mocimbalancemessage.imbalancereferenceprice"] = ((*message).imbalance_reference_price().has_value() ? canonical::scaled((*(*message).imbalance_reference_price()).mantissa(), (*(*message).imbalance_reference_price()).exponent()) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::OrderBookedMessage*>(each.message())) {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.orderbookedmessage";
            values[entry + ".bodymessage.businessmessage.orderbookedmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderbookedmessage.brokernumber"] = ((*message).broker_number().has_value() ? canonical::number((*(*message).broker_number())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookedmessage.orderside"] = canonical::text(canonical::character((*message).order_side()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderbookedmessage.orderid"] = ((*message).order_id().has_value() ? canonical::number((*(*message).order_id())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookedmessage.price"] = ((*message).price().has_value() ? canonical::scaled((*(*message).price()).mantissa(), (*(*message).price()).exponent()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookedmessage.volume"] = ((*message).volume().has_value() ? canonical::number((*(*message).volume())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookedmessage.prioritytimestamp"] = ((*message).priority_time_stamp().has_value() ? canonical::number((*(*message).priority_time_stamp())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookedmessage.tradingsystemtimestamp"] = ((*message).trading_system_time_stamp().has_value() ? canonical::number((*(*message).trading_system_time_stamp())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::OrderBookedTermsMessage*>(each.message())) {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.orderbookedtermsmessage";
            values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.brokernumber"] = ((*message).broker_number().has_value() ? canonical::number((*(*message).broker_number())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.orderside"] = canonical::text(canonical::character((*message).order_side()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.orderid"] = ((*message).order_id().has_value() ? canonical::number((*(*message).order_id())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.price"] = ((*message).price().has_value() ? canonical::scaled((*(*message).price()).mantissa(), (*(*message).price()).exponent()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.volume"] = ((*message).volume().has_value() ? canonical::number((*(*message).volume())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.nonresident"] = canonical::text(canonical::character((*message).non_resident()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.settlementterms"] = canonical::text(canonical::character((*message).settlement_terms()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.settlementdate"] = ((*message).settlement_date().has_value() ? canonical::number((*(*message).settlement_date())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.prioritytimestamp"] = ((*message).priority_time_stamp().has_value() ? canonical::number((*(*message).priority_time_stamp())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.tradingsystemtimestamp"] = ((*message).trading_system_time_stamp().has_value() ? canonical::number((*(*message).trading_system_time_stamp())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::OrderCancelledMessage*>(each.message())) {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.ordercancelledmessage";
            values[entry + ".bodymessage.businessmessage.ordercancelledmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".bodymessage.businessmessage.ordercancelledmessage.brokernumber"] = ((*message).broker_number().has_value() ? canonical::number((*(*message).broker_number())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.ordercancelledmessage.orderside"] = canonical::text(canonical::character((*message).order_side()), ' ', false);
            values[entry + ".bodymessage.businessmessage.ordercancelledmessage.orderid"] = ((*message).order_id().has_value() ? canonical::number((*(*message).order_id())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.ordercancelledmessage.tradingsystemtimestamp"] = ((*message).trading_system_time_stamp().has_value() ? canonical::number((*(*message).trading_system_time_stamp())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::OrderCancelledTermsMessage*>(each.message())) {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.ordercancelledtermsmessage";
            values[entry + ".bodymessage.businessmessage.ordercancelledtermsmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".bodymessage.businessmessage.ordercancelledtermsmessage.brokernumber"] = ((*message).broker_number().has_value() ? canonical::number((*(*message).broker_number())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.ordercancelledtermsmessage.orderside"] = canonical::text(canonical::character((*message).order_side()), ' ', false);
            values[entry + ".bodymessage.businessmessage.ordercancelledtermsmessage.orderid"] = ((*message).order_id().has_value() ? canonical::number((*(*message).order_id())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.ordercancelledtermsmessage.tradingsystemtimestamp"] = ((*message).trading_system_time_stamp().has_value() ? canonical::number((*(*message).trading_system_time_stamp())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::OrderPriceTimeAssignedMessage*>(each.message())) {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.orderpricetimeassignedmessage";
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedmessage.brokernumber"] = ((*message).broker_number().has_value() ? canonical::number((*(*message).broker_number())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedmessage.orderside"] = canonical::text(canonical::character((*message).order_side()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedmessage.orderid"] = ((*message).order_id().has_value() ? canonical::number((*(*message).order_id())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedmessage.price"] = ((*message).price().has_value() ? canonical::scaled((*(*message).price()).mantissa(), (*(*message).price()).exponent()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedmessage.volume"] = ((*message).volume().has_value() ? canonical::number((*(*message).volume())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedmessage.prioritytimestamp"] = ((*message).priority_time_stamp().has_value() ? canonical::number((*(*message).priority_time_stamp())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedmessage.tradingsystemtimestamp"] = ((*message).trading_system_time_stamp().has_value() ? canonical::number((*(*message).trading_system_time_stamp())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::OrderPriceTimeAssignedTermsMessage*>(each.message())) {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.orderpricetimeassignedtermsmessage";
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedtermsmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedtermsmessage.brokernumber"] = ((*message).broker_number().has_value() ? canonical::number((*(*message).broker_number())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedtermsmessage.orderside"] = canonical::text(canonical::character((*message).order_side()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedtermsmessage.orderid"] = ((*message).order_id().has_value() ? canonical::number((*(*message).order_id())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedtermsmessage.price"] = ((*message).price().has_value() ? canonical::scaled((*(*message).price()).mantissa(), (*(*message).price()).exponent()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedtermsmessage.volume"] = ((*message).volume().has_value() ? canonical::number((*(*message).volume())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedtermsmessage.prioritytimestamp"] = ((*message).priority_time_stamp().has_value() ? canonical::number((*(*message).priority_time_stamp())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedtermsmessage.tradingsystemtimestamp"] = ((*message).trading_system_time_stamp().has_value() ? canonical::number((*(*message).trading_system_time_stamp())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::StockStatusMessage*>(each.message())) {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.stockstatusmessage";
            values[entry + ".bodymessage.businessmessage.stockstatusmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".bodymessage.businessmessage.stockstatusmessage.comment"] = canonical::text(std::string((*message).comment()), ' ', false);
            values[entry + ".bodymessage.businessmessage.stockstatusmessage.stockstate"] = canonical::text(std::string((*message).stock_state()), ' ', false);
            values[entry + ".bodymessage.businessmessage.stockstatusmessage.tradingsystemtimestamp"] = ((*message).trading_system_time_stamp().has_value() ? canonical::number((*(*message).trading_system_time_stamp())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::TradeReportMessage*>(each.message())) {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.tradereportmessage";
            values[entry + ".bodymessage.businessmessage.tradereportmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradereportmessage.tradenumber"] = ((*message).trade_number().has_value() ? canonical::number((*(*message).trade_number())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereportmessage.price"] = ((*message).price().has_value() ? canonical::scaled((*(*message).price()).mantissa(), (*(*message).price()).exponent()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereportmessage.volume"] = ((*message).volume().has_value() ? canonical::number((*(*message).volume())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereportmessage.buybrokernumber"] = ((*message).buy_broker_number().has_value() ? canonical::number((*(*message).buy_broker_number())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereportmessage.buyorderid"] = ((*message).buy_order_id().has_value() ? canonical::number((*(*message).buy_order_id())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereportmessage.buydisplayvolume"] = ((*message).buy_display_volume().has_value() ? canonical::number((*(*message).buy_display_volume())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereportmessage.sellbrokernumber"] = ((*message).sell_broker_number().has_value() ? canonical::number((*(*message).sell_broker_number())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereportmessage.sellorderid"] = ((*message).sell_order_id().has_value() ? canonical::number((*(*message).sell_order_id())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereportmessage.selldisplayvolume"] = ((*message).sell_display_volume().has_value() ? canonical::number((*(*message).sell_display_volume())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereportmessage.bypass"] = canonical::text(canonical::character((*message).bypass()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradereportmessage.tradetimestamp"] = ((*message).trade_time_stamp().has_value() ? canonical::number((*(*message).trade_time_stamp())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereportmessage.crosstype"] = canonical::text(canonical::character((*message).cross_type()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradereportmessage.tradingsystemtimestamp"] = ((*message).trading_system_time_stamp().has_value() ? canonical::number((*(*message).trading_system_time_stamp())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::TradeReportTermsMessage*>(each.message())) {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.tradereporttermsmessage";
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.tradenumber"] = ((*message).trade_number().has_value() ? canonical::number((*(*message).trade_number())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.price"] = ((*message).price().has_value() ? canonical::scaled((*(*message).price()).mantissa(), (*(*message).price()).exponent()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.volume"] = ((*message).volume().has_value() ? canonical::number((*(*message).volume())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.buybrokernumber"] = ((*message).buy_broker_number().has_value() ? canonical::number((*(*message).buy_broker_number())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.buyorderid"] = ((*message).buy_order_id().has_value() ? canonical::number((*(*message).buy_order_id())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.buydisplayvolume"] = ((*message).buy_display_volume().has_value() ? canonical::number((*(*message).buy_display_volume())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.sellbrokernumber"] = ((*message).sell_broker_number().has_value() ? canonical::number((*(*message).sell_broker_number())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.sellorderid"] = ((*message).sell_order_id().has_value() ? canonical::number((*(*message).sell_order_id())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.selldisplayvolume"] = ((*message).sell_display_volume().has_value() ? canonical::number((*(*message).sell_display_volume())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.tradetimestamp"] = ((*message).trade_time_stamp().has_value() ? canonical::number((*(*message).trade_time_stamp())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.nonresident"] = canonical::text(canonical::character((*message).non_resident()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.settlementterms"] = canonical::text(canonical::character((*message).settlement_terms()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.settlementdate"] = ((*message).settlement_date().has_value() ? canonical::number((*(*message).settlement_date())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.crosstype"] = canonical::text(canonical::character((*message).cross_type()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.tradingsystemtimestamp"] = ((*message).trading_system_time_stamp().has_value() ? canonical::number((*(*message).trading_system_time_stamp())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::TradeCancelledMessage*>(each.message())) {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.tradecancelledmessage";
            values[entry + ".bodymessage.businessmessage.tradecancelledmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradecancelledmessage.tradenumber"] = ((*message).trade_number().has_value() ? canonical::number((*(*message).trade_number())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecancelledmessage.tradingsystemtimestamp"] = ((*message).trading_system_time_stamp().has_value() ? canonical::number((*(*message).trading_system_time_stamp())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::TradeCancelledTermsMessage*>(each.message())) {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.tradecancelledtermsmessage";
            values[entry + ".bodymessage.businessmessage.tradecancelledtermsmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradecancelledtermsmessage.tradenumber"] = ((*message).trade_number().has_value() ? canonical::number((*(*message).trade_number())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecancelledtermsmessage.tradingsystemtimestamp"] = ((*message).trading_system_time_stamp().has_value() ? canonical::number((*(*message).trading_system_time_stamp())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::TradeCorrectionMessage*>(each.message())) {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.tradecorrectionmessage";
            values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.tradenumber"] = ((*message).trade_number().has_value() ? canonical::number((*(*message).trade_number())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.price"] = ((*message).price().has_value() ? canonical::scaled((*(*message).price()).mantissa(), (*(*message).price()).exponent()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.volume"] = ((*message).volume().has_value() ? canonical::number((*(*message).volume())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.buybrokernumber"] = ((*message).buy_broker_number().has_value() ? canonical::number((*(*message).buy_broker_number())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.sellbrokernumber"] = ((*message).sell_broker_number().has_value() ? canonical::number((*(*message).sell_broker_number())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.initiatedby"] = canonical::text(canonical::character((*message).initiated_by()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.origtradenumber"] = ((*message).orig_trade_number().has_value() ? canonical::number((*(*message).orig_trade_number())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.bypass"] = canonical::text(canonical::character((*message).bypass()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.tradetimestamp"] = ((*message).trade_time_stamp().has_value() ? canonical::number((*(*message).trade_time_stamp())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.crosstype"] = canonical::text(canonical::character((*message).cross_type()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.tradingsystemtimestamp"] = ((*message).trading_system_time_stamp().has_value() ? canonical::number((*(*message).trading_system_time_stamp())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::TradeCorrectionTermsMessage*>(each.message())) {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.tradecorrectiontermsmessage";
            values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.tradenumber"] = ((*message).trade_number().has_value() ? canonical::number((*(*message).trade_number())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.price"] = ((*message).price().has_value() ? canonical::scaled((*(*message).price()).mantissa(), (*(*message).price()).exponent()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.volume"] = ((*message).volume().has_value() ? canonical::number((*(*message).volume())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.buybrokernumber"] = ((*message).buy_broker_number().has_value() ? canonical::number((*(*message).buy_broker_number())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.sellbrokernumber"] = ((*message).sell_broker_number().has_value() ? canonical::number((*(*message).sell_broker_number())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.initiatedby"] = canonical::text(canonical::character((*message).initiated_by()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.origtradenumber"] = ((*message).orig_trade_number().has_value() ? canonical::number((*(*message).orig_trade_number())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.tradetimestamp"] = ((*message).trade_time_stamp().has_value() ? canonical::number((*(*message).trade_time_stamp())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.nonresident"] = canonical::text(canonical::character((*message).non_resident()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.settlementterms"] = canonical::text(canonical::character((*message).settlement_terms()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.settlementdate"] = ((*message).settlement_date().has_value() ? canonical::number((*(*message).settlement_date())) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.crosstype"] = canonical::text(canonical::character((*message).cross_type()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.tradingsystemtimestamp"] = ((*message).trading_system_time_stamp().has_value() ? canonical::number((*(*message).trading_system_time_stamp())) : canonical::absent());
        }
    }

    return values;
}

// Read each datagram of a sample with Classes and hold it to the model's values
int check(const char* name, const char* capture, const char* expected) {
    const char* packets = std::getenv("OMI_PACKETS_DIR");

    if (packets == nullptr) {
        std::printf("FAIL: OMI_PACKETS_DIR is not set\n");
        return 1;
    }

    const auto model = canonical::load(canonical::root() + "/" + expected);
    std::vector<std::pair<std::string, std::int64_t>> sources;
    sources.emplace_back(std::string{packets} + "/" + capture, 0);

    packet::PcapIterator captures(sources);
    std::size_t datagram = 0;
    int differences = 0;

    while (captures.advance()) {
        const packet::Frame frame(captures.data(), captures.length());

        if (!frame.valid() || !frame.is_udp()) { continue; }

        if (datagram >= model.size()) {
            std::printf("FAIL %s: more datagrams than the model read\n", name);
            return 1;
        }

        differences += canonical::compare(name, datagram, model[datagram], read(frame));
        ++datagram;
    }

    if (datagram != model.size()) {
        std::printf("FAIL %s: %zu datagrams, the model read %zu\n", name, datagram, model.size());
        return 1;
    }

    if (differences == 0) {
        std::printf("ok   %s: %zu datagrams\n", name, datagram);
    }

    return differences == 0 ? 0 : 1;
}

}

int main() {
    std::printf("== Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10 (classes values)\n");
    int failures = 0;
    failures += check("AssignCopOrdersMessage", "Tmx/Tsx.QuantumFeedLevel2.Xmt.v2.10/AssignCopOrdersMessage.pcap", "tmx/tsx/quantumfeedlevel2/xmt/v2.10/AssignCopOrdersMessage.values");
    failures += check("OrderBookedMessage", "Tmx/Tsx.QuantumFeedLevel2.Xmt.v2.10/OrderBookedMessage.pcap", "tmx/tsx/quantumfeedlevel2/xmt/v2.10/OrderBookedMessage.values");
    failures += check("OrderCancelledMessage", "Tmx/Tsx.QuantumFeedLevel2.Xmt.v2.10/OrderCancelledMessage.pcap", "tmx/tsx/quantumfeedlevel2/xmt/v2.10/OrderCancelledMessage.values");
    failures += check("TradeReportMessage", "Tmx/Tsx.QuantumFeedLevel2.Xmt.v2.10/TradeReportMessage.pcap", "tmx/tsx/quantumfeedlevel2/xmt/v2.10/TradeReportMessage.values");
    return failures == 0 ? 0 : 1;
}
