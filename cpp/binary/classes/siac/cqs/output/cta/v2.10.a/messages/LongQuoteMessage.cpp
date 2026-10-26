#include "LongQuoteMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cqs::output::cta::v2_10_a {

LongQuoteMessage::LongQuoteMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, QuoteCondition quote_condition, SecurityStatusIndicator security_status_indicator, Decimal bid_price_lower_limit_price_band, std::uint32_t bid_size_long, Decimal offer_price_upper_limit_price_band, std::uint32_t offer_size_long, RetailInterestIndicator retail_interest_indicator, SettlementCondition settlement_condition, MarketCondition market_condition, const std::string& finra_market_maker_id, FinraBboIndicator finra_bbo_indicator, const Timestamp2& timestamp_2, ShortSaleRestrictionIndicator short_sale_restriction_indicator, PrimaryListingMarketParticipantId primary_listing_market_participant_id, FinancialStatusIndicator financial_status_indicator, SipGeneratedMessageIdentifier sip_generated_message_identifier, LimitUpLimitDownLuldIndicator limit_up_limit_down_luld_indicator, NationalBboLuldIndicator national_bbo_luld_indicator, NationalBboIndicator national_bbo_indicator, const std::optional<NationalBestBidLongAppendage>& national_best_bid_long_appendage, const std::optional<NationalBestOfferLongAppendage>& national_best_offer_long_appendage, const std::optional<NationalBestBidAndOfferLongAppendage>& national_best_bid_and_offer_long_appendage, const std::optional<NationalBestBidShortAppendage>& national_best_bid_short_appendage, const std::optional<NationalBestOfferShortAppendage>& national_best_offer_short_appendage, const std::optional<NationalBestBidAndOfferShortAppendage>& national_best_bid_and_offer_short_appendage)
  : participant_id_(participant_id), timestamp_1_(timestamp_1), message_id_(message_id), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), security_symbol_(security_symbol), instrument_type_(instrument_type), quote_condition_(quote_condition), security_status_indicator_(security_status_indicator), bid_price_lower_limit_price_band_(bid_price_lower_limit_price_band), bid_size_long_(bid_size_long), offer_price_upper_limit_price_band_(offer_price_upper_limit_price_band), offer_size_long_(offer_size_long), retail_interest_indicator_(retail_interest_indicator), settlement_condition_(settlement_condition), market_condition_(market_condition), finra_market_maker_id_(finra_market_maker_id), finra_bbo_indicator_(finra_bbo_indicator), timestamp_2_(timestamp_2), short_sale_restriction_indicator_(short_sale_restriction_indicator), primary_listing_market_participant_id_(primary_listing_market_participant_id), financial_status_indicator_(financial_status_indicator), sip_generated_message_identifier_(sip_generated_message_identifier), limit_up_limit_down_luld_indicator_(limit_up_limit_down_luld_indicator), national_bbo_luld_indicator_(national_bbo_luld_indicator), national_bbo_indicator_(national_bbo_indicator), national_best_bid_long_appendage_(national_best_bid_long_appendage), national_best_offer_long_appendage_(national_best_offer_long_appendage), national_best_bid_and_offer_long_appendage_(national_best_bid_and_offer_long_appendage), national_best_bid_short_appendage_(national_best_bid_short_appendage), national_best_offer_short_appendage_(national_best_offer_short_appendage), national_best_bid_and_offer_short_appendage_(national_best_bid_and_offer_short_appendage) {}

ParticipantId LongQuoteMessage::participant_id() const { return participant_id_; }
void LongQuoteMessage::set_participant_id(ParticipantId value) { participant_id_ = value; }

const Timestamp1& LongQuoteMessage::timestamp_1() const { return timestamp_1_; }
Timestamp1& LongQuoteMessage::timestamp_1() { return timestamp_1_; }
void LongQuoteMessage::set_timestamp_1(const Timestamp1& value) { timestamp_1_ = value; }

std::uint8_t LongQuoteMessage::message_id() const { return message_id_; }
void LongQuoteMessage::set_message_id(std::uint8_t value) { message_id_ = value; }

std::uint32_t LongQuoteMessage::transaction_id() const { return transaction_id_; }
void LongQuoteMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::int64_t LongQuoteMessage::participant_reference_number() const { return participant_reference_number_; }
void LongQuoteMessage::set_participant_reference_number(std::int64_t value) { participant_reference_number_ = value; }

const std::string& LongQuoteMessage::security_symbol() const { return security_symbol_; }
std::string& LongQuoteMessage::security_symbol() { return security_symbol_; }
void LongQuoteMessage::set_security_symbol(const std::string& value) { security_symbol_ = value; }

InstrumentType LongQuoteMessage::instrument_type() const { return instrument_type_; }
void LongQuoteMessage::set_instrument_type(InstrumentType value) { instrument_type_ = value; }

QuoteCondition LongQuoteMessage::quote_condition() const { return quote_condition_; }
void LongQuoteMessage::set_quote_condition(QuoteCondition value) { quote_condition_ = value; }

SecurityStatusIndicator LongQuoteMessage::security_status_indicator() const { return security_status_indicator_; }
void LongQuoteMessage::set_security_status_indicator(SecurityStatusIndicator value) { security_status_indicator_ = value; }

Decimal LongQuoteMessage::bid_price_lower_limit_price_band() const { return bid_price_lower_limit_price_band_; }
void LongQuoteMessage::set_bid_price_lower_limit_price_band(Decimal value) { bid_price_lower_limit_price_band_ = value; }

std::uint32_t LongQuoteMessage::bid_size_long() const { return bid_size_long_; }
void LongQuoteMessage::set_bid_size_long(std::uint32_t value) { bid_size_long_ = value; }

Decimal LongQuoteMessage::offer_price_upper_limit_price_band() const { return offer_price_upper_limit_price_band_; }
void LongQuoteMessage::set_offer_price_upper_limit_price_band(Decimal value) { offer_price_upper_limit_price_band_ = value; }

std::uint32_t LongQuoteMessage::offer_size_long() const { return offer_size_long_; }
void LongQuoteMessage::set_offer_size_long(std::uint32_t value) { offer_size_long_ = value; }

RetailInterestIndicator LongQuoteMessage::retail_interest_indicator() const { return retail_interest_indicator_; }
void LongQuoteMessage::set_retail_interest_indicator(RetailInterestIndicator value) { retail_interest_indicator_ = value; }

SettlementCondition LongQuoteMessage::settlement_condition() const { return settlement_condition_; }
void LongQuoteMessage::set_settlement_condition(SettlementCondition value) { settlement_condition_ = value; }

MarketCondition LongQuoteMessage::market_condition() const { return market_condition_; }
void LongQuoteMessage::set_market_condition(MarketCondition value) { market_condition_ = value; }

const std::string& LongQuoteMessage::finra_market_maker_id() const { return finra_market_maker_id_; }
std::string& LongQuoteMessage::finra_market_maker_id() { return finra_market_maker_id_; }
void LongQuoteMessage::set_finra_market_maker_id(const std::string& value) { finra_market_maker_id_ = value; }

FinraBboIndicator LongQuoteMessage::finra_bbo_indicator() const { return finra_bbo_indicator_; }
void LongQuoteMessage::set_finra_bbo_indicator(FinraBboIndicator value) { finra_bbo_indicator_ = value; }

const Timestamp2& LongQuoteMessage::timestamp_2() const { return timestamp_2_; }
Timestamp2& LongQuoteMessage::timestamp_2() { return timestamp_2_; }
void LongQuoteMessage::set_timestamp_2(const Timestamp2& value) { timestamp_2_ = value; }

ShortSaleRestrictionIndicator LongQuoteMessage::short_sale_restriction_indicator() const { return short_sale_restriction_indicator_; }
void LongQuoteMessage::set_short_sale_restriction_indicator(ShortSaleRestrictionIndicator value) { short_sale_restriction_indicator_ = value; }

PrimaryListingMarketParticipantId LongQuoteMessage::primary_listing_market_participant_id() const { return primary_listing_market_participant_id_; }
void LongQuoteMessage::set_primary_listing_market_participant_id(PrimaryListingMarketParticipantId value) { primary_listing_market_participant_id_ = value; }

FinancialStatusIndicator LongQuoteMessage::financial_status_indicator() const { return financial_status_indicator_; }
void LongQuoteMessage::set_financial_status_indicator(FinancialStatusIndicator value) { financial_status_indicator_ = value; }

SipGeneratedMessageIdentifier LongQuoteMessage::sip_generated_message_identifier() const { return sip_generated_message_identifier_; }
void LongQuoteMessage::set_sip_generated_message_identifier(SipGeneratedMessageIdentifier value) { sip_generated_message_identifier_ = value; }

LimitUpLimitDownLuldIndicator LongQuoteMessage::limit_up_limit_down_luld_indicator() const { return limit_up_limit_down_luld_indicator_; }
void LongQuoteMessage::set_limit_up_limit_down_luld_indicator(LimitUpLimitDownLuldIndicator value) { limit_up_limit_down_luld_indicator_ = value; }

NationalBboLuldIndicator LongQuoteMessage::national_bbo_luld_indicator() const { return national_bbo_luld_indicator_; }
void LongQuoteMessage::set_national_bbo_luld_indicator(NationalBboLuldIndicator value) { national_bbo_luld_indicator_ = value; }

NationalBboIndicator LongQuoteMessage::national_bbo_indicator() const { return national_bbo_indicator_; }
void LongQuoteMessage::set_national_bbo_indicator(NationalBboIndicator value) { national_bbo_indicator_ = value; }

const std::optional<NationalBestBidLongAppendage>& LongQuoteMessage::national_best_bid_long_appendage() const { return national_best_bid_long_appendage_; }
std::optional<NationalBestBidLongAppendage>& LongQuoteMessage::national_best_bid_long_appendage() { return national_best_bid_long_appendage_; }
void LongQuoteMessage::set_national_best_bid_long_appendage(const std::optional<NationalBestBidLongAppendage>& value) { national_best_bid_long_appendage_ = value; }

const std::optional<NationalBestOfferLongAppendage>& LongQuoteMessage::national_best_offer_long_appendage() const { return national_best_offer_long_appendage_; }
std::optional<NationalBestOfferLongAppendage>& LongQuoteMessage::national_best_offer_long_appendage() { return national_best_offer_long_appendage_; }
void LongQuoteMessage::set_national_best_offer_long_appendage(const std::optional<NationalBestOfferLongAppendage>& value) { national_best_offer_long_appendage_ = value; }

const std::optional<NationalBestBidAndOfferLongAppendage>& LongQuoteMessage::national_best_bid_and_offer_long_appendage() const { return national_best_bid_and_offer_long_appendage_; }
std::optional<NationalBestBidAndOfferLongAppendage>& LongQuoteMessage::national_best_bid_and_offer_long_appendage() { return national_best_bid_and_offer_long_appendage_; }
void LongQuoteMessage::set_national_best_bid_and_offer_long_appendage(const std::optional<NationalBestBidAndOfferLongAppendage>& value) { national_best_bid_and_offer_long_appendage_ = value; }

const std::optional<NationalBestBidShortAppendage>& LongQuoteMessage::national_best_bid_short_appendage() const { return national_best_bid_short_appendage_; }
std::optional<NationalBestBidShortAppendage>& LongQuoteMessage::national_best_bid_short_appendage() { return national_best_bid_short_appendage_; }
void LongQuoteMessage::set_national_best_bid_short_appendage(const std::optional<NationalBestBidShortAppendage>& value) { national_best_bid_short_appendage_ = value; }

const std::optional<NationalBestOfferShortAppendage>& LongQuoteMessage::national_best_offer_short_appendage() const { return national_best_offer_short_appendage_; }
std::optional<NationalBestOfferShortAppendage>& LongQuoteMessage::national_best_offer_short_appendage() { return national_best_offer_short_appendage_; }
void LongQuoteMessage::set_national_best_offer_short_appendage(const std::optional<NationalBestOfferShortAppendage>& value) { national_best_offer_short_appendage_ = value; }

const std::optional<NationalBestBidAndOfferShortAppendage>& LongQuoteMessage::national_best_bid_and_offer_short_appendage() const { return national_best_bid_and_offer_short_appendage_; }
std::optional<NationalBestBidAndOfferShortAppendage>& LongQuoteMessage::national_best_bid_and_offer_short_appendage() { return national_best_bid_and_offer_short_appendage_; }
void LongQuoteMessage::set_national_best_bid_and_offer_short_appendage(const std::optional<NationalBestBidAndOfferShortAppendage>& value) { national_best_bid_and_offer_short_appendage_ = value; }

QuoteMessagePayloadCode LongQuoteMessage::type() const { return message_type; }

std::string_view LongQuoteMessage::name() const { return "Long Quote Message"; }

std::size_t LongQuoteMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("LongQuoteMessage", offset + 1, length);
    participant_id_ = static_cast<ParticipantId>(wire::read_char(data + offset));
    offset += 1;

    offset += timestamp_1_.decode(data + offset, length - offset);

    wire::require("LongQuoteMessage", offset + 1, length);
    message_id_ = wire::read_u8(data + offset);
    offset += 1;

    wire::require("LongQuoteMessage", offset + 4, length);
    transaction_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("LongQuoteMessage", offset + 8, length);
    participant_reference_number_ = wire::read_i64_be(data + offset);
    offset += 8;

    wire::require("LongQuoteMessage", offset + 11, length);
    security_symbol_ = wire::read_text(data + offset, 11, ' ');
    offset += 11;

    wire::require("LongQuoteMessage", offset + 1, length);
    instrument_type_ = static_cast<InstrumentType>(wire::read_char(data + offset));
    offset += 1;

    wire::require("LongQuoteMessage", offset + 1, length);
    quote_condition_ = static_cast<QuoteCondition>(wire::read_char(data + offset));
    offset += 1;

    wire::require("LongQuoteMessage", offset + 1, length);
    security_status_indicator_ = static_cast<SecurityStatusIndicator>(wire::read_char(data + offset));
    offset += 1;

    wire::require("LongQuoteMessage", offset + 8, length);
    bid_price_lower_limit_price_band_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    wire::require("LongQuoteMessage", offset + 4, length);
    bid_size_long_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("LongQuoteMessage", offset + 8, length);
    offer_price_upper_limit_price_band_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    wire::require("LongQuoteMessage", offset + 4, length);
    offer_size_long_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("LongQuoteMessage", offset + 1, length);
    retail_interest_indicator_ = static_cast<RetailInterestIndicator>(wire::read_char(data + offset));
    offset += 1;

    wire::require("LongQuoteMessage", offset + 1, length);
    settlement_condition_ = static_cast<SettlementCondition>(wire::read_char(data + offset));
    offset += 1;

    wire::require("LongQuoteMessage", offset + 1, length);
    market_condition_ = static_cast<MarketCondition>(wire::read_char(data + offset));
    offset += 1;

    wire::require("LongQuoteMessage", offset + 4, length);
    finra_market_maker_id_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    wire::require("LongQuoteMessage", offset + 1, length);
    finra_bbo_indicator_ = static_cast<FinraBboIndicator>(wire::read_char(data + offset));
    offset += 1;

    offset += timestamp_2_.decode(data + offset, length - offset);

    wire::require("LongQuoteMessage", offset + 1, length);
    short_sale_restriction_indicator_ = static_cast<ShortSaleRestrictionIndicator>(wire::read_char(data + offset));
    offset += 1;

    wire::require("LongQuoteMessage", offset + 1, length);
    primary_listing_market_participant_id_ = static_cast<PrimaryListingMarketParticipantId>(wire::read_char(data + offset));
    offset += 1;

    wire::require("LongQuoteMessage", offset + 1, length);
    financial_status_indicator_ = static_cast<FinancialStatusIndicator>(wire::read_char(data + offset));
    offset += 1;

    wire::require("LongQuoteMessage", offset + 1, length);
    sip_generated_message_identifier_ = static_cast<SipGeneratedMessageIdentifier>(wire::read_char(data + offset));
    offset += 1;

    wire::require("LongQuoteMessage", offset + 1, length);
    limit_up_limit_down_luld_indicator_ = static_cast<LimitUpLimitDownLuldIndicator>(wire::read_char(data + offset));
    offset += 1;

    wire::require("LongQuoteMessage", offset + 1, length);
    national_bbo_luld_indicator_ = static_cast<NationalBboLuldIndicator>(wire::read_char(data + offset));
    offset += 1;

    wire::require("LongQuoteMessage", offset + 1, length);
    national_bbo_indicator_ = static_cast<NationalBboIndicator>(wire::read_char(data + offset));
    offset += 1;

    if (static_cast<char>(national_bbo_indicator_) == 'Q') {
        NationalBestBidLongAppendage value;
        offset += value.decode(data + offset, length - offset);
        national_best_bid_long_appendage_ = std::move(value);
    } else {
        national_best_bid_long_appendage_.reset();
    }

    if (static_cast<char>(national_bbo_indicator_) == 'I') {
        NationalBestOfferLongAppendage value;
        offset += value.decode(data + offset, length - offset);
        national_best_offer_long_appendage_ = std::move(value);
    } else {
        national_best_offer_long_appendage_.reset();
    }

    if (static_cast<char>(national_bbo_indicator_) == 'U') {
        NationalBestBidAndOfferLongAppendage value;
        offset += value.decode(data + offset, length - offset);
        national_best_bid_and_offer_long_appendage_ = std::move(value);
    } else {
        national_best_bid_and_offer_long_appendage_.reset();
    }

    if (static_cast<char>(national_bbo_indicator_) == 'P') {
        NationalBestBidShortAppendage value;
        offset += value.decode(data + offset, length - offset);
        national_best_bid_short_appendage_ = std::move(value);
    } else {
        national_best_bid_short_appendage_.reset();
    }

    if (static_cast<char>(national_bbo_indicator_) == 'H') {
        NationalBestOfferShortAppendage value;
        offset += value.decode(data + offset, length - offset);
        national_best_offer_short_appendage_ = std::move(value);
    } else {
        national_best_offer_short_appendage_.reset();
    }

    if (static_cast<char>(national_bbo_indicator_) == 'T') {
        NationalBestBidAndOfferShortAppendage value;
        offset += value.decode(data + offset, length - offset);
        national_best_bid_and_offer_short_appendage_ = std::move(value);
    } else {
        national_best_bid_and_offer_short_appendage_.reset();
    }

    return offset;
}

std::size_t LongQuoteMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LongQuoteMessage", encoded_size(), capacity);

    wire::write_char(data + offset, static_cast<char>(participant_id_));
    offset += 1;

    offset += timestamp_1_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(message_id_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(transaction_id_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(participant_reference_number_));
    offset += 8;

    wire::write_text(data + offset, 11, ' ', security_symbol_);
    offset += 11;

    wire::write_char(data + offset, static_cast<char>(instrument_type_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(quote_condition_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(security_status_indicator_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(bid_price_lower_limit_price_band_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(bid_size_long_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(offer_price_upper_limit_price_band_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(offer_size_long_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(retail_interest_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(settlement_condition_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(market_condition_));
    offset += 1;

    wire::write_text(data + offset, 4, ' ', finra_market_maker_id_);
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(finra_bbo_indicator_));
    offset += 1;

    offset += timestamp_2_.encode(data + offset, capacity - offset);

    wire::write_char(data + offset, static_cast<char>(short_sale_restriction_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(primary_listing_market_participant_id_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(financial_status_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(sip_generated_message_identifier_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(limit_up_limit_down_luld_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(national_bbo_luld_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(national_bbo_indicator_));
    offset += 1;

    if (national_best_bid_long_appendage_) {
        offset += national_best_bid_long_appendage_->encode(data + offset, capacity - offset);
    }

    if (national_best_offer_long_appendage_) {
        offset += national_best_offer_long_appendage_->encode(data + offset, capacity - offset);
    }

    if (national_best_bid_and_offer_long_appendage_) {
        offset += national_best_bid_and_offer_long_appendage_->encode(data + offset, capacity - offset);
    }

    if (national_best_bid_short_appendage_) {
        offset += national_best_bid_short_appendage_->encode(data + offset, capacity - offset);
    }

    if (national_best_offer_short_appendage_) {
        offset += national_best_offer_short_appendage_->encode(data + offset, capacity - offset);
    }

    if (national_best_bid_and_offer_short_appendage_) {
        offset += national_best_bid_and_offer_short_appendage_->encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t LongQuoteMessage::encoded_size() const {
    return 1 + timestamp_1_.encoded_size() + 1 + 4 + 8 + 11 + 1 + 1 + 1 + 8 + 4 + 8 + 4 + 1 + 1 + 1 + 4 + 1 + timestamp_2_.encoded_size() + 1 + 1 + 1 + 1 + 1 + 1 + 1 + (national_best_bid_long_appendage_ ? national_best_bid_long_appendage_->encoded_size() : 0) + (national_best_offer_long_appendage_ ? national_best_offer_long_appendage_->encoded_size() : 0) + (national_best_bid_and_offer_long_appendage_ ? national_best_bid_and_offer_long_appendage_->encoded_size() : 0) + (national_best_bid_short_appendage_ ? national_best_bid_short_appendage_->encoded_size() : 0) + (national_best_offer_short_appendage_ ? national_best_offer_short_appendage_->encoded_size() : 0) + (national_best_bid_and_offer_short_appendage_ ? national_best_bid_and_offer_short_appendage_->encoded_size() : 0);
}

void LongQuoteMessage::accept(QuoteMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<QuoteMessagePayload> LongQuoteMessage::clone() const {
    return std::make_unique<LongQuoteMessage>(*this);
}

void LongQuoteMessage::print(std::ostream& out) const {
    out << "LongQuoteMessage{";
    out << "participant_id=";
    out << participant_id_;
    out << ", timestamp_1=";
    timestamp_1_.print(out);
    out << ", message_id=";
    out << static_cast<int>(message_id_);
    out << ", transaction_id=";
    out << transaction_id_;
    out << ", participant_reference_number=";
    out << participant_reference_number_;
    out << ", security_symbol=";
    print::text(out, security_symbol_);
    out << ", instrument_type=";
    out << instrument_type_;
    out << ", quote_condition=";
    out << quote_condition_;
    out << ", security_status_indicator=";
    out << security_status_indicator_;
    out << ", bid_price_lower_limit_price_band=";
    out << bid_price_lower_limit_price_band_;
    out << ", bid_size_long=";
    out << bid_size_long_;
    out << ", offer_price_upper_limit_price_band=";
    out << offer_price_upper_limit_price_band_;
    out << ", offer_size_long=";
    out << offer_size_long_;
    out << ", retail_interest_indicator=";
    out << retail_interest_indicator_;
    out << ", settlement_condition=";
    out << settlement_condition_;
    out << ", market_condition=";
    out << market_condition_;
    out << ", finra_market_maker_id=";
    print::text(out, finra_market_maker_id_);
    out << ", finra_bbo_indicator=";
    out << finra_bbo_indicator_;
    out << ", timestamp_2=";
    timestamp_2_.print(out);
    out << ", short_sale_restriction_indicator=";
    out << short_sale_restriction_indicator_;
    out << ", primary_listing_market_participant_id=";
    out << primary_listing_market_participant_id_;
    out << ", financial_status_indicator=";
    out << financial_status_indicator_;
    out << ", sip_generated_message_identifier=";
    out << sip_generated_message_identifier_;
    out << ", limit_up_limit_down_luld_indicator=";
    out << limit_up_limit_down_luld_indicator_;
    out << ", national_bbo_luld_indicator=";
    out << national_bbo_luld_indicator_;
    out << ", national_bbo_indicator=";
    out << national_bbo_indicator_;
    out << ", national_best_bid_long_appendage=";
    print::optional(out, national_best_bid_long_appendage_);
    out << ", national_best_offer_long_appendage=";
    print::optional(out, national_best_offer_long_appendage_);
    out << ", national_best_bid_and_offer_long_appendage=";
    print::optional(out, national_best_bid_and_offer_long_appendage_);
    out << ", national_best_bid_short_appendage=";
    print::optional(out, national_best_bid_short_appendage_);
    out << ", national_best_offer_short_appendage=";
    print::optional(out, national_best_offer_short_appendage_);
    out << ", national_best_bid_and_offer_short_appendage=";
    print::optional(out, national_best_bid_and_offer_short_appendage_);
    out << '}';
}

bool LongQuoteMessage::equals(const QuoteMessagePayload& other) const {
    const auto* that = dynamic_cast<const LongQuoteMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool LongQuoteMessage::operator==(const LongQuoteMessage& other) const {
    return participant_id_ == other.participant_id_
        && timestamp_1_ == other.timestamp_1_
        && message_id_ == other.message_id_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && security_symbol_ == other.security_symbol_
        && instrument_type_ == other.instrument_type_
        && quote_condition_ == other.quote_condition_
        && security_status_indicator_ == other.security_status_indicator_
        && bid_price_lower_limit_price_band_ == other.bid_price_lower_limit_price_band_
        && bid_size_long_ == other.bid_size_long_
        && offer_price_upper_limit_price_band_ == other.offer_price_upper_limit_price_band_
        && offer_size_long_ == other.offer_size_long_
        && retail_interest_indicator_ == other.retail_interest_indicator_
        && settlement_condition_ == other.settlement_condition_
        && market_condition_ == other.market_condition_
        && finra_market_maker_id_ == other.finra_market_maker_id_
        && finra_bbo_indicator_ == other.finra_bbo_indicator_
        && timestamp_2_ == other.timestamp_2_
        && short_sale_restriction_indicator_ == other.short_sale_restriction_indicator_
        && primary_listing_market_participant_id_ == other.primary_listing_market_participant_id_
        && financial_status_indicator_ == other.financial_status_indicator_
        && sip_generated_message_identifier_ == other.sip_generated_message_identifier_
        && limit_up_limit_down_luld_indicator_ == other.limit_up_limit_down_luld_indicator_
        && national_bbo_luld_indicator_ == other.national_bbo_luld_indicator_
        && national_bbo_indicator_ == other.national_bbo_indicator_
        && national_best_bid_long_appendage_ == other.national_best_bid_long_appendage_
        && national_best_offer_long_appendage_ == other.national_best_offer_long_appendage_
        && national_best_bid_and_offer_long_appendage_ == other.national_best_bid_and_offer_long_appendage_
        && national_best_bid_short_appendage_ == other.national_best_bid_short_appendage_
        && national_best_offer_short_appendage_ == other.national_best_offer_short_appendage_
        && national_best_bid_and_offer_short_appendage_ == other.national_best_bid_and_offer_short_appendage_;
}

bool LongQuoteMessage::operator!=(const LongQuoteMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cqs::output::cta::v2_10_a
