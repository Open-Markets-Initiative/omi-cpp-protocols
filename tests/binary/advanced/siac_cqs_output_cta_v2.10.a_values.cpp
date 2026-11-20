// Siac.Cqs.Output.Cta.v2.10.a canonical values, through the Advanced session layer: every value Advanced
// reads from each sample, at its address, held to what the model reads.

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
#include "cpp/binary/advanced/siac/cqs/output/cta/v2.10.a/messages/session.hpp"

namespace protocol = ::siac::cqs::output::cta::v2_10_a;

namespace {

// The handler the session layer hands each datagram's values to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    protocol::seq_action on_transport_header(const protocol::block_header& header, const packet::Frame&) {
        values["packet.blockheader.version"] = canonical::number(header.version.get().value());
        values["packet.blockheader.blocksize"] = canonical::number(header.block_size.get().value());
        values["packet.blockheader.datafeedindicator"] = canonical::text(canonical::character(header.data_feed_indicator.get().value()));
        values["packet.blockheader.retransmissionindicator"] = canonical::text(canonical::character(header.retransmission_indicator.get().value()));
        values["packet.blockheader.blocksequencenumber"] = canonical::number(header.block_sequence_number.get().value());
        values["packet.blockheader.messagesinblock"] = canonical::number(header.messages_in_block.get().value());
        values["packet.blockheader.sipblocktimestamp.seconds"] = canonical::number(header.sip_block_timestamp.seconds.get().value());
        values["packet.blockheader.sipblocktimestamp.nanoseconds"] = canonical::number(header.sip_block_timestamp.nanoseconds.get().value());
        values["packet.blockheader.blockchecksum"] = canonical::number(header.block_checksum.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::block_header&) {
        ++index;
    }

    void on_message(const protocol::symbol_reference_data_message& message, std::uint64_t, const protocol::block_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".categorypayload"] = "packet.message.categorypayload.administrativemessage";
        values[entry + ".categorypayload.administrativemessage.administrativemessagetype"] = canonical::text(canonical::character(message.administrative_message_type.get().value()));
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload"] = "packet.message.categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage";
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.participantid"] = canonical::text(canonical::character(message.fields.participant_id.get().value()));
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.timestamp1.seconds"] = canonical::number(message.fields.timestamp_1.seconds.get().value());
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.timestamp1.nanoseconds"] = canonical::number(message.fields.timestamp_1.nanoseconds.get().value());
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.messageid"] = canonical::number(message.fields.message_id.get().value());
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.transactionid"] = canonical::number(message.fields.transaction_id.get().value());
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.participantreferencenumber"] = canonical::number(message.fields.participant_reference_number.get().value());
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.securitysymbol"] = canonical::text(std::string(message.fields.security_symbol.get().value()), ' ', false);
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.priorsecuritysymbol"] = canonical::text(std::string(message.fields.prior_security_symbol.get().value()), ' ', false);
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character(message.fields.primary_listing_market_participant_id.get().value()), {std::string_view(" ", 1)});
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.primarylistingmarketpreviousclosingprice"] = canonical::scaled(message.fields.primary_listing_market_previous_closing_price.get().value(), -6);
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.consolidatedclosingprice"] = canonical::scaled(message.fields.consolidated_closing_price.get().value(), -6);
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.roundlotsize"] = canonical::number(message.fields.round_lot_size.get().value());
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.luldtier"] = canonical::text(canonical::character(message.fields.luld_tier.get().value()));
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.luldleverageratio"] = canonical::scaled(message.fields.luld_leverage_ratio.get().value(), -6);
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.test"] = canonical::text(canonical::character(message.fields.test.get().value()));
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.ipo"] = canonical::text(canonical::character(message.fields.ipo.get().value()));
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.financialstatusindicator"] = canonical::text(canonical::character(message.fields.financial_status_indicator.get().value()));
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.shortsalerestrictionindicator"] = canonical::text(canonical::character(message.fields.short_sale_restriction_indicator.get().value()), {std::string_view(" ", 1)});
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.haltreason"] = canonical::text(canonical::character(message.fields.halt_reason.get().value()));
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.instrumenttype"] = canonical::text(canonical::character(message.fields.instrument_type.get().value()));
    }

    void on_message(const protocol::start_of_day_message& message, std::uint64_t, const protocol::block_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".categorypayload"] = "packet.message.categorypayload.controlmessage";
        values[entry + ".categorypayload.controlmessage.controlmessagetype"] = canonical::text(canonical::character(message.control_message_type.get().value()));
        values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.startofdaymessage";
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.participantid"] = canonical::text(canonical::character(message.fields.participant_id.get().value()));
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.timestamp1.seconds"] = canonical::number(message.fields.timestamp_1.seconds.get().value());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.timestamp1.nanoseconds"] = canonical::number(message.fields.timestamp_1.nanoseconds.get().value());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.messageid"] = canonical::number(message.fields.message_id.get().value());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.transactionid"] = canonical::number(message.fields.transaction_id.get().value());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.participantreferencenumber"] = canonical::number(message.fields.participant_reference_number.get().value());
    }

    void on_message(const protocol::finra_close_message& message, std::uint64_t, const protocol::block_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".categorypayload"] = "packet.message.categorypayload.controlmessage";
        values[entry + ".categorypayload.controlmessage.controlmessagetype"] = canonical::text(canonical::character(message.control_message_type.get().value()));
        values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.finraclosemessage";
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraclosemessage.participantid"] = canonical::text(canonical::character(message.fields.participant_id.get().value()));
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraclosemessage.timestamp1.seconds"] = canonical::number(message.fields.timestamp_1.seconds.get().value());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraclosemessage.timestamp1.nanoseconds"] = canonical::number(message.fields.timestamp_1.nanoseconds.get().value());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraclosemessage.messageid"] = canonical::number(message.fields.message_id.get().value());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraclosemessage.transactionid"] = canonical::number(message.fields.transaction_id.get().value());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraclosemessage.participantreferencenumber"] = canonical::number(message.fields.participant_reference_number.get().value());
    }

    void on_message(const protocol::reset_block_sequence_number_message& message, std::uint64_t, const protocol::block_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".categorypayload"] = "packet.message.categorypayload.controlmessage";
        values[entry + ".categorypayload.controlmessage.controlmessagetype"] = canonical::text(canonical::character(message.control_message_type.get().value()));
        values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage";
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.participantid"] = canonical::text(canonical::character(message.fields.participant_id.get().value()));
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.timestamp1.seconds"] = canonical::number(message.fields.timestamp_1.seconds.get().value());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.timestamp1.nanoseconds"] = canonical::number(message.fields.timestamp_1.nanoseconds.get().value());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.messageid"] = canonical::number(message.fields.message_id.get().value());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.transactionid"] = canonical::number(message.fields.transaction_id.get().value());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.participantreferencenumber"] = canonical::number(message.fields.participant_reference_number.get().value());
    }

    void on_message(const protocol::finra_open_message& message, std::uint64_t, const protocol::block_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".categorypayload"] = "packet.message.categorypayload.controlmessage";
        values[entry + ".categorypayload.controlmessage.controlmessagetype"] = canonical::text(canonical::character(message.control_message_type.get().value()));
        values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.finraopenmessage";
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraopenmessage.participantid"] = canonical::text(canonical::character(message.fields.participant_id.get().value()));
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraopenmessage.timestamp1.seconds"] = canonical::number(message.fields.timestamp_1.seconds.get().value());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraopenmessage.timestamp1.nanoseconds"] = canonical::number(message.fields.timestamp_1.nanoseconds.get().value());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraopenmessage.messageid"] = canonical::number(message.fields.message_id.get().value());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraopenmessage.transactionid"] = canonical::number(message.fields.transaction_id.get().value());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraopenmessage.participantreferencenumber"] = canonical::number(message.fields.participant_reference_number.get().value());
    }

    void on_message(const protocol::disaster_recovery_data_center_activation_message& message, std::uint64_t, const protocol::block_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".categorypayload"] = "packet.message.categorypayload.controlmessage";
        values[entry + ".categorypayload.controlmessage.controlmessagetype"] = canonical::text(canonical::character(message.control_message_type.get().value()));
        values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage";
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.participantid"] = canonical::text(canonical::character(message.fields.participant_id.get().value()));
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.timestamp1.seconds"] = canonical::number(message.fields.timestamp_1.seconds.get().value());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.timestamp1.nanoseconds"] = canonical::number(message.fields.timestamp_1.nanoseconds.get().value());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.messageid"] = canonical::number(message.fields.message_id.get().value());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.transactionid"] = canonical::number(message.fields.transaction_id.get().value());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.participantreferencenumber"] = canonical::number(message.fields.participant_reference_number.get().value());
    }

    void on_message(const protocol::line_integrity_message& message, std::uint64_t, const protocol::block_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".categorypayload"] = "packet.message.categorypayload.controlmessage";
        values[entry + ".categorypayload.controlmessage.controlmessagetype"] = canonical::text(canonical::character(message.control_message_type.get().value()));
        values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.lineintegritymessage";
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.participantid"] = canonical::text(canonical::character(message.fields.participant_id.get().value()));
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.timestamp1.seconds"] = canonical::number(message.fields.timestamp_1.seconds.get().value());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.timestamp1.nanoseconds"] = canonical::number(message.fields.timestamp_1.nanoseconds.get().value());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.messageid"] = canonical::number(message.fields.message_id.get().value());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.transactionid"] = canonical::number(message.fields.transaction_id.get().value());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.participantreferencenumber"] = canonical::number(message.fields.participant_reference_number.get().value());
    }

    void on_message(const protocol::end_of_day_message& message, std::uint64_t, const protocol::block_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".categorypayload"] = "packet.message.categorypayload.controlmessage";
        values[entry + ".categorypayload.controlmessage.controlmessagetype"] = canonical::text(canonical::character(message.control_message_type.get().value()));
        values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.endofdaymessage";
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.participantid"] = canonical::text(canonical::character(message.fields.participant_id.get().value()));
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.timestamp1.seconds"] = canonical::number(message.fields.timestamp_1.seconds.get().value());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.timestamp1.nanoseconds"] = canonical::number(message.fields.timestamp_1.nanoseconds.get().value());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.messageid"] = canonical::number(message.fields.message_id.get().value());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.transactionid"] = canonical::number(message.fields.transaction_id.get().value());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.participantreferencenumber"] = canonical::number(message.fields.participant_reference_number.get().value());
    }

    void on_message(const protocol::market_wide_circuit_breaker_decline_level_status_message& message, std::uint64_t, const protocol::block_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".categorypayload"] = "packet.message.categorypayload.marketstatusmessage";
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagetype"] = canonical::text(canonical::character(message.market_status_message_type.get().value()));
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload"] = "packet.message.categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage";
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.participantid"] = canonical::text(canonical::character(message.fields.participant_id.get().value()));
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.timestamp1.seconds"] = canonical::number(message.fields.timestamp_1.seconds.get().value());
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.timestamp1.nanoseconds"] = canonical::number(message.fields.timestamp_1.nanoseconds.get().value());
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.messageid"] = canonical::number(message.fields.message_id.get().value());
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.transactionid"] = canonical::number(message.fields.transaction_id.get().value());
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.participantreferencenumber"] = canonical::number(message.fields.participant_reference_number.get().value());
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.mwcblevel1"] = canonical::scaled(message.fields.mwcb_level_1.get().value(), -6);
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.mwcblevel2"] = canonical::scaled(message.fields.mwcb_level_2.get().value(), -6);
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.mwcblevel3"] = canonical::scaled(message.fields.mwcb_level_3.get().value(), -6);
    }

    void on_message(const protocol::market_wide_circuit_breaker_status_message& message, std::uint64_t, const protocol::block_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".categorypayload"] = "packet.message.categorypayload.marketstatusmessage";
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagetype"] = canonical::text(canonical::character(message.market_status_message_type.get().value()));
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload"] = "packet.message.categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage";
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.participantid"] = canonical::text(canonical::character(message.fields.participant_id.get().value()));
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.timestamp1.seconds"] = canonical::number(message.fields.timestamp_1.seconds.get().value());
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.timestamp1.nanoseconds"] = canonical::number(message.fields.timestamp_1.nanoseconds.get().value());
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.messageid"] = canonical::number(message.fields.message_id.get().value());
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.transactionid"] = canonical::number(message.fields.transaction_id.get().value());
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.participantreferencenumber"] = canonical::number(message.fields.participant_reference_number.get().value());
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.marketwidecircuitbreakerlevelindicator"] = canonical::text(canonical::character(message.fields.market_wide_circuit_breaker_level_indicator.get().value()), {std::string_view(" ", 1)});
    }

    void on_message(const protocol::auction_status_message& message, std::uint64_t, const protocol::block_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".categorypayload"] = "packet.message.categorypayload.quotemessage";
        values[entry + ".categorypayload.quotemessage.quotemessagetype"] = canonical::text(canonical::character(message.quote_message_type.get().value()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload"] = "packet.message.categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage";
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.participantid"] = canonical::text(canonical::character(message.fields.participant_id.get().value()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.timestamp1.seconds"] = canonical::number(message.fields.timestamp_1.seconds.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.timestamp1.nanoseconds"] = canonical::number(message.fields.timestamp_1.nanoseconds.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.messageid"] = canonical::number(message.fields.message_id.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.transactionid"] = canonical::number(message.fields.transaction_id.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.participantreferencenumber"] = canonical::number(message.fields.participant_reference_number.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.securitysymbol"] = canonical::text(std::string(message.fields.security_symbol.get().value()), ' ', false);
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.instrumenttype"] = canonical::text(canonical::character(message.fields.instrument_type.get().value()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.auctioncollarreferenceprice"] = canonical::scaled(message.fields.auction_collar_reference_price.get().value(), -6);
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.auctioncollarupperthresholdprice"] = canonical::scaled(message.fields.auction_collar_upper_threshold_price.get().value(), -6);
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.auctioncollarlowerthresholdprice"] = canonical::scaled(message.fields.auction_collar_lower_threshold_price.get().value(), -6);
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.numberofextensions"] = canonical::number(message.fields.number_of_extensions.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.shortsalerestrictionindicator"] = canonical::text(canonical::character(message.fields.short_sale_restriction_indicator.get().value()), {std::string_view(" ", 1)});
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character(message.fields.primary_listing_market_participant_id.get().value()), {std::string_view(" ", 1)});
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.financialstatusindicator"] = canonical::text(canonical::character(message.fields.financial_status_indicator.get().value()));
    }

    void on_message(const protocol::long_quote_message& message, std::uint64_t, const protocol::block_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".categorypayload"] = "packet.message.categorypayload.quotemessage";
        values[entry + ".categorypayload.quotemessage.quotemessagetype"] = canonical::text(canonical::character(message.quote_message_type.get().value()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload"] = "packet.message.categorypayload.quotemessage.quotemessagepayload.longquotemessage";
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.participantid"] = canonical::text(canonical::character(message.fields.participant_id.get().value()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.timestamp1.seconds"] = canonical::number(message.fields.timestamp_1.seconds.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.timestamp1.nanoseconds"] = canonical::number(message.fields.timestamp_1.nanoseconds.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.messageid"] = canonical::number(message.fields.message_id.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.transactionid"] = canonical::number(message.fields.transaction_id.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.participantreferencenumber"] = canonical::number(message.fields.participant_reference_number.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.securitysymbol"] = canonical::text(std::string(message.fields.security_symbol.get().value()), ' ', false);
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.instrumenttype"] = canonical::text(canonical::character(message.fields.instrument_type.get().value()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.quotecondition"] = canonical::text(canonical::character(message.fields.quote_condition.get().value()), {std::string_view(" ", 1)});
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.securitystatusindicator"] = canonical::text(canonical::character(message.fields.security_status_indicator.get().value()), {std::string_view(" ", 1)});
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.bidpricelowerlimitpriceband"] = canonical::scaled(message.fields.bid_price_lower_limit_price_band.get().value(), -6);
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.bidsizelong"] = canonical::number(message.fields.bid_size_long.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.offerpriceupperlimitpriceband"] = canonical::scaled(message.fields.offer_price_upper_limit_price_band.get().value(), -6);
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.offersizelong"] = canonical::number(message.fields.offer_size_long.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.retailinterestindicator"] = canonical::text(canonical::character(message.fields.retail_interest_indicator.get().value()), {std::string_view(" ", 1)});
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.settlementcondition"] = canonical::text(canonical::character(message.fields.settlement_condition.get().value()), {std::string_view(" ", 1)});
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.marketcondition"] = canonical::text(canonical::character(message.fields.market_condition.get().value()), {std::string_view(" ", 1)});
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.finramarketmakerid"] = canonical::text(std::string(message.fields.finra_market_maker_id.get().value()), ' ', false);
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.finrabboindicator"] = canonical::text(canonical::character(message.fields.finra_bbo_indicator.get().value()), {std::string_view(" ", 1)});
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.shortsalerestrictionindicator"] = canonical::text(canonical::character(message.fields.short_sale_restriction_indicator.get().value()), {std::string_view(" ", 1)});
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character(message.fields.primary_listing_market_participant_id.get().value()), {std::string_view(" ", 1)});
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.financialstatusindicator"] = canonical::text(canonical::character(message.fields.financial_status_indicator.get().value()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.sipgeneratedmessageidentifier"] = canonical::text(canonical::character(message.fields.sip_generated_message_identifier.get().value()), {std::string_view(" ", 1)});
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.limituplimitdownluldindicator"] = canonical::text(canonical::character(message.fields.limit_up_limit_down_luld_indicator.get().value()), {std::string_view(" ", 1)});
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.nationalbboluldindicator"] = canonical::text(canonical::character(message.fields.national_bbo_luld_indicator.get().value()), {std::string_view(" ", 1)});
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.nationalbboindicator"] = canonical::text(canonical::character(message.fields.national_bbo_indicator.get().value()), {std::string_view(" ", 1)});
    }

    void on_message(const protocol::short_quote_message& message, std::uint64_t, const protocol::block_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".categorypayload"] = "packet.message.categorypayload.quotemessage";
        values[entry + ".categorypayload.quotemessage.quotemessagetype"] = canonical::text(canonical::character(message.quote_message_type.get().value()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload"] = "packet.message.categorypayload.quotemessage.quotemessagepayload.shortquotemessage";
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.participantid"] = canonical::text(canonical::character(message.fields.participant_id.get().value()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.timestamp1.seconds"] = canonical::number(message.fields.timestamp_1.seconds.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.timestamp1.nanoseconds"] = canonical::number(message.fields.timestamp_1.nanoseconds.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.messageid"] = canonical::number(message.fields.message_id.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.transactionid"] = canonical::number(message.fields.transaction_id.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.participantreferencenumber"] = canonical::number(message.fields.participant_reference_number.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.securitysymbol"] = canonical::text(std::string(message.fields.security_symbol.get().value()), ' ', false);
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.bidpriceshort"] = canonical::scaled(message.fields.bid_price_short.get().value(), -2);
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.bidsizeshort"] = canonical::number(message.fields.bid_size_short.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.offerpriceshort"] = canonical::scaled(message.fields.offer_price_short.get().value(), -2);
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.offersizeshort"] = canonical::number(message.fields.offer_size_short.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character(message.fields.primary_listing_market_participant_id.get().value()), {std::string_view(" ", 1)});
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.nationalbboindicator"] = canonical::text(canonical::character(message.fields.national_bbo_indicator.get().value()), {std::string_view(" ", 1)});
    }

    void on_message(const protocol::special_long_quote_message& message, std::uint64_t, const protocol::block_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".categorypayload"] = "packet.message.categorypayload.quotemessage";
        values[entry + ".categorypayload.quotemessage.quotemessagetype"] = canonical::text(canonical::character(message.quote_message_type.get().value()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload"] = "packet.message.categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage";
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.participantid"] = canonical::text(canonical::character(message.fields.participant_id.get().value()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.timestamp1.seconds"] = canonical::number(message.fields.timestamp_1.seconds.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.timestamp1.nanoseconds"] = canonical::number(message.fields.timestamp_1.nanoseconds.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.messageid"] = canonical::number(message.fields.message_id.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.transactionid"] = canonical::number(message.fields.transaction_id.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.participantreferencenumber"] = canonical::number(message.fields.participant_reference_number.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.securitysymbol"] = canonical::text(std::string(message.fields.security_symbol.get().value()), ' ', false);
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.instrumenttype"] = canonical::text(canonical::character(message.fields.instrument_type.get().value()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.quotecondition"] = canonical::text(canonical::character(message.fields.quote_condition.get().value()), {std::string_view(" ", 1)});
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.securitystatusindicator"] = canonical::text(canonical::character(message.fields.security_status_indicator.get().value()), {std::string_view(" ", 1)});
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.bidpricelong"] = canonical::scaled(message.fields.bid_price_long.get().value(), -6);
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.bidsizelong"] = canonical::number(message.fields.bid_size_long.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.offerpricelong"] = canonical::scaled(message.fields.offer_price_long.get().value(), -6);
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.offersizelong"] = canonical::number(message.fields.offer_size_long.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.retailinterestindicator"] = canonical::text(canonical::character(message.fields.retail_interest_indicator.get().value()), {std::string_view(" ", 1)});
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.settlementcondition"] = canonical::text(canonical::character(message.fields.settlement_condition.get().value()), {std::string_view(" ", 1)});
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.marketcondition"] = canonical::text(canonical::character(message.fields.market_condition.get().value()), {std::string_view(" ", 1)});
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finramarketmakerid"] = canonical::text(std::string(message.fields.finra_market_maker_id.get().value()), ' ', false);
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finrabestbidquotecondition"] = canonical::text(canonical::character(message.fields.finra_best_bid_quote_condition.get().value()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finrabestbidprice"] = canonical::scaled(message.fields.finra_best_bid_price.get().value(), -6);
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finrabestbidsize"] = canonical::number(message.fields.finra_best_bid_size.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finrabestbidmarketmakerid"] = canonical::text(std::string(message.fields.finra_best_bid_market_maker_id.get().value()), ' ', false);
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finrabestofferquotecondition"] = canonical::text(canonical::character(message.fields.finra_best_offer_quote_condition.get().value()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finrabestofferprice"] = canonical::scaled(message.fields.finra_best_offer_price.get().value(), -6);
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finrabestoffersize"] = canonical::number(message.fields.finra_best_offer_size.get().value());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finrabestoffermarketmakerid"] = canonical::text(std::string(message.fields.finra_best_offer_market_maker_id.get().value()), ' ', false);
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.shortsalerestrictionindicator"] = canonical::text(canonical::character(message.fields.short_sale_restriction_indicator.get().value()), {std::string_view(" ", 1)});
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character(message.fields.primary_listing_market_participant_id.get().value()), {std::string_view(" ", 1)});
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.financialstatusindicator"] = canonical::text(canonical::character(message.fields.financial_status_indicator.get().value()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.sipgeneratedmessageidentifier"] = canonical::text(canonical::character(message.fields.sip_generated_message_identifier.get().value()), {std::string_view(" ", 1)});
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finrabboluldindicator"] = canonical::text(canonical::character(message.fields.finra_bbo_luld_indicator.get().value()), {std::string_view(" ", 1)});
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.nationalbboluldindicator"] = canonical::text(canonical::character(message.fields.national_bbo_luld_indicator.get().value()), {std::string_view(" ", 1)});
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.nationalbboindicator"] = canonical::text(canonical::character(message.fields.national_bbo_indicator.get().value()), {std::string_view(" ", 1)});
    }
};

// The values Advanced reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    Reader reader;
    protocol::process_segment(reader, frame.payload, frame.payload_len, 0, frame);
    return reader.values;
}

// Read each datagram of a sample with Advanced and hold it to the model's values
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
    std::printf("== Siac.Cqs.Output.Cta.v2.10.a (advanced values)\n");
    int failures = 0;
    failures += check("EndOfDayMessage", "Siac/Cqs.Output.Cta.v2.10.a/EndOfDayMessage.pcap", "siac/cqs/output/cta/v2.10.a/EndOfDayMessage.values");
    failures += check("FinraCloseMessage", "Siac/Cqs.Output.Cta.v2.10.a/FinraCloseMessage.pcap", "siac/cqs/output/cta/v2.10.a/FinraCloseMessage.values");
    failures += check("FinraOpenMessage", "Siac/Cqs.Output.Cta.v2.10.a/FinraOpenMessage.pcap", "siac/cqs/output/cta/v2.10.a/FinraOpenMessage.values");
    failures += check("LineIntegrityMessage", "Siac/Cqs.Output.Cta.v2.10.a/LineIntegrityMessage.pcap", "siac/cqs/output/cta/v2.10.a/LineIntegrityMessage.values");
    failures += check("LongQuoteMessage", "Siac/Cqs.Output.Cta.v2.10.a/LongQuoteMessage.pcap", "siac/cqs/output/cta/v2.10.a/LongQuoteMessage.values");
    failures += check("MarketWideCircuitBreakerDeclineLevelStatusMessage", "Siac/Cqs.Output.Cta.v2.10.a/MarketWideCircuitBreakerDeclineLevelStatusMessage.pcap", "siac/cqs/output/cta/v2.10.a/MarketWideCircuitBreakerDeclineLevelStatusMessage.values");
    failures += check("StartOfDayMessage", "Siac/Cqs.Output.Cta.v2.10.a/StartOfDayMessage.pcap", "siac/cqs/output/cta/v2.10.a/StartOfDayMessage.values");
    failures += check("SymbolReferenceDataMessage", "Siac/Cqs.Output.Cta.v2.10.a/SymbolReferenceDataMessage.pcap", "siac/cqs/output/cta/v2.10.a/SymbolReferenceDataMessage.values");
    return failures == 0 ? 0 : 1;
}
