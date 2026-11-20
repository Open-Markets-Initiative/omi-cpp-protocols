// Siac.Opra.Output.Obi.v6.2 canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/binary/modern/siac/opra/output/obi/v6.2/definitions.hpp"

namespace protocol = ::siac::opra::output::obi::v6_2;

namespace {

// The values the Modern iterator reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    values["packet.blockheader.version"] = canonical::number(iterator.block_header->version.get());
    values["packet.blockheader.blocksize"] = canonical::number(iterator.block_header->block_size.get());
    values["packet.blockheader.datafeedindicator"] = canonical::text(canonical::character(iterator.block_header->data_feed_indicator.get()));
    values["packet.blockheader.retransmissionindicator"] = canonical::text(canonical::character(iterator.block_header->retransmission_indicator.get()), {std::string_view(" ", 1)});
    values["packet.blockheader.sessionindicator"] = canonical::number(iterator.block_header->session_indicator.get());
    values["packet.blockheader.blocksequencenumber"] = canonical::number(iterator.block_header->block_sequence_number.get());
    values["packet.blockheader.messagesinblock"] = canonical::number(iterator.block_header->messages_in_block.get());
    values["packet.blockheader.blocktimestamp.seconds"] = canonical::number(iterator.block_header->block_timestamp.seconds.get());
    values["packet.blockheader.blocktimestamp.nanoseconds"] = canonical::number(iterator.block_header->block_timestamp.nanoseconds.get());
    values["packet.blockheader.blockchecksum"] = canonical::number(iterator.block_header->block_checksum.get());

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.participantid"] = canonical::text(canonical::character(iterator.message_header->participant_id.get()));
        values[entry + ".messageheader.messagecategory"] = canonical::text(canonical::character(iterator.message_header->message_category.get()));

        if (iterator.message_category == 'C') {
            values[entry + ".payload"] = "packet.message.payload.administrativecategory";
            [[maybe_unused]] const auto* message = protocol::AdministrativeCategory::parse(iterator.message);
            values[entry + ".payload.administrativecategory.administrativemessagetype"] = canonical::text(canonical::character(message->administrative_message_type.get()), {std::string_view(" ", 1)});
            if (message->administrative_message_type.get() == ' ') {
                values[entry + ".payload.administrativecategory.administrativemessagepayload"] = "packet.message.payload.administrativecategory.administrativemessagepayload.administrativemessage";
                [[maybe_unused]] const auto* message_2 = protocol::AdministrativeMessage::parse(iterator.message + sizeof(protocol::AdministrativeCategory));
                values[entry + ".payload.administrativecategory.administrativemessagepayload.administrativemessage.messageindicator"] = canonical::text(canonical::character(message_2->message_indicator.get()));
                values[entry + ".payload.administrativecategory.administrativemessagepayload.administrativemessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".payload.administrativecategory.administrativemessagepayload.administrativemessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".payload.administrativecategory.administrativemessagepayload.administrativemessage.messagedatalength"] = canonical::number(message_2->message_data_length.get());
            }
        } else if (iterator.message_category == 'H') {
            values[entry + ".payload"] = "packet.message.payload.controlcategory";
            [[maybe_unused]] const auto* message = protocol::ControlCategory::parse(iterator.message);
            values[entry + ".payload.controlcategory.controlmessagetype"] = canonical::text(canonical::character(message->control_message_type.get()));
            if (message->control_message_type.get() == 'C' || message->control_message_type.get() == 'E' || message->control_message_type.get() == 'F' || message->control_message_type.get() == 'J' || message->control_message_type.get() == 'K' || message->control_message_type.get() == 'L' || message->control_message_type.get() == 'M' || message->control_message_type.get() == 'N' || message->control_message_type.get() == 'P') {
                values[entry + ".payload.controlcategory.controlmessagepayload"] = "packet.message.payload.controlcategory.controlmessagepayload.controlmessage";
                [[maybe_unused]] const auto* message_2 = protocol::ControlMessage::parse(iterator.message + sizeof(protocol::ControlCategory));
                values[entry + ".payload.controlcategory.controlmessagepayload.controlmessage.messageindicator"] = canonical::text(canonical::character(message_2->message_indicator.get()));
                values[entry + ".payload.controlcategory.controlmessagepayload.controlmessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".payload.controlcategory.controlmessagepayload.controlmessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
            }
        } else if (iterator.message_category == 'a') {
            values[entry + ".payload"] = "packet.message.payload.equityandindexlastsalecategory";
            [[maybe_unused]] const auto* message = protocol::EquityAndIndexLastSaleCategory::parse(iterator.message);
            values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagetype"] = canonical::text(canonical::character(message->equity_and_index_last_sale_message_type.get()));
            if (message->equity_and_index_last_sale_message_type.get() == 'A' || message->equity_and_index_last_sale_message_type.get() == 'B' || message->equity_and_index_last_sale_message_type.get() == 'C' || message->equity_and_index_last_sale_message_type.get() == 'D' || message->equity_and_index_last_sale_message_type.get() == 'E' || message->equity_and_index_last_sale_message_type.get() == 'F' || message->equity_and_index_last_sale_message_type.get() == 'G' || message->equity_and_index_last_sale_message_type.get() == 'H' || message->equity_and_index_last_sale_message_type.get() == 'I' || message->equity_and_index_last_sale_message_type.get() == 'J' || message->equity_and_index_last_sale_message_type.get() == 'K' || message->equity_and_index_last_sale_message_type.get() == 'L' || message->equity_and_index_last_sale_message_type.get() == 'M' || message->equity_and_index_last_sale_message_type.get() == 'N' || message->equity_and_index_last_sale_message_type.get() == 'O' || message->equity_and_index_last_sale_message_type.get() == 'P' || message->equity_and_index_last_sale_message_type.get() == 'Q' || message->equity_and_index_last_sale_message_type.get() == 'R' || message->equity_and_index_last_sale_message_type.get() == 'S' || message->equity_and_index_last_sale_message_type.get() == 'T' || message->equity_and_index_last_sale_message_type.get() == 'X') {
                values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload"] = "packet.message.payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage";
                [[maybe_unused]] const auto* message_2 = protocol::EquityAndIndexLastSaleMessage::parse(iterator.message + sizeof(protocol::EquityAndIndexLastSaleCategory));
                values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.messageindicator"] = canonical::text(canonical::character(message_2->message_indicator.get()));
                values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.securitysymbol"] = canonical::text(std::string(message_2->security_symbol.get()), ' ', false);
                values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.expirationblock.expirationmonth"] = canonical::text(canonical::character(message_2->expiration_block.expiration_month.get()), ' ', false);
                values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.expirationblock.expirationday"] = canonical::number(message_2->expiration_block.expiration_day.get());
                values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.expirationblock.expirationyear"] = canonical::number(message_2->expiration_block.expiration_year.get());
                values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.strikepricedenominatorcode"] = canonical::text(canonical::character(message_2->strike_price_denominator_code.get()), ' ', false);
                values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.strikeprice"] = canonical::number(message_2->strike_price.integer());
                values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.volume"] = canonical::number(message_2->volume.get());
                values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.premiumpricedenominatorcode"] = canonical::text(canonical::character(message_2->premium_price_denominator_code.get()), ' ', false);
                values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.premiumprice"] = canonical::number(message_2->premium_price.integer());
                values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.tradeidentifier"] = canonical::number(message_2->trade_identifier.get());
            }
        } else if (iterator.message_category == 'd') {
            values[entry + ".payload"] = "packet.message.payload.openinterestcategory";
            [[maybe_unused]] const auto* message = protocol::OpenInterestCategory::parse(iterator.message);
            values[entry + ".payload.openinterestcategory.openinterestmessagetype"] = canonical::text(canonical::character(message->open_interest_message_type.get()), {std::string_view(" ", 1)});
            if (message->open_interest_message_type.get() == ' ') {
                values[entry + ".payload.openinterestcategory.openinterestmessagepayload"] = "packet.message.payload.openinterestcategory.openinterestmessagepayload.openinterestmessage";
                [[maybe_unused]] const auto* message_2 = protocol::OpenInterestMessage::parse(iterator.message + sizeof(protocol::OpenInterestCategory));
                values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.messageindicator"] = canonical::text(canonical::character(message_2->message_indicator.get()));
                values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.securitysymbol"] = canonical::text(std::string(message_2->security_symbol.get()), ' ', false);
                values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.expirationblock.expirationmonth"] = canonical::text(canonical::character(message_2->expiration_block.expiration_month.get()), ' ', false);
                values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.expirationblock.expirationday"] = canonical::number(message_2->expiration_block.expiration_day.get());
                values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.expirationblock.expirationyear"] = canonical::number(message_2->expiration_block.expiration_year.get());
                values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.strikepricedenominatorcode"] = canonical::text(canonical::character(message_2->strike_price_denominator_code.get()), ' ', false);
                values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.strikeprice"] = canonical::number(message_2->strike_price.integer());
                values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.openinterestvolume"] = canonical::number(message_2->open_interest_volume.get());
            }
        } else if (iterator.message_category == 'f') {
            values[entry + ".payload"] = "packet.message.payload.equityandindexendofdaysummarycategory";
            [[maybe_unused]] const auto* message = protocol::EquityAndIndexEndOfDaySummaryCategory::parse(iterator.message);
            values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagetype"] = canonical::text(canonical::character(message->equity_and_index_end_of_day_summary_message_type.get()), {std::string_view(" ", 1)});
            if (message->equity_and_index_end_of_day_summary_message_type.get() == ' ') {
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload"] = "packet.message.payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage";
                [[maybe_unused]] const auto* message_2 = protocol::EquityAndIndexEndOfDaySummaryMessage::parse(iterator.message + sizeof(protocol::EquityAndIndexEndOfDaySummaryCategory));
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.messageindicator"] = canonical::text(canonical::character(message_2->message_indicator.get()));
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.securitysymbol"] = canonical::text(std::string(message_2->security_symbol.get()), ' ', false);
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.expirationblock.expirationmonth"] = canonical::text(canonical::character(message_2->expiration_block.expiration_month.get()), ' ', false);
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.expirationblock.expirationday"] = canonical::number(message_2->expiration_block.expiration_day.get());
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.expirationblock.expirationyear"] = canonical::number(message_2->expiration_block.expiration_year.get());
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.strikepricedenominatorcode"] = canonical::text(canonical::character(message_2->strike_price_denominator_code.get()), ' ', false);
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.strikeprice"] = canonical::number(message_2->strike_price.integer());
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.volume"] = canonical::number(message_2->volume.get());
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.openinterestvolume"] = canonical::number(message_2->open_interest_volume.get());
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.premiumpricedenominatorcode"] = canonical::text(canonical::character(message_2->premium_price_denominator_code.get()), ' ', false);
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.openprice"] = canonical::number(message_2->open_price.get());
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.highprice"] = canonical::number(message_2->high_price.get());
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.lowprice"] = canonical::number(message_2->low_price.get());
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.lastprice"] = canonical::number(message_2->last_price.get());
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.netchange"] = canonical::number(message_2->net_change.get());
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.underlyingpricedenominatorcode"] = canonical::text(canonical::character(message_2->underlying_price_denominator_code.get()), ' ', false);
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.underlyingprice"] = canonical::number(message_2->underlying_price.integer());
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.bidprice"] = canonical::number(message_2->bid_price.get());
                values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.offerprice"] = canonical::number(message_2->offer_price.get());
            }
        } else if (iterator.message_category == 'k') {
            values[entry + ".payload"] = "packet.message.payload.longequityandindexquotecategory";
            [[maybe_unused]] const auto* message = protocol::LongEquityAndIndexQuoteCategory::parse(iterator.message);
            values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagetype"] = canonical::text(canonical::character(message->long_equity_and_index_quote_message_type.get()), {std::string_view(" ", 1)});
            if (message->long_equity_and_index_quote_message_type.get() == ' ' || message->long_equity_and_index_quote_message_type.get() == 'F' || message->long_equity_and_index_quote_message_type.get() == 'I' || message->long_equity_and_index_quote_message_type.get() == 'R' || message->long_equity_and_index_quote_message_type.get() == 'T' || message->long_equity_and_index_quote_message_type.get() == 'A' || message->long_equity_and_index_quote_message_type.get() == 'B' || message->long_equity_and_index_quote_message_type.get() == 'O' || message->long_equity_and_index_quote_message_type.get() == 'C' || message->long_equity_and_index_quote_message_type.get() == 'X' || message->long_equity_and_index_quote_message_type.get() == 'Y') {
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload"] = "packet.message.payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage";
                [[maybe_unused]] const auto* message_2 = protocol::LongEquityAndIndexQuoteMessage::parse(iterator.message + sizeof(protocol::LongEquityAndIndexQuoteCategory));
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.bboindicator"] = canonical::text(canonical::character(message_2->bbo_indicator.get()), ' ', false, {std::string_view(" ", 1), std::string_view("", 0)});
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.securitysymbol"] = canonical::text(std::string(message_2->security_symbol.get()), ' ', false);
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.expirationblock.expirationmonth"] = canonical::text(canonical::character(message_2->expiration_block.expiration_month.get()), ' ', false);
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.expirationblock.expirationday"] = canonical::number(message_2->expiration_block.expiration_day.get());
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.expirationblock.expirationyear"] = canonical::number(message_2->expiration_block.expiration_year.get());
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.strikepricedenominatorcode"] = canonical::text(canonical::character(message_2->strike_price_denominator_code.get()), ' ', false);
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.strikeprice"] = canonical::number(message_2->strike_price.integer());
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.premiumpricedenominatorcode"] = canonical::text(canonical::character(message_2->premium_price_denominator_code.get()), ' ', false);
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.bidprice"] = canonical::number(message_2->bid_price.get());
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.bidsize"] = canonical::number(message_2->bid_size.get());
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.offerprice"] = canonical::number(message_2->offer_price.get());
                values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.offersize"] = canonical::number(message_2->offer_size.get());
            }
        } else if (iterator.message_category == 'q') {
            values[entry + ".payload"] = "packet.message.payload.shortequityandindexquotecategory";
            [[maybe_unused]] const auto* message = protocol::ShortEquityAndIndexQuoteCategory::parse(iterator.message);
            values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagetype"] = canonical::text(canonical::character(message->short_equity_and_index_quote_message_type.get()), {std::string_view(" ", 1)});
            if (message->short_equity_and_index_quote_message_type.get() == ' ' || message->short_equity_and_index_quote_message_type.get() == 'F' || message->short_equity_and_index_quote_message_type.get() == 'I' || message->short_equity_and_index_quote_message_type.get() == 'R' || message->short_equity_and_index_quote_message_type.get() == 'T' || message->short_equity_and_index_quote_message_type.get() == 'A' || message->short_equity_and_index_quote_message_type.get() == 'B' || message->short_equity_and_index_quote_message_type.get() == 'O' || message->short_equity_and_index_quote_message_type.get() == 'C' || message->short_equity_and_index_quote_message_type.get() == 'X' || message->short_equity_and_index_quote_message_type.get() == 'Y') {
                values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload"] = "packet.message.payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage";
                [[maybe_unused]] const auto* message_2 = protocol::ShortEquityAndIndexQuoteMessage::parse(iterator.message + sizeof(protocol::ShortEquityAndIndexQuoteCategory));
                values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.bboindicator"] = canonical::text(canonical::character(message_2->bbo_indicator.get()), ' ', false, {std::string_view(" ", 1), std::string_view("", 0)});
                values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.securitysymbolshort"] = canonical::text(std::string(message_2->security_symbol_short.get()), ' ', false);
                values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.expirationblock.expirationmonth"] = canonical::text(canonical::character(message_2->expiration_block.expiration_month.get()), ' ', false);
                values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.expirationblock.expirationday"] = canonical::number(message_2->expiration_block.expiration_day.get());
                values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.expirationblock.expirationyear"] = canonical::number(message_2->expiration_block.expiration_year.get());
                values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.strikepriceshort"] = canonical::scaled(message_2->strike_price_short.integer(), -1);
                values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.bidpriceshort"] = canonical::scaled(message_2->bid_price_short.integer(), -2);
                values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.bidsizeshort"] = canonical::number(message_2->bid_size_short.get());
                values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.offerpriceshort"] = canonical::scaled(message_2->offer_price_short.integer(), -2);
                values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.offersizeshort"] = canonical::number(message_2->offer_size_short.get());
            }
        } else if (iterator.message_category == 'Y') {
            values[entry + ".payload"] = "packet.message.payload.underlyingvaluecategory";
            [[maybe_unused]] const auto* message = protocol::UnderlyingValueCategory::parse(iterator.message);
            values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagetype"] = canonical::text(canonical::character(message->underlying_value_message_type.get()), {std::string_view(" ", 1)});
            if (message->underlying_value_message_type.get() == ' ') {
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload"] = "packet.message.payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluelastsalemessage";
                [[maybe_unused]] const auto* message_2 = protocol::UnderlyingValueLastSaleMessage::parse(iterator.message + sizeof(protocol::UnderlyingValueCategory));
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluelastsalemessage.messageindicator"] = canonical::text(canonical::character(message_2->message_indicator.get()));
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluelastsalemessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluelastsalemessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluelastsalemessage.securitysymbol"] = canonical::text(std::string(message_2->security_symbol.get()), ' ', false);
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluelastsalemessage.indexvaluedenominatorcode"] = canonical::text(canonical::character(message_2->index_value_denominator_code.get()), ' ', false);
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluelastsalemessage.indexvalue"] = canonical::number(message_2->index_value.integer());
            } else if (message->underlying_value_message_type.get() == 'I') {
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload"] = "packet.message.payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage";
                [[maybe_unused]] const auto* message_2 = protocol::UnderlyingValueBidAndOfferMessage::parse(iterator.message + sizeof(protocol::UnderlyingValueCategory));
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage.messageindicator"] = canonical::text(canonical::character(message_2->message_indicator.get()));
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage.transactionid"] = canonical::number(message_2->transaction_id.get());
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage.participantreferencenumber"] = canonical::number(message_2->participant_reference_number.get());
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage.securitysymbol"] = canonical::text(std::string(message_2->security_symbol.get()), ' ', false);
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage.indexvaluedenominatorcode"] = canonical::text(canonical::character(message_2->index_value_denominator_code.get()), ' ', false);
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage.bidindexvalue"] = canonical::number(message_2->bid_index_value.get());
                values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage.offerindexvalue"] = canonical::number(message_2->offer_index_value.get());
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
    std::printf("== Siac.Opra.Output.Obi.v6.2 (modern values)\n");
    int failures = 0;
    failures += check("AdministrativeMessage", "Siac/Opra.Output.Obi.v6.2/AdministrativeMessage.pcap", "siac/opra/output/obi/v6.2/AdministrativeMessage.values");
    failures += check("ControlMessage", "Siac/Opra.Output.Obi.v6.2/ControlMessage.pcap", "siac/opra/output/obi/v6.2/ControlMessage.values");
    failures += check("LongEquityAndIndexQuoteMessage", "Siac/Opra.Output.Obi.v6.2/LongEquityAndIndexQuoteMessage.pcap", "siac/opra/output/obi/v6.2/LongEquityAndIndexQuoteMessage.values");
    failures += check("ShortEquityAndIndexQuoteMessage", "Siac/Opra.Output.Obi.v6.2/ShortEquityAndIndexQuoteMessage.pcap", "siac/opra/output/obi/v6.2/ShortEquityAndIndexQuoteMessage.values");
    return failures == 0 ? 0 : 1;
}
