// Siac.Opra.Output.Obi.v6.2 canonical values, through the Classes Packet: every value Classes decodes from
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
#include "cpp/binary/classes/siac/opra/output/obi/v6.2/definitions.hpp"

namespace protocol = ::siac::opra::output::obi::v6_2;

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
    values["packet.blockheader.sessionindicator"] = canonical::number(packet.block_header().session_indicator());
    values["packet.blockheader.blocksequencenumber"] = canonical::number(packet.block_header().block_sequence_number());
    values["packet.blockheader.messagesinblock"] = canonical::number(packet.block_header().messages_in_block());
    values["packet.blockheader.blocktimestamp.seconds"] = canonical::number(packet.block_header().block_timestamp().seconds());
    values["packet.blockheader.blocktimestamp.nanoseconds"] = canonical::number(packet.block_header().block_timestamp().nanoseconds());
    values["packet.blockheader.blockchecksum"] = canonical::number(packet.block_header().block_checksum());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.participantid"] = canonical::text(canonical::character(each.message_header().participant_id()));
        values[entry + ".messageheader.messagecategory"] = canonical::text(canonical::character(each.message_header().message_category()));

        if (const auto* message = dynamic_cast<const protocol::AdministrativeCategory*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.administrativecategory";
            values[entry + ".payload.administrativecategory.administrativemessagetype"] = canonical::text(canonical::character((*message).administrative_message_type()));
            if (const auto* message_2 = dynamic_cast<const protocol::AdministrativeMessage*>(message->administrative_message_payload())) {
                values[entry + ".payload.administrativecategory.administrativemessagepayload"] = "packet.message.payload.administrativecategory.administrativemessagepayload.administrativemessage";
                values[entry + ".payload.administrativecategory.administrativemessagepayload.administrativemessage.messageindicator"] = canonical::text(canonical::character((*message_2).message_indicator()));
                values[entry + ".payload.administrativecategory.administrativemessagepayload.administrativemessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".payload.administrativecategory.administrativemessagepayload.administrativemessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".payload.administrativecategory.administrativemessagepayload.administrativemessage.messagedatalength"] = canonical::number((*message_2).message_data_length());
            }
        } else if (const auto* message = dynamic_cast<const protocol::ControlCategory*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.controlcategory";
            values[entry + ".payload.controlcategory.controlmessagetype"] = canonical::text(canonical::character((*message).control_message_type()));
            if (const auto* message_2 = dynamic_cast<const protocol::ControlMessage*>(message->control_message_payload())) {
                values[entry + ".payload.controlcategory.controlmessagepayload"] = "packet.message.payload.controlcategory.controlmessagepayload.controlmessage";
                values[entry + ".payload.controlcategory.controlmessagepayload.controlmessage.messageindicator"] = canonical::text(canonical::character((*message_2).message_indicator()));
                values[entry + ".payload.controlcategory.controlmessagepayload.controlmessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".payload.controlcategory.controlmessagepayload.controlmessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
            }
        } else if (const auto* message = dynamic_cast<const protocol::EquityAndIndexLastSaleCategory*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.equityandindexlastsalecategory";
            values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagetype"] = canonical::text(canonical::character((*message).equity_and_index_last_sale_message_type()));
            if (const auto* message_2 = dynamic_cast<const protocol::EquityAndIndexLastSaleMessage*>(message->equity_and_index_last_sale_message_payload())) {
                values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload"] = "packet.message.payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage";
                values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.messageindicator"] = canonical::text(canonical::character((*message_2).message_indicator()));
                values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.securitysymbol"] = canonical::text(std::string((*message_2).security_symbol()), ' ', false);
                values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.expirationblock.expirationmonth"] = canonical::text(canonical::character((*message_2).expiration_block().expiration_month()), ' ', false);
                values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.expirationblock.expirationday"] = canonical::number((*message_2).expiration_block().expiration_day());
                values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.expirationblock.expirationyear"] = canonical::number((*message_2).expiration_block().expiration_year());
                values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.strikepricedenominatorcode"] = canonical::text(canonical::character((*message_2).strike_price_denominator_code()), ' ', false);
                values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.strikeprice"] = canonical::number((*message_2).strike_price().mantissa());
                values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.volume"] = canonical::number((*message_2).volume());
                values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.premiumpricedenominatorcode"] = canonical::text(canonical::character((*message_2).premium_price_denominator_code()), ' ', false);
                values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.premiumprice"] = canonical::number((*message_2).premium_price().mantissa());
                values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.tradeidentifier"] = canonical::number((*message_2).trade_identifier());
            }
        } else if (const auto* message = dynamic_cast<const protocol::OpenInterestCategory*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.openinterestcategory";
            values[entry + ".payload.openinterestcategory.openinterestmessagetype"] = canonical::text(canonical::character((*message).open_interest_message_type()));
            if (const auto* message_2 = dynamic_cast<const protocol::OpenInterestMessage*>(message->open_interest_message_payload())) {
                values[entry + ".payload.openinterestcategory.openinterestmessagepayload"] = "packet.message.payload.openinterestcategory.openinterestmessagepayload.openinterestmessage";
                values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.messageindicator"] = canonical::text(canonical::character((*message_2).message_indicator()));
                values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.securitysymbol"] = canonical::text(std::string((*message_2).security_symbol()), ' ', false);
                values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.expirationblock.expirationmonth"] = canonical::text(canonical::character((*message_2).expiration_block().expiration_month()), ' ', false);
                values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.expirationblock.expirationday"] = canonical::number((*message_2).expiration_block().expiration_day());
                values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.expirationblock.expirationyear"] = canonical::number((*message_2).expiration_block().expiration_year());
                values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.strikepricedenominatorcode"] = canonical::text(canonical::character((*message_2).strike_price_denominator_code()), ' ', false);
                values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.strikeprice"] = canonical::number((*message_2).strike_price().mantissa());
                values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.openinterestvolume"] = canonical::number((*message_2).open_interest_volume());
            }
        } else if (const auto* message = dynamic_cast<const protocol::EquityAndIndexEndOfDaySummaryCategory*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.equityandindexendofdaysummarycategory";
            values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagetype"] = canonical::text(canonical::character((*message).equity_and_index_end_of_day_summary_message_type()));
            if (const auto* message_2 = dynamic_cast<const protocol::EquityAndIndexEndOfDaySummaryMessage*>(message->equity_and_index_end_of_day_summary_message_payload())) {
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload"] = "packet.message.payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage";
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.messageindicator"] = canonical::text(canonical::character((*message_2).message_indicator()));
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.securitysymbol"] = canonical::text(std::string((*message_2).security_symbol()), ' ', false);
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.expirationblock.expirationmonth"] = canonical::text(canonical::character((*message_2).expiration_block().expiration_month()), ' ', false);
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.expirationblock.expirationday"] = canonical::number((*message_2).expiration_block().expiration_day());
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.expirationblock.expirationyear"] = canonical::number((*message_2).expiration_block().expiration_year());
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.strikepricedenominatorcode"] = canonical::text(canonical::character((*message_2).strike_price_denominator_code()), ' ', false);
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.strikeprice"] = canonical::number((*message_2).strike_price().mantissa());
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.volume"] = canonical::number((*message_2).volume());
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.openinterestvolume"] = canonical::number((*message_2).open_interest_volume());
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.premiumpricedenominatorcode"] = canonical::text(canonical::character((*message_2).premium_price_denominator_code()), ' ', false);
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.openprice"] = canonical::number((*message_2).open_price());
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.highprice"] = canonical::number((*message_2).high_price());
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.lowprice"] = canonical::number((*message_2).low_price());
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.lastprice"] = canonical::number((*message_2).last_price());
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.netchange"] = canonical::number((*message_2).net_change());
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.underlyingpricedenominatorcode"] = canonical::text(canonical::character((*message_2).underlying_price_denominator_code()), ' ', false);
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.underlyingprice"] = canonical::number((*message_2).underlying_price().mantissa());
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.bidprice"] = canonical::number((*message_2).bid_price());
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.offerprice"] = canonical::number((*message_2).offer_price());
            }
        } else if (const auto* message = dynamic_cast<const protocol::LongEquityAndIndexQuoteCategory*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.longequityandindexquotecategory";
            values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagetype"] = canonical::text(canonical::character((*message).long_equity_and_index_quote_message_type()));
            if (const auto* message_2 = dynamic_cast<const protocol::LongEquityAndIndexQuoteMessage*>(message->long_equity_and_index_quote_message_payload())) {
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload"] = "packet.message.payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage";
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.bboindicator"] = canonical::text(canonical::character((*message_2).bbo_indicator()), ' ', false);
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.securitysymbol"] = canonical::text(std::string((*message_2).security_symbol()), ' ', false);
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.expirationblock.expirationmonth"] = canonical::text(canonical::character((*message_2).expiration_block().expiration_month()), ' ', false);
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.expirationblock.expirationday"] = canonical::number((*message_2).expiration_block().expiration_day());
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.expirationblock.expirationyear"] = canonical::number((*message_2).expiration_block().expiration_year());
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.strikepricedenominatorcode"] = canonical::text(canonical::character((*message_2).strike_price_denominator_code()), ' ', false);
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.strikeprice"] = canonical::number((*message_2).strike_price().mantissa());
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.premiumpricedenominatorcode"] = canonical::text(canonical::character((*message_2).premium_price_denominator_code()), ' ', false);
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.bidprice"] = canonical::number((*message_2).bid_price());
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.bidsize"] = canonical::number((*message_2).bid_size());
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.offerprice"] = canonical::number((*message_2).offer_price());
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.offersize"] = canonical::number((*message_2).offer_size());
            }
        } else if (const auto* message = dynamic_cast<const protocol::ShortEquityAndIndexQuoteCategory*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.shortequityandindexquotecategory";
            values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagetype"] = canonical::text(canonical::character((*message).short_equity_and_index_quote_message_type()));
            if (const auto* message_2 = dynamic_cast<const protocol::ShortEquityAndIndexQuoteMessage*>(message->short_equity_and_index_quote_message_payload())) {
                values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload"] = "packet.message.payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage";
                values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.bboindicator"] = canonical::text(canonical::character((*message_2).bbo_indicator()), ' ', false);
                values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.securitysymbolshort"] = canonical::text(std::string((*message_2).security_symbol_short()), ' ', false);
                values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.expirationblock.expirationmonth"] = canonical::text(canonical::character((*message_2).expiration_block().expiration_month()), ' ', false);
                values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.expirationblock.expirationday"] = canonical::number((*message_2).expiration_block().expiration_day());
                values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.expirationblock.expirationyear"] = canonical::number((*message_2).expiration_block().expiration_year());
                values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.strikepriceshort"] = canonical::scaled((*message_2).strike_price_short().mantissa(), (*message_2).strike_price_short().exponent());
                values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.bidpriceshort"] = canonical::scaled((*message_2).bid_price_short().mantissa(), (*message_2).bid_price_short().exponent());
                values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.bidsizeshort"] = canonical::number((*message_2).bid_size_short());
                values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.offerpriceshort"] = canonical::scaled((*message_2).offer_price_short().mantissa(), (*message_2).offer_price_short().exponent());
                values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.offersizeshort"] = canonical::number((*message_2).offer_size_short());
            }
        } else if (const auto* message = dynamic_cast<const protocol::UnderlyingValueCategory*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.underlyingvaluecategory";
            values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagetype"] = canonical::text(canonical::character((*message).underlying_value_message_type()));
            if (const auto* message_2 = dynamic_cast<const protocol::UnderlyingValueLastSaleMessage*>(message->underlying_value_message_payload())) {
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload"] = "packet.message.payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluelastsalemessage";
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluelastsalemessage.messageindicator"] = canonical::text(canonical::character((*message_2).message_indicator()));
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluelastsalemessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluelastsalemessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluelastsalemessage.securitysymbol"] = canonical::text(std::string((*message_2).security_symbol()), ' ', false);
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluelastsalemessage.indexvaluedenominatorcode"] = canonical::text(canonical::character((*message_2).index_value_denominator_code()), ' ', false);
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluelastsalemessage.indexvalue"] = canonical::number((*message_2).index_value().mantissa());
            } else if (const auto* message_2 = dynamic_cast<const protocol::UnderlyingValueBidAndOfferMessage*>(message->underlying_value_message_payload())) {
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload"] = "packet.message.payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage";
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage.messageindicator"] = canonical::text(canonical::character((*message_2).message_indicator()));
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage.transactionid"] = canonical::number((*message_2).transaction_id());
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage.participantreferencenumber"] = canonical::number((*message_2).participant_reference_number());
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage.securitysymbol"] = canonical::text(std::string((*message_2).security_symbol()), ' ', false);
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage.indexvaluedenominatorcode"] = canonical::text(canonical::character((*message_2).index_value_denominator_code()), ' ', false);
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage.bidindexvalue"] = canonical::number((*message_2).bid_index_value());
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage.offerindexvalue"] = canonical::number((*message_2).offer_index_value());
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
    std::printf("== Siac.Opra.Output.Obi.v6.2 (classes values)\n");
    int failures = 0;
    failures += check("AdministrativeMessage", "Siac/Opra.Output.Obi.v6.2/AdministrativeMessage.pcap", "siac/opra/output/obi/v6.2/AdministrativeMessage.values");
    failures += check("ControlMessage", "Siac/Opra.Output.Obi.v6.2/ControlMessage.pcap", "siac/opra/output/obi/v6.2/ControlMessage.values");
    failures += check("LongEquityAndIndexQuoteMessage", "Siac/Opra.Output.Obi.v6.2/LongEquityAndIndexQuoteMessage.pcap", "siac/opra/output/obi/v6.2/LongEquityAndIndexQuoteMessage.values");
    failures += check("ShortEquityAndIndexQuoteMessage", "Siac/Opra.Output.Obi.v6.2/ShortEquityAndIndexQuoteMessage.pcap", "siac/opra/output/obi/v6.2/ShortEquityAndIndexQuoteMessage.values");
    return failures == 0 ? 0 : 1;
}
