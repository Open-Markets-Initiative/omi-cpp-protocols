// Siac.Cqs.Output.Cta.v2.10.a canonical values, through the Flyweight reader: every value Flyweight reads
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
#include "cpp/binary/flyweight/siac/cqs/output/cta/v2.10.a/definitions.hpp"

namespace protocol = ::siac::cqs::output::cta::v2_10_a;

namespace {

// The messages Administrative Message Payload selects, their values set in the entry of the message holding it
struct AdministrativeMessagePayloadHandler {
    canonical::Listing& values;
    const std::string& entry;

    void on(const protocol::SymbolReferenceDataMessage& message) {
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload"] = "packet.message.categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage";
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.participantid"] = canonical::text(canonical::character(message.participant_id()));
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.timestamp1.seconds"] = canonical::number(message.timestamp_1().seconds());
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.timestamp1.nanoseconds"] = canonical::number(message.timestamp_1().nanoseconds());
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.messageid"] = canonical::number(message.message_id());
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.transactionid"] = canonical::number(message.transaction_id());
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.participantreferencenumber"] = canonical::number(message.participant_reference_number());
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.securitysymbol"] = canonical::text(std::string(message.security_symbol()), ' ', false);
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.priorsecuritysymbol"] = canonical::text(std::string(message.prior_security_symbol()), ' ', false);
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character(message.primary_listing_market_participant_id()));
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.primarylistingmarketpreviousclosingprice"] = canonical::scaled(message.primary_listing_market_previous_closing_price().mantissa(), message.primary_listing_market_previous_closing_price().exponent());
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.consolidatedclosingprice"] = canonical::scaled(message.consolidated_closing_price().mantissa(), message.consolidated_closing_price().exponent());
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.roundlotsize"] = canonical::number(message.round_lot_size());
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.reserved"] = canonical::text(canonical::character(message.reserved()));
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.luldtier"] = canonical::text(canonical::character(message.luld_tier()));
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.luldleverageratio"] = canonical::scaled(message.luld_leverage_ratio().mantissa(), message.luld_leverage_ratio().exponent());
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.test"] = canonical::text(canonical::character(message.test()));
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.ipo"] = canonical::text(canonical::character(message.ipo()));
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.financialstatusindicator"] = canonical::text(canonical::character(message.financial_status_indicator()));
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.shortsalerestrictionindicator"] = canonical::text(canonical::character(message.short_sale_restriction_indicator()));
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.haltreason"] = canonical::text(canonical::character(message.halt_reason()));
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.instrumenttype"] = canonical::text(canonical::character(message.instrument_type()));
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.secondreserved"] = canonical::text(canonical::character(message.second_reserved()));
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.thirdreserved"] = canonical::text(canonical::character(message.third_reserved()));
        values[entry + ".categorypayload.administrativemessage.administrativemessagepayload.symbolreferencedatamessage.reserved128"] = canonical::text(std::string(message.reserved_128()), ' ', false);
    }
};

// The messages Control Message Payload selects, their values set in the entry of the message holding it
struct ControlMessagePayloadHandler {
    canonical::Listing& values;
    const std::string& entry;

    void on(const protocol::StartOfDayMessage& message) {
        values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.startofdaymessage";
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.participantid"] = canonical::text(canonical::character(message.participant_id()));
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.timestamp1.seconds"] = canonical::number(message.timestamp_1().seconds());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.timestamp1.nanoseconds"] = canonical::number(message.timestamp_1().nanoseconds());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.messageid"] = canonical::number(message.message_id());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.transactionid"] = canonical::number(message.transaction_id());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.startofdaymessage.participantreferencenumber"] = canonical::number(message.participant_reference_number());
    }

    void on(const protocol::FinraCloseMessage& message) {
        values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.finraclosemessage";
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraclosemessage.participantid"] = canonical::text(canonical::character(message.participant_id()));
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraclosemessage.timestamp1.seconds"] = canonical::number(message.timestamp_1().seconds());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraclosemessage.timestamp1.nanoseconds"] = canonical::number(message.timestamp_1().nanoseconds());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraclosemessage.messageid"] = canonical::number(message.message_id());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraclosemessage.transactionid"] = canonical::number(message.transaction_id());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraclosemessage.participantreferencenumber"] = canonical::number(message.participant_reference_number());
    }

    void on(const protocol::ResetBlockSequenceNumberMessage& message) {
        values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage";
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.participantid"] = canonical::text(canonical::character(message.participant_id()));
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.timestamp1.seconds"] = canonical::number(message.timestamp_1().seconds());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.timestamp1.nanoseconds"] = canonical::number(message.timestamp_1().nanoseconds());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.messageid"] = canonical::number(message.message_id());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.transactionid"] = canonical::number(message.transaction_id());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.resetblocksequencenumbermessage.participantreferencenumber"] = canonical::number(message.participant_reference_number());
    }

    void on(const protocol::FinraOpenMessage& message) {
        values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.finraopenmessage";
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraopenmessage.participantid"] = canonical::text(canonical::character(message.participant_id()));
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraopenmessage.timestamp1.seconds"] = canonical::number(message.timestamp_1().seconds());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraopenmessage.timestamp1.nanoseconds"] = canonical::number(message.timestamp_1().nanoseconds());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraopenmessage.messageid"] = canonical::number(message.message_id());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraopenmessage.transactionid"] = canonical::number(message.transaction_id());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.finraopenmessage.participantreferencenumber"] = canonical::number(message.participant_reference_number());
    }

    void on(const protocol::DisasterRecoveryDataCenterActivationMessage& message) {
        values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage";
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.participantid"] = canonical::text(canonical::character(message.participant_id()));
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.timestamp1.seconds"] = canonical::number(message.timestamp_1().seconds());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.timestamp1.nanoseconds"] = canonical::number(message.timestamp_1().nanoseconds());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.messageid"] = canonical::number(message.message_id());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.transactionid"] = canonical::number(message.transaction_id());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.disasterrecoverydatacenteractivationmessage.participantreferencenumber"] = canonical::number(message.participant_reference_number());
    }

    void on(const protocol::LineIntegrityMessage& message) {
        values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.lineintegritymessage";
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.participantid"] = canonical::text(canonical::character(message.participant_id()));
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.timestamp1.seconds"] = canonical::number(message.timestamp_1().seconds());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.timestamp1.nanoseconds"] = canonical::number(message.timestamp_1().nanoseconds());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.messageid"] = canonical::number(message.message_id());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.transactionid"] = canonical::number(message.transaction_id());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.lineintegritymessage.participantreferencenumber"] = canonical::number(message.participant_reference_number());
    }

    void on(const protocol::EndOfDayMessage& message) {
        values[entry + ".categorypayload.controlmessage.controlmessagepayload"] = "packet.message.categorypayload.controlmessage.controlmessagepayload.endofdaymessage";
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.participantid"] = canonical::text(canonical::character(message.participant_id()));
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.timestamp1.seconds"] = canonical::number(message.timestamp_1().seconds());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.timestamp1.nanoseconds"] = canonical::number(message.timestamp_1().nanoseconds());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.messageid"] = canonical::number(message.message_id());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.transactionid"] = canonical::number(message.transaction_id());
        values[entry + ".categorypayload.controlmessage.controlmessagepayload.endofdaymessage.participantreferencenumber"] = canonical::number(message.participant_reference_number());
    }
};

// The messages Market Status Message Payload selects, their values set in the entry of the message holding it
struct MarketStatusMessagePayloadHandler {
    canonical::Listing& values;
    const std::string& entry;

    void on(const protocol::MarketWideCircuitBreakerDeclineLevelStatusMessage& message) {
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload"] = "packet.message.categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage";
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.participantid"] = canonical::text(canonical::character(message.participant_id()));
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.timestamp1.seconds"] = canonical::number(message.timestamp_1().seconds());
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.timestamp1.nanoseconds"] = canonical::number(message.timestamp_1().nanoseconds());
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.messageid"] = canonical::number(message.message_id());
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.transactionid"] = canonical::number(message.transaction_id());
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.participantreferencenumber"] = canonical::number(message.participant_reference_number());
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.mwcblevel1"] = canonical::scaled(message.mwcb_level_1().mantissa(), message.mwcb_level_1().exponent());
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.mwcblevel2"] = canonical::scaled(message.mwcb_level_2().mantissa(), message.mwcb_level_2().exponent());
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.mwcblevel3"] = canonical::scaled(message.mwcb_level_3().mantissa(), message.mwcb_level_3().exponent());
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerdeclinelevelstatusmessage.reserved"] = canonical::text(canonical::character(message.reserved()));
    }

    void on(const protocol::MarketWideCircuitBreakerStatusMessage& message) {
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload"] = "packet.message.categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage";
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.participantid"] = canonical::text(canonical::character(message.participant_id()));
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.timestamp1.seconds"] = canonical::number(message.timestamp_1().seconds());
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.timestamp1.nanoseconds"] = canonical::number(message.timestamp_1().nanoseconds());
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.messageid"] = canonical::number(message.message_id());
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.transactionid"] = canonical::number(message.transaction_id());
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.participantreferencenumber"] = canonical::number(message.participant_reference_number());
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.marketwidecircuitbreakerlevelindicator"] = canonical::text(canonical::character(message.market_wide_circuit_breaker_level_indicator()));
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagepayload.marketwidecircuitbreakerstatusmessage.reserved"] = canonical::text(canonical::character(message.reserved()));
    }
};

// The messages Quote Message Payload selects, their values set in the entry of the message holding it
struct QuoteMessagePayloadHandler {
    canonical::Listing& values;
    const std::string& entry;

    void on(const protocol::AuctionStatusMessage& message) {
        values[entry + ".categorypayload.quotemessage.quotemessagepayload"] = "packet.message.categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage";
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.participantid"] = canonical::text(canonical::character(message.participant_id()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.timestamp1.seconds"] = canonical::number(message.timestamp_1().seconds());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.timestamp1.nanoseconds"] = canonical::number(message.timestamp_1().nanoseconds());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.messageid"] = canonical::number(message.message_id());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.transactionid"] = canonical::number(message.transaction_id());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.participantreferencenumber"] = canonical::number(message.participant_reference_number());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.securitysymbol"] = canonical::text(std::string(message.security_symbol()), ' ', false);
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.instrumenttype"] = canonical::text(canonical::character(message.instrument_type()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.auctioncollarreferenceprice"] = canonical::scaled(message.auction_collar_reference_price().mantissa(), message.auction_collar_reference_price().exponent());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.auctioncollarupperthresholdprice"] = canonical::scaled(message.auction_collar_upper_threshold_price().mantissa(), message.auction_collar_upper_threshold_price().exponent());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.auctioncollarlowerthresholdprice"] = canonical::scaled(message.auction_collar_lower_threshold_price().mantissa(), message.auction_collar_lower_threshold_price().exponent());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.numberofextensions"] = canonical::number(message.number_of_extensions());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.shortsalerestrictionindicator"] = canonical::text(canonical::character(message.short_sale_restriction_indicator()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character(message.primary_listing_market_participant_id()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.financialstatusindicator"] = canonical::text(canonical::character(message.financial_status_indicator()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.auctionstatusmessage.reserved62"] = canonical::text(std::string(message.reserved_62()), ' ', false);
    }

    void on(const protocol::LongQuoteMessage& message) {
        values[entry + ".categorypayload.quotemessage.quotemessagepayload"] = "packet.message.categorypayload.quotemessage.quotemessagepayload.longquotemessage";
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.participantid"] = canonical::text(canonical::character(message.participant_id()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.timestamp1.seconds"] = canonical::number(message.timestamp_1().seconds());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.timestamp1.nanoseconds"] = canonical::number(message.timestamp_1().nanoseconds());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.messageid"] = canonical::number(message.message_id());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.transactionid"] = canonical::number(message.transaction_id());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.participantreferencenumber"] = canonical::number(message.participant_reference_number());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.securitysymbol"] = canonical::text(std::string(message.security_symbol()), ' ', false);
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.instrumenttype"] = canonical::text(canonical::character(message.instrument_type()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.quotecondition"] = canonical::text(canonical::character(message.quote_condition()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.securitystatusindicator"] = canonical::text(canonical::character(message.security_status_indicator()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.bidpricelowerlimitpriceband"] = canonical::scaled(message.bid_price_lower_limit_price_band().mantissa(), message.bid_price_lower_limit_price_band().exponent());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.bidsizelong"] = canonical::number(message.bid_size_long());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.offerpriceupperlimitpriceband"] = canonical::scaled(message.offer_price_upper_limit_price_band().mantissa(), message.offer_price_upper_limit_price_band().exponent());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.offersizelong"] = canonical::number(message.offer_size_long());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.retailinterestindicator"] = canonical::text(canonical::character(message.retail_interest_indicator()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.settlementcondition"] = canonical::text(canonical::character(message.settlement_condition()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.marketcondition"] = canonical::text(canonical::character(message.market_condition()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.finramarketmakerid"] = canonical::text(std::string(message.finra_market_maker_id()), ' ', false);
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.finrabboindicator"] = canonical::text(canonical::character(message.finra_bbo_indicator()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.timestamp2.seconds"] = canonical::number(message.timestamp_2().seconds());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.timestamp2.nanoseconds"] = canonical::number(message.timestamp_2().nanoseconds());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.shortsalerestrictionindicator"] = canonical::text(canonical::character(message.short_sale_restriction_indicator()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character(message.primary_listing_market_participant_id()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.financialstatusindicator"] = canonical::text(canonical::character(message.financial_status_indicator()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.sipgeneratedmessageidentifier"] = canonical::text(canonical::character(message.sip_generated_message_identifier()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.limituplimitdownluldindicator"] = canonical::text(canonical::character(message.limit_up_limit_down_luld_indicator()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.nationalbboluldindicator"] = canonical::text(canonical::character(message.national_bbo_luld_indicator()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.longquotemessage.nationalbboindicator"] = canonical::text(canonical::character(message.national_bbo_indicator()));
    }

    void on(const protocol::ShortQuoteMessage& message) {
        values[entry + ".categorypayload.quotemessage.quotemessagepayload"] = "packet.message.categorypayload.quotemessage.quotemessagepayload.shortquotemessage";
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.participantid"] = canonical::text(canonical::character(message.participant_id()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.timestamp1.seconds"] = canonical::number(message.timestamp_1().seconds());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.timestamp1.nanoseconds"] = canonical::number(message.timestamp_1().nanoseconds());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.messageid"] = canonical::number(message.message_id());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.transactionid"] = canonical::number(message.transaction_id());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.participantreferencenumber"] = canonical::number(message.participant_reference_number());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.securitysymbol"] = canonical::text(std::string(message.security_symbol()), ' ', false);
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.bidpriceshort"] = canonical::scaled(message.bid_price_short().mantissa(), message.bid_price_short().exponent());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.bidsizeshort"] = canonical::number(message.bid_size_short());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.offerpriceshort"] = canonical::scaled(message.offer_price_short().mantissa(), message.offer_price_short().exponent());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.offersizeshort"] = canonical::number(message.offer_size_short());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character(message.primary_listing_market_participant_id()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.shortquotemessage.nationalbboindicator"] = canonical::text(canonical::character(message.national_bbo_indicator()));
    }

    void on(const protocol::SpecialLongQuoteMessage& message) {
        values[entry + ".categorypayload.quotemessage.quotemessagepayload"] = "packet.message.categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage";
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.participantid"] = canonical::text(canonical::character(message.participant_id()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.timestamp1.seconds"] = canonical::number(message.timestamp_1().seconds());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.timestamp1.nanoseconds"] = canonical::number(message.timestamp_1().nanoseconds());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.messageid"] = canonical::number(message.message_id());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.transactionid"] = canonical::number(message.transaction_id());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.participantreferencenumber"] = canonical::number(message.participant_reference_number());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.securitysymbol"] = canonical::text(std::string(message.security_symbol()), ' ', false);
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.instrumenttype"] = canonical::text(canonical::character(message.instrument_type()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.quotecondition"] = canonical::text(canonical::character(message.quote_condition()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.securitystatusindicator"] = canonical::text(canonical::character(message.security_status_indicator()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.bidpricelong"] = canonical::scaled(message.bid_price_long().mantissa(), message.bid_price_long().exponent());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.bidsizelong"] = canonical::number(message.bid_size_long());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.offerpricelong"] = canonical::scaled(message.offer_price_long().mantissa(), message.offer_price_long().exponent());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.offersizelong"] = canonical::number(message.offer_size_long());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.retailinterestindicator"] = canonical::text(canonical::character(message.retail_interest_indicator()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.settlementcondition"] = canonical::text(canonical::character(message.settlement_condition()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.marketcondition"] = canonical::text(canonical::character(message.market_condition()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finramarketmakerid"] = canonical::text(std::string(message.finra_market_maker_id()), ' ', false);
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finrabestbidquotecondition"] = canonical::text(canonical::character(message.finra_best_bid_quote_condition()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finrabestbidprice"] = canonical::scaled(message.finra_best_bid_price().mantissa(), message.finra_best_bid_price().exponent());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finrabestbidsize"] = canonical::number(message.finra_best_bid_size());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finrabestbidmarketmakerid"] = canonical::text(std::string(message.finra_best_bid_market_maker_id()), ' ', false);
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finrabestofferquotecondition"] = canonical::text(canonical::character(message.finra_best_offer_quote_condition()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finrabestofferprice"] = canonical::scaled(message.finra_best_offer_price().mantissa(), message.finra_best_offer_price().exponent());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finrabestoffersize"] = canonical::number(message.finra_best_offer_size());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finrabestoffermarketmakerid"] = canonical::text(std::string(message.finra_best_offer_market_maker_id()), ' ', false);
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.timestamp2.seconds"] = canonical::number(message.timestamp_2().seconds());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.timestamp2.nanoseconds"] = canonical::number(message.timestamp_2().nanoseconds());
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.shortsalerestrictionindicator"] = canonical::text(canonical::character(message.short_sale_restriction_indicator()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.primarylistingmarketparticipantid"] = canonical::text(canonical::character(message.primary_listing_market_participant_id()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.financialstatusindicator"] = canonical::text(canonical::character(message.financial_status_indicator()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.sipgeneratedmessageidentifier"] = canonical::text(canonical::character(message.sip_generated_message_identifier()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.finrabboluldindicator"] = canonical::text(canonical::character(message.finra_bbo_luld_indicator()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.nationalbboluldindicator"] = canonical::text(canonical::character(message.national_bbo_luld_indicator()));
        values[entry + ".categorypayload.quotemessage.quotemessagepayload.speciallongquotemessage.nationalbboindicator"] = canonical::text(canonical::character(message.national_bbo_indicator()));
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
        values["packet.blockheader.blocksequencenumber"] = canonical::number(packet.block_header().block_sequence_number());
        values["packet.blockheader.messagesinblock"] = canonical::number(packet.block_header().messages_in_block());
        values["packet.blockheader.sipblocktimestamp.seconds"] = canonical::number(packet.block_header().sip_block_timestamp().seconds());
        values["packet.blockheader.sipblocktimestamp.nanoseconds"] = canonical::number(packet.block_header().sip_block_timestamp().nanoseconds());
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

    void on(const protocol::AdministrativeMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".categorypayload"] = "packet.message.categorypayload.administrativemessage";
        values[entry + ".categorypayload.administrativemessage.administrativemessagetype"] = canonical::text(canonical::character(message.administrative_message_type()));
        AdministrativeMessagePayloadHandler selected{ values, entry };
        message.administrative_message_payload(selected);
    }

    void on(const protocol::ControlMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".categorypayload"] = "packet.message.categorypayload.controlmessage";
        values[entry + ".categorypayload.controlmessage.controlmessagetype"] = canonical::text(canonical::character(message.control_message_type()));
        ControlMessagePayloadHandler selected{ values, entry };
        message.control_message_payload(selected);
    }

    void on(const protocol::MarketStatusMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".categorypayload"] = "packet.message.categorypayload.marketstatusmessage";
        values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagetype"] = canonical::text(canonical::character(message.market_status_message_type()));
        MarketStatusMessagePayloadHandler selected{ values, entry };
        message.market_status_message_payload(selected);
    }

    void on(const protocol::QuoteMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".categorypayload"] = "packet.message.categorypayload.quotemessage";
        values[entry + ".categorypayload.quotemessage.quotemessagetype"] = canonical::text(canonical::character(message.quote_message_type()));
        QuoteMessagePayloadHandler selected{ values, entry };
        message.quote_message_payload(selected);
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
    std::printf("== Siac.Cqs.Output.Cta.v2.10.a (flyweight values)\n");
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
