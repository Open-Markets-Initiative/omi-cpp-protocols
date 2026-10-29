// Siac.Cts.Output.Cta.v2.9 canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/binary/modern/siac/cts/output/cta/v2.9/definitions.hpp"

namespace protocol = ::siac::cts::output::cta::v2_9;

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
            if (message->administrative_message_type.get() == 'A') {
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload"] = "packet.message.categorypayload.administrativemessage.administrativemessagepayload.startofendofdaymessage";
                [[maybe_unused]] const auto* message_2 = protocol::StartOfEndOfDayMessage::parse(iterator.message + sizeof(protocol::AdministrativeMessage));
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.startofendofdaymessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.startofendofdaymessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.startofendofdaymessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.startofendofdaymessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.startofendofdaymessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.startofendofdaymessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
            } else if (message->administrative_message_type.get() == 'B') {
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload"] = "packet.message.categorypayload.administrativemessage.administrativemessagepayload.endofendofdaymessage";
                [[maybe_unused]] const auto* message_2 = protocol::EndOfEndOfDayMessage::parse(iterator.message + sizeof(protocol::AdministrativeMessage));
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.endofendofdaymessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.endofendofdaymessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.endofendofdaymessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.endofendofdaymessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.endofendofdaymessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.endofendofdaymessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
            } else if (message->administrative_message_type.get() == 'C') {
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload"] = "packet.message.categorypayload.administrativemessage.administrativemessagepayload.startofstartofdaymessage";
                [[maybe_unused]] const auto* message_2 = protocol::StartOfStartOfDayMessage::parse(iterator.message + sizeof(protocol::AdministrativeMessage));
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.startofstartofdaymessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.startofstartofdaymessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.startofstartofdaymessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.startofstartofdaymessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.startofstartofdaymessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.startofstartofdaymessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
            } else if (message->administrative_message_type.get() == 'D') {
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload"] = "packet.message.categorypayload.administrativemessage.administrativemessagepayload.endofstartofdaymessage";
                [[maybe_unused]] const auto* message_2 = protocol::EndOfStartOfDayMessage::parse(iterator.message + sizeof(protocol::AdministrativeMessage));
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.endofstartofdaymessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.endofstartofdaymessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.endofstartofdaymessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.endofstartofdaymessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.endofstartofdaymessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.endofstartofdaymessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
            }
        } else if (iterator.message_category == 'C') {
            values[entry + ".categorypayload"] = "packet.message.categorypayload.controlmessage";
            [[maybe_unused]] const auto* message = protocol::ControlMessage::parse(iterator.message);
            values[entry + ".categorypayload.controlmessage.controlmessagetype"] = canonical::text(canonical::character(message->control_message_type.get()));
            if (message->control_message_type.get() == 'A') {
                values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.startofdaymessage";
                [[maybe_unused]] const auto* message_2 = protocol::StartOfDayMessage::parse(iterator.message + sizeof(protocol::ControlMessage));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
            } else if (message->control_message_type.get() == 'L') {
                values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage";
                [[maybe_unused]] const auto* message_2 = protocol::ResetBlockSequenceNumberMessage::parse(iterator.message + sizeof(protocol::ControlMessage));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
            } else if (message->control_message_type.get() == 'P') {
                values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage";
                [[maybe_unused]] const auto* message_2 = protocol::DisasterRecoveryDataCenterActivationMessage::parse(iterator.message + sizeof(protocol::ControlMessage));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
            } else if (message->control_message_type.get() == 'T') {
                values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.lineintegritymessage";
                [[maybe_unused]] const auto* message_2 = protocol::LineIntegrityMessage::parse(iterator.message + sizeof(protocol::ControlMessage));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
            } else if (message->control_message_type.get() == 'Z') {
                values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.endofdaymessage";
                [[maybe_unused]] const auto* message_2 = protocol::EndOfDayMessage::parse(iterator.message + sizeof(protocol::ControlMessage));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
            }
        } else if (iterator.message_category == 'I') {
            values[entry + ".categorypayload"] = "packet.message.categorypayload.indicesmessage";
            [[maybe_unused]] const auto* message = protocol::IndicesMessage::parse(iterator.message);
            values[entry + ".categorypayload.indicesmessage.indicesmessagetype"] = canonical::text(canonical::character(message->indices_message_type.get()));
            if (message->indices_message_type.get() == 'I') {
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload"] = "packet.message.categorypayload.indicesmessage.indicesmessagepayload.indexmessage";
                [[maybe_unused]] const auto* message_2 = protocol::IndexMessage::parse(iterator.message + sizeof(protocol::IndicesMessage));
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.indexmessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.indexmessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.indexmessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.indexmessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.indexmessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.indexmessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.indexmessage.indexsymbol"] = canonical::text(std::string(message_2->index_symbol.get()), ' ', false);
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.indexmessage.indexvalue"] = canonical::scaled(message_2->index_value.integer(), -6);
            } else if (message->indices_message_type.get() == 'Q') {
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload"] = "packet.message.categorypayload.indicesmessage.indicesmessagepayload.bidandofferindexmessage";
                [[maybe_unused]] const auto* message_2 = protocol::BidAndOfferIndexMessage::parse(iterator.message + sizeof(protocol::IndicesMessage));
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.bidandofferindexmessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.bidandofferindexmessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.bidandofferindexmessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.bidandofferindexmessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.bidandofferindexmessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.bidandofferindexmessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.bidandofferindexmessage.indexsymbol"] = canonical::text(std::string(message_2->index_symbol.get()), ' ', false);
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.bidandofferindexmessage.bidindexvalue"] = canonical::scaled(message_2->bid_index_value.integer(), -6);
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.bidandofferindexmessage.offerindexvalue"] = canonical::scaled(message_2->offer_index_value.integer(), -6);
            }
        } else if (iterator.message_category == 'M') {
            values[entry + ".categorypayload"] = "packet.message.categorypayload.marketstatusmessage";
            [[maybe_unused]] const auto* message = protocol::MarketStatusMessage::parse(iterator.message);
            values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagetype"] = canonical::text(canonical::character(message->market_status_message_type.get()));
            if (message->market_status_message_type.get() == 'K') {
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload"] = "packet.message.categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage";
                [[maybe_unused]] const auto* message_2 = protocol::MarketWideCircuitBreakerDeclineLevelStatusMessage::parse(iterator.message + sizeof(protocol::MarketStatusMessage));
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
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
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.marketwidecircuitbreakerlevelindicator"] = canonical::text(canonical::character(message_2->market_wide_circuit_breaker_level_indicator.get()));
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.reserved"] = canonical::number(message_2->reserved.get());
            } else if (message->market_status_message_type.get() == 'N') {
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload"] = "packet.message.categorypayload.marketstatusmessage.marketstatusmessagepayload.approximateadjustedvolumemarketcentermessage";
                [[maybe_unused]] const auto* message_2 = protocol::ApproximateAdjustedVolumeMarketCenterMessage::parse(iterator.message + sizeof(protocol::MarketStatusMessage));
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximateadjustedvolumemarketcentermessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximateadjustedvolumemarketcentermessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximateadjustedvolumemarketcentermessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximateadjustedvolumemarketcentermessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximateadjustedvolumemarketcentermessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximateadjustedvolumemarketcentermessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximateadjustedvolumemarketcentermessage.numberofparticipants"] = canonical::number(message_2->number_of_participants.get());
            } else if (message->market_status_message_type.get() == 'O') {
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload"] = "packet.message.categorypayload.marketstatusmessage.marketstatusmessagepayload.approximatetradesandtotaldollarvaluemessage";
                [[maybe_unused]] const auto* message_2 = protocol::ApproximateTradesAndTotalDollarValueMessage::parse(iterator.message + sizeof(protocol::MarketStatusMessage));
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximatetradesandtotaldollarvaluemessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximatetradesandtotaldollarvaluemessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximatetradesandtotaldollarvaluemessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximatetradesandtotaldollarvaluemessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximatetradesandtotaldollarvaluemessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximatetradesandtotaldollarvaluemessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximatetradesandtotaldollarvaluemessage.totaltrades"] = canonical::number(message_2->total_trades.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximatetradesandtotaldollarvaluemessage.dollarvalue"] = canonical::scaled(message_2->dollar_value.integer(), -6);
            } else if (message->market_status_message_type.get() == 'P') {
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload"] = "packet.message.categorypayload.marketstatusmessage.marketstatusmessagepayload.crossingsessionsummarymessage";
                [[maybe_unused]] const auto* message_2 = protocol::CrossingSessionSummaryMessage::parse(iterator.message + sizeof(protocol::MarketStatusMessage));
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.crossingsessionsummarymessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.crossingsessionsummarymessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.crossingsessionsummarymessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.crossingsessionsummarymessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.crossingsessionsummarymessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.crossingsessionsummarymessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.crossingsessionsummarymessage.crossingsessionitotaltradesvolume"] = canonical::number(message_2->crossing_session_i_total_trades_volume.get());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.crossingsessionsummarymessage.crossingsessioniidollarvalue"] = canonical::scaled(message_2->crossing_session_ii_dollar_value.integer(), -6);
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.crossingsessionsummarymessage.crossingsessioniitotaltradesvolume"] = canonical::number(message_2->crossing_session_ii_total_trades_volume.get());
            }
        } else if (iterator.message_category == 'P') {
            values[entry + ".categorypayload"] = "packet.message.categorypayload.priordaymessage";
            [[maybe_unused]] const auto* message = protocol::PriorDayMessage::parse(iterator.message);
            values[entry + ".categorypayload.priordaymessage.priordaymessagetype"] = canonical::text(canonical::character(message->prior_day_message_type.get()));
            if (message->prior_day_message_type.get() == 'C') {
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload"] = "packet.message.categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage";
                [[maybe_unused]] const auto* message_2 = protocol::PriorDayTradeCorrectionMessage::parse(iterator.message + sizeof(protocol::PriorDayMessage));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.securitysymbol"] = canonical::text(std::string(message_2->security_symbol.get()), ' ', false);
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.instrumenttype"] = canonical::text(canonical::character(message_2->instrument_type.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.correctedtrade.saleconditions.settlementtype"] = canonical::text(canonical::character(message_2->corrected_trade.sale_conditions.settlement_type.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.correctedtrade.saleconditions.tradethroughexemptreason"] = canonical::text(canonical::character(message_2->corrected_trade.sale_conditions.trade_through_exempt_reason.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.correctedtrade.saleconditions.extendedhoursorsequencetype"] = canonical::text(canonical::character(message_2->corrected_trade.sale_conditions.extended_hours_or_sequence_type.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.correctedtrade.saleconditions.srotradedetail"] = canonical::text(canonical::character(message_2->corrected_trade.sale_conditions.sro_trade_detail.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.correctedtrade.tradeprice"] = canonical::scaled(message_2->corrected_trade.trade_price.integer(), -6);
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.correctedtrade.tradevolume"] = canonical::number(message_2->corrected_trade.trade_volume.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.correctedtrade.sellerssaledays"] = canonical::number(message_2->corrected_trade.sellers_sale_days.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.correctedtrade.stopstockindicator"] = canonical::text(canonical::character(message_2->corrected_trade.stop_stock_indicator.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.correctedtrade.tradethroughexemptindicator"] = canonical::text(canonical::character(message_2->corrected_trade.trade_through_exempt_indicator.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.correctedtrade.shortsalerestrictionindicator"] = canonical::text(canonical::character(message_2->corrected_trade.short_sale_restriction_indicator.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.correctedtrade.priordaytradedateandtime.seconds"] = canonical::number(message_2->corrected_trade.prior_day_trade_date_and_time.seconds.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.correctedtrade.priordaytradedateandtime.nanoseconds"] = canonical::number(message_2->corrected_trade.prior_day_trade_date_and_time.nanoseconds.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.tradereportingfacilityid"] = canonical::text(canonical::character(message_2->trade_reporting_facility_id.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.originaltrade.saleconditions.settlementtype"] = canonical::text(canonical::character(message_2->original_trade.sale_conditions.settlement_type.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.originaltrade.saleconditions.tradethroughexemptreason"] = canonical::text(canonical::character(message_2->original_trade.sale_conditions.trade_through_exempt_reason.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.originaltrade.saleconditions.extendedhoursorsequencetype"] = canonical::text(canonical::character(message_2->original_trade.sale_conditions.extended_hours_or_sequence_type.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.originaltrade.saleconditions.srotradedetail"] = canonical::text(canonical::character(message_2->original_trade.sale_conditions.sro_trade_detail.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.originaltrade.tradeprice"] = canonical::scaled(message_2->original_trade.trade_price.integer(), -6);
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.originaltrade.tradevolume"] = canonical::number(message_2->original_trade.trade_volume.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.originaltrade.sellerssaledays"] = canonical::number(message_2->original_trade.sellers_sale_days.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.originaltrade.stopstockindicator"] = canonical::text(canonical::character(message_2->original_trade.stop_stock_indicator.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.originaltrade.tradethroughexemptindicator"] = canonical::text(canonical::character(message_2->original_trade.trade_through_exempt_indicator.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.originaltrade.shortsalerestrictionindicator"] = canonical::text(canonical::character(message_2->original_trade.short_sale_restriction_indicator.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.originaltrade.priordaytradedateandtime.seconds"] = canonical::number(message_2->original_trade.prior_day_trade_date_and_time.seconds.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.originaltrade.priordaytradedateandtime.nanoseconds"] = canonical::number(message_2->original_trade.prior_day_trade_date_and_time.nanoseconds.get());
            } else if (message->prior_day_message_type.get() == 'T') {
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload"] = "packet.message.categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage";
                [[maybe_unused]] const auto* message_2 = protocol::PriorDayTradeMessage::parse(iterator.message + sizeof(protocol::PriorDayMessage));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.securitysymbol"] = canonical::text(std::string(message_2->security_symbol.get()), ' ', false);
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.instrumenttype"] = canonical::text(canonical::character(message_2->instrument_type.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.saleconditions.settlementtype"] = canonical::text(canonical::character(message_2->sale_conditions.settlement_type.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.saleconditions.tradethroughexemptreason"] = canonical::text(canonical::character(message_2->sale_conditions.trade_through_exempt_reason.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.saleconditions.extendedhoursorsequencetype"] = canonical::text(canonical::character(message_2->sale_conditions.extended_hours_or_sequence_type.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.saleconditions.srotradedetail"] = canonical::text(canonical::character(message_2->sale_conditions.sro_trade_detail.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.tradeprice"] = canonical::scaled(message_2->trade_price.integer(), -6);
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.tradevolume"] = canonical::number(message_2->trade_volume.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.sellerssaledays"] = canonical::number(message_2->sellers_sale_days.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.stopstockindicator"] = canonical::text(canonical::character(message_2->stop_stock_indicator.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.tradethroughexemptindicator"] = canonical::text(canonical::character(message_2->trade_through_exempt_indicator.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.shortsalerestrictionindicator"] = canonical::text(canonical::character(message_2->short_sale_restriction_indicator.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.tradereportingfacilityid"] = canonical::text(canonical::character(message_2->trade_reporting_facility_id.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.priordaytradedateandtime.seconds"] = canonical::number(message_2->prior_day_trade_date_and_time.seconds.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.priordaytradedateandtime.nanoseconds"] = canonical::number(message_2->prior_day_trade_date_and_time.nanoseconds.get());
            } else if (message->prior_day_message_type.get() == 'X') {
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload"] = "packet.message.categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage";
                [[maybe_unused]] const auto* message_2 = protocol::PriorDayTradeCancelErrorMessage::parse(iterator.message + sizeof(protocol::PriorDayMessage));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.securitysymbol"] = canonical::text(std::string(message_2->security_symbol.get()), ' ', false);
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.instrumenttype"] = canonical::text(canonical::character(message_2->instrument_type.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.saleconditions.settlementtype"] = canonical::text(canonical::character(message_2->sale_conditions.settlement_type.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.saleconditions.tradethroughexemptreason"] = canonical::text(canonical::character(message_2->sale_conditions.trade_through_exempt_reason.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.saleconditions.extendedhoursorsequencetype"] = canonical::text(canonical::character(message_2->sale_conditions.extended_hours_or_sequence_type.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.saleconditions.srotradedetail"] = canonical::text(canonical::character(message_2->sale_conditions.sro_trade_detail.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.tradeprice"] = canonical::scaled(message_2->trade_price.integer(), -6);
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.tradevolume"] = canonical::number(message_2->trade_volume.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.sellerssaledays"] = canonical::number(message_2->sellers_sale_days.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.stopstockindicator"] = canonical::text(canonical::character(message_2->stop_stock_indicator.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.tradethroughexemptindicator"] = canonical::text(canonical::character(message_2->trade_through_exempt_indicator.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.shortsalerestrictionindicator"] = canonical::text(canonical::character(message_2->short_sale_restriction_indicator.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.tradereportingfacilityid"] = canonical::text(canonical::character(message_2->trade_reporting_facility_id.get()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.priordaytradedateandtime.seconds"] = canonical::number(message_2->prior_day_trade_date_and_time.seconds.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.priordaytradedateandtime.nanoseconds"] = canonical::number(message_2->prior_day_trade_date_and_time.nanoseconds.get());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.cancelerroraction"] = canonical::text(canonical::character(message_2->cancel_error_action.get()));
            }
        } else if (iterator.message_category == 'S') {
            values[entry + ".categorypayload"] = "packet.message.categorypayload.summarymessage";
            [[maybe_unused]] const auto* message = protocol::SummaryMessage::parse(iterator.message);
            values[entry + ".categorypayload.summarymessage.summarymessagetype"] = canonical::text(canonical::character(message->summary_message_type.get()));
            if (message->summary_message_type.get() == 'A') {
                values[entry + ".categorypayload.summarymessage.summarymessagepayload"] = "packet.message.categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage";
                [[maybe_unused]] const auto* message_2 = protocol::ConsolidatedStartOfDaySummaryMessage::parse(iterator.message + sizeof(protocol::SummaryMessage));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.securitysymbol"] = canonical::text(std::string(message_2->security_symbol.get()), ' ', false);
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.instrumenttype"] = canonical::text(canonical::character(message_2->instrument_type.get()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.summaryparticipantid"] = canonical::text(canonical::character(message_2->summary_participant_id.get()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.previousclosepricedate"] = canonical::number(message_2->previous_close_price_date.get());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.previouscloseprice"] = canonical::scaled(message_2->previous_close_price.integer(), -6);
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.shortsalerestrictionindicator"] = canonical::text(canonical::character(message_2->short_sale_restriction_indicator.get()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character(message_2->primary_listing_market_participant_id.get()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.financialstatusindicator"] = canonical::text(canonical::character(message_2->financial_status_indicator.get()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.numberofparticipants"] = canonical::number(message_2->number_of_participants.get());
            } else if (message->summary_message_type.get() == 'B') {
                values[entry + ".categorypayload.summarymessage.summarymessagepayload"] = "packet.message.categorypayload.summarymessage.summarymessagepayload.participantstartofdaysummarymessage";
                [[maybe_unused]] const auto* message_2 = protocol::ParticipantStartOfDaySummaryMessage::parse(iterator.message + sizeof(protocol::SummaryMessage));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantstartofdaysummarymessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantstartofdaysummarymessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantstartofdaysummarymessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantstartofdaysummarymessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantstartofdaysummarymessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantstartofdaysummarymessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantstartofdaysummarymessage.securitysymbol"] = canonical::text(std::string(message_2->security_symbol.get()), ' ', false);
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantstartofdaysummarymessage.instrumenttype"] = canonical::text(canonical::character(message_2->instrument_type.get()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantstartofdaysummarymessage.summaryparticipantid"] = canonical::text(canonical::character(message_2->summary_participant_id.get()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantstartofdaysummarymessage.previousclosepricedate"] = canonical::number(message_2->previous_close_price_date.get());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantstartofdaysummarymessage.previouscloseprice"] = canonical::scaled(message_2->previous_close_price.integer(), -6);
            } else if (message->summary_message_type.get() == 'C') {
                values[entry + ".categorypayload.summarymessage.summarymessagepayload"] = "packet.message.categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage";
                [[maybe_unused]] const auto* message_2 = protocol::ConsolidatedEndOfDaySummaryMessage::parse(iterator.message + sizeof(protocol::SummaryMessage));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.securitysymbol"] = canonical::text(std::string(message_2->security_symbol.get()), ' ', false);
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.instrumenttype"] = canonical::text(canonical::character(message_2->instrument_type.get()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.lastparticipantid"] = canonical::text(canonical::character(message_2->last_participant_id.get()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.previousclosepricedate"] = canonical::number(message_2->previous_close_price_date.get());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.lastprice"] = canonical::scaled(message_2->last_price.integer(), -6);
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.highprice"] = canonical::scaled(message_2->high_price.integer(), -6);
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.lowprice"] = canonical::scaled(message_2->low_price.integer(), -6);
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.totalvolume"] = canonical::number(message_2->total_volume.get());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.shortsalerestrictionindicator"] = canonical::text(canonical::character(message_2->short_sale_restriction_indicator.get()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character(message_2->primary_listing_market_participant_id.get()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.financialstatusindicator"] = canonical::text(canonical::character(message_2->financial_status_indicator.get()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.numberofparticipants"] = canonical::number(message_2->number_of_participants.get());
            } else if (message->summary_message_type.get() == 'D') {
                values[entry + ".categorypayload.summarymessage.summarymessagepayload"] = "packet.message.categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage";
                [[maybe_unused]] const auto* message_2 = protocol::ParticipantEndOfDaySummaryMessage::parse(iterator.message + sizeof(protocol::SummaryMessage));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.securitysymbol"] = canonical::text(std::string(message_2->security_symbol.get()), ' ', false);
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.instrumenttype"] = canonical::text(canonical::character(message_2->instrument_type.get()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.initiatingparticipantid"] = canonical::text(canonical::character(message_2->initiating_participant_id.get()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.previousclosepricedate"] = canonical::number(message_2->previous_close_price_date.get());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.lastprice"] = canonical::scaled(message_2->last_price.integer(), -6);
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.highprice"] = canonical::scaled(message_2->high_price.integer(), -6);
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.lowprice"] = canonical::scaled(message_2->low_price.integer(), -6);
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.openprice"] = canonical::scaled(message_2->open_price.integer(), -6);
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.totalvolume"] = canonical::number(message_2->total_volume.get());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.tick"] = canonical::text(canonical::character(message_2->tick.get()));
            }
        } else if (iterator.message_category == 'T') {
            values[entry + ".categorypayload"] = "packet.message.categorypayload.trademessage";
            [[maybe_unused]] const auto* message = protocol::TradeMessage::parse(iterator.message);
            values[entry + ".categorypayload.trademessage.trademessagetype"] = canonical::text(canonical::character(message->trade_message_type.get()));
            if (message->trade_message_type.get() == 'A') {
                values[entry + ".categorypayload.trademessage.trademessagepayload"] = "packet.message.categorypayload.trademessage.trademessagepayload.auctionstatusmessage";
                [[maybe_unused]] const auto* message_2 = protocol::AuctionStatusMessage::parse(iterator.message + sizeof(protocol::TradeMessage));
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.securitysymbol"] = canonical::text(std::string(message_2->security_symbol.get()), ' ', false);
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.instrumenttype"] = canonical::text(canonical::character(message_2->instrument_type.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.auctioncollarreferenceprice"] = canonical::scaled(message_2->auction_collar_reference_price.integer(), -6);
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.auctioncollarupperthresholdprice"] = canonical::scaled(message_2->auction_collar_upper_threshold_price.integer(), -6);
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.auctioncollarlowerthresholdprice"] = canonical::scaled(message_2->auction_collar_lower_threshold_price.integer(), -6);
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.numberofextensions"] = canonical::number(message_2->number_of_extensions.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.shortsalerestrictionindicator"] = canonical::text(canonical::character(message_2->short_sale_restriction_indicator.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character(message_2->primary_listing_market_participant_id.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.financialstatusindicator"] = canonical::text(canonical::character(message_2->financial_status_indicator.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.futureuse"] = canonical::text(std::string(message_2->future_use.get()), ' ', false);
            } else if (message->trade_message_type.get() == 'C') {
                values[entry + ".categorypayload.trademessage.trademessagepayload"] = "packet.message.categorypayload.trademessage.trademessagepayload.tradecorrectionmessage";
                [[maybe_unused]] const auto* message_2 = protocol::TradeCorrectionMessage::parse(iterator.message + sizeof(protocol::TradeMessage));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.securitysymbol"] = canonical::text(std::string(message_2->security_symbol.get()), ' ', false);
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.instrumenttype"] = canonical::text(canonical::character(message_2->instrument_type.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.correctedtrade.saleconditions.settlementtype"] = canonical::text(canonical::character(message_2->corrected_trade.sale_conditions.settlement_type.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.correctedtrade.saleconditions.tradethroughexemptreason"] = canonical::text(canonical::character(message_2->corrected_trade.sale_conditions.trade_through_exempt_reason.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.correctedtrade.saleconditions.extendedhoursorsequencetype"] = canonical::text(canonical::character(message_2->corrected_trade.sale_conditions.extended_hours_or_sequence_type.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.correctedtrade.saleconditions.srotradedetail"] = canonical::text(canonical::character(message_2->corrected_trade.sale_conditions.sro_trade_detail.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.correctedtrade.tradeprice"] = canonical::scaled(message_2->corrected_trade.trade_price.integer(), -6);
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.correctedtrade.tradevolume"] = canonical::number(message_2->corrected_trade.trade_volume.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.correctedtrade.sellerssaledays"] = canonical::number(message_2->corrected_trade.sellers_sale_days.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.correctedtrade.stopstockindicator"] = canonical::text(canonical::character(message_2->corrected_trade.stop_stock_indicator.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.correctedtrade.tradethroughexemptindicator"] = canonical::text(canonical::character(message_2->corrected_trade.trade_through_exempt_indicator.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.correctedtrade.shortsalerestrictionindicator"] = canonical::text(canonical::character(message_2->corrected_trade.short_sale_restriction_indicator.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.correctedtrade.priordaytradedateandtime.seconds"] = canonical::number(message_2->corrected_trade.prior_day_trade_date_and_time.seconds.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.correctedtrade.priordaytradedateandtime.nanoseconds"] = canonical::number(message_2->corrected_trade.prior_day_trade_date_and_time.nanoseconds.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.tradereportingfacilityid"] = canonical::text(canonical::character(message_2->trade_reporting_facility_id.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.timestamp2.seconds"] = canonical::number(message_2->timestamp_2.seconds.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.timestamp2.nanoseconds"] = canonical::number(message_2->timestamp_2.nanoseconds.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.originalparticipantreferencenumber"] = canonical::number(message_2->original_participant_reference_number.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.originaltrade.saleconditions.settlementtype"] = canonical::text(canonical::character(message_2->original_trade.sale_conditions.settlement_type.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.originaltrade.saleconditions.tradethroughexemptreason"] = canonical::text(canonical::character(message_2->original_trade.sale_conditions.trade_through_exempt_reason.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.originaltrade.saleconditions.extendedhoursorsequencetype"] = canonical::text(canonical::character(message_2->original_trade.sale_conditions.extended_hours_or_sequence_type.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.originaltrade.saleconditions.srotradedetail"] = canonical::text(canonical::character(message_2->original_trade.sale_conditions.sro_trade_detail.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.originaltrade.tradeprice"] = canonical::scaled(message_2->original_trade.trade_price.integer(), -6);
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.originaltrade.tradevolume"] = canonical::number(message_2->original_trade.trade_volume.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.originaltrade.sellerssaledays"] = canonical::number(message_2->original_trade.sellers_sale_days.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.originaltrade.stopstockindicator"] = canonical::text(canonical::character(message_2->original_trade.stop_stock_indicator.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.originaltrade.tradethroughexemptindicator"] = canonical::text(canonical::character(message_2->original_trade.trade_through_exempt_indicator.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.originaltrade.shortsalerestrictionindicator"] = canonical::text(canonical::character(message_2->original_trade.short_sale_restriction_indicator.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.originaltrade.priordaytradedateandtime.seconds"] = canonical::number(message_2->original_trade.prior_day_trade_date_and_time.seconds.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.originaltrade.priordaytradedateandtime.nanoseconds"] = canonical::number(message_2->original_trade.prior_day_trade_date_and_time.nanoseconds.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character(message_2->primary_listing_market_participant_id.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.financialstatusindicator"] = canonical::text(canonical::character(message_2->financial_status_indicator.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.consolidateddata.previousclosepricedate"] = canonical::number(message_2->consolidated_data.previous_close_price_date.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.consolidateddata.lastparticipantid"] = canonical::text(canonical::character(message_2->consolidated_data.last_participant_id.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.consolidateddata.lastprice"] = canonical::scaled(message_2->consolidated_data.last_price.integer(), -6);
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.consolidateddata.highprice"] = canonical::scaled(message_2->consolidated_data.high_price.integer(), -6);
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.consolidateddata.lowprice"] = canonical::scaled(message_2->consolidated_data.low_price.integer(), -6);
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.consolidateddata.totalvolumeshort"] = canonical::number(message_2->consolidated_data.total_volume_short.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.consolidateddata.tick"] = canonical::text(canonical::character(message_2->consolidated_data.tick.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.participantdata.previousclosepricedate"] = canonical::number(message_2->participant_data.previous_close_price_date.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.participantdata.lastprice"] = canonical::scaled(message_2->participant_data.last_price.integer(), -6);
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.participantdata.highprice"] = canonical::scaled(message_2->participant_data.high_price.integer(), -6);
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.participantdata.lowprice"] = canonical::scaled(message_2->participant_data.low_price.integer(), -6);
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.participantdata.openprice"] = canonical::scaled(message_2->participant_data.open_price.integer(), -6);
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.participantdata.totalvolumeshort"] = canonical::number(message_2->participant_data.total_volume_short.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.participantdata.tick"] = canonical::text(canonical::character(message_2->participant_data.tick.get()));
            } else if (message->trade_message_type.get() == 'L') {
                values[entry + ".categorypayload.trademessage.trademessagepayload"] = "packet.message.categorypayload.trademessage.trademessagepayload.longtrademessage";
                [[maybe_unused]] const auto* message_2 = protocol::LongTradeMessage::parse(iterator.message + sizeof(protocol::TradeMessage));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.securitysymbol"] = canonical::text(std::string(message_2->security_symbol.get()), ' ', false);
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.instrumenttype"] = canonical::text(canonical::character(message_2->instrument_type.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.saleconditions.settlementtype"] = canonical::text(canonical::character(message_2->sale_conditions.settlement_type.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.saleconditions.tradethroughexemptreason"] = canonical::text(canonical::character(message_2->sale_conditions.trade_through_exempt_reason.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.saleconditions.extendedhoursorsequencetype"] = canonical::text(canonical::character(message_2->sale_conditions.extended_hours_or_sequence_type.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.saleconditions.srotradedetail"] = canonical::text(canonical::character(message_2->sale_conditions.sro_trade_detail.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.tradeprice"] = canonical::scaled(message_2->trade_price.integer(), -6);
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.tradevolume"] = canonical::number(message_2->trade_volume.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.sellerssaledays"] = canonical::number(message_2->sellers_sale_days.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.stopstockindicator"] = canonical::text(canonical::character(message_2->stop_stock_indicator.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.tradethroughexemptindicator"] = canonical::text(canonical::character(message_2->trade_through_exempt_indicator.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.tradereportingfacilityid"] = canonical::text(canonical::character(message_2->trade_reporting_facility_id.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.timestamp2.seconds"] = canonical::number(message_2->timestamp_2.seconds.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.timestamp2.nanoseconds"] = canonical::number(message_2->timestamp_2.nanoseconds.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.shortsalerestrictionindicator"] = canonical::text(canonical::character(message_2->short_sale_restriction_indicator.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character(message_2->primary_listing_market_participant_id.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.financialstatusindicator"] = canonical::text(canonical::character(message_2->financial_status_indicator.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.heldtradeindicator"] = canonical::text(canonical::character(message_2->held_trade_indicator.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.consolidatedhighlowlastindicator"] = canonical::text(canonical::character(message_2->consolidated_high_low_last_indicator.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.participantopenhighlowlastindicator"] = canonical::text(canonical::character(message_2->participant_open_high_low_last_indicator.get()));
            } else if (message->trade_message_type.get() == 'S') {
                values[entry + ".categorypayload.trademessage.trademessagepayload"] = "packet.message.categorypayload.trademessage.trademessagepayload.tradingstatusmessage";
                [[maybe_unused]] const auto* message_2 = protocol::TradingStatusMessage::parse(iterator.message + sizeof(protocol::TradeMessage));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.securitysymbol"] = canonical::text(std::string(message_2->security_symbol.get()), ' ', false);
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.instrumenttype"] = canonical::text(canonical::character(message_2->instrument_type.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.lastprice"] = canonical::scaled(message_2->last_price.integer(), -6);
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.highindicationpriceupperlimitpriceband"] = canonical::scaled(message_2->high_indication_price_upper_limit_price_band.integer(), -6);
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.lowindicationpricelowerlimitpriceband"] = canonical::scaled(message_2->low_indication_price_lower_limit_price_band.integer(), -6);
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.buyvolume"] = canonical::number(message_2->buy_volume.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.sellvolume"] = canonical::number(message_2->sell_volume.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.securitystatus"] = canonical::text(canonical::character(message_2->security_status.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.haltreason"] = canonical::text(canonical::character(message_2->halt_reason.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.shortsalerestrictionindicator"] = canonical::text(canonical::character(message_2->short_sale_restriction_indicator.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character(message_2->primary_listing_market_participant_id.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.financialstatusindicator"] = canonical::text(canonical::character(message_2->financial_status_indicator.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.limituplimitdownindicator"] = canonical::text(canonical::character(message_2->limit_up_limit_down_indicator.get()));
            } else if (message->trade_message_type.get() == 'T') {
                values[entry + ".categorypayload.trademessage.trademessagepayload"] = "packet.message.categorypayload.trademessage.trademessagepayload.shorttrademessage";
                [[maybe_unused]] const auto* message_2 = protocol::ShortTradeMessage::parse(iterator.message + sizeof(protocol::TradeMessage));
                values[entry + ".categorypayload.trademessage.trademessagepayload.shorttrademessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.shorttrademessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.shorttrademessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.shorttrademessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.shorttrademessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.shorttrademessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.shorttrademessage.securitysymbolshort"] = canonical::text(std::string(message_2->security_symbol_short.get()), ' ', false);
                values[entry + ".categorypayload.trademessage.trademessagepayload.shorttrademessage.salecondition"] = canonical::text(canonical::character(message_2->sale_condition.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.shorttrademessage.saleconditioncategory"] = canonical::text(canonical::character(message_2->sale_condition_category.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.shorttrademessage.tradepriceshort"] = canonical::scaled(message_2->trade_price_short.integer(), -2);
                values[entry + ".categorypayload.trademessage.trademessagepayload.shorttrademessage.tradevolumeshort"] = canonical::number(message_2->trade_volume_short.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.shorttrademessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character(message_2->primary_listing_market_participant_id.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.shorttrademessage.consolidatedhighlowlastindicator"] = canonical::text(canonical::character(message_2->consolidated_high_low_last_indicator.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.shorttrademessage.participantopenhighlowlastindicator"] = canonical::text(canonical::character(message_2->participant_open_high_low_last_indicator.get()));
            } else if (message->trade_message_type.get() == 'X') {
                values[entry + ".categorypayload.trademessage.trademessagepayload"] = "packet.message.categorypayload.trademessage.trademessagepayload.tradecancelerrormessage";
                [[maybe_unused]] const auto* message_2 = protocol::TradeCancelErrorMessage::parse(iterator.message + sizeof(protocol::TradeMessage));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.participantid"] = canonical::text(canonical::character(message_2->participant_id.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.timestamp1.seconds"] = canonical::number(message_2->timestamp_1.seconds.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.timestamp1.nanoseconds"] = canonical::number(message_2->timestamp_1.nanoseconds.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.messageid"] = canonical::number(message_2->message_id.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.securitysymbol"] = canonical::text(std::string(message_2->security_symbol.get()), ' ', false);
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.instrumenttype"] = canonical::text(canonical::character(message_2->instrument_type.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.saleconditions.settlementtype"] = canonical::text(canonical::character(message_2->sale_conditions.settlement_type.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.saleconditions.tradethroughexemptreason"] = canonical::text(canonical::character(message_2->sale_conditions.trade_through_exempt_reason.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.saleconditions.extendedhoursorsequencetype"] = canonical::text(canonical::character(message_2->sale_conditions.extended_hours_or_sequence_type.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.saleconditions.srotradedetail"] = canonical::text(canonical::character(message_2->sale_conditions.sro_trade_detail.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.tradeprice"] = canonical::scaled(message_2->trade_price.integer(), -6);
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.tradevolume"] = canonical::number(message_2->trade_volume.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.sellerssaledays"] = canonical::number(message_2->sellers_sale_days.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.stopstockindicator"] = canonical::text(canonical::character(message_2->stop_stock_indicator.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.tradethroughexemptindicator"] = canonical::text(canonical::character(message_2->trade_through_exempt_indicator.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.tradereportingfacilityid"] = canonical::text(canonical::character(message_2->trade_reporting_facility_id.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.originalparticipantreferencenumber"] = canonical::number(message_2->original_participant_reference_number.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.timestamp2.seconds"] = canonical::number(message_2->timestamp_2.seconds.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.timestamp2.nanoseconds"] = canonical::number(message_2->timestamp_2.nanoseconds.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.cancelerroraction"] = canonical::text(canonical::character(message_2->cancel_error_action.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.shortsalerestrictionindicator"] = canonical::text(canonical::character(message_2->short_sale_restriction_indicator.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character(message_2->primary_listing_market_participant_id.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.financialstatusindicator"] = canonical::text(canonical::character(message_2->financial_status_indicator.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.consolidateddata.previousclosepricedate"] = canonical::number(message_2->consolidated_data.previous_close_price_date.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.consolidateddata.lastparticipantid"] = canonical::text(canonical::character(message_2->consolidated_data.last_participant_id.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.consolidateddata.lastprice"] = canonical::scaled(message_2->consolidated_data.last_price.integer(), -6);
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.consolidateddata.highprice"] = canonical::scaled(message_2->consolidated_data.high_price.integer(), -6);
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.consolidateddata.lowprice"] = canonical::scaled(message_2->consolidated_data.low_price.integer(), -6);
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.consolidateddata.totalvolumeshort"] = canonical::number(message_2->consolidated_data.total_volume_short.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.consolidateddata.tick"] = canonical::text(canonical::character(message_2->consolidated_data.tick.get()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.participantdata.previousclosepricedate"] = canonical::number(message_2->participant_data.previous_close_price_date.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.participantdata.lastprice"] = canonical::scaled(message_2->participant_data.last_price.integer(), -6);
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.participantdata.highprice"] = canonical::scaled(message_2->participant_data.high_price.integer(), -6);
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.participantdata.lowprice"] = canonical::scaled(message_2->participant_data.low_price.integer(), -6);
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.participantdata.openprice"] = canonical::scaled(message_2->participant_data.open_price.integer(), -6);
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.participantdata.totalvolumeshort"] = canonical::number(message_2->participant_data.total_volume_short.get());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.participantdata.tick"] = canonical::text(canonical::character(message_2->participant_data.tick.get()));
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
    std::printf("== Siac.Cts.Output.Cta.v2.9 (modern values)\n");
    int failures = 0;
    failures += check("LineIntegrityMessage", "Siac/Cts.Output.Cta.v2.9/LineIntegrityMessage.pcap", "siac/cts/output/cta/v2.9/LineIntegrityMessage.values");
    failures += check("LongTradeMessage", "Siac/Cts.Output.Cta.v2.9/LongTradeMessage.pcap", "siac/cts/output/cta/v2.9/LongTradeMessage.values");
    failures += check("TradingStatusMessage", "Siac/Cts.Output.Cta.v2.9/TradingStatusMessage.pcap", "siac/cts/output/cta/v2.9/TradingStatusMessage.values");
    return failures == 0 ? 0 : 1;
}
