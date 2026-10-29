// Siac.Cqs.Output.Cta.v1.91 canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/binary/modern/siac/cqs/output/cta/v1.91/definitions.hpp"

namespace protocol = ::siac::cqs::output::cta::v1_91;

namespace {

// The values the Modern iterator reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    values["packet.blockheader.version"] = canonical::number(iterator.block_header->version.get());
    values["packet.blockheader.blocksize"] = canonical::number(iterator.block_header->block_size.get());
    values["packet.blockheader.datafeedindicator"] = canonical::text(canonical::character(iterator.block_header->data_feed_indicator.get()));
    values["packet.blockheader.retransmissionindicator"] = canonical::text(canonical::character(iterator.block_header->retransmission_indicator.get()));
    values["packet.blockheader.blocksequencenumber"] = canonical::number(iterator.block_header->block_sequence_number.get());
    values["packet.blockheader.messagesinblock"] = canonical::number(iterator.block_header->messages_in_block.get());
    values["packet.blockheader.sipblocktimestamp.seconds"] = canonical::number(iterator.block_header->sip_block_timestamp.seconds.get());
    values["packet.blockheader.sipblocktimestamp.nanoseconds"] = canonical::number(iterator.block_header->sip_block_timestamp.nanoseconds.get());
    values["packet.blockheader.blockchecksum"] = canonical::number(iterator.block_header->block_checksum.get());

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".messagelength"] = canonical::number(iterator.message_header->message_length.get());
        values[entry + ".messagecategory"] = canonical::text(canonical::character(iterator.message_header->message_category.get()));

        if (iterator.message_category == 'A') {
            values[entry + ".categorypayload"] = "packet.message.categorypayload.administrativemessage";
            [[maybe_unused]] const auto* message = protocol::AdministrativeMessage::parse(iterator.message);
            values[entry + ".categorypayload.administrativemessage.administrativemessagetype"] = canonical::text(canonical::character(message->administrative_message_type.get()));
            if (message->administrative_message_type.get() == 'H') {
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload"] = "packet.message.categorypayload.administrativemessage.administrativemessagepayload.administrativeunformattedmessage";
                [[maybe_unused]] const auto* message_2 = protocol::AdministrativeUnformattedMessage::parse(iterator.message + sizeof(protocol::AdministrativeMessage));
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.administrativeunformattedmessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.administrativeunformattedmessage.participanttimestamp.seconds"] = canonical::number(message_2->participant_timestamp.seconds.get());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.administrativeunformattedmessage.participanttimestamp.nanoseconds"] = canonical::number(message_2->participant_timestamp.nanoseconds.get());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.administrativeunformattedmessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.administrativeunformattedmessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.administrativeunformattedmessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.administrativeunformattedmessage.text"] = canonical::text(std::string(message_2->text.get()), ' ', false);
            }
        } else if (iterator.message_category == 'C') {
            values[entry + ".categorypayload"] = "packet.message.categorypayload.controlmessage";
            [[maybe_unused]] const auto* message = protocol::ControlMessage::parse(iterator.message);
            values[entry + ".categorypayload.controlmessage.controlmessagetype"] = canonical::text(canonical::character(message->control_message_type.get()));
            if (message->control_message_type.get() == 'A') {
                values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.startofdaymessage";
                [[maybe_unused]] const auto* message_2 = protocol::StartOfDayMessage::parse(iterator.message + sizeof(protocol::ControlMessage));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.participanttimestamp.seconds"] = canonical::number(message_2->participant_timestamp.seconds.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.participanttimestamp.nanoseconds"] = canonical::number(message_2->participant_timestamp.nanoseconds.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
            } else if (message->control_message_type.get() == 'C') {
                values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.finraclosemessage";
                [[maybe_unused]] const auto* message_2 = protocol::FinraCloseMessage::parse(iterator.message + sizeof(protocol::ControlMessage));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraclosemessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraclosemessage.participanttimestamp.seconds"] = canonical::number(message_2->participant_timestamp.seconds.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraclosemessage.participanttimestamp.nanoseconds"] = canonical::number(message_2->participant_timestamp.nanoseconds.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraclosemessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraclosemessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraclosemessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
            } else if (message->control_message_type.get() == 'L') {
                values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage";
                [[maybe_unused]] const auto* message_2 = protocol::ResetBlockSequenceNumberMessage::parse(iterator.message + sizeof(protocol::ControlMessage));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.participanttimestamp.seconds"] = canonical::number(message_2->participant_timestamp.seconds.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.participanttimestamp.nanoseconds"] = canonical::number(message_2->participant_timestamp.nanoseconds.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
            } else if (message->control_message_type.get() == 'M') {
                values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.startoftestcyclemessage";
                [[maybe_unused]] const auto* message_2 = protocol::StartOfTestCycleMessage::parse(iterator.message + sizeof(protocol::ControlMessage));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.startoftestcyclemessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.startoftestcyclemessage.participanttimestamp.seconds"] = canonical::number(message_2->participant_timestamp.seconds.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.startoftestcyclemessage.participanttimestamp.nanoseconds"] = canonical::number(message_2->participant_timestamp.nanoseconds.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.startoftestcyclemessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.startoftestcyclemessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.startoftestcyclemessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
            } else if (message->control_message_type.get() == 'N') {
                values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.endoftestcyclemessage";
                [[maybe_unused]] const auto* message_2 = protocol::EndOfTestCycleMessage::parse(iterator.message + sizeof(protocol::ControlMessage));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.endoftestcyclemessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.endoftestcyclemessage.participanttimestamp.seconds"] = canonical::number(message_2->participant_timestamp.seconds.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.endoftestcyclemessage.participanttimestamp.nanoseconds"] = canonical::number(message_2->participant_timestamp.nanoseconds.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.endoftestcyclemessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.endoftestcyclemessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.endoftestcyclemessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
            } else if (message->control_message_type.get() == 'O') {
                values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.finraopenmessage";
                [[maybe_unused]] const auto* message_2 = protocol::FinraOpenMessage::parse(iterator.message + sizeof(protocol::ControlMessage));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraopenmessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraopenmessage.participanttimestamp.seconds"] = canonical::number(message_2->participant_timestamp.seconds.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraopenmessage.participanttimestamp.nanoseconds"] = canonical::number(message_2->participant_timestamp.nanoseconds.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraopenmessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraopenmessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraopenmessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
            } else if (message->control_message_type.get() == 'P') {
                values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage";
                [[maybe_unused]] const auto* message_2 = protocol::DisasterRecoveryDataCenterActivationMessage::parse(iterator.message + sizeof(protocol::ControlMessage));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.participanttimestamp.seconds"] = canonical::number(message_2->participant_timestamp.seconds.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.participanttimestamp.nanoseconds"] = canonical::number(message_2->participant_timestamp.nanoseconds.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
            } else if (message->control_message_type.get() == 'T') {
                values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.lineintegritymessage";
                [[maybe_unused]] const auto* message_2 = protocol::LineIntegrityMessage::parse(iterator.message + sizeof(protocol::ControlMessage));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.participanttimestamp.seconds"] = canonical::number(message_2->participant_timestamp.seconds.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.participanttimestamp.nanoseconds"] = canonical::number(message_2->participant_timestamp.nanoseconds.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
            } else if (message->control_message_type.get() == 'Z') {
                values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.endofdaymessage";
                [[maybe_unused]] const auto* message_2 = protocol::EndOfDayMessage::parse(iterator.message + sizeof(protocol::ControlMessage));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.participanttimestamp.seconds"] = canonical::number(message_2->participant_timestamp.seconds.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.participanttimestamp.nanoseconds"] = canonical::number(message_2->participant_timestamp.nanoseconds.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
            }
        } else if (iterator.message_category == 'M') {
            values[entry + ".categorypayload"] = "packet.message.categorypayload.marketstatusmessage";
            [[maybe_unused]] const auto* message = protocol::MarketStatusMessage::parse(iterator.message);
            values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagetype"] = canonical::text(canonical::character(message->market_status_message_type.get()));
            if (message->market_status_message_type.get() == 'K') {
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload"] = "packet.message.categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage";
                [[maybe_unused]] const auto* message_2 = protocol::MarketWideCircuitBreakerDeclineLevelStatusMessage::parse(iterator.message + sizeof(protocol::MarketStatusMessage));
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.participanttimestamp.seconds"] = canonical::number(message_2->participant_timestamp.seconds.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.participanttimestamp.nanoseconds"] = canonical::number(message_2->participant_timestamp.nanoseconds.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.mwcblevel1"] = canonical::scaled(message_2->mwcb_level_1.integer(), -6);
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.mwcblevel2"] = canonical::scaled(message_2->mwcb_level_2.integer(), -6);
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.mwcblevel3"] = canonical::scaled(message_2->mwcb_level_3.integer(), -6);
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.reserved"] = canonical::number(message_2->reserved.get());
            } else if (message->market_status_message_type.get() == 'L') {
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload"] = "packet.message.categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage";
                [[maybe_unused]] const auto* message_2 = protocol::MarketWideCircuitBreakerStatusMessage::parse(iterator.message + sizeof(protocol::MarketStatusMessage));
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.participanttimestamp.seconds"] = canonical::number(message_2->participant_timestamp.seconds.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.participanttimestamp.nanoseconds"] = canonical::number(message_2->participant_timestamp.nanoseconds.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.marketwidecircuitbreakerlevelindicator"] = canonical::text(canonical::character(message_2->market_wide_circuit_breaker_level_indicator.get()));
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.reserved"] = canonical::number(message_2->reserved.get());
            }
        } else if (iterator.message_category == 'Q') {
            values[entry + ".categorypayload"] = "packet.message.categorypayload.quotemessage";
            [[maybe_unused]] const auto* message = protocol::QuoteMessage::parse(iterator.message);
            values[entry + ".categorypayload.quotemessage.quotemessagetype"] = canonical::text(canonical::character(message->quote_message_type.get()));
            if (message->quote_message_type.get() == 'A') {
                values[entry + ".categorypayload.quotemessage.quotemessagepayload"] = "packet.message.categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage";
                [[maybe_unused]] const auto* message_2 = protocol::AuctionStatusMessage::parse(iterator.message + sizeof(protocol::QuoteMessage));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.participanttimestamp.seconds"] = canonical::number(message_2->participant_timestamp.seconds.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.participanttimestamp.nanoseconds"] = canonical::number(message_2->participant_timestamp.nanoseconds.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.securitysymbollong"] = canonical::text(std::string(message_2->security_symbol_long.get()), ' ', false);
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.instrumenttype"] = canonical::text(canonical::character(message_2->instrument_type.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.auctioncollarreferenceprice"] = (static_cast<std::uint64_t>(message_2->auction_collar_reference_price.integer()) != 0x0ULL ? canonical::scaled(message_2->auction_collar_reference_price.integer(), -6) : canonical::absent());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.auctioncollarupperthresholdprice"] = (static_cast<std::uint64_t>(message_2->auction_collar_upper_threshold_price.integer()) != 0x0ULL ? canonical::scaled(message_2->auction_collar_upper_threshold_price.integer(), -6) : canonical::absent());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.auctioncollarlowerthresholdprice"] = (static_cast<std::uint64_t>(message_2->auction_collar_lower_threshold_price.integer()) != 0x0ULL ? canonical::scaled(message_2->auction_collar_lower_threshold_price.integer(), -6) : canonical::absent());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.numberofextensions"] = canonical::number(message_2->number_of_extensions.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.shortsalerestrictionindicator"] = canonical::text(canonical::character(message_2->short_sale_restriction_indicator.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character(message_2->primary_listing_market_participant_id.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.financialstatusindicator"] = canonical::text(canonical::character(message_2->financial_status_indicator.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.future"] = canonical::text(canonical::character(message_2->future.get()), ' ', false);
            } else if (message->quote_message_type.get() == 'L') {
                values[entry + ".categorypayload.quotemessage.quotemessagepayload"] = "packet.message.categorypayload.quotemessage.quotemessagepayload.longquotemessage";
                [[maybe_unused]] const auto* message_2 = protocol::LongQuoteMessage::parse(iterator.message + sizeof(protocol::QuoteMessage));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.participanttimestamp.seconds"] = canonical::number(message_2->participant_timestamp.seconds.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.participanttimestamp.nanoseconds"] = canonical::number(message_2->participant_timestamp.nanoseconds.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.securitysymbollong"] = canonical::text(std::string(message_2->security_symbol_long.get()), ' ', false);
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.instrumenttype"] = canonical::text(canonical::character(message_2->instrument_type.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.quotecondition"] = canonical::text(canonical::character(message_2->quote_condition.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.securitystatusindicator"] = canonical::text(canonical::character(message_2->security_status_indicator.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.bidpricelowerlimitpriceband"] = canonical::scaled(message_2->bid_price_lower_limit_price_band.integer(), -6);
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.bidsizelong"] = canonical::number(message_2->bid_size_long.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.offerpriceupperlimitpriceband"] = canonical::scaled(message_2->offer_price_upper_limit_price_band.integer(), -6);
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.offersizelong"] = canonical::number(message_2->offer_size_long.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.retailinterestindicator"] = canonical::text(canonical::character(message_2->retail_interest_indicator.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.settlementcondition"] = canonical::text(canonical::character(message_2->settlement_condition.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.marketcondition"] = canonical::text(canonical::character(message_2->market_condition.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.finramarketmakerid"] = canonical::text(std::string(message_2->finra_market_maker_id.get()), ' ', false);
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.finrabboindicator"] = canonical::text(canonical::character(message_2->finra_bbo_indicator.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.adftimestamp.seconds"] = canonical::number(message_2->adf_timestamp.seconds.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.adftimestamp.nanoseconds"] = canonical::number(message_2->adf_timestamp.nanoseconds.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.shortsalerestrictionindicator"] = canonical::text(canonical::character(message_2->short_sale_restriction_indicator.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character(message_2->primary_listing_market_participant_id.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.financialstatusindicator"] = canonical::text(canonical::character(message_2->financial_status_indicator.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.sipgeneratedmessageidentifier"] = canonical::text(canonical::character(message_2->sip_generated_message_identifier.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.luldindicator"] = canonical::text(canonical::character(message_2->luld_indicator.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.nationalbboluldindicator"] = canonical::text(canonical::character(message_2->national_bbo_luld_indicator.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.nationalbboindicator"] = canonical::text(canonical::character(message_2->national_bbo_indicator.get()));
            } else if (message->quote_message_type.get() == 'Q') {
                values[entry + ".categorypayload.quotemessage.quotemessagepayload"] = "packet.message.categorypayload.quotemessage.quotemessagepayload.shortquotemessage";
                [[maybe_unused]] const auto* message_2 = protocol::ShortQuoteMessage::parse(iterator.message + sizeof(protocol::QuoteMessage));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.participanttimestamp.seconds"] = canonical::number(message_2->participant_timestamp.seconds.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.participanttimestamp.nanoseconds"] = canonical::number(message_2->participant_timestamp.nanoseconds.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.securitysymbolshort"] = canonical::text(std::string(message_2->security_symbol_short.get()), ' ', false);
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.bidpriceshort"] = canonical::scaled(message_2->bid_price_short.integer(), -2);
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.bidsizeshort"] = canonical::number(message_2->bid_size_short.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.offerpriceshort"] = canonical::scaled(message_2->offer_price_short.integer(), -2);
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.offersizeshort"] = canonical::number(message_2->offer_size_short.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character(message_2->primary_listing_market_participant_id.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.nationalbboindicator"] = canonical::text(canonical::character(message_2->national_bbo_indicator.get()));
            } else if (message->quote_message_type.get() == 'S') {
                values[entry + ".categorypayload.quotemessage.quotemessagepayload"] = "packet.message.categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage";
                [[maybe_unused]] const auto* message_2 = protocol::SpecialLongQuoteMessage::parse(iterator.message + sizeof(protocol::QuoteMessage));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.participanttimestamp.seconds"] = canonical::number(message_2->participant_timestamp.seconds.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.participanttimestamp.nanoseconds"] = canonical::number(message_2->participant_timestamp.nanoseconds.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.securitysymbollong"] = canonical::text(std::string(message_2->security_symbol_long.get()), ' ', false);
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.instrumenttype"] = canonical::text(canonical::character(message_2->instrument_type.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.quotecondition"] = canonical::text(canonical::character(message_2->quote_condition.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.securitystatusindicator"] = canonical::text(canonical::character(message_2->security_status_indicator.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.bidpricelong"] = canonical::scaled(message_2->bid_price_long.integer(), -6);
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.bidsizelong"] = canonical::number(message_2->bid_size_long.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.offerpricelong"] = canonical::scaled(message_2->offer_price_long.integer(), -6);
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.offersizelong"] = canonical::number(message_2->offer_size_long.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.retailinterestindicator"] = canonical::text(canonical::character(message_2->retail_interest_indicator.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.settlementcondition"] = canonical::text(canonical::character(message_2->settlement_condition.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.marketcondition"] = canonical::text(canonical::character(message_2->market_condition.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finramarketmakerid"] = canonical::text(std::string(message_2->finra_market_maker_id.get()), ' ', false);
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finrabestbidquotecondition"] = canonical::text(canonical::character(message_2->finra_best_bid_quote_condition.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finrabestbidprice"] = canonical::scaled(message_2->finra_best_bid_price.integer(), -6);
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finrabestbidsize"] = canonical::number(message_2->finra_best_bid_size.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finrabestbidmarketmakerid"] = canonical::text(std::string(message_2->finra_best_bid_market_maker_id.get()), ' ', false);
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finrabestofferquotecondition"] = canonical::text(canonical::character(message_2->finra_best_offer_quote_condition.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finrabestofferprice"] = canonical::scaled(message_2->finra_best_offer_price.integer(), -6);
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finrabestoffersize"] = canonical::number(message_2->finra_best_offer_size.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finrabestoffermarketmakerid"] = canonical::text(std::string(message_2->finra_best_offer_market_maker_id.get()), ' ', false);
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.adftimestamp.seconds"] = canonical::number(message_2->adf_timestamp.seconds.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.adftimestamp.nanoseconds"] = canonical::number(message_2->adf_timestamp.nanoseconds.get());
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.shortsalerestrictionindicator"] = canonical::text(canonical::character(message_2->short_sale_restriction_indicator.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character(message_2->primary_listing_market_participant_id.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.financialstatusindicator"] = canonical::text(canonical::character(message_2->financial_status_indicator.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.sipgeneratedmessageidentifier"] = canonical::text(canonical::character(message_2->sip_generated_message_identifier.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finrabboluldindicator"] = canonical::text(canonical::character(message_2->finra_bbo_luld_indicator.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.nationalbboluldindicator"] = canonical::text(canonical::character(message_2->national_bbo_luld_indicator.get()));
                values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.nationalbboindicator"] = canonical::text(canonical::character(message_2->national_bbo_indicator.get()));
            }
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
    std::printf("== Siac.Cqs.Output.Cta.v1.91 (modern values)\n");
    int failures = 0;
    failures += check("LongQuoteMessage", "Siac/Cqs.Output.Cta.v1.91/LongQuoteMessage.pcap", "siac/cqs/output/cta/v1.91/LongQuoteMessage.values");
    return failures == 0 ? 0 : 1;
}
