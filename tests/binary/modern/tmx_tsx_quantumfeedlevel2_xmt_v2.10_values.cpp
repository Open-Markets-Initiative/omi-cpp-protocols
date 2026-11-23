// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10 canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/binary/modern/tmx/tsx/quantumfeedlevel2/xmt/v2.10/definitions.hpp"

namespace protocol = ::tmx::tsx::quantumfeedlevel2::xmt::v2_10;

namespace {

// The values the Modern iterator reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::BodyIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    values["packet.frameheader.startofframe"] = canonical::number(iterator.frame_header->start_of_frame.get());
    values["packet.frameheader.protocolname"] = canonical::text(canonical::character(iterator.frame_header->protocol_name.get()));
    values["packet.frameheader.protocolversion"] = canonical::numeric(canonical::character(iterator.frame_header->protocol_version.get()));
    values["packet.frameheader.messagelength"] = canonical::number(iterator.frame_header->message_length.get());
    values["packet.frameheader.sessionid"] = canonical::number(iterator.frame_header->session_id.get());
    values["packet.frameheader.ackrequiredpossdup"] = canonical::text(canonical::character(iterator.frame_header->ack_required_poss_dup.get()));
    values["packet.frameheader.numbody"] = canonical::number(iterator.frame_header->num_body.get());

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "packet.packetbody.businessbodies.body[" + std::to_string(index++) + "]";
        values[entry + ".bodyheader.msglength"] = canonical::number(iterator.body_header->msg_length.get());
        values[entry + ".bodyheader.msgtype"] = canonical::text(canonical::character(iterator.body_header->msg_type.get()));

        if (iterator.msg_type == 'J') {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.symbolstatusmessage";
            [[maybe_unused]] const auto* message = protocol::SymbolStatusMessage::parse(iterator.message);
            values[entry + ".bodymessage.businessmessage.symbolstatusmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.symbolstatusmessage.stockgroup"] = (static_cast<std::uint8_t>(message->stock_group.get()) != 0x0U ? canonical::number(message->stock_group.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.symbolstatusmessage.cusip"] = canonical::text(std::string(message->cusip.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.symbolstatusmessage.boardlot"] = (static_cast<std::uint16_t>(message->board_lot.get()) != 0x0U ? canonical::number(message->board_lot.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.symbolstatusmessage.currency"] = canonical::text(canonical::character(message->currency.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.symbolstatusmessage.facevalue"] = (static_cast<std::uint64_t>(message->face_value.integer()) != 0x0ULL ? canonical::scaled(message->face_value.integer(), -6) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.symbolstatusmessage.lastsale"] = (static_cast<std::uint64_t>(message->last_sale.integer()) != 0x0ULL ? canonical::scaled(message->last_sale.integer(), -6) : canonical::absent());
        } else if (iterator.msg_type == 'G') {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.orderbookmessage";
            [[maybe_unused]] const auto* message = protocol::OrderBookMessage::parse(iterator.message);
            values[entry + ".bodymessage.businessmessage.orderbookmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderbookmessage.brokernumber"] = (static_cast<std::uint16_t>(message->broker_number.get()) != 0x0U ? canonical::number(message->broker_number.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookmessage.orderside"] = canonical::text(canonical::character(message->order_side.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderbookmessage.orderid"] = (static_cast<std::uint64_t>(message->order_id.get()) != 0x0ULL ? canonical::number(message->order_id.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookmessage.price"] = (static_cast<std::uint64_t>(message->price.integer()) != 0x0ULL ? canonical::scaled(message->price.integer(), -6) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookmessage.volume"] = (static_cast<std::uint32_t>(message->volume.get()) != 0x0U ? canonical::number(message->volume.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookmessage.prioritytimestamp"] = (static_cast<std::uint64_t>(message->priority_time_stamp.get()) != 0x0ULL ? canonical::number(message->priority_time_stamp.get()) : canonical::absent());
        } else if (iterator.msg_type == 'j') {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.orderbooktermsmessage";
            [[maybe_unused]] const auto* message = protocol::OrderBookTermsMessage::parse(iterator.message);
            values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.brokernumber"] = (static_cast<std::uint16_t>(message->broker_number.get()) != 0x0U ? canonical::number(message->broker_number.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.orderside"] = canonical::text(canonical::character(message->order_side.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.orderid"] = (static_cast<std::uint64_t>(message->order_id.get()) != 0x0ULL ? canonical::number(message->order_id.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.price"] = (static_cast<std::uint64_t>(message->price.integer()) != 0x0ULL ? canonical::scaled(message->price.integer(), -6) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.volume"] = (static_cast<std::uint32_t>(message->volume.get()) != 0x0U ? canonical::number(message->volume.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.nonresident"] = canonical::text(canonical::character(message->non_resident.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.settlementterms"] = canonical::text(canonical::character(message->settlement_terms.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.settlementdate"] = (static_cast<std::uint32_t>(message->settlement_date.get()) != 0x0U ? canonical::number(message->settlement_date.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.prioritytimestamp"] = (static_cast<std::uint64_t>(message->priority_time_stamp.get()) != 0x0ULL ? canonical::number(message->priority_time_stamp.get()) : canonical::absent());
        } else if (iterator.msg_type == 'A') {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.assigncopordersmessage";
            [[maybe_unused]] const auto* message = protocol::AssignCopOrdersMessage::parse(iterator.message);
            values[entry + ".bodymessage.businessmessage.assigncopordersmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.assigncopordersmessage.calculatedopeningprice"] = (static_cast<std::uint64_t>(message->calculated_opening_price.integer()) != 0x0ULL ? canonical::scaled(message->calculated_opening_price.integer(), -6) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.assigncopordersmessage.orderside"] = canonical::text(canonical::character(message->order_side.get()), ' ', false);
            for (std::size_t cop_order_index = 0; const auto& cop_order_entry : message->cop_order) {
                const std::string cop_order_at = std::string{entry + ".bodymessage.businessmessage.assigncopordersmessage.coporder"} + "[" + std::to_string(cop_order_index++) + "]";
                values[cop_order_at + ".brokernumber"] = (static_cast<std::uint16_t>(cop_order_entry.broker_number.get()) != 0x0U ? canonical::number(cop_order_entry.broker_number.get()) : canonical::absent());
                values[cop_order_at + ".orderid"] = (static_cast<std::uint64_t>(cop_order_entry.order_id.get()) != 0x0ULL ? canonical::number(cop_order_entry.order_id.get()) : canonical::absent());
            }
            values[entry + ".bodymessage.businessmessage.assigncopordersmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? canonical::number(message->trading_system_time_stamp.get()) : canonical::absent());
        } else if (iterator.msg_type == 'B') {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.assigncopnoordersmessage";
            [[maybe_unused]] const auto* message = protocol::AssignCopNoOrdersMessage::parse(iterator.message);
            values[entry + ".bodymessage.businessmessage.assigncopnoordersmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.assigncopnoordersmessage.calculatedopeningprice"] = (static_cast<std::uint64_t>(message->calculated_opening_price.integer()) != 0x0ULL ? canonical::scaled(message->calculated_opening_price.integer(), -6) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.assigncopnoordersmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? canonical::number(message->trading_system_time_stamp.get()) : canonical::absent());
        } else if (iterator.msg_type == 'C') {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.assignlimitmessage";
            [[maybe_unused]] const auto* message = protocol::AssignLimitMessage::parse(iterator.message);
            values[entry + ".bodymessage.businessmessage.assignlimitmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.assignlimitmessage.calculatedopeningprice"] = (static_cast<std::uint64_t>(message->calculated_opening_price.integer()) != 0x0ULL ? canonical::scaled(message->calculated_opening_price.integer(), -6) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.assignlimitmessage.orderside"] = canonical::text(canonical::character(message->order_side.get()), ' ', false);
            for (std::size_t cop_limit_index = 0; const auto& cop_limit_entry : message->cop_limit) {
                const std::string cop_limit_at = std::string{entry + ".bodymessage.businessmessage.assignlimitmessage.coplimit"} + "[" + std::to_string(cop_limit_index++) + "]";
                values[cop_limit_at + ".brokernumber"] = (static_cast<std::uint16_t>(cop_limit_entry.broker_number.get()) != 0x0U ? canonical::number(cop_limit_entry.broker_number.get()) : canonical::absent());
                values[cop_limit_at + ".orderid"] = (static_cast<std::uint64_t>(cop_limit_entry.order_id.get()) != 0x0ULL ? canonical::number(cop_limit_entry.order_id.get()) : canonical::absent());
                values[cop_limit_at + ".price"] = (static_cast<std::uint64_t>(cop_limit_entry.price.integer()) != 0x0ULL ? canonical::scaled(cop_limit_entry.price.integer(), -6) : canonical::absent());
            }
            values[entry + ".bodymessage.businessmessage.assignlimitmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? canonical::number(message->trading_system_time_stamp.get()) : canonical::absent());
        } else if (iterator.msg_type == 'E') {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.marketstateupdatemessage";
            [[maybe_unused]] const auto* message = protocol::MarketStateUpdateMessage::parse(iterator.message);
            values[entry + ".bodymessage.businessmessage.marketstateupdatemessage.marketstate"] = canonical::text(canonical::character(message->market_state.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.marketstateupdatemessage.stockgroup"] = (static_cast<std::uint8_t>(message->stock_group.get()) != 0x0U ? canonical::number(message->stock_group.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.marketstateupdatemessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? canonical::number(message->trading_system_time_stamp.get()) : canonical::absent());
        } else if (iterator.msg_type == 'F') {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.mocimbalancemessage";
            [[maybe_unused]] const auto* message = protocol::MocImbalanceMessage::parse(iterator.message);
            values[entry + ".bodymessage.businessmessage.mocimbalancemessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.mocimbalancemessage.imbalanceside"] = canonical::text(canonical::character(message->imbalance_side.get()), ' ', false, {std::string_view(" ", 1), std::string_view("", 0)});
            values[entry + ".bodymessage.businessmessage.mocimbalancemessage.imbalancevolume"] = (static_cast<std::uint32_t>(message->imbalance_volume.get()) != 0x0U ? canonical::number(message->imbalance_volume.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.mocimbalancemessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? canonical::number(message->trading_system_time_stamp.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.mocimbalancemessage.imbalancereferenceprice"] = (static_cast<std::uint64_t>(message->imbalance_reference_price.integer()) != 0x0ULL ? canonical::scaled(message->imbalance_reference_price.integer(), -6) : canonical::absent());
        } else if (iterator.msg_type == 'P') {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.orderbookedmessage";
            [[maybe_unused]] const auto* message = protocol::OrderBookedMessage::parse(iterator.message);
            values[entry + ".bodymessage.businessmessage.orderbookedmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderbookedmessage.brokernumber"] = (static_cast<std::uint16_t>(message->broker_number.get()) != 0x0U ? canonical::number(message->broker_number.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookedmessage.orderside"] = canonical::text(canonical::character(message->order_side.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderbookedmessage.orderid"] = (static_cast<std::uint64_t>(message->order_id.get()) != 0x0ULL ? canonical::number(message->order_id.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookedmessage.price"] = (static_cast<std::uint64_t>(message->price.integer()) != 0x0ULL ? canonical::scaled(message->price.integer(), -6) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookedmessage.volume"] = (static_cast<std::uint32_t>(message->volume.get()) != 0x0U ? canonical::number(message->volume.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookedmessage.prioritytimestamp"] = (static_cast<std::uint64_t>(message->priority_time_stamp.get()) != 0x0ULL ? canonical::number(message->priority_time_stamp.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookedmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? canonical::number(message->trading_system_time_stamp.get()) : canonical::absent());
        } else if (iterator.msg_type == 'm') {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.orderbookedtermsmessage";
            [[maybe_unused]] const auto* message = protocol::OrderBookedTermsMessage::parse(iterator.message);
            values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.brokernumber"] = (static_cast<std::uint16_t>(message->broker_number.get()) != 0x0U ? canonical::number(message->broker_number.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.orderside"] = canonical::text(canonical::character(message->order_side.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.orderid"] = (static_cast<std::uint64_t>(message->order_id.get()) != 0x0ULL ? canonical::number(message->order_id.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.price"] = (static_cast<std::uint64_t>(message->price.integer()) != 0x0ULL ? canonical::scaled(message->price.integer(), -6) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.volume"] = (static_cast<std::uint32_t>(message->volume.get()) != 0x0U ? canonical::number(message->volume.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.nonresident"] = canonical::text(canonical::character(message->non_resident.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.settlementterms"] = canonical::text(canonical::character(message->settlement_terms.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.settlementdate"] = (static_cast<std::uint32_t>(message->settlement_date.get()) != 0x0U ? canonical::number(message->settlement_date.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.prioritytimestamp"] = (static_cast<std::uint64_t>(message->priority_time_stamp.get()) != 0x0ULL ? canonical::number(message->priority_time_stamp.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? canonical::number(message->trading_system_time_stamp.get()) : canonical::absent());
        } else if (iterator.msg_type == 'Q') {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.ordercancelledmessage";
            [[maybe_unused]] const auto* message = protocol::OrderCancelledMessage::parse(iterator.message);
            values[entry + ".bodymessage.businessmessage.ordercancelledmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.ordercancelledmessage.brokernumber"] = (static_cast<std::uint16_t>(message->broker_number.get()) != 0x0U ? canonical::number(message->broker_number.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.ordercancelledmessage.orderside"] = canonical::text(canonical::character(message->order_side.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.ordercancelledmessage.orderid"] = (static_cast<std::uint64_t>(message->order_id.get()) != 0x0ULL ? canonical::number(message->order_id.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.ordercancelledmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? canonical::number(message->trading_system_time_stamp.get()) : canonical::absent());
        } else if (iterator.msg_type == 'n') {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.ordercancelledtermsmessage";
            [[maybe_unused]] const auto* message = protocol::OrderCancelledTermsMessage::parse(iterator.message);
            values[entry + ".bodymessage.businessmessage.ordercancelledtermsmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.ordercancelledtermsmessage.brokernumber"] = (static_cast<std::uint16_t>(message->broker_number.get()) != 0x0U ? canonical::number(message->broker_number.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.ordercancelledtermsmessage.orderside"] = canonical::text(canonical::character(message->order_side.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.ordercancelledtermsmessage.orderid"] = (static_cast<std::uint64_t>(message->order_id.get()) != 0x0ULL ? canonical::number(message->order_id.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.ordercancelledtermsmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? canonical::number(message->trading_system_time_stamp.get()) : canonical::absent());
        } else if (iterator.msg_type == 'R') {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.orderpricetimeassignedmessage";
            [[maybe_unused]] const auto* message = protocol::OrderPriceTimeAssignedMessage::parse(iterator.message);
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedmessage.brokernumber"] = (static_cast<std::uint16_t>(message->broker_number.get()) != 0x0U ? canonical::number(message->broker_number.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedmessage.orderside"] = canonical::text(canonical::character(message->order_side.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedmessage.orderid"] = (static_cast<std::uint64_t>(message->order_id.get()) != 0x0ULL ? canonical::number(message->order_id.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedmessage.price"] = (static_cast<std::uint64_t>(message->price.integer()) != 0x0ULL ? canonical::scaled(message->price.integer(), -6) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedmessage.volume"] = (static_cast<std::uint32_t>(message->volume.get()) != 0x0U ? canonical::number(message->volume.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedmessage.prioritytimestamp"] = (static_cast<std::uint64_t>(message->priority_time_stamp.get()) != 0x0ULL ? canonical::number(message->priority_time_stamp.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? canonical::number(message->trading_system_time_stamp.get()) : canonical::absent());
        } else if (iterator.msg_type == 'o') {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.orderpricetimeassignedtermsmessage";
            [[maybe_unused]] const auto* message = protocol::OrderPriceTimeAssignedTermsMessage::parse(iterator.message);
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedtermsmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedtermsmessage.brokernumber"] = (static_cast<std::uint16_t>(message->broker_number.get()) != 0x0U ? canonical::number(message->broker_number.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedtermsmessage.orderside"] = canonical::text(canonical::character(message->order_side.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedtermsmessage.orderid"] = (static_cast<std::uint64_t>(message->order_id.get()) != 0x0ULL ? canonical::number(message->order_id.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedtermsmessage.price"] = (static_cast<std::uint64_t>(message->price.integer()) != 0x0ULL ? canonical::scaled(message->price.integer(), -6) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedtermsmessage.volume"] = (static_cast<std::uint32_t>(message->volume.get()) != 0x0U ? canonical::number(message->volume.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedtermsmessage.prioritytimestamp"] = (static_cast<std::uint64_t>(message->priority_time_stamp.get()) != 0x0ULL ? canonical::number(message->priority_time_stamp.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.orderpricetimeassignedtermsmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? canonical::number(message->trading_system_time_stamp.get()) : canonical::absent());
        } else if (iterator.msg_type == 'I') {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.stockstatusmessage";
            [[maybe_unused]] const auto* message = protocol::StockStatusMessage::parse(iterator.message);
            values[entry + ".bodymessage.businessmessage.stockstatusmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.stockstatusmessage.comment"] = canonical::text(std::string(message->comment.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.stockstatusmessage.stockstate"] = canonical::text(std::string(message->stock_state.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.stockstatusmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? canonical::number(message->trading_system_time_stamp.get()) : canonical::absent());
        } else if (iterator.msg_type == 'S') {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.tradereportmessage";
            [[maybe_unused]] const auto* message = protocol::TradeReportMessage::parse(iterator.message);
            values[entry + ".bodymessage.businessmessage.tradereportmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradereportmessage.tradenumber"] = (static_cast<std::uint32_t>(message->trade_number.get()) != 0x0U ? canonical::number(message->trade_number.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereportmessage.price"] = (static_cast<std::uint64_t>(message->price.integer()) != 0x0ULL ? canonical::scaled(message->price.integer(), -6) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereportmessage.volume"] = (static_cast<std::uint32_t>(message->volume.get()) != 0x0U ? canonical::number(message->volume.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereportmessage.buybrokernumber"] = (static_cast<std::uint16_t>(message->buy_broker_number.get()) != 0x0U ? canonical::number(message->buy_broker_number.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereportmessage.buyorderid"] = (static_cast<std::uint64_t>(message->buy_order_id.get()) != 0x0ULL ? canonical::number(message->buy_order_id.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereportmessage.buydisplayvolume"] = (static_cast<std::uint32_t>(message->buy_display_volume.get()) != 0x0U ? canonical::number(message->buy_display_volume.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereportmessage.sellbrokernumber"] = (static_cast<std::uint16_t>(message->sell_broker_number.get()) != 0x0U ? canonical::number(message->sell_broker_number.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereportmessage.sellorderid"] = (static_cast<std::uint64_t>(message->sell_order_id.get()) != 0x0ULL ? canonical::number(message->sell_order_id.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereportmessage.selldisplayvolume"] = (static_cast<std::uint32_t>(message->sell_display_volume.get()) != 0x0U ? canonical::number(message->sell_display_volume.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereportmessage.bypass"] = canonical::text(canonical::character(message->bypass.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradereportmessage.tradetimestamp"] = (static_cast<std::uint32_t>(message->trade_time_stamp.get()) != 0x0U ? canonical::number(message->trade_time_stamp.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereportmessage.crosstype"] = canonical::text(canonical::character(message->cross_type.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradereportmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? canonical::number(message->trading_system_time_stamp.get()) : canonical::absent());
        } else if (iterator.msg_type == 'p') {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.tradereporttermsmessage";
            [[maybe_unused]] const auto* message = protocol::TradeReportTermsMessage::parse(iterator.message);
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.tradenumber"] = (static_cast<std::uint32_t>(message->trade_number.get()) != 0x0U ? canonical::number(message->trade_number.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.price"] = (static_cast<std::uint64_t>(message->price.integer()) != 0x0ULL ? canonical::scaled(message->price.integer(), -6) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.volume"] = (static_cast<std::uint32_t>(message->volume.get()) != 0x0U ? canonical::number(message->volume.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.buybrokernumber"] = (static_cast<std::uint16_t>(message->buy_broker_number.get()) != 0x0U ? canonical::number(message->buy_broker_number.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.buyorderid"] = (static_cast<std::uint64_t>(message->buy_order_id.get()) != 0x0ULL ? canonical::number(message->buy_order_id.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.buydisplayvolume"] = (static_cast<std::uint32_t>(message->buy_display_volume.get()) != 0x0U ? canonical::number(message->buy_display_volume.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.sellbrokernumber"] = (static_cast<std::uint16_t>(message->sell_broker_number.get()) != 0x0U ? canonical::number(message->sell_broker_number.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.sellorderid"] = (static_cast<std::uint64_t>(message->sell_order_id.get()) != 0x0ULL ? canonical::number(message->sell_order_id.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.selldisplayvolume"] = (static_cast<std::uint32_t>(message->sell_display_volume.get()) != 0x0U ? canonical::number(message->sell_display_volume.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.tradetimestamp"] = (static_cast<std::uint32_t>(message->trade_time_stamp.get()) != 0x0U ? canonical::number(message->trade_time_stamp.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.nonresident"] = canonical::text(canonical::character(message->non_resident.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.settlementterms"] = canonical::text(canonical::character(message->settlement_terms.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.settlementdate"] = (static_cast<std::uint32_t>(message->settlement_date.get()) != 0x0U ? canonical::number(message->settlement_date.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.crosstype"] = canonical::text(canonical::character(message->cross_type.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? canonical::number(message->trading_system_time_stamp.get()) : canonical::absent());
        } else if (iterator.msg_type == 'T') {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.tradecancelledmessage";
            [[maybe_unused]] const auto* message = protocol::TradeCancelledMessage::parse(iterator.message);
            values[entry + ".bodymessage.businessmessage.tradecancelledmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradecancelledmessage.tradenumber"] = (static_cast<std::uint32_t>(message->trade_number.get()) != 0x0U ? canonical::number(message->trade_number.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecancelledmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? canonical::number(message->trading_system_time_stamp.get()) : canonical::absent());
        } else if (iterator.msg_type == 'q') {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.tradecancelledtermsmessage";
            [[maybe_unused]] const auto* message = protocol::TradeCancelledTermsMessage::parse(iterator.message);
            values[entry + ".bodymessage.businessmessage.tradecancelledtermsmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradecancelledtermsmessage.tradenumber"] = (static_cast<std::uint32_t>(message->trade_number.get()) != 0x0U ? canonical::number(message->trade_number.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecancelledtermsmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? canonical::number(message->trading_system_time_stamp.get()) : canonical::absent());
        } else if (iterator.msg_type == 'U') {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.tradecorrectionmessage";
            [[maybe_unused]] const auto* message = protocol::TradeCorrectionMessage::parse(iterator.message);
            values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.tradenumber"] = (static_cast<std::uint32_t>(message->trade_number.get()) != 0x0U ? canonical::number(message->trade_number.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.price"] = (static_cast<std::uint64_t>(message->price.integer()) != 0x0ULL ? canonical::scaled(message->price.integer(), -6) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.volume"] = (static_cast<std::uint32_t>(message->volume.get()) != 0x0U ? canonical::number(message->volume.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.buybrokernumber"] = (static_cast<std::uint16_t>(message->buy_broker_number.get()) != 0x0U ? canonical::number(message->buy_broker_number.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.sellbrokernumber"] = (static_cast<std::uint16_t>(message->sell_broker_number.get()) != 0x0U ? canonical::number(message->sell_broker_number.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.initiatedby"] = canonical::text(canonical::character(message->initiated_by.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.origtradenumber"] = (static_cast<std::uint32_t>(message->orig_trade_number.get()) != 0x0U ? canonical::number(message->orig_trade_number.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.bypass"] = canonical::text(canonical::character(message->bypass.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.tradetimestamp"] = (static_cast<std::uint32_t>(message->trade_time_stamp.get()) != 0x0U ? canonical::number(message->trade_time_stamp.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.crosstype"] = canonical::text(canonical::character(message->cross_type.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? canonical::number(message->trading_system_time_stamp.get()) : canonical::absent());
        } else if (iterator.msg_type == 'r') {
            values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.tradecorrectiontermsmessage";
            [[maybe_unused]] const auto* message = protocol::TradeCorrectionTermsMessage::parse(iterator.message);
            values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.tradenumber"] = (static_cast<std::uint32_t>(message->trade_number.get()) != 0x0U ? canonical::number(message->trade_number.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.price"] = (static_cast<std::uint64_t>(message->price.integer()) != 0x0ULL ? canonical::scaled(message->price.integer(), -6) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.volume"] = (static_cast<std::uint32_t>(message->volume.get()) != 0x0U ? canonical::number(message->volume.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.buybrokernumber"] = (static_cast<std::uint16_t>(message->buy_broker_number.get()) != 0x0U ? canonical::number(message->buy_broker_number.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.sellbrokernumber"] = (static_cast<std::uint16_t>(message->sell_broker_number.get()) != 0x0U ? canonical::number(message->sell_broker_number.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.initiatedby"] = canonical::text(canonical::character(message->initiated_by.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.origtradenumber"] = (static_cast<std::uint32_t>(message->orig_trade_number.get()) != 0x0U ? canonical::number(message->orig_trade_number.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.tradetimestamp"] = (static_cast<std::uint32_t>(message->trade_time_stamp.get()) != 0x0U ? canonical::number(message->trade_time_stamp.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.nonresident"] = canonical::text(canonical::character(message->non_resident.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.settlementterms"] = canonical::text(canonical::character(message->settlement_terms.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.settlementdate"] = (static_cast<std::uint32_t>(message->settlement_date.get()) != 0x0U ? canonical::number(message->settlement_date.get()) : canonical::absent());
            values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.crosstype"] = canonical::text(canonical::character(message->cross_type.get()), ' ', false);
            values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message->trading_system_time_stamp.get()) != 0x0ULL ? canonical::number(message->trading_system_time_stamp.get()) : canonical::absent());
        }
    }

    return values;
}

// Read each datagram of a sample with Modern and hold it to the model's values
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
    std::printf("== Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10 (modern values)\n");
    int failures = 0;
    failures += check("AssignCopOrdersMessage", "Tmx/Tsx.QuantumFeedLevel2.Xmt.v2.10/AssignCopOrdersMessage.pcap", "tmx/tsx/quantumfeedlevel2/xmt/v2.10/AssignCopOrdersMessage.values");
    failures += check("OrderBookedMessage", "Tmx/Tsx.QuantumFeedLevel2.Xmt.v2.10/OrderBookedMessage.pcap", "tmx/tsx/quantumfeedlevel2/xmt/v2.10/OrderBookedMessage.values");
    failures += check("OrderCancelledMessage", "Tmx/Tsx.QuantumFeedLevel2.Xmt.v2.10/OrderCancelledMessage.pcap", "tmx/tsx/quantumfeedlevel2/xmt/v2.10/OrderCancelledMessage.values");
    failures += check("TradeReportMessage", "Tmx/Tsx.QuantumFeedLevel2.Xmt.v2.10/TradeReportMessage.pcap", "tmx/tsx/quantumfeedlevel2/xmt/v2.10/TradeReportMessage.values");
    return failures == 0 ? 0 : 1;
}
