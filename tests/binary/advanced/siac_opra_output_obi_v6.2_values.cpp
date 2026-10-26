// Siac.Opra.Output.Obi.v6.2 canonical values, through the Advanced session layer: every value Advanced
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
#include "cpp/binary/advanced/siac/opra/output/obi/v6.2/messages/session.hpp"

namespace protocol = ::siac::opra::output::obi::v6_2;

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
        values["packet.blockheader.sessionindicator"] = canonical::number(header.session_indicator.get().value());
        values["packet.blockheader.blocksequencenumber"] = canonical::number(header.block_sequence_number.get().value());
        values["packet.blockheader.messagesinblock"] = canonical::number(header.messages_in_block.get().value());
        values["packet.blockheader.blocktimestamp.seconds"] = canonical::number(header.block_timestamp.seconds.get().value());
        values["packet.blockheader.blocktimestamp.nanoseconds"] = canonical::number(header.block_timestamp.nanoseconds.get().value());
        values["packet.blockheader.blockchecksum"] = canonical::number(header.block_checksum.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::block_header&) {
        ++index;
    }

    void on_message(const protocol::administrative_message& message, std::uint64_t, const protocol::block_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.participantid"] = canonical::text(canonical::character(message.header.participant_id.get().value()));
        values[entry + ".messageheader.messagecategory"] = canonical::text(canonical::character(message.header.message_category.get().value()));
        values[entry + ".payload"] = "packet.message.payload.administrativecategory";
        values[entry + ".payload.administrativecategory.administrativemessagetype"] = canonical::text(canonical::character(message.administrative_message_type.get().value()));
        values[entry + ".payload.administrativecategory.administrativemessagepayload"] = "packet.message.payload.administrativecategory.administrativemessagepayload.administrativemessage";
        values[entry + ".payload.administrativecategory.administrativemessagepayload.administrativemessage.messageindicator"] = canonical::text(canonical::character(message.fields.message_indicator.get().value()));
        values[entry + ".payload.administrativecategory.administrativemessagepayload.administrativemessage.transactionid"] = canonical::number(message.fields.transaction_id.get().value());
        values[entry + ".payload.administrativecategory.administrativemessagepayload.administrativemessage.participantreferencenumber"] = canonical::number(message.fields.participant_reference_number.get().value());
        values[entry + ".payload.administrativecategory.administrativemessagepayload.administrativemessage.messagedatalength"] = canonical::number(message.fields.message_data_length.get().value());
    }

    void on_message(const protocol::control_message& message, std::uint64_t, const protocol::block_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.participantid"] = canonical::text(canonical::character(message.header.participant_id.get().value()));
        values[entry + ".messageheader.messagecategory"] = canonical::text(canonical::character(message.header.message_category.get().value()));
        values[entry + ".payload"] = "packet.message.payload.controlcategory";
        values[entry + ".payload.controlcategory.controlmessagetype"] = canonical::text(canonical::character(message.control_message_type.get().value()));
        values[entry + ".payload.controlcategory.controlmessagepayload"] = "packet.message.payload.controlcategory.controlmessagepayload.controlmessage";
        values[entry + ".payload.controlcategory.controlmessagepayload.controlmessage.messageindicator"] = canonical::text(canonical::character(message.fields.message_indicator.get().value()));
        values[entry + ".payload.controlcategory.controlmessagepayload.controlmessage.transactionid"] = canonical::number(message.fields.transaction_id.get().value());
        values[entry + ".payload.controlcategory.controlmessagepayload.controlmessage.participantreferencenumber"] = canonical::number(message.fields.participant_reference_number.get().value());
    }

    void on_message(const protocol::equity_and_index_last_sale_message& message, std::uint64_t, const protocol::block_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.participantid"] = canonical::text(canonical::character(message.header.participant_id.get().value()));
        values[entry + ".messageheader.messagecategory"] = canonical::text(canonical::character(message.header.message_category.get().value()));
        values[entry + ".payload"] = "packet.message.payload.equityandindexlastsalecategory";
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagetype"] = canonical::text(canonical::character(message.equity_and_index_last_sale_message_type.get().value()));
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload"] = "packet.message.payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage";
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.messageindicator"] = canonical::text(canonical::character(message.fields.message_indicator.get().value()));
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.transactionid"] = canonical::number(message.fields.transaction_id.get().value());
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.participantreferencenumber"] = canonical::number(message.fields.participant_reference_number.get().value());
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.securitysymbol"] = canonical::text(std::string(message.fields.security_symbol.get().value()), ' ', false);
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.expirationblock.expirationmonth"] = canonical::text(canonical::character(message.fields.expiration_block.expiration_month.get().value()), ' ', false);
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.expirationblock.expirationday"] = canonical::number(message.fields.expiration_block.expiration_day.get().value());
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.expirationblock.expirationyear"] = canonical::number(message.fields.expiration_block.expiration_year.get().value());
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.strikepricedenominatorcode"] = canonical::text(canonical::character(message.fields.strike_price_denominator_code.get().value()), ' ', false);
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.strikeprice"] = canonical::number(message.fields.strike_price.get().value());
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.volume"] = canonical::number(message.fields.volume.get().value());
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.premiumpricedenominatorcode"] = canonical::text(canonical::character(message.fields.premium_price_denominator_code.get().value()), ' ', false);
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.premiumprice"] = canonical::number(message.fields.premium_price.get().value());
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.tradeidentifier"] = canonical::number(message.fields.trade_identifier.get().value());
    }

    void on_message(const protocol::open_interest_message& message, std::uint64_t, const protocol::block_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.participantid"] = canonical::text(canonical::character(message.header.participant_id.get().value()));
        values[entry + ".messageheader.messagecategory"] = canonical::text(canonical::character(message.header.message_category.get().value()));
        values[entry + ".payload"] = "packet.message.payload.openinterestcategory";
        values[entry + ".payload.openinterestcategory.openinterestmessagetype"] = canonical::text(canonical::character(message.open_interest_message_type.get().value()));
        values[entry + ".payload.openinterestcategory.openinterestmessagepayload"] = "packet.message.payload.openinterestcategory.openinterestmessagepayload.openinterestmessage";
        values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.messageindicator"] = canonical::text(canonical::character(message.fields.message_indicator.get().value()));
        values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.transactionid"] = canonical::number(message.fields.transaction_id.get().value());
        values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.participantreferencenumber"] = canonical::number(message.fields.participant_reference_number.get().value());
        values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.securitysymbol"] = canonical::text(std::string(message.fields.security_symbol.get().value()), ' ', false);
        values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.expirationblock.expirationmonth"] = canonical::text(canonical::character(message.fields.expiration_block.expiration_month.get().value()), ' ', false);
        values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.expirationblock.expirationday"] = canonical::number(message.fields.expiration_block.expiration_day.get().value());
        values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.expirationblock.expirationyear"] = canonical::number(message.fields.expiration_block.expiration_year.get().value());
        values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.strikepricedenominatorcode"] = canonical::text(canonical::character(message.fields.strike_price_denominator_code.get().value()), ' ', false);
        values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.strikeprice"] = canonical::number(message.fields.strike_price.get().value());
        values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.openinterestvolume"] = canonical::number(message.fields.open_interest_volume.get().value());
    }

    void on_message(const protocol::equity_and_index_end_of_day_summary_message& message, std::uint64_t, const protocol::block_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.participantid"] = canonical::text(canonical::character(message.header.participant_id.get().value()));
        values[entry + ".messageheader.messagecategory"] = canonical::text(canonical::character(message.header.message_category.get().value()));
        values[entry + ".payload"] = "packet.message.payload.equityandindexendofdaysummarycategory";
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagetype"] = canonical::text(canonical::character(message.equity_and_index_end_of_day_summary_message_type.get().value()));
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload"] = "packet.message.payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage";
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.messageindicator"] = canonical::text(canonical::character(message.fields.message_indicator.get().value()));
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.transactionid"] = canonical::number(message.fields.transaction_id.get().value());
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.participantreferencenumber"] = canonical::number(message.fields.participant_reference_number.get().value());
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.securitysymbol"] = canonical::text(std::string(message.fields.security_symbol.get().value()), ' ', false);
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.expirationblock.expirationmonth"] = canonical::text(canonical::character(message.fields.expiration_block.expiration_month.get().value()), ' ', false);
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.expirationblock.expirationday"] = canonical::number(message.fields.expiration_block.expiration_day.get().value());
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.expirationblock.expirationyear"] = canonical::number(message.fields.expiration_block.expiration_year.get().value());
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.strikepricedenominatorcode"] = canonical::text(canonical::character(message.fields.strike_price_denominator_code.get().value()), ' ', false);
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.strikeprice"] = canonical::number(message.fields.strike_price.get().value());
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.volume"] = canonical::number(message.fields.volume.get().value());
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.openinterestvolume"] = canonical::number(message.fields.open_interest_volume.get().value());
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.premiumpricedenominatorcode"] = canonical::text(canonical::character(message.fields.premium_price_denominator_code.get().value()), ' ', false);
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.openprice"] = canonical::number(message.fields.open_price.get().value());
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.highprice"] = canonical::number(message.fields.high_price.get().value());
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.lowprice"] = canonical::number(message.fields.low_price.get().value());
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.lastprice"] = canonical::number(message.fields.last_price.get().value());
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.netchange"] = canonical::number(message.fields.net_change.get().value());
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.underlyingpricedenominatorcode"] = canonical::text(canonical::character(message.fields.underlying_price_denominator_code.get().value()), ' ', false);
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.underlyingprice"] = canonical::number(message.fields.underlying_price.get().value());
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.bidprice"] = canonical::number(message.fields.bid_price.get().value());
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.offerprice"] = canonical::number(message.fields.offer_price.get().value());
    }

    void on_message(const protocol::long_equity_and_index_quote_message& message, std::uint64_t, const protocol::block_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.participantid"] = canonical::text(canonical::character(message.header.participant_id.get().value()));
        values[entry + ".messageheader.messagecategory"] = canonical::text(canonical::character(message.header.message_category.get().value()));
        values[entry + ".payload"] = "packet.message.payload.longequityandindexquotecategory";
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagetype"] = canonical::text(canonical::character(message.long_equity_and_index_quote_message_type.get().value()));
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload"] = "packet.message.payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage";
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.bboindicator"] = canonical::text(canonical::character(message.fields.bbo_indicator.get().value()), ' ', false);
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.transactionid"] = canonical::number(message.fields.transaction_id.get().value());
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.participantreferencenumber"] = canonical::number(message.fields.participant_reference_number.get().value());
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.securitysymbol"] = canonical::text(std::string(message.fields.security_symbol.get().value()), ' ', false);
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.expirationblock.expirationmonth"] = canonical::text(canonical::character(message.fields.expiration_block.expiration_month.get().value()), ' ', false);
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.expirationblock.expirationday"] = canonical::number(message.fields.expiration_block.expiration_day.get().value());
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.expirationblock.expirationyear"] = canonical::number(message.fields.expiration_block.expiration_year.get().value());
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.strikepricedenominatorcode"] = canonical::text(canonical::character(message.fields.strike_price_denominator_code.get().value()), ' ', false);
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.strikeprice"] = canonical::number(message.fields.strike_price.get().value());
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.premiumpricedenominatorcode"] = canonical::text(canonical::character(message.fields.premium_price_denominator_code.get().value()), ' ', false);
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.bidprice"] = canonical::number(message.fields.bid_price.get().value());
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.bidsize"] = canonical::number(message.fields.bid_size.get().value());
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.offerprice"] = canonical::number(message.fields.offer_price.get().value());
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.offersize"] = canonical::number(message.fields.offer_size.get().value());
    }

    void on_message(const protocol::short_equity_and_index_quote_message& message, std::uint64_t, const protocol::block_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.participantid"] = canonical::text(canonical::character(message.header.participant_id.get().value()));
        values[entry + ".messageheader.messagecategory"] = canonical::text(canonical::character(message.header.message_category.get().value()));
        values[entry + ".payload"] = "packet.message.payload.shortequityandindexquotecategory";
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagetype"] = canonical::text(canonical::character(message.short_equity_and_index_quote_message_type.get().value()));
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload"] = "packet.message.payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage";
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.bboindicator"] = canonical::text(canonical::character(message.fields.bbo_indicator.get().value()), ' ', false);
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.transactionid"] = canonical::number(message.fields.transaction_id.get().value());
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.participantreferencenumber"] = canonical::number(message.fields.participant_reference_number.get().value());
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.securitysymbolshort"] = canonical::text(std::string(message.fields.security_symbol_short.get().value()), ' ', false);
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.expirationblock.expirationmonth"] = canonical::text(canonical::character(message.fields.expiration_block.expiration_month.get().value()), ' ', false);
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.expirationblock.expirationday"] = canonical::number(message.fields.expiration_block.expiration_day.get().value());
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.expirationblock.expirationyear"] = canonical::number(message.fields.expiration_block.expiration_year.get().value());
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.strikepriceshort"] = canonical::scaled(message.fields.strike_price_short.get().value(), -1);
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.bidpriceshort"] = canonical::scaled(message.fields.bid_price_short.get().value(), -2);
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.bidsizeshort"] = canonical::number(message.fields.bid_size_short.get().value());
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.offerpriceshort"] = canonical::scaled(message.fields.offer_price_short.get().value(), -2);
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.offersizeshort"] = canonical::number(message.fields.offer_size_short.get().value());
    }

    void on_message(const protocol::underlying_value_last_sale_message& message, std::uint64_t, const protocol::block_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.participantid"] = canonical::text(canonical::character(message.header.participant_id.get().value()));
        values[entry + ".messageheader.messagecategory"] = canonical::text(canonical::character(message.header.message_category.get().value()));
        values[entry + ".payload"] = "packet.message.payload.underlyingvaluecategory";
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagetype"] = canonical::text(canonical::character(message.underlying_value_message_type.get().value()));
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload"] = "packet.message.payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluelastsalemessage";
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluelastsalemessage.messageindicator"] = canonical::text(canonical::character(message.fields.message_indicator.get().value()));
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluelastsalemessage.transactionid"] = canonical::number(message.fields.transaction_id.get().value());
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluelastsalemessage.participantreferencenumber"] = canonical::number(message.fields.participant_reference_number.get().value());
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluelastsalemessage.securitysymbol"] = canonical::text(std::string(message.fields.security_symbol.get().value()), ' ', false);
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluelastsalemessage.indexvaluedenominatorcode"] = canonical::text(canonical::character(message.fields.index_value_denominator_code.get().value()), ' ', false);
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluelastsalemessage.indexvalue"] = canonical::number(message.fields.index_value.get().value());
    }

    void on_message(const protocol::underlying_value_bid_and_offer_message& message, std::uint64_t, const protocol::block_header&) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.participantid"] = canonical::text(canonical::character(message.header.participant_id.get().value()));
        values[entry + ".messageheader.messagecategory"] = canonical::text(canonical::character(message.header.message_category.get().value()));
        values[entry + ".payload"] = "packet.message.payload.underlyingvaluecategory";
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagetype"] = canonical::text(canonical::character(message.underlying_value_message_type.get().value()));
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload"] = "packet.message.payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage";
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage.messageindicator"] = canonical::text(canonical::character(message.fields.message_indicator.get().value()));
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage.transactionid"] = canonical::number(message.fields.transaction_id.get().value());
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage.participantreferencenumber"] = canonical::number(message.fields.participant_reference_number.get().value());
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage.securitysymbol"] = canonical::text(std::string(message.fields.security_symbol.get().value()), ' ', false);
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage.indexvaluedenominatorcode"] = canonical::text(canonical::character(message.fields.index_value_denominator_code.get().value()), ' ', false);
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage.bidindexvalue"] = canonical::number(message.fields.bid_index_value.get().value());
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage.offerindexvalue"] = canonical::number(message.fields.offer_index_value.get().value());
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
    std::printf("== Siac.Opra.Output.Obi.v6.2 (advanced values)\n");
    int failures = 0;
    failures += check("AdministrativeMessage", "Siac/Opra.Output.Obi.v6.2/AdministrativeMessage.pcap", "siac/opra/output/obi/v6.2/AdministrativeMessage.values");
    failures += check("ControlMessage", "Siac/Opra.Output.Obi.v6.2/ControlMessage.pcap", "siac/opra/output/obi/v6.2/ControlMessage.values");
    failures += check("LongEquityAndIndexQuoteMessage", "Siac/Opra.Output.Obi.v6.2/LongEquityAndIndexQuoteMessage.pcap", "siac/opra/output/obi/v6.2/LongEquityAndIndexQuoteMessage.values");
    failures += check("ShortEquityAndIndexQuoteMessage", "Siac/Opra.Output.Obi.v6.2/ShortEquityAndIndexQuoteMessage.pcap", "siac/opra/output/obi/v6.2/ShortEquityAndIndexQuoteMessage.values");
    return failures == 0 ? 0 : 1;
}
