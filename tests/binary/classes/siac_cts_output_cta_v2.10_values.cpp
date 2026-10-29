// Siac.Cts.Output.Cta.v2.10 canonical values, through the Classes Packet: every value Classes decodes from
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
#include "cpp/binary/classes/siac/cts/output/cta/v2.10/definitions.hpp"

namespace protocol = ::siac::cts::output::cta::v2_10;

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

    values["packet.blockheader.version"] = canonical::number(packet.block_header().version());
    values["packet.blockheader.blocksize"] = canonical::number(packet.block_header().block_size());
    values["packet.blockheader.datafeedindicator"] = canonical::text(canonical::character(packet.block_header().data_feed_indicator()));
    values["packet.blockheader.retransmissionindicator"] = canonical::text(canonical::character(packet.block_header().retransmission_indicator()));
    values["packet.blockheader.blocksequencenumber"] = canonical::number(packet.block_header().block_sequence_number());
    values["packet.blockheader.messagesinblock"] = canonical::number(packet.block_header().messages_in_block());
    values["packet.blockheader.sipblocktimestamp.seconds"] = canonical::number(packet.block_header().sip_block_timestamp().seconds());
    values["packet.blockheader.sipblocktimestamp.nanoseconds"] = canonical::number(packet.block_header().sip_block_timestamp().nanoseconds());
    values["packet.blockheader.blockchecksum"] = canonical::number(packet.block_header().block_checksum());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".messagelength"] = canonical::number(each.message_length());
        values[entry + ".messagecategory"] = canonical::text(canonical::character(each.message_category()));

        if (const auto* message = dynamic_cast<const protocol::AdministrativeMessage*>(each.message())) {
            values[entry + ".categorypayload"] = "packet.message.categorypayload.administrativemessage";
            values[entry + ".categorypayload.administrativemessage.administrativemessagetype"] = canonical::text(canonical::character((*message).administrative_message_type()));
            if (const auto* message_2 = dynamic_cast<const protocol::StartOfEndOfDayMessage*>(message->administrative_message_payload())) {
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload"] = "packet.message.categorypayload.administrativemessage.administrativemessagepayload.startofendofdaymessage";
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.startofendofdaymessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.startofendofdaymessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.startofendofdaymessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.startofendofdaymessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.startofendofdaymessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.startofendofdaymessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
            } else if (const auto* message_2 = dynamic_cast<const protocol::EndOfEndOfDayMessage*>(message->administrative_message_payload())) {
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload"] = "packet.message.categorypayload.administrativemessage.administrativemessagepayload.endofendofdaymessage";
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.endofendofdaymessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.endofendofdaymessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.endofendofdaymessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.endofendofdaymessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.endofendofdaymessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.endofendofdaymessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
            } else if (const auto* message_2 = dynamic_cast<const protocol::StartOfStartOfDayMessage*>(message->administrative_message_payload())) {
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload"] = "packet.message.categorypayload.administrativemessage.administrativemessagepayload.startofstartofdaymessage";
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.startofstartofdaymessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.startofstartofdaymessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.startofstartofdaymessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.startofstartofdaymessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.startofstartofdaymessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.startofstartofdaymessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
            } else if (const auto* message_2 = dynamic_cast<const protocol::EndOfStartOfDayMessage*>(message->administrative_message_payload())) {
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload"] = "packet.message.categorypayload.administrativemessage.administrativemessagepayload.endofstartofdaymessage";
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.endofstartofdaymessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.endofstartofdaymessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.endofstartofdaymessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.endofstartofdaymessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.endofstartofdaymessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.endofstartofdaymessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
            }
        } else if (const auto* message = dynamic_cast<const protocol::ControlMessage*>(each.message())) {
            values[entry + ".categorypayload"] = "packet.message.categorypayload.controlmessage";
            values[entry + ".categorypayload.controlmessage.controlmessagetype"] = canonical::text(canonical::character((*message).control_message_type()));
            if (const auto* message_2 = dynamic_cast<const protocol::StartOfDayMessage*>(message->control_message_payload())) {
                values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.startofdaymessage";
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
            } else if (const auto* message_2 = dynamic_cast<const protocol::ResetBlockSequenceNumberMessage*>(message->control_message_payload())) {
                values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage";
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
            } else if (const auto* message_2 = dynamic_cast<const protocol::DisasterRecoveryDataCenterActivationMessage*>(message->control_message_payload())) {
                values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage";
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
            } else if (const auto* message_2 = dynamic_cast<const protocol::LineIntegrityMessage*>(message->control_message_payload())) {
                values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.lineintegritymessage";
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
            } else if (const auto* message_2 = dynamic_cast<const protocol::EndOfDayMessage*>(message->control_message_payload())) {
                values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.endofdaymessage";
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
            }
        } else if (const auto* message = dynamic_cast<const protocol::IndicesMessage*>(each.message())) {
            values[entry + ".categorypayload"] = "packet.message.categorypayload.indicesmessage";
            values[entry + ".categorypayload.indicesmessage.indicesmessagetype"] = canonical::text(canonical::character((*message).indices_message_type()));
            if (const auto* message_2 = dynamic_cast<const protocol::IndexMessage*>(message->indices_message_payload())) {
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload"] = "packet.message.categorypayload.indicesmessage.indicesmessagepayload.indexmessage";
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.indexmessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.indexmessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.indexmessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.indexmessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.indexmessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.indexmessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.indexmessage.indexsymbol"] = canonical::text(std::string((*message_2).index_symbol()), ' ', false);
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.indexmessage.indexvalue"] = canonical::scaled((*message_2).index_value().mantissa(), (*message_2).index_value().exponent());
            } else if (const auto* message_2 = dynamic_cast<const protocol::BidAndOfferIndexMessage*>(message->indices_message_payload())) {
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload"] = "packet.message.categorypayload.indicesmessage.indicesmessagepayload.bidandofferindexmessage";
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.bidandofferindexmessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.bidandofferindexmessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.bidandofferindexmessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.bidandofferindexmessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.bidandofferindexmessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.bidandofferindexmessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.bidandofferindexmessage.indexsymbol"] = canonical::text(std::string((*message_2).index_symbol()), ' ', false);
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.bidandofferindexmessage.bidindexvalue"] = canonical::scaled((*message_2).bid_index_value().mantissa(), (*message_2).bid_index_value().exponent());
                values[entry + ".categorypayload.indicesmessage.indicesmessagepayload.bidandofferindexmessage.offerindexvalue"] = canonical::scaled((*message_2).offer_index_value().mantissa(), (*message_2).offer_index_value().exponent());
            }
        } else if (const auto* message = dynamic_cast<const protocol::MarketStatusMessage*>(each.message())) {
            values[entry + ".categorypayload"] = "packet.message.categorypayload.marketstatusmessage";
            values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagetype"] = canonical::text(canonical::character((*message).market_status_message_type()));
            if (const auto* message_2 = dynamic_cast<const protocol::MarketWideCircuitBreakerDeclineLevelStatusMessage*>(message->market_status_message_payload())) {
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload"] = "packet.message.categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage";
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.mwcblevel1"] = canonical::scaled((*message_2).mwcb_level_1().mantissa(), (*message_2).mwcb_level_1().exponent());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.mwcblevel2"] = canonical::scaled((*message_2).mwcb_level_2().mantissa(), (*message_2).mwcb_level_2().exponent());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.mwcblevel3"] = canonical::scaled((*message_2).mwcb_level_3().mantissa(), (*message_2).mwcb_level_3().exponent());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.reserved"] = canonical::number((*message_2).reserved());
            } else if (const auto* message_2 = dynamic_cast<const protocol::MarketWideCircuitBreakerStatusMessage*>(message->market_status_message_payload())) {
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload"] = "packet.message.categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage";
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.marketwidecircuitbreakerlevelindicator"] = canonical::text(canonical::character((*message_2).market_wide_circuit_breaker_level_indicator()));
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.reserved"] = canonical::number((*message_2).reserved());
            } else if (const auto* message_2 = dynamic_cast<const protocol::ApproximateAdjustedVolumeMarketCenterMessage*>(message->market_status_message_payload())) {
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload"] = "packet.message.categorypayload.marketstatusmessage.marketstatusmessagepayload.approximateadjustedvolumemarketcentermessage";
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximateadjustedvolumemarketcentermessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximateadjustedvolumemarketcentermessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximateadjustedvolumemarketcentermessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximateadjustedvolumemarketcentermessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximateadjustedvolumemarketcentermessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximateadjustedvolumemarketcentermessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximateadjustedvolumemarketcentermessage.numberofparticipants"] = canonical::number((*message_2).number_of_participants());
            } else if (const auto* message_2 = dynamic_cast<const protocol::FractionalApproximateAdjustedVolumeMarketCenterMessage*>(message->market_status_message_payload())) {
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload"] = "packet.message.categorypayload.marketstatusmessage.marketstatusmessagepayload.fractionalapproximateadjustedvolumemarketcentermessage";
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.fractionalapproximateadjustedvolumemarketcentermessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.fractionalapproximateadjustedvolumemarketcentermessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.fractionalapproximateadjustedvolumemarketcentermessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.fractionalapproximateadjustedvolumemarketcentermessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.fractionalapproximateadjustedvolumemarketcentermessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.fractionalapproximateadjustedvolumemarketcentermessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.fractionalapproximateadjustedvolumemarketcentermessage.numberofparticipants"] = canonical::number((*message_2).number_of_participants());
            } else if (const auto* message_2 = dynamic_cast<const protocol::ApproximateTradesAndTotalDollarValueMessage*>(message->market_status_message_payload())) {
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload"] = "packet.message.categorypayload.marketstatusmessage.marketstatusmessagepayload.approximatetradesandtotaldollarvaluemessage";
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximatetradesandtotaldollarvaluemessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximatetradesandtotaldollarvaluemessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximatetradesandtotaldollarvaluemessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximatetradesandtotaldollarvaluemessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximatetradesandtotaldollarvaluemessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximatetradesandtotaldollarvaluemessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximatetradesandtotaldollarvaluemessage.totaltrades"] = canonical::number((*message_2).total_trades());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.approximatetradesandtotaldollarvaluemessage.dollarvalue"] = canonical::scaled((*message_2).dollar_value().mantissa(), (*message_2).dollar_value().exponent());
            } else if (const auto* message_2 = dynamic_cast<const protocol::CrossingSessionSummaryMessage*>(message->market_status_message_payload())) {
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload"] = "packet.message.categorypayload.marketstatusmessage.marketstatusmessagepayload.crossingsessionsummarymessage";
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.crossingsessionsummarymessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.crossingsessionsummarymessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.crossingsessionsummarymessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.crossingsessionsummarymessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.crossingsessionsummarymessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.crossingsessionsummarymessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.crossingsessionsummarymessage.crossingsessionitotaltradesvolume"] = canonical::number((*message_2).crossing_session_i_total_trades_volume());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.crossingsessionsummarymessage.crossingsessioniidollarvalue"] = canonical::scaled((*message_2).crossing_session_ii_dollar_value().mantissa(), (*message_2).crossing_session_ii_dollar_value().exponent());
                values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.crossingsessionsummarymessage.crossingsessioniitotaltradesvolume"] = canonical::number((*message_2).crossing_session_ii_total_trades_volume());
            }
        } else if (const auto* message = dynamic_cast<const protocol::PriorDayMessage*>(each.message())) {
            values[entry + ".categorypayload"] = "packet.message.categorypayload.priordaymessage";
            values[entry + ".categorypayload.priordaymessage.priordaymessagetype"] = canonical::text(canonical::character((*message).prior_day_message_type()));
            if (const auto* message_2 = dynamic_cast<const protocol::PriorDayTradeCorrectionMessage*>(message->prior_day_message_payload())) {
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload"] = "packet.message.categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage";
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.securitysymbol"] = canonical::text(std::string((*message_2).security_symbol()), ' ', false);
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.instrumenttype"] = canonical::text(canonical::character((*message_2).instrument_type()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.priordaycorrectedtrade.saleconditions.settlementtype"] = canonical::text(canonical::character((*message_2).prior_day_corrected_trade().sale_conditions().settlement_type()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.priordaycorrectedtrade.saleconditions.tradethroughexemptreason"] = canonical::text(canonical::character((*message_2).prior_day_corrected_trade().sale_conditions().trade_through_exempt_reason()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.priordaycorrectedtrade.saleconditions.extendedhoursorsequencetype"] = canonical::text(canonical::character((*message_2).prior_day_corrected_trade().sale_conditions().extended_hours_or_sequence_type()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.priordaycorrectedtrade.saleconditions.srotradedetail"] = canonical::text(canonical::character((*message_2).prior_day_corrected_trade().sale_conditions().sro_trade_detail()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.priordaycorrectedtrade.tradeprice"] = canonical::scaled((*message_2).prior_day_corrected_trade().trade_price().mantissa(), (*message_2).prior_day_corrected_trade().trade_price().exponent());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.priordaycorrectedtrade.tradevolume"] = canonical::number((*message_2).prior_day_corrected_trade().trade_volume());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.priordaycorrectedtrade.sellerssaledays"] = canonical::number((*message_2).prior_day_corrected_trade().sellers_sale_days());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.priordaycorrectedtrade.stopstockindicator"] = canonical::text(canonical::character((*message_2).prior_day_corrected_trade().stop_stock_indicator()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.priordaycorrectedtrade.tradethroughexemptindicator"] = canonical::text(canonical::character((*message_2).prior_day_corrected_trade().trade_through_exempt_indicator()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.priordaycorrectedtrade.shortsalerestrictionindicator"] = canonical::text(canonical::character((*message_2).prior_day_corrected_trade().short_sale_restriction_indicator()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.priordaycorrectedtrade.priordaytradedateandtime.seconds"] = canonical::number((*message_2).prior_day_corrected_trade().prior_day_trade_date_and_time().seconds());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.priordaycorrectedtrade.priordaytradedateandtime.nanoseconds"] = canonical::number((*message_2).prior_day_corrected_trade().prior_day_trade_date_and_time().nanoseconds());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.tradereportingfacilityid"] = canonical::text(canonical::character((*message_2).trade_reporting_facility_id()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.priordayoriginaltrade.saleconditions.settlementtype"] = canonical::text(canonical::character((*message_2).prior_day_original_trade().sale_conditions().settlement_type()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.priordayoriginaltrade.saleconditions.tradethroughexemptreason"] = canonical::text(canonical::character((*message_2).prior_day_original_trade().sale_conditions().trade_through_exempt_reason()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.priordayoriginaltrade.saleconditions.extendedhoursorsequencetype"] = canonical::text(canonical::character((*message_2).prior_day_original_trade().sale_conditions().extended_hours_or_sequence_type()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.priordayoriginaltrade.saleconditions.srotradedetail"] = canonical::text(canonical::character((*message_2).prior_day_original_trade().sale_conditions().sro_trade_detail()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.priordayoriginaltrade.tradeprice"] = canonical::scaled((*message_2).prior_day_original_trade().trade_price().mantissa(), (*message_2).prior_day_original_trade().trade_price().exponent());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.priordayoriginaltrade.tradevolume"] = canonical::number((*message_2).prior_day_original_trade().trade_volume());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.priordayoriginaltrade.sellerssaledays"] = canonical::number((*message_2).prior_day_original_trade().sellers_sale_days());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.priordayoriginaltrade.stopstockindicator"] = canonical::text(canonical::character((*message_2).prior_day_original_trade().stop_stock_indicator()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.priordayoriginaltrade.tradethroughexemptindicator"] = canonical::text(canonical::character((*message_2).prior_day_original_trade().trade_through_exempt_indicator()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.priordayoriginaltrade.shortsalerestrictionindicator"] = canonical::text(canonical::character((*message_2).prior_day_original_trade().short_sale_restriction_indicator()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.priordayoriginaltrade.priordaytradedateandtime.seconds"] = canonical::number((*message_2).prior_day_original_trade().prior_day_trade_date_and_time().seconds());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecorrectionmessage.priordayoriginaltrade.priordaytradedateandtime.nanoseconds"] = canonical::number((*message_2).prior_day_original_trade().prior_day_trade_date_and_time().nanoseconds());
            } else if (const auto* message_2 = dynamic_cast<const protocol::FractionalPriorDayTradeCorrectionMessage*>(message->prior_day_message_payload())) {
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload"] = "packet.message.categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage";
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.securitysymbol"] = canonical::text(std::string((*message_2).security_symbol()), ' ', false);
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.instrumenttype"] = canonical::text(canonical::character((*message_2).instrument_type()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.fractionalpriordaycorrectedtrade.saleconditions.settlementtype"] = canonical::text(canonical::character((*message_2).fractional_prior_day_corrected_trade().sale_conditions().settlement_type()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.fractionalpriordaycorrectedtrade.saleconditions.tradethroughexemptreason"] = canonical::text(canonical::character((*message_2).fractional_prior_day_corrected_trade().sale_conditions().trade_through_exempt_reason()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.fractionalpriordaycorrectedtrade.saleconditions.extendedhoursorsequencetype"] = canonical::text(canonical::character((*message_2).fractional_prior_day_corrected_trade().sale_conditions().extended_hours_or_sequence_type()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.fractionalpriordaycorrectedtrade.saleconditions.srotradedetail"] = canonical::text(canonical::character((*message_2).fractional_prior_day_corrected_trade().sale_conditions().sro_trade_detail()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.fractionalpriordaycorrectedtrade.tradeprice"] = canonical::scaled((*message_2).fractional_prior_day_corrected_trade().trade_price().mantissa(), (*message_2).fractional_prior_day_corrected_trade().trade_price().exponent());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.fractionalpriordaycorrectedtrade.fractionaltradevolume"] = canonical::scaled((*message_2).fractional_prior_day_corrected_trade().fractional_trade_volume().mantissa(), (*message_2).fractional_prior_day_corrected_trade().fractional_trade_volume().exponent());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.fractionalpriordaycorrectedtrade.sellerssaledays"] = canonical::number((*message_2).fractional_prior_day_corrected_trade().sellers_sale_days());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.fractionalpriordaycorrectedtrade.stopstockindicator"] = canonical::text(canonical::character((*message_2).fractional_prior_day_corrected_trade().stop_stock_indicator()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.fractionalpriordaycorrectedtrade.tradethroughexemptindicator"] = canonical::text(canonical::character((*message_2).fractional_prior_day_corrected_trade().trade_through_exempt_indicator()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.fractionalpriordaycorrectedtrade.shortsalerestrictionindicator"] = canonical::text(canonical::character((*message_2).fractional_prior_day_corrected_trade().short_sale_restriction_indicator()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.fractionalpriordaycorrectedtrade.priordaytradedateandtime.seconds"] = canonical::number((*message_2).fractional_prior_day_corrected_trade().prior_day_trade_date_and_time().seconds());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.fractionalpriordaycorrectedtrade.priordaytradedateandtime.nanoseconds"] = canonical::number((*message_2).fractional_prior_day_corrected_trade().prior_day_trade_date_and_time().nanoseconds());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.tradereportingfacilityid"] = canonical::text(canonical::character((*message_2).trade_reporting_facility_id()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.fractionalpriordayoriginaltrade.saleconditions.settlementtype"] = canonical::text(canonical::character((*message_2).fractional_prior_day_original_trade().sale_conditions().settlement_type()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.fractionalpriordayoriginaltrade.saleconditions.tradethroughexemptreason"] = canonical::text(canonical::character((*message_2).fractional_prior_day_original_trade().sale_conditions().trade_through_exempt_reason()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.fractionalpriordayoriginaltrade.saleconditions.extendedhoursorsequencetype"] = canonical::text(canonical::character((*message_2).fractional_prior_day_original_trade().sale_conditions().extended_hours_or_sequence_type()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.fractionalpriordayoriginaltrade.saleconditions.srotradedetail"] = canonical::text(canonical::character((*message_2).fractional_prior_day_original_trade().sale_conditions().sro_trade_detail()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.fractionalpriordayoriginaltrade.tradeprice"] = canonical::scaled((*message_2).fractional_prior_day_original_trade().trade_price().mantissa(), (*message_2).fractional_prior_day_original_trade().trade_price().exponent());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.fractionalpriordayoriginaltrade.fractionaltradevolume"] = canonical::scaled((*message_2).fractional_prior_day_original_trade().fractional_trade_volume().mantissa(), (*message_2).fractional_prior_day_original_trade().fractional_trade_volume().exponent());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.fractionalpriordayoriginaltrade.sellerssaledays"] = canonical::number((*message_2).fractional_prior_day_original_trade().sellers_sale_days());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.fractionalpriordayoriginaltrade.stopstockindicator"] = canonical::text(canonical::character((*message_2).fractional_prior_day_original_trade().stop_stock_indicator()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.fractionalpriordayoriginaltrade.tradethroughexemptindicator"] = canonical::text(canonical::character((*message_2).fractional_prior_day_original_trade().trade_through_exempt_indicator()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.fractionalpriordayoriginaltrade.shortsalerestrictionindicator"] = canonical::text(canonical::character((*message_2).fractional_prior_day_original_trade().short_sale_restriction_indicator()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.fractionalpriordayoriginaltrade.priordaytradedateandtime.seconds"] = canonical::number((*message_2).fractional_prior_day_original_trade().prior_day_trade_date_and_time().seconds());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecorrectionmessage.fractionalpriordayoriginaltrade.priordaytradedateandtime.nanoseconds"] = canonical::number((*message_2).fractional_prior_day_original_trade().prior_day_trade_date_and_time().nanoseconds());
            } else if (const auto* message_2 = dynamic_cast<const protocol::PriorDayTradeMessage*>(message->prior_day_message_payload())) {
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload"] = "packet.message.categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage";
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.securitysymbol"] = canonical::text(std::string((*message_2).security_symbol()), ' ', false);
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.instrumenttype"] = canonical::text(canonical::character((*message_2).instrument_type()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.saleconditions.settlementtype"] = canonical::text(canonical::character((*message_2).sale_conditions().settlement_type()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.saleconditions.tradethroughexemptreason"] = canonical::text(canonical::character((*message_2).sale_conditions().trade_through_exempt_reason()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.saleconditions.extendedhoursorsequencetype"] = canonical::text(canonical::character((*message_2).sale_conditions().extended_hours_or_sequence_type()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.saleconditions.srotradedetail"] = canonical::text(canonical::character((*message_2).sale_conditions().sro_trade_detail()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.tradeprice"] = canonical::scaled((*message_2).trade_price().mantissa(), (*message_2).trade_price().exponent());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.tradevolume"] = canonical::number((*message_2).trade_volume());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.sellerssaledays"] = canonical::number((*message_2).sellers_sale_days());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.stopstockindicator"] = canonical::text(canonical::character((*message_2).stop_stock_indicator()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.tradethroughexemptindicator"] = canonical::text(canonical::character((*message_2).trade_through_exempt_indicator()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.shortsalerestrictionindicator"] = canonical::text(canonical::character((*message_2).short_sale_restriction_indicator()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.tradereportingfacilityid"] = canonical::text(canonical::character((*message_2).trade_reporting_facility_id()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.priordaytradedateandtime.seconds"] = canonical::number((*message_2).prior_day_trade_date_and_time().seconds());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytrademessage.priordaytradedateandtime.nanoseconds"] = canonical::number((*message_2).prior_day_trade_date_and_time().nanoseconds());
            } else if (const auto* message_2 = dynamic_cast<const protocol::FractionalPriorDayTradeMessage*>(message->prior_day_message_payload())) {
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload"] = "packet.message.categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytrademessage";
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytrademessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytrademessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytrademessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytrademessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytrademessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytrademessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytrademessage.securitysymbol"] = canonical::text(std::string((*message_2).security_symbol()), ' ', false);
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytrademessage.instrumenttype"] = canonical::text(canonical::character((*message_2).instrument_type()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytrademessage.saleconditions.settlementtype"] = canonical::text(canonical::character((*message_2).sale_conditions().settlement_type()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytrademessage.saleconditions.tradethroughexemptreason"] = canonical::text(canonical::character((*message_2).sale_conditions().trade_through_exempt_reason()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytrademessage.saleconditions.extendedhoursorsequencetype"] = canonical::text(canonical::character((*message_2).sale_conditions().extended_hours_or_sequence_type()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytrademessage.saleconditions.srotradedetail"] = canonical::text(canonical::character((*message_2).sale_conditions().sro_trade_detail()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytrademessage.tradeprice"] = canonical::scaled((*message_2).trade_price().mantissa(), (*message_2).trade_price().exponent());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytrademessage.fractionaltradevolume"] = canonical::scaled((*message_2).fractional_trade_volume().mantissa(), (*message_2).fractional_trade_volume().exponent());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytrademessage.sellerssaledays"] = canonical::number((*message_2).sellers_sale_days());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytrademessage.stopstockindicator"] = canonical::text(canonical::character((*message_2).stop_stock_indicator()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytrademessage.tradethroughexemptindicator"] = canonical::text(canonical::character((*message_2).trade_through_exempt_indicator()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytrademessage.shortsalerestrictionindicator"] = canonical::text(canonical::character((*message_2).short_sale_restriction_indicator()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytrademessage.tradereportingfacilityid"] = canonical::text(canonical::character((*message_2).trade_reporting_facility_id()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytrademessage.priordaytradedateandtime.seconds"] = canonical::number((*message_2).prior_day_trade_date_and_time().seconds());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytrademessage.priordaytradedateandtime.nanoseconds"] = canonical::number((*message_2).prior_day_trade_date_and_time().nanoseconds());
            } else if (const auto* message_2 = dynamic_cast<const protocol::PriorDayTradeCancelErrorMessage*>(message->prior_day_message_payload())) {
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload"] = "packet.message.categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage";
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.securitysymbol"] = canonical::text(std::string((*message_2).security_symbol()), ' ', false);
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.instrumenttype"] = canonical::text(canonical::character((*message_2).instrument_type()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.saleconditions.settlementtype"] = canonical::text(canonical::character((*message_2).sale_conditions().settlement_type()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.saleconditions.tradethroughexemptreason"] = canonical::text(canonical::character((*message_2).sale_conditions().trade_through_exempt_reason()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.saleconditions.extendedhoursorsequencetype"] = canonical::text(canonical::character((*message_2).sale_conditions().extended_hours_or_sequence_type()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.saleconditions.srotradedetail"] = canonical::text(canonical::character((*message_2).sale_conditions().sro_trade_detail()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.tradeprice"] = canonical::scaled((*message_2).trade_price().mantissa(), (*message_2).trade_price().exponent());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.tradevolume"] = canonical::number((*message_2).trade_volume());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.sellerssaledays"] = canonical::number((*message_2).sellers_sale_days());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.stopstockindicator"] = canonical::text(canonical::character((*message_2).stop_stock_indicator()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.tradethroughexemptindicator"] = canonical::text(canonical::character((*message_2).trade_through_exempt_indicator()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.shortsalerestrictionindicator"] = canonical::text(canonical::character((*message_2).short_sale_restriction_indicator()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.tradereportingfacilityid"] = canonical::text(canonical::character((*message_2).trade_reporting_facility_id()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.priordaytradedateandtime.seconds"] = canonical::number((*message_2).prior_day_trade_date_and_time().seconds());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.priordaytradedateandtime.nanoseconds"] = canonical::number((*message_2).prior_day_trade_date_and_time().nanoseconds());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.priordaytradecancelerrormessage.cancelerroraction"] = canonical::text(canonical::character((*message_2).cancel_error_action()));
            } else if (const auto* message_2 = dynamic_cast<const protocol::FractionalPriorDayTradeCancelErrorMessage*>(message->prior_day_message_payload())) {
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload"] = "packet.message.categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecancelerrormessage";
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecancelerrormessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecancelerrormessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecancelerrormessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecancelerrormessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecancelerrormessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecancelerrormessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecancelerrormessage.securitysymbol"] = canonical::text(std::string((*message_2).security_symbol()), ' ', false);
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecancelerrormessage.instrumenttype"] = canonical::text(canonical::character((*message_2).instrument_type()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecancelerrormessage.saleconditions.settlementtype"] = canonical::text(canonical::character((*message_2).sale_conditions().settlement_type()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecancelerrormessage.saleconditions.tradethroughexemptreason"] = canonical::text(canonical::character((*message_2).sale_conditions().trade_through_exempt_reason()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecancelerrormessage.saleconditions.extendedhoursorsequencetype"] = canonical::text(canonical::character((*message_2).sale_conditions().extended_hours_or_sequence_type()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecancelerrormessage.saleconditions.srotradedetail"] = canonical::text(canonical::character((*message_2).sale_conditions().sro_trade_detail()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecancelerrormessage.tradeprice"] = canonical::scaled((*message_2).trade_price().mantissa(), (*message_2).trade_price().exponent());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecancelerrormessage.fractionaltradevolume"] = canonical::scaled((*message_2).fractional_trade_volume().mantissa(), (*message_2).fractional_trade_volume().exponent());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecancelerrormessage.sellerssaledays"] = canonical::number((*message_2).sellers_sale_days());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecancelerrormessage.stopstockindicator"] = canonical::text(canonical::character((*message_2).stop_stock_indicator()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecancelerrormessage.tradethroughexemptindicator"] = canonical::text(canonical::character((*message_2).trade_through_exempt_indicator()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecancelerrormessage.shortsalerestrictionindicator"] = canonical::text(canonical::character((*message_2).short_sale_restriction_indicator()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecancelerrormessage.tradereportingfacilityid"] = canonical::text(canonical::character((*message_2).trade_reporting_facility_id()));
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecancelerrormessage.priordaytradedateandtime.seconds"] = canonical::number((*message_2).prior_day_trade_date_and_time().seconds());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecancelerrormessage.priordaytradedateandtime.nanoseconds"] = canonical::number((*message_2).prior_day_trade_date_and_time().nanoseconds());
                values[entry + ".categorypayload.priordaymessage.priordaymessagepayload.fractionalpriordaytradecancelerrormessage.cancelerroraction"] = canonical::text(canonical::character((*message_2).cancel_error_action()));
            }
        } else if (const auto* message = dynamic_cast<const protocol::SummaryMessage*>(each.message())) {
            values[entry + ".categorypayload"] = "packet.message.categorypayload.summarymessage";
            values[entry + ".categorypayload.summarymessage.summarymessagetype"] = canonical::text(canonical::character((*message).summary_message_type()));
            if (const auto* message_2 = dynamic_cast<const protocol::ConsolidatedStartOfDaySummaryMessage*>(message->summary_message_payload())) {
                values[entry + ".categorypayload.summarymessage.summarymessagepayload"] = "packet.message.categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage";
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.securitysymbol"] = canonical::text(std::string((*message_2).security_symbol()), ' ', false);
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.instrumenttype"] = canonical::text(canonical::character((*message_2).instrument_type()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.summaryparticipantid"] = canonical::text(canonical::character((*message_2).summary_participant_id()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.previousclosepricedate"] = canonical::number((*message_2).previous_close_price_date());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.previouscloseprice"] = canonical::scaled((*message_2).previous_close_price().mantissa(), (*message_2).previous_close_price().exponent());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.shortsalerestrictionindicator"] = canonical::text(canonical::character((*message_2).short_sale_restriction_indicator()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character((*message_2).primary_listing_market_participant_id()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.financialstatusindicator"] = canonical::text(canonical::character((*message_2).financial_status_indicator()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedstartofdaysummarymessage.numberofparticipants"] = canonical::number((*message_2).number_of_participants());
            } else if (const auto* message_2 = dynamic_cast<const protocol::ParticipantStartOfDaySummaryMessage*>(message->summary_message_payload())) {
                values[entry + ".categorypayload.summarymessage.summarymessagepayload"] = "packet.message.categorypayload.summarymessage.summarymessagepayload.participantstartofdaysummarymessage";
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantstartofdaysummarymessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantstartofdaysummarymessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantstartofdaysummarymessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantstartofdaysummarymessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantstartofdaysummarymessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantstartofdaysummarymessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantstartofdaysummarymessage.securitysymbol"] = canonical::text(std::string((*message_2).security_symbol()), ' ', false);
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantstartofdaysummarymessage.instrumenttype"] = canonical::text(canonical::character((*message_2).instrument_type()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantstartofdaysummarymessage.summaryparticipantid"] = canonical::text(canonical::character((*message_2).summary_participant_id()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantstartofdaysummarymessage.previousclosepricedate"] = canonical::number((*message_2).previous_close_price_date());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantstartofdaysummarymessage.previouscloseprice"] = canonical::scaled((*message_2).previous_close_price().mantissa(), (*message_2).previous_close_price().exponent());
            } else if (const auto* message_2 = dynamic_cast<const protocol::ConsolidatedEndOfDaySummaryMessage*>(message->summary_message_payload())) {
                values[entry + ".categorypayload.summarymessage.summarymessagepayload"] = "packet.message.categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage";
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.securitysymbol"] = canonical::text(std::string((*message_2).security_symbol()), ' ', false);
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.instrumenttype"] = canonical::text(canonical::character((*message_2).instrument_type()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.lastparticipantid"] = canonical::text(canonical::character((*message_2).last_participant_id()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.previousclosepricedate"] = canonical::number((*message_2).previous_close_price_date());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.lastprice"] = canonical::scaled((*message_2).last_price().mantissa(), (*message_2).last_price().exponent());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.highprice"] = canonical::scaled((*message_2).high_price().mantissa(), (*message_2).high_price().exponent());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.lowprice"] = canonical::scaled((*message_2).low_price().mantissa(), (*message_2).low_price().exponent());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.totalvolume"] = canonical::number((*message_2).total_volume());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.shortsalerestrictionindicator"] = canonical::text(canonical::character((*message_2).short_sale_restriction_indicator()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character((*message_2).primary_listing_market_participant_id()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.financialstatusindicator"] = canonical::text(canonical::character((*message_2).financial_status_indicator()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.consolidatedendofdaysummarymessage.numberofparticipants"] = canonical::number((*message_2).number_of_participants());
            } else if (const auto* message_2 = dynamic_cast<const protocol::FractionalConsolidatedEndOfDaySummaryMessage*>(message->summary_message_payload())) {
                values[entry + ".categorypayload.summarymessage.summarymessagepayload"] = "packet.message.categorypayload.summarymessage.summarymessagepayload.fractionalconsolidatedendofdaysummarymessage";
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalconsolidatedendofdaysummarymessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalconsolidatedendofdaysummarymessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalconsolidatedendofdaysummarymessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalconsolidatedendofdaysummarymessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalconsolidatedendofdaysummarymessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalconsolidatedendofdaysummarymessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalconsolidatedendofdaysummarymessage.securitysymbol"] = canonical::text(std::string((*message_2).security_symbol()), ' ', false);
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalconsolidatedendofdaysummarymessage.instrumenttype"] = canonical::text(canonical::character((*message_2).instrument_type()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalconsolidatedendofdaysummarymessage.lastparticipantid"] = canonical::text(canonical::character((*message_2).last_participant_id()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalconsolidatedendofdaysummarymessage.previousclosepricedate"] = canonical::number((*message_2).previous_close_price_date());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalconsolidatedendofdaysummarymessage.lastprice"] = canonical::scaled((*message_2).last_price().mantissa(), (*message_2).last_price().exponent());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalconsolidatedendofdaysummarymessage.highprice"] = canonical::scaled((*message_2).high_price().mantissa(), (*message_2).high_price().exponent());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalconsolidatedendofdaysummarymessage.lowprice"] = canonical::scaled((*message_2).low_price().mantissa(), (*message_2).low_price().exponent());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalconsolidatedendofdaysummarymessage.fractionaltotalvolume"] = canonical::scaled((*message_2).fractional_total_volume().mantissa(), (*message_2).fractional_total_volume().exponent());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalconsolidatedendofdaysummarymessage.shortsalerestrictionindicator"] = canonical::text(canonical::character((*message_2).short_sale_restriction_indicator()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalconsolidatedendofdaysummarymessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character((*message_2).primary_listing_market_participant_id()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalconsolidatedendofdaysummarymessage.financialstatusindicator"] = canonical::text(canonical::character((*message_2).financial_status_indicator()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalconsolidatedendofdaysummarymessage.numberofparticipants"] = canonical::number((*message_2).number_of_participants());
            } else if (const auto* message_2 = dynamic_cast<const protocol::ParticipantEndOfDaySummaryMessage*>(message->summary_message_payload())) {
                values[entry + ".categorypayload.summarymessage.summarymessagepayload"] = "packet.message.categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage";
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.securitysymbol"] = canonical::text(std::string((*message_2).security_symbol()), ' ', false);
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.instrumenttype"] = canonical::text(canonical::character((*message_2).instrument_type()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.initiatingparticipantid"] = canonical::text(canonical::character((*message_2).initiating_participant_id()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.previousclosepricedate"] = canonical::number((*message_2).previous_close_price_date());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.lastprice"] = canonical::scaled((*message_2).last_price().mantissa(), (*message_2).last_price().exponent());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.highprice"] = canonical::scaled((*message_2).high_price().mantissa(), (*message_2).high_price().exponent());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.lowprice"] = canonical::scaled((*message_2).low_price().mantissa(), (*message_2).low_price().exponent());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.openprice"] = canonical::scaled((*message_2).open_price().mantissa(), (*message_2).open_price().exponent());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.totalvolume"] = canonical::number((*message_2).total_volume());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.participantendofdaysummarymessage.tick"] = canonical::text(canonical::character((*message_2).tick()));
            } else if (const auto* message_2 = dynamic_cast<const protocol::FractionalParticipantEndOfDaySummaryMessage*>(message->summary_message_payload())) {
                values[entry + ".categorypayload.summarymessage.summarymessagepayload"] = "packet.message.categorypayload.summarymessage.summarymessagepayload.fractionalparticipantendofdaysummarymessage";
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalparticipantendofdaysummarymessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalparticipantendofdaysummarymessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalparticipantendofdaysummarymessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalparticipantendofdaysummarymessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalparticipantendofdaysummarymessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalparticipantendofdaysummarymessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalparticipantendofdaysummarymessage.securitysymbol"] = canonical::text(std::string((*message_2).security_symbol()), ' ', false);
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalparticipantendofdaysummarymessage.instrumenttype"] = canonical::text(canonical::character((*message_2).instrument_type()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalparticipantendofdaysummarymessage.initiatingparticipantid"] = canonical::text(canonical::character((*message_2).initiating_participant_id()));
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalparticipantendofdaysummarymessage.previousclosepricedate"] = canonical::number((*message_2).previous_close_price_date());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalparticipantendofdaysummarymessage.lastprice"] = canonical::scaled((*message_2).last_price().mantissa(), (*message_2).last_price().exponent());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalparticipantendofdaysummarymessage.highprice"] = canonical::scaled((*message_2).high_price().mantissa(), (*message_2).high_price().exponent());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalparticipantendofdaysummarymessage.lowprice"] = canonical::scaled((*message_2).low_price().mantissa(), (*message_2).low_price().exponent());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalparticipantendofdaysummarymessage.openprice"] = canonical::scaled((*message_2).open_price().mantissa(), (*message_2).open_price().exponent());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalparticipantendofdaysummarymessage.fractionaltotalvolume"] = canonical::scaled((*message_2).fractional_total_volume().mantissa(), (*message_2).fractional_total_volume().exponent());
                values[entry + ".categorypayload.summarymessage.summarymessagepayload.fractionalparticipantendofdaysummarymessage.tick"] = canonical::text(canonical::character((*message_2).tick()));
            }
        } else if (const auto* message = dynamic_cast<const protocol::TradeMessage*>(each.message())) {
            values[entry + ".categorypayload"] = "packet.message.categorypayload.trademessage";
            values[entry + ".categorypayload.trademessage.trademessagetype"] = canonical::text(canonical::character((*message).trade_message_type()));
            if (const auto* message_2 = dynamic_cast<const protocol::AuctionStatusMessage*>(message->trade_message_payload())) {
                values[entry + ".categorypayload.trademessage.trademessagepayload"] = "packet.message.categorypayload.trademessage.trademessagepayload.auctionstatusmessage";
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.securitysymbol"] = canonical::text(std::string((*message_2).security_symbol()), ' ', false);
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.instrumenttype"] = canonical::text(canonical::character((*message_2).instrument_type()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.auctioncollarreferenceprice"] = canonical::scaled((*message_2).auction_collar_reference_price().mantissa(), (*message_2).auction_collar_reference_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.auctioncollarupperthresholdprice"] = canonical::scaled((*message_2).auction_collar_upper_threshold_price().mantissa(), (*message_2).auction_collar_upper_threshold_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.auctioncollarlowerthresholdprice"] = canonical::scaled((*message_2).auction_collar_lower_threshold_price().mantissa(), (*message_2).auction_collar_lower_threshold_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.numberofextensions"] = canonical::number((*message_2).number_of_extensions());
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.shortsalerestrictionindicator"] = canonical::text(canonical::character((*message_2).short_sale_restriction_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character((*message_2).primary_listing_market_participant_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.financialstatusindicator"] = canonical::text(canonical::character((*message_2).financial_status_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.auctionstatusmessage.futureuse"] = canonical::text(std::string((*message_2).future_use()), ' ', false);
            } else if (const auto* message_2 = dynamic_cast<const protocol::TradeCorrectionMessage*>(message->trade_message_payload())) {
                values[entry + ".categorypayload.trademessage.trademessagepayload"] = "packet.message.categorypayload.trademessage.trademessagepayload.tradecorrectionmessage";
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.securitysymbol"] = canonical::text(std::string((*message_2).security_symbol()), ' ', false);
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.instrumenttype"] = canonical::text(canonical::character((*message_2).instrument_type()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.correctedtrade.saleconditions.settlementtype"] = canonical::text(canonical::character((*message_2).corrected_trade().sale_conditions().settlement_type()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.correctedtrade.saleconditions.tradethroughexemptreason"] = canonical::text(canonical::character((*message_2).corrected_trade().sale_conditions().trade_through_exempt_reason()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.correctedtrade.saleconditions.extendedhoursorsequencetype"] = canonical::text(canonical::character((*message_2).corrected_trade().sale_conditions().extended_hours_or_sequence_type()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.correctedtrade.saleconditions.srotradedetail"] = canonical::text(canonical::character((*message_2).corrected_trade().sale_conditions().sro_trade_detail()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.correctedtrade.tradeprice"] = canonical::scaled((*message_2).corrected_trade().trade_price().mantissa(), (*message_2).corrected_trade().trade_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.correctedtrade.tradevolume"] = canonical::number((*message_2).corrected_trade().trade_volume());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.correctedtrade.sellerssaledays"] = canonical::number((*message_2).corrected_trade().sellers_sale_days());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.correctedtrade.stopstockindicator"] = canonical::text(canonical::character((*message_2).corrected_trade().stop_stock_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.correctedtrade.tradethroughexemptindicator"] = canonical::text(canonical::character((*message_2).corrected_trade().trade_through_exempt_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.correctedtrade.shortsalerestrictionindicator"] = canonical::text(canonical::character((*message_2).corrected_trade().short_sale_restriction_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.tradereportingfacilityid"] = canonical::text(canonical::character((*message_2).trade_reporting_facility_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.timestamp2.seconds"] = canonical::number((*message_2).timestamp_2().seconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.timestamp2.nanoseconds"] = canonical::number((*message_2).timestamp_2().nanoseconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.originalparticipantreferencenumber"] = canonical::number((*message_2).original_participant_reference_number());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.originaltrade.saleconditions.settlementtype"] = canonical::text(canonical::character((*message_2).original_trade().sale_conditions().settlement_type()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.originaltrade.saleconditions.tradethroughexemptreason"] = canonical::text(canonical::character((*message_2).original_trade().sale_conditions().trade_through_exempt_reason()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.originaltrade.saleconditions.extendedhoursorsequencetype"] = canonical::text(canonical::character((*message_2).original_trade().sale_conditions().extended_hours_or_sequence_type()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.originaltrade.saleconditions.srotradedetail"] = canonical::text(canonical::character((*message_2).original_trade().sale_conditions().sro_trade_detail()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.originaltrade.tradeprice"] = canonical::scaled((*message_2).original_trade().trade_price().mantissa(), (*message_2).original_trade().trade_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.originaltrade.tradevolume"] = canonical::number((*message_2).original_trade().trade_volume());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.originaltrade.sellerssaledays"] = canonical::number((*message_2).original_trade().sellers_sale_days());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.originaltrade.stopstockindicator"] = canonical::text(canonical::character((*message_2).original_trade().stop_stock_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.originaltrade.tradethroughexemptindicator"] = canonical::text(canonical::character((*message_2).original_trade().trade_through_exempt_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.originaltrade.shortsalerestrictionindicator"] = canonical::text(canonical::character((*message_2).original_trade().short_sale_restriction_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character((*message_2).primary_listing_market_participant_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.financialstatusindicator"] = canonical::text(canonical::character((*message_2).financial_status_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.consolidateddata.previousclosepricedate"] = canonical::number((*message_2).consolidated_data().previous_close_price_date());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.consolidateddata.lastparticipantid"] = canonical::text(canonical::character((*message_2).consolidated_data().last_participant_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.consolidateddata.lastprice"] = canonical::scaled((*message_2).consolidated_data().last_price().mantissa(), (*message_2).consolidated_data().last_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.consolidateddata.highprice"] = canonical::scaled((*message_2).consolidated_data().high_price().mantissa(), (*message_2).consolidated_data().high_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.consolidateddata.lowprice"] = canonical::scaled((*message_2).consolidated_data().low_price().mantissa(), (*message_2).consolidated_data().low_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.consolidateddata.totalvolumeshort"] = canonical::number((*message_2).consolidated_data().total_volume_short());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.consolidateddata.tick"] = canonical::text(canonical::character((*message_2).consolidated_data().tick()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.participantdata.previousclosepricedate"] = canonical::number((*message_2).participant_data().previous_close_price_date());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.participantdata.lastprice"] = canonical::scaled((*message_2).participant_data().last_price().mantissa(), (*message_2).participant_data().last_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.participantdata.highprice"] = canonical::scaled((*message_2).participant_data().high_price().mantissa(), (*message_2).participant_data().high_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.participantdata.lowprice"] = canonical::scaled((*message_2).participant_data().low_price().mantissa(), (*message_2).participant_data().low_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.participantdata.openprice"] = canonical::scaled((*message_2).participant_data().open_price().mantissa(), (*message_2).participant_data().open_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.participantdata.totalvolumeshort"] = canonical::number((*message_2).participant_data().total_volume_short());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecorrectionmessage.participantdata.tick"] = canonical::text(canonical::character((*message_2).participant_data().tick()));
            } else if (const auto* message_2 = dynamic_cast<const protocol::FractionalTradeCorrectionMessage*>(message->trade_message_payload())) {
                values[entry + ".categorypayload.trademessage.trademessagepayload"] = "packet.message.categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage";
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.securitysymbol"] = canonical::text(std::string((*message_2).security_symbol()), ' ', false);
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.instrumenttype"] = canonical::text(canonical::character((*message_2).instrument_type()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionalcorrectedtrade.saleconditions.settlementtype"] = canonical::text(canonical::character((*message_2).fractional_corrected_trade().sale_conditions().settlement_type()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionalcorrectedtrade.saleconditions.tradethroughexemptreason"] = canonical::text(canonical::character((*message_2).fractional_corrected_trade().sale_conditions().trade_through_exempt_reason()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionalcorrectedtrade.saleconditions.extendedhoursorsequencetype"] = canonical::text(canonical::character((*message_2).fractional_corrected_trade().sale_conditions().extended_hours_or_sequence_type()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionalcorrectedtrade.saleconditions.srotradedetail"] = canonical::text(canonical::character((*message_2).fractional_corrected_trade().sale_conditions().sro_trade_detail()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionalcorrectedtrade.tradeprice"] = canonical::scaled((*message_2).fractional_corrected_trade().trade_price().mantissa(), (*message_2).fractional_corrected_trade().trade_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionalcorrectedtrade.fractionaltradevolume"] = canonical::scaled((*message_2).fractional_corrected_trade().fractional_trade_volume().mantissa(), (*message_2).fractional_corrected_trade().fractional_trade_volume().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionalcorrectedtrade.sellerssaledays"] = canonical::number((*message_2).fractional_corrected_trade().sellers_sale_days());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionalcorrectedtrade.stopstockindicator"] = canonical::text(canonical::character((*message_2).fractional_corrected_trade().stop_stock_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionalcorrectedtrade.tradethroughexemptindicator"] = canonical::text(canonical::character((*message_2).fractional_corrected_trade().trade_through_exempt_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionalcorrectedtrade.shortsalerestrictionindicator"] = canonical::text(canonical::character((*message_2).fractional_corrected_trade().short_sale_restriction_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.tradereportingfacilityid"] = canonical::text(canonical::character((*message_2).trade_reporting_facility_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.timestamp2.seconds"] = canonical::number((*message_2).timestamp_2().seconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.timestamp2.nanoseconds"] = canonical::number((*message_2).timestamp_2().nanoseconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.originalparticipantreferencenumber"] = canonical::number((*message_2).original_participant_reference_number());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionaloriginaltrade.saleconditions.settlementtype"] = canonical::text(canonical::character((*message_2).fractional_original_trade().sale_conditions().settlement_type()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionaloriginaltrade.saleconditions.tradethroughexemptreason"] = canonical::text(canonical::character((*message_2).fractional_original_trade().sale_conditions().trade_through_exempt_reason()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionaloriginaltrade.saleconditions.extendedhoursorsequencetype"] = canonical::text(canonical::character((*message_2).fractional_original_trade().sale_conditions().extended_hours_or_sequence_type()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionaloriginaltrade.saleconditions.srotradedetail"] = canonical::text(canonical::character((*message_2).fractional_original_trade().sale_conditions().sro_trade_detail()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionaloriginaltrade.tradeprice"] = canonical::scaled((*message_2).fractional_original_trade().trade_price().mantissa(), (*message_2).fractional_original_trade().trade_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionaloriginaltrade.fractionaltradevolume"] = canonical::scaled((*message_2).fractional_original_trade().fractional_trade_volume().mantissa(), (*message_2).fractional_original_trade().fractional_trade_volume().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionaloriginaltrade.sellerssaledays"] = canonical::number((*message_2).fractional_original_trade().sellers_sale_days());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionaloriginaltrade.stopstockindicator"] = canonical::text(canonical::character((*message_2).fractional_original_trade().stop_stock_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionaloriginaltrade.tradethroughexemptindicator"] = canonical::text(canonical::character((*message_2).fractional_original_trade().trade_through_exempt_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionaloriginaltrade.shortsalerestrictionindicator"] = canonical::text(canonical::character((*message_2).fractional_original_trade().short_sale_restriction_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character((*message_2).primary_listing_market_participant_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.financialstatusindicator"] = canonical::text(canonical::character((*message_2).financial_status_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionalconsolidateddata.previousclosepricedate"] = canonical::number((*message_2).fractional_consolidated_data().previous_close_price_date());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionalconsolidateddata.lastparticipantid"] = canonical::text(canonical::character((*message_2).fractional_consolidated_data().last_participant_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionalconsolidateddata.lastprice"] = canonical::scaled((*message_2).fractional_consolidated_data().last_price().mantissa(), (*message_2).fractional_consolidated_data().last_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionalconsolidateddata.highprice"] = canonical::scaled((*message_2).fractional_consolidated_data().high_price().mantissa(), (*message_2).fractional_consolidated_data().high_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionalconsolidateddata.lowprice"] = canonical::scaled((*message_2).fractional_consolidated_data().low_price().mantissa(), (*message_2).fractional_consolidated_data().low_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionalconsolidateddata.fractionaltotalvolume"] = canonical::scaled((*message_2).fractional_consolidated_data().fractional_total_volume().mantissa(), (*message_2).fractional_consolidated_data().fractional_total_volume().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionalconsolidateddata.tick"] = canonical::text(canonical::character((*message_2).fractional_consolidated_data().tick()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionalparticipantdata.previousclosepricedate"] = canonical::number((*message_2).fractional_participant_data().previous_close_price_date());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionalparticipantdata.lastprice"] = canonical::scaled((*message_2).fractional_participant_data().last_price().mantissa(), (*message_2).fractional_participant_data().last_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionalparticipantdata.highprice"] = canonical::scaled((*message_2).fractional_participant_data().high_price().mantissa(), (*message_2).fractional_participant_data().high_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionalparticipantdata.lowprice"] = canonical::scaled((*message_2).fractional_participant_data().low_price().mantissa(), (*message_2).fractional_participant_data().low_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionalparticipantdata.openprice"] = canonical::scaled((*message_2).fractional_participant_data().open_price().mantissa(), (*message_2).fractional_participant_data().open_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionalparticipantdata.fractionaltotalvolume"] = canonical::scaled((*message_2).fractional_participant_data().fractional_total_volume().mantissa(), (*message_2).fractional_participant_data().fractional_total_volume().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecorrectionmessage.fractionalparticipantdata.tick"] = canonical::text(canonical::character((*message_2).fractional_participant_data().tick()));
            } else if (const auto* message_2 = dynamic_cast<const protocol::LongTradeMessage*>(message->trade_message_payload())) {
                values[entry + ".categorypayload.trademessage.trademessagepayload"] = "packet.message.categorypayload.trademessage.trademessagepayload.longtrademessage";
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.securitysymbol"] = canonical::text(std::string((*message_2).security_symbol()), ' ', false);
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.instrumenttype"] = canonical::text(canonical::character((*message_2).instrument_type()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.saleconditions.settlementtype"] = canonical::text(canonical::character((*message_2).sale_conditions().settlement_type()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.saleconditions.tradethroughexemptreason"] = canonical::text(canonical::character((*message_2).sale_conditions().trade_through_exempt_reason()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.saleconditions.extendedhoursorsequencetype"] = canonical::text(canonical::character((*message_2).sale_conditions().extended_hours_or_sequence_type()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.saleconditions.srotradedetail"] = canonical::text(canonical::character((*message_2).sale_conditions().sro_trade_detail()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.tradeprice"] = canonical::scaled((*message_2).trade_price().mantissa(), (*message_2).trade_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.tradevolume"] = canonical::number((*message_2).trade_volume());
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.sellerssaledays"] = canonical::number((*message_2).sellers_sale_days());
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.stopstockindicator"] = canonical::text(canonical::character((*message_2).stop_stock_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.tradethroughexemptindicator"] = canonical::text(canonical::character((*message_2).trade_through_exempt_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.tradereportingfacilityid"] = canonical::text(canonical::character((*message_2).trade_reporting_facility_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.timestamp2.seconds"] = canonical::number((*message_2).timestamp_2().seconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.timestamp2.nanoseconds"] = canonical::number((*message_2).timestamp_2().nanoseconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.shortsalerestrictionindicator"] = canonical::text(canonical::character((*message_2).short_sale_restriction_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character((*message_2).primary_listing_market_participant_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.financialstatusindicator"] = canonical::text(canonical::character((*message_2).financial_status_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.heldtradeindicator"] = canonical::text(canonical::character((*message_2).held_trade_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.consolidatedhighlowlastindicator"] = canonical::text(canonical::character((*message_2).consolidated_high_low_last_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.longtrademessage.participantopenhighlowlastindicator"] = canonical::text(canonical::character((*message_2).participant_open_high_low_last_indicator()));
            } else if (const auto* message_2 = dynamic_cast<const protocol::FractionalLongTradeMessage*>(message->trade_message_payload())) {
                values[entry + ".categorypayload.trademessage.trademessagepayload"] = "packet.message.categorypayload.trademessage.trademessagepayload.fractionallongtrademessage";
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionallongtrademessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionallongtrademessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionallongtrademessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionallongtrademessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionallongtrademessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionallongtrademessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionallongtrademessage.securitysymbol"] = canonical::text(std::string((*message_2).security_symbol()), ' ', false);
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionallongtrademessage.instrumenttype"] = canonical::text(canonical::character((*message_2).instrument_type()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionallongtrademessage.saleconditions.settlementtype"] = canonical::text(canonical::character((*message_2).sale_conditions().settlement_type()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionallongtrademessage.saleconditions.tradethroughexemptreason"] = canonical::text(canonical::character((*message_2).sale_conditions().trade_through_exempt_reason()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionallongtrademessage.saleconditions.extendedhoursorsequencetype"] = canonical::text(canonical::character((*message_2).sale_conditions().extended_hours_or_sequence_type()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionallongtrademessage.saleconditions.srotradedetail"] = canonical::text(canonical::character((*message_2).sale_conditions().sro_trade_detail()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionallongtrademessage.tradeprice"] = canonical::scaled((*message_2).trade_price().mantissa(), (*message_2).trade_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionallongtrademessage.fractionaltradevolume"] = canonical::scaled((*message_2).fractional_trade_volume().mantissa(), (*message_2).fractional_trade_volume().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionallongtrademessage.sellerssaledays"] = canonical::number((*message_2).sellers_sale_days());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionallongtrademessage.stopstockindicator"] = canonical::text(canonical::character((*message_2).stop_stock_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionallongtrademessage.tradethroughexemptindicator"] = canonical::text(canonical::character((*message_2).trade_through_exempt_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionallongtrademessage.tradereportingfacilityid"] = canonical::text(canonical::character((*message_2).trade_reporting_facility_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionallongtrademessage.timestamp2.seconds"] = canonical::number((*message_2).timestamp_2().seconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionallongtrademessage.timestamp2.nanoseconds"] = canonical::number((*message_2).timestamp_2().nanoseconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionallongtrademessage.shortsalerestrictionindicator"] = canonical::text(canonical::character((*message_2).short_sale_restriction_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionallongtrademessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character((*message_2).primary_listing_market_participant_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionallongtrademessage.financialstatusindicator"] = canonical::text(canonical::character((*message_2).financial_status_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionallongtrademessage.heldtradeindicator"] = canonical::text(canonical::character((*message_2).held_trade_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionallongtrademessage.consolidatedhighlowlastindicator"] = canonical::text(canonical::character((*message_2).consolidated_high_low_last_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionallongtrademessage.participantopenhighlowlastindicator"] = canonical::text(canonical::character((*message_2).participant_open_high_low_last_indicator()));
            } else if (const auto* message_2 = dynamic_cast<const protocol::TradingStatusMessage*>(message->trade_message_payload())) {
                values[entry + ".categorypayload.trademessage.trademessagepayload"] = "packet.message.categorypayload.trademessage.trademessagepayload.tradingstatusmessage";
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.securitysymbol"] = canonical::text(std::string((*message_2).security_symbol()), ' ', false);
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.instrumenttype"] = canonical::text(canonical::character((*message_2).instrument_type()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.lastprice"] = canonical::scaled((*message_2).last_price().mantissa(), (*message_2).last_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.highindicationpriceupperlimitpriceband"] = canonical::scaled((*message_2).high_indication_price_upper_limit_price_band().mantissa(), (*message_2).high_indication_price_upper_limit_price_band().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.lowindicationpricelowerlimitpriceband"] = canonical::scaled((*message_2).low_indication_price_lower_limit_price_band().mantissa(), (*message_2).low_indication_price_lower_limit_price_band().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.buyvolume"] = canonical::number((*message_2).buy_volume());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.sellvolume"] = canonical::number((*message_2).sell_volume());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.securitystatus"] = canonical::text(canonical::character((*message_2).security_status()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.haltreason"] = canonical::text(canonical::character((*message_2).halt_reason()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.shortsalerestrictionindicator"] = canonical::text(canonical::character((*message_2).short_sale_restriction_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character((*message_2).primary_listing_market_participant_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.financialstatusindicator"] = canonical::text(canonical::character((*message_2).financial_status_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradingstatusmessage.limituplimitdownindicator"] = canonical::text(canonical::character((*message_2).limit_up_limit_down_indicator()));
            } else if (const auto* message_2 = dynamic_cast<const protocol::ShortTradeMessage*>(message->trade_message_payload())) {
                values[entry + ".categorypayload.trademessage.trademessagepayload"] = "packet.message.categorypayload.trademessage.trademessagepayload.shorttrademessage";
                values[entry + ".categorypayload.trademessage.trademessagepayload.shorttrademessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.shorttrademessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.shorttrademessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.shorttrademessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.trademessage.trademessagepayload.shorttrademessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.trademessage.trademessagepayload.shorttrademessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.trademessage.trademessagepayload.shorttrademessage.securitysymbolshort"] = canonical::text(std::string((*message_2).security_symbol_short()), ' ', false);
                values[entry + ".categorypayload.trademessage.trademessagepayload.shorttrademessage.salecondition"] = canonical::text(canonical::character((*message_2).sale_condition()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.shorttrademessage.saleconditioncategory"] = canonical::text(canonical::character((*message_2).sale_condition_category()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.shorttrademessage.tradepriceshort"] = canonical::scaled((*message_2).trade_price_short().mantissa(), (*message_2).trade_price_short().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.shorttrademessage.tradevolumeshort"] = canonical::number((*message_2).trade_volume_short());
                values[entry + ".categorypayload.trademessage.trademessagepayload.shorttrademessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character((*message_2).primary_listing_market_participant_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.shorttrademessage.consolidatedhighlowlastindicator"] = canonical::text(canonical::character((*message_2).consolidated_high_low_last_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.shorttrademessage.participantopenhighlowlastindicator"] = canonical::text(canonical::character((*message_2).participant_open_high_low_last_indicator()));
            } else if (const auto* message_2 = dynamic_cast<const protocol::FractionalShortTradeMessage*>(message->trade_message_payload())) {
                values[entry + ".categorypayload.trademessage.trademessagepayload"] = "packet.message.categorypayload.trademessage.trademessagepayload.fractionalshorttrademessage";
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionalshorttrademessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionalshorttrademessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionalshorttrademessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionalshorttrademessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionalshorttrademessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionalshorttrademessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionalshorttrademessage.securitysymbolshort"] = canonical::text(std::string((*message_2).security_symbol_short()), ' ', false);
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionalshorttrademessage.salecondition"] = canonical::text(canonical::character((*message_2).sale_condition()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionalshorttrademessage.saleconditioncategory"] = canonical::text(canonical::character((*message_2).sale_condition_category()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionalshorttrademessage.tradepriceshort"] = canonical::scaled((*message_2).trade_price_short().mantissa(), (*message_2).trade_price_short().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionalshorttrademessage.fractionaltradevolumeshort"] = canonical::scaled((*message_2).fractional_trade_volume_short().mantissa(), (*message_2).fractional_trade_volume_short().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionalshorttrademessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character((*message_2).primary_listing_market_participant_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionalshorttrademessage.consolidatedhighlowlastindicator"] = canonical::text(canonical::character((*message_2).consolidated_high_low_last_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionalshorttrademessage.participantopenhighlowlastindicator"] = canonical::text(canonical::character((*message_2).participant_open_high_low_last_indicator()));
            } else if (const auto* message_2 = dynamic_cast<const protocol::TradeCancelErrorMessage*>(message->trade_message_payload())) {
                values[entry + ".categorypayload.trademessage.trademessagepayload"] = "packet.message.categorypayload.trademessage.trademessagepayload.tradecancelerrormessage";
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.securitysymbol"] = canonical::text(std::string((*message_2).security_symbol()), ' ', false);
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.instrumenttype"] = canonical::text(canonical::character((*message_2).instrument_type()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.saleconditions.settlementtype"] = canonical::text(canonical::character((*message_2).sale_conditions().settlement_type()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.saleconditions.tradethroughexemptreason"] = canonical::text(canonical::character((*message_2).sale_conditions().trade_through_exempt_reason()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.saleconditions.extendedhoursorsequencetype"] = canonical::text(canonical::character((*message_2).sale_conditions().extended_hours_or_sequence_type()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.saleconditions.srotradedetail"] = canonical::text(canonical::character((*message_2).sale_conditions().sro_trade_detail()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.tradeprice"] = canonical::scaled((*message_2).trade_price().mantissa(), (*message_2).trade_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.tradevolume"] = canonical::number((*message_2).trade_volume());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.sellerssaledays"] = canonical::number((*message_2).sellers_sale_days());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.stopstockindicator"] = canonical::text(canonical::character((*message_2).stop_stock_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.tradethroughexemptindicator"] = canonical::text(canonical::character((*message_2).trade_through_exempt_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.tradereportingfacilityid"] = canonical::text(canonical::character((*message_2).trade_reporting_facility_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.originalparticipantreferencenumber"] = canonical::number((*message_2).original_participant_reference_number());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.timestamp2.seconds"] = canonical::number((*message_2).timestamp_2().seconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.timestamp2.nanoseconds"] = canonical::number((*message_2).timestamp_2().nanoseconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.cancelerroraction"] = canonical::text(canonical::character((*message_2).cancel_error_action()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.shortsalerestrictionindicator"] = canonical::text(canonical::character((*message_2).short_sale_restriction_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character((*message_2).primary_listing_market_participant_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.financialstatusindicator"] = canonical::text(canonical::character((*message_2).financial_status_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.consolidateddata.previousclosepricedate"] = canonical::number((*message_2).consolidated_data().previous_close_price_date());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.consolidateddata.lastparticipantid"] = canonical::text(canonical::character((*message_2).consolidated_data().last_participant_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.consolidateddata.lastprice"] = canonical::scaled((*message_2).consolidated_data().last_price().mantissa(), (*message_2).consolidated_data().last_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.consolidateddata.highprice"] = canonical::scaled((*message_2).consolidated_data().high_price().mantissa(), (*message_2).consolidated_data().high_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.consolidateddata.lowprice"] = canonical::scaled((*message_2).consolidated_data().low_price().mantissa(), (*message_2).consolidated_data().low_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.consolidateddata.totalvolumeshort"] = canonical::number((*message_2).consolidated_data().total_volume_short());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.consolidateddata.tick"] = canonical::text(canonical::character((*message_2).consolidated_data().tick()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.participantdata.previousclosepricedate"] = canonical::number((*message_2).participant_data().previous_close_price_date());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.participantdata.lastprice"] = canonical::scaled((*message_2).participant_data().last_price().mantissa(), (*message_2).participant_data().last_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.participantdata.highprice"] = canonical::scaled((*message_2).participant_data().high_price().mantissa(), (*message_2).participant_data().high_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.participantdata.lowprice"] = canonical::scaled((*message_2).participant_data().low_price().mantissa(), (*message_2).participant_data().low_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.participantdata.openprice"] = canonical::scaled((*message_2).participant_data().open_price().mantissa(), (*message_2).participant_data().open_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.participantdata.totalvolumeshort"] = canonical::number((*message_2).participant_data().total_volume_short());
                values[entry + ".categorypayload.trademessage.trademessagepayload.tradecancelerrormessage.participantdata.tick"] = canonical::text(canonical::character((*message_2).participant_data().tick()));
            } else if (const auto* message_2 = dynamic_cast<const protocol::FractionalTradeCancelErrorMessage*>(message->trade_message_payload())) {
                values[entry + ".categorypayload.trademessage.trademessagepayload"] = "packet.message.categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage";
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.participantid"] = canonical::text(canonical::character((*message_2).participant_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.timestamp1.seconds"] = canonical::number((*message_2).timestamp_1().seconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.timestamp1.nanoseconds"] = canonical::number((*message_2).timestamp_1().nanoseconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.messageid"] = canonical::number((*message_2).message_id());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.securitysymbol"] = canonical::text(std::string((*message_2).security_symbol()), ' ', false);
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.instrumenttype"] = canonical::text(canonical::character((*message_2).instrument_type()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.saleconditions.settlementtype"] = canonical::text(canonical::character((*message_2).sale_conditions().settlement_type()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.saleconditions.tradethroughexemptreason"] = canonical::text(canonical::character((*message_2).sale_conditions().trade_through_exempt_reason()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.saleconditions.extendedhoursorsequencetype"] = canonical::text(canonical::character((*message_2).sale_conditions().extended_hours_or_sequence_type()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.saleconditions.srotradedetail"] = canonical::text(canonical::character((*message_2).sale_conditions().sro_trade_detail()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.tradeprice"] = canonical::scaled((*message_2).trade_price().mantissa(), (*message_2).trade_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.fractionaltradevolume"] = canonical::scaled((*message_2).fractional_trade_volume().mantissa(), (*message_2).fractional_trade_volume().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.sellerssaledays"] = canonical::number((*message_2).sellers_sale_days());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.stopstockindicator"] = canonical::text(canonical::character((*message_2).stop_stock_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.tradethroughexemptindicator"] = canonical::text(canonical::character((*message_2).trade_through_exempt_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.tradereportingfacilityid"] = canonical::text(canonical::character((*message_2).trade_reporting_facility_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.originalparticipantreferencenumber"] = canonical::number((*message_2).original_participant_reference_number());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.timestamp2.seconds"] = canonical::number((*message_2).timestamp_2().seconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.timestamp2.nanoseconds"] = canonical::number((*message_2).timestamp_2().nanoseconds());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.cancelerroraction"] = canonical::text(canonical::character((*message_2).cancel_error_action()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.shortsalerestrictionindicator"] = canonical::text(canonical::character((*message_2).short_sale_restriction_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character((*message_2).primary_listing_market_participant_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.financialstatusindicator"] = canonical::text(canonical::character((*message_2).financial_status_indicator()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.fractionalconsolidateddata.previousclosepricedate"] = canonical::number((*message_2).fractional_consolidated_data().previous_close_price_date());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.fractionalconsolidateddata.lastparticipantid"] = canonical::text(canonical::character((*message_2).fractional_consolidated_data().last_participant_id()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.fractionalconsolidateddata.lastprice"] = canonical::scaled((*message_2).fractional_consolidated_data().last_price().mantissa(), (*message_2).fractional_consolidated_data().last_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.fractionalconsolidateddata.highprice"] = canonical::scaled((*message_2).fractional_consolidated_data().high_price().mantissa(), (*message_2).fractional_consolidated_data().high_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.fractionalconsolidateddata.lowprice"] = canonical::scaled((*message_2).fractional_consolidated_data().low_price().mantissa(), (*message_2).fractional_consolidated_data().low_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.fractionalconsolidateddata.fractionaltotalvolume"] = canonical::scaled((*message_2).fractional_consolidated_data().fractional_total_volume().mantissa(), (*message_2).fractional_consolidated_data().fractional_total_volume().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.fractionalconsolidateddata.tick"] = canonical::text(canonical::character((*message_2).fractional_consolidated_data().tick()));
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.fractionalparticipantdata.previousclosepricedate"] = canonical::number((*message_2).fractional_participant_data().previous_close_price_date());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.fractionalparticipantdata.lastprice"] = canonical::scaled((*message_2).fractional_participant_data().last_price().mantissa(), (*message_2).fractional_participant_data().last_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.fractionalparticipantdata.highprice"] = canonical::scaled((*message_2).fractional_participant_data().high_price().mantissa(), (*message_2).fractional_participant_data().high_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.fractionalparticipantdata.lowprice"] = canonical::scaled((*message_2).fractional_participant_data().low_price().mantissa(), (*message_2).fractional_participant_data().low_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.fractionalparticipantdata.openprice"] = canonical::scaled((*message_2).fractional_participant_data().open_price().mantissa(), (*message_2).fractional_participant_data().open_price().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.fractionalparticipantdata.fractionaltotalvolume"] = canonical::scaled((*message_2).fractional_participant_data().fractional_total_volume().mantissa(), (*message_2).fractional_participant_data().fractional_total_volume().exponent());
                values[entry + ".categorypayload.trademessage.trademessagepayload.fractionaltradecancelerrormessage.fractionalparticipantdata.tick"] = canonical::text(canonical::character((*message_2).fractional_participant_data().tick()));
            }
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
    std::printf("== Siac.Cts.Output.Cta.v2.10 (classes values)\n");
    int failures = 0;
    failures += check("TradeCorrectionMessage", "Siac/Cts.Output.Cta.v2.10/TradeCorrectionMessage.pcap", "siac/cts/output/cta/v2.10/TradeCorrectionMessage.values");
    return failures == 0 ? 0 : 1;
}
