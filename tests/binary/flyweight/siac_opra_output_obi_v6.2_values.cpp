// Siac.Opra.Output.Obi.v6.2 canonical values, through the Flyweight reader: every value Flyweight reads
// from each sample, at its address, held to what the model reads.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <span>
#include <string>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "tests/canonical/Canonical.hpp"
#include "cpp/binary/flyweight/siac/opra/output/obi/v6.2/definitions.hpp"

namespace protocol = ::siac::opra::output::obi::v6_2;

namespace {

// The messages Administrative Message Payload selects, their values set in the entry of the message holding it
struct AdministrativeMessagePayloadHandler {
    canonical::Listing& values;
    const std::string& entry;

    void on(const protocol::AdministrativeMessage& message) {
        values[entry + ".payload.administrativecategory.administrativemessagepayload"] = "packet.message.payload.administrativecategory.administrativemessagepayload.administrativemessage";
        values[entry + ".payload.administrativecategory.administrativemessagepayload.administrativemessage.messageindicator"] = canonical::text(canonical::character(message.message_indicator()));
        values[entry + ".payload.administrativecategory.administrativemessagepayload.administrativemessage.transactionid"] = canonical::number(message.transaction_id());
        values[entry + ".payload.administrativecategory.administrativemessagepayload.administrativemessage.participantreferencenumber"] = canonical::number(message.participant_reference_number());
        values[entry + ".payload.administrativecategory.administrativemessagepayload.administrativemessage.messagedatalength"] = canonical::number(message.message_data_length());
    }
};

// The messages Control Message Payload selects, their values set in the entry of the message holding it
struct ControlMessagePayloadHandler {
    canonical::Listing& values;
    const std::string& entry;

    void on(const protocol::ControlMessage& message) {
        values[entry + ".payload.controlcategory.controlmessagepayload"] = "packet.message.payload.controlcategory.controlmessagepayload.controlmessage";
        values[entry + ".payload.controlcategory.controlmessagepayload.controlmessage.messageindicator"] = canonical::text(canonical::character(message.message_indicator()));
        values[entry + ".payload.controlcategory.controlmessagepayload.controlmessage.transactionid"] = canonical::number(message.transaction_id());
        values[entry + ".payload.controlcategory.controlmessagepayload.controlmessage.participantreferencenumber"] = canonical::number(message.participant_reference_number());
    }
};

// The messages Equity And Index Last Sale Message Payload selects, their values set in the entry of the message holding it
struct EquityAndIndexLastSaleMessagePayloadHandler {
    canonical::Listing& values;
    const std::string& entry;

    void on(const protocol::EquityAndIndexLastSaleMessage& message) {
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload"] = "packet.message.payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage";
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.messageindicator"] = canonical::text(canonical::character(message.message_indicator()));
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.transactionid"] = canonical::number(message.transaction_id());
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.participantreferencenumber"] = canonical::number(message.participant_reference_number());
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.securitysymbol"] = canonical::text(std::string(message.security_symbol()), ' ', false);
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.expirationblock.expirationmonth"] = canonical::text(canonical::character(message.expiration_block().expiration_month()), ' ', false);
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.expirationblock.expirationday"] = canonical::number(message.expiration_block().expiration_day());
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.expirationblock.expirationyear"] = canonical::number(message.expiration_block().expiration_year());
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.strikepricedenominatorcode"] = canonical::text(canonical::character(message.strike_price_denominator_code()), ' ', false);
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.strikeprice"] = canonical::number(message.strike_price().mantissa());
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.volume"] = canonical::number(message.volume());
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.premiumpricedenominatorcode"] = canonical::text(canonical::character(message.premium_price_denominator_code()), ' ', false);
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.premiumprice"] = canonical::number(message.premium_price().mantissa());
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagepayload.equityandindexlastsalemessage.tradeidentifier"] = canonical::number(message.trade_identifier());
    }
};

// The messages Open Interest Message Payload selects, their values set in the entry of the message holding it
struct OpenInterestMessagePayloadHandler {
    canonical::Listing& values;
    const std::string& entry;

    void on(const protocol::OpenInterestMessage& message) {
        values[entry + ".payload.openinterestcategory.openinterestmessagepayload"] = "packet.message.payload.openinterestcategory.openinterestmessagepayload.openinterestmessage";
        values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.messageindicator"] = canonical::text(canonical::character(message.message_indicator()));
        values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.transactionid"] = canonical::number(message.transaction_id());
        values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.participantreferencenumber"] = canonical::number(message.participant_reference_number());
        values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.securitysymbol"] = canonical::text(std::string(message.security_symbol()), ' ', false);
        values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.expirationblock.expirationmonth"] = canonical::text(canonical::character(message.expiration_block().expiration_month()), ' ', false);
        values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.expirationblock.expirationday"] = canonical::number(message.expiration_block().expiration_day());
        values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.expirationblock.expirationyear"] = canonical::number(message.expiration_block().expiration_year());
        values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.strikepricedenominatorcode"] = canonical::text(canonical::character(message.strike_price_denominator_code()), ' ', false);
        values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.strikeprice"] = canonical::number(message.strike_price().mantissa());
        values[entry + ".payload.openinterestcategory.openinterestmessagepayload.openinterestmessage.openinterestvolume"] = canonical::number(message.open_interest_volume());
    }
};

// The messages Equity And Index End Of Day Summary Message Payload selects, their values set in the entry of the message holding it
struct EquityAndIndexEndOfDaySummaryMessagePayloadHandler {
    canonical::Listing& values;
    const std::string& entry;

    void on(const protocol::EquityAndIndexEndOfDaySummaryMessage& message) {
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload"] = "packet.message.payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage";
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.messageindicator"] = canonical::text(canonical::character(message.message_indicator()));
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.transactionid"] = canonical::number(message.transaction_id());
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.participantreferencenumber"] = canonical::number(message.participant_reference_number());
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.securitysymbol"] = canonical::text(std::string(message.security_symbol()), ' ', false);
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.expirationblock.expirationmonth"] = canonical::text(canonical::character(message.expiration_block().expiration_month()), ' ', false);
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.expirationblock.expirationday"] = canonical::number(message.expiration_block().expiration_day());
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.expirationblock.expirationyear"] = canonical::number(message.expiration_block().expiration_year());
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.strikepricedenominatorcode"] = canonical::text(canonical::character(message.strike_price_denominator_code()), ' ', false);
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.strikeprice"] = canonical::number(message.strike_price().mantissa());
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.volume"] = canonical::number(message.volume());
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.openinterestvolume"] = canonical::number(message.open_interest_volume());
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.premiumpricedenominatorcode"] = canonical::text(canonical::character(message.premium_price_denominator_code()), ' ', false);
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.openprice"] = canonical::number(message.open_price());
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.highprice"] = canonical::number(message.high_price());
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.lowprice"] = canonical::number(message.low_price());
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.lastprice"] = canonical::number(message.last_price());
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.netchange"] = canonical::number(message.net_change());
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.underlyingpricedenominatorcode"] = canonical::text(canonical::character(message.underlying_price_denominator_code()), ' ', false);
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.underlyingprice"] = canonical::number(message.underlying_price().mantissa());
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.bidprice"] = canonical::number(message.bid_price());
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagepayload.equityandindexendofdaysummarymessage.offerprice"] = canonical::number(message.offer_price());
    }
};

// The messages Long Equity And Index Quote Message Payload selects, their values set in the entry of the message holding it
struct LongEquityAndIndexQuoteMessagePayloadHandler {
    canonical::Listing& values;
    const std::string& entry;

    void on(const protocol::LongEquityAndIndexQuoteMessage& message) {
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload"] = "packet.message.payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage";
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.bboindicator"] = canonical::text(canonical::character(message.bbo_indicator()), ' ', false);
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.transactionid"] = canonical::number(message.transaction_id());
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.participantreferencenumber"] = canonical::number(message.participant_reference_number());
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.securitysymbol"] = canonical::text(std::string(message.security_symbol()), ' ', false);
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.expirationblock.expirationmonth"] = canonical::text(canonical::character(message.expiration_block().expiration_month()), ' ', false);
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.expirationblock.expirationday"] = canonical::number(message.expiration_block().expiration_day());
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.expirationblock.expirationyear"] = canonical::number(message.expiration_block().expiration_year());
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.strikepricedenominatorcode"] = canonical::text(canonical::character(message.strike_price_denominator_code()), ' ', false);
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.strikeprice"] = canonical::number(message.strike_price().mantissa());
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.premiumpricedenominatorcode"] = canonical::text(canonical::character(message.premium_price_denominator_code()), ' ', false);
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.bidprice"] = canonical::number(message.bid_price());
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.bidsize"] = canonical::number(message.bid_size());
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.offerprice"] = canonical::number(message.offer_price());
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagepayload.longequityandindexquotemessage.offersize"] = canonical::number(message.offer_size());
    }
};

// The messages Short Equity And Index Quote Message Payload selects, their values set in the entry of the message holding it
struct ShortEquityAndIndexQuoteMessagePayloadHandler {
    canonical::Listing& values;
    const std::string& entry;

    void on(const protocol::ShortEquityAndIndexQuoteMessage& message) {
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload"] = "packet.message.payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage";
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.bboindicator"] = canonical::text(canonical::character(message.bbo_indicator()), ' ', false);
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.transactionid"] = canonical::number(message.transaction_id());
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.participantreferencenumber"] = canonical::number(message.participant_reference_number());
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.securitysymbolshort"] = canonical::text(std::string(message.security_symbol_short()), ' ', false);
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.expirationblock.expirationmonth"] = canonical::text(canonical::character(message.expiration_block().expiration_month()), ' ', false);
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.expirationblock.expirationday"] = canonical::number(message.expiration_block().expiration_day());
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.expirationblock.expirationyear"] = canonical::number(message.expiration_block().expiration_year());
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.strikepriceshort"] = canonical::scaled(message.strike_price_short().mantissa(), message.strike_price_short().exponent());
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.bidpriceshort"] = canonical::scaled(message.bid_price_short().mantissa(), message.bid_price_short().exponent());
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.bidsizeshort"] = canonical::number(message.bid_size_short());
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.offerpriceshort"] = canonical::scaled(message.offer_price_short().mantissa(), message.offer_price_short().exponent());
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagepayload.shortequityandindexquotemessage.offersizeshort"] = canonical::number(message.offer_size_short());
    }
};

// The messages Underlying Value Message Payload selects, their values set in the entry of the message holding it
struct UnderlyingValueMessagePayloadHandler {
    canonical::Listing& values;
    const std::string& entry;

    void on(const protocol::UnderlyingValueLastSaleMessage& message) {
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload"] = "packet.message.payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluelastsalemessage";
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluelastsalemessage.messageindicator"] = canonical::text(canonical::character(message.message_indicator()));
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluelastsalemessage.transactionid"] = canonical::number(message.transaction_id());
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluelastsalemessage.participantreferencenumber"] = canonical::number(message.participant_reference_number());
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluelastsalemessage.securitysymbol"] = canonical::text(std::string(message.security_symbol()), ' ', false);
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluelastsalemessage.indexvaluedenominatorcode"] = canonical::text(canonical::character(message.index_value_denominator_code()), ' ', false);
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluelastsalemessage.indexvalue"] = canonical::number(message.index_value().mantissa());
    }

    void on(const protocol::UnderlyingValueBidAndOfferMessage& message) {
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload"] = "packet.message.payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage";
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage.messageindicator"] = canonical::text(canonical::character(message.message_indicator()));
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage.transactionid"] = canonical::number(message.transaction_id());
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage.participantreferencenumber"] = canonical::number(message.participant_reference_number());
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage.securitysymbol"] = canonical::text(std::string(message.security_symbol()), ' ', false);
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage.indexvaluedenominatorcode"] = canonical::text(canonical::character(message.index_value_denominator_code()), ' ', false);
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage.bidindexvalue"] = canonical::number(message.bid_index_value());
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagepayload.underlyingvaluebidandoffermessage.offerindexvalue"] = canonical::number(message.offer_index_value());
    }
};

// The handler the reader hands each datagram's views to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
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
    }

    // a message this test prints no values of, or a code no message answers to, still takes its entry
    template <typename Message>
    void on(const Message&) {
        ++index;
    }

    template <typename Code>
    void on_unknown(Code, std::span<const std::byte>) {
        ++index;
    }

    void on(const protocol::AdministrativeCategory& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.administrativecategory";
        values[entry + ".payload.administrativecategory.administrativemessagetype"] = canonical::text(canonical::character(message.administrative_message_type()));
        AdministrativeMessagePayloadHandler selected{ values, entry };
        message.administrative_message_payload(selected);
    }

    void on(const protocol::ControlCategory& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.controlcategory";
        values[entry + ".payload.controlcategory.controlmessagetype"] = canonical::text(canonical::character(message.control_message_type()));
        ControlMessagePayloadHandler selected{ values, entry };
        message.control_message_payload(selected);
    }

    void on(const protocol::EquityAndIndexLastSaleCategory& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.equityandindexlastsalecategory";
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagetype"] = canonical::text(canonical::character(message.equity_and_index_last_sale_message_type()));
        EquityAndIndexLastSaleMessagePayloadHandler selected{ values, entry };
        message.equity_and_index_last_sale_message_payload(selected);
    }

    void on(const protocol::OpenInterestCategory& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.openinterestcategory";
        values[entry + ".payload.openinterestcategory.openinterestmessagetype"] = canonical::text(canonical::character(message.open_interest_message_type()));
        OpenInterestMessagePayloadHandler selected{ values, entry };
        message.open_interest_message_payload(selected);
    }

    void on(const protocol::EquityAndIndexEndOfDaySummaryCategory& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.equityandindexendofdaysummarycategory";
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagetype"] = canonical::text(canonical::character(message.equity_and_index_end_of_day_summary_message_type()));
        EquityAndIndexEndOfDaySummaryMessagePayloadHandler selected{ values, entry };
        message.equity_and_index_end_of_day_summary_message_payload(selected);
    }

    void on(const protocol::LongEquityAndIndexQuoteCategory& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.longequityandindexquotecategory";
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagetype"] = canonical::text(canonical::character(message.long_equity_and_index_quote_message_type()));
        LongEquityAndIndexQuoteMessagePayloadHandler selected{ values, entry };
        message.long_equity_and_index_quote_message_payload(selected);
    }

    void on(const protocol::ShortEquityAndIndexQuoteCategory& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.shortequityandindexquotecategory";
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagetype"] = canonical::text(canonical::character(message.short_equity_and_index_quote_message_type()));
        ShortEquityAndIndexQuoteMessagePayloadHandler selected{ values, entry };
        message.short_equity_and_index_quote_message_payload(selected);
    }

    void on(const protocol::UnderlyingValueCategory& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.underlyingvaluecategory";
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagetype"] = canonical::text(canonical::character(message.underlying_value_message_type()));
        UnderlyingValueMessagePayloadHandler selected{ values, entry };
        message.underlying_value_message_payload(selected);
    }
};

// The values the Flyweight reader reads from one datagram, by indexed address. A datagram it cannot
// read is a value the model never reads, so it fails rather than passing with nothing compared.
canonical::Listing read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::PacketReader::read(std::span<const std::byte>(frame.payload, frame.payload_len), reader);
    } catch (const protocol::DecodeError& error) {
        reader.values["(does not decode)"] = error.what();
    }

    return reader.values;
}

// Read each datagram of a sample with Flyweight and hold it to the model's values
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
    std::printf("== Siac.Opra.Output.Obi.v6.2 (flyweight values)\n");
    int failures = 0;
    failures += check("AdministrativeMessage", "Siac/Opra.Output.Obi.v6.2/AdministrativeMessage.pcap", "siac/opra/output/obi/v6.2/AdministrativeMessage.values");
    failures += check("ControlMessage", "Siac/Opra.Output.Obi.v6.2/ControlMessage.pcap", "siac/opra/output/obi/v6.2/ControlMessage.values");
    failures += check("LongEquityAndIndexQuoteMessage", "Siac/Opra.Output.Obi.v6.2/LongEquityAndIndexQuoteMessage.pcap", "siac/opra/output/obi/v6.2/LongEquityAndIndexQuoteMessage.values");
    failures += check("ShortEquityAndIndexQuoteMessage", "Siac/Opra.Output.Obi.v6.2/ShortEquityAndIndexQuoteMessage.pcap", "siac/opra/output/obi/v6.2/ShortEquityAndIndexQuoteMessage.values");
    return failures == 0 ? 0 : 1;
}
