#include "ShortQuoteMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cqs::output::cta::v2_10_a {

ShortQuoteMessage::ShortQuoteMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, Decimal bid_price_short, std::uint16_t bid_size_short, Decimal offer_price_short, std::uint16_t offer_size_short, PrimaryListingMarketParticipantId primary_listing_market_participant_id, NationalBboIndicator national_bbo_indicator, const std::optional<NationalBestBidLongAppendage>& national_best_bid_long_appendage, const std::optional<NationalBestOfferLongAppendage>& national_best_offer_long_appendage, const std::optional<NationalBestBidAndOfferLongAppendage>& national_best_bid_and_offer_long_appendage, const std::optional<NationalBestBidShortAppendage>& national_best_bid_short_appendage, const std::optional<NationalBestOfferShortAppendage>& national_best_offer_short_appendage, const std::optional<NationalBestBidAndOfferShortAppendage>& national_best_bid_and_offer_short_appendage)
  : participant_id_(participant_id), timestamp_1_(timestamp_1), message_id_(message_id), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), security_symbol_(security_symbol), bid_price_short_(bid_price_short), bid_size_short_(bid_size_short), offer_price_short_(offer_price_short), offer_size_short_(offer_size_short), primary_listing_market_participant_id_(primary_listing_market_participant_id), national_bbo_indicator_(national_bbo_indicator), national_best_bid_long_appendage_(national_best_bid_long_appendage), national_best_offer_long_appendage_(national_best_offer_long_appendage), national_best_bid_and_offer_long_appendage_(national_best_bid_and_offer_long_appendage), national_best_bid_short_appendage_(national_best_bid_short_appendage), national_best_offer_short_appendage_(national_best_offer_short_appendage), national_best_bid_and_offer_short_appendage_(national_best_bid_and_offer_short_appendage) {}

ParticipantId ShortQuoteMessage::participant_id() const { return participant_id_; }
void ShortQuoteMessage::set_participant_id(ParticipantId value) { participant_id_ = value; }

const Timestamp1& ShortQuoteMessage::timestamp_1() const { return timestamp_1_; }
Timestamp1& ShortQuoteMessage::timestamp_1() { return timestamp_1_; }
void ShortQuoteMessage::set_timestamp_1(const Timestamp1& value) { timestamp_1_ = value; }

std::uint8_t ShortQuoteMessage::message_id() const { return message_id_; }
void ShortQuoteMessage::set_message_id(std::uint8_t value) { message_id_ = value; }

std::uint32_t ShortQuoteMessage::transaction_id() const { return transaction_id_; }
void ShortQuoteMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::int64_t ShortQuoteMessage::participant_reference_number() const { return participant_reference_number_; }
void ShortQuoteMessage::set_participant_reference_number(std::int64_t value) { participant_reference_number_ = value; }

const std::string& ShortQuoteMessage::security_symbol() const { return security_symbol_; }
std::string& ShortQuoteMessage::security_symbol() { return security_symbol_; }
void ShortQuoteMessage::set_security_symbol(const std::string& value) { security_symbol_ = value; }

Decimal ShortQuoteMessage::bid_price_short() const { return bid_price_short_; }
void ShortQuoteMessage::set_bid_price_short(Decimal value) { bid_price_short_ = value; }

std::uint16_t ShortQuoteMessage::bid_size_short() const { return bid_size_short_; }
void ShortQuoteMessage::set_bid_size_short(std::uint16_t value) { bid_size_short_ = value; }

Decimal ShortQuoteMessage::offer_price_short() const { return offer_price_short_; }
void ShortQuoteMessage::set_offer_price_short(Decimal value) { offer_price_short_ = value; }

std::uint16_t ShortQuoteMessage::offer_size_short() const { return offer_size_short_; }
void ShortQuoteMessage::set_offer_size_short(std::uint16_t value) { offer_size_short_ = value; }

PrimaryListingMarketParticipantId ShortQuoteMessage::primary_listing_market_participant_id() const { return primary_listing_market_participant_id_; }
void ShortQuoteMessage::set_primary_listing_market_participant_id(PrimaryListingMarketParticipantId value) { primary_listing_market_participant_id_ = value; }

NationalBboIndicator ShortQuoteMessage::national_bbo_indicator() const { return national_bbo_indicator_; }
void ShortQuoteMessage::set_national_bbo_indicator(NationalBboIndicator value) { national_bbo_indicator_ = value; }

const std::optional<NationalBestBidLongAppendage>& ShortQuoteMessage::national_best_bid_long_appendage() const { return national_best_bid_long_appendage_; }
std::optional<NationalBestBidLongAppendage>& ShortQuoteMessage::national_best_bid_long_appendage() { return national_best_bid_long_appendage_; }
void ShortQuoteMessage::set_national_best_bid_long_appendage(const std::optional<NationalBestBidLongAppendage>& value) { national_best_bid_long_appendage_ = value; }

const std::optional<NationalBestOfferLongAppendage>& ShortQuoteMessage::national_best_offer_long_appendage() const { return national_best_offer_long_appendage_; }
std::optional<NationalBestOfferLongAppendage>& ShortQuoteMessage::national_best_offer_long_appendage() { return national_best_offer_long_appendage_; }
void ShortQuoteMessage::set_national_best_offer_long_appendage(const std::optional<NationalBestOfferLongAppendage>& value) { national_best_offer_long_appendage_ = value; }

const std::optional<NationalBestBidAndOfferLongAppendage>& ShortQuoteMessage::national_best_bid_and_offer_long_appendage() const { return national_best_bid_and_offer_long_appendage_; }
std::optional<NationalBestBidAndOfferLongAppendage>& ShortQuoteMessage::national_best_bid_and_offer_long_appendage() { return national_best_bid_and_offer_long_appendage_; }
void ShortQuoteMessage::set_national_best_bid_and_offer_long_appendage(const std::optional<NationalBestBidAndOfferLongAppendage>& value) { national_best_bid_and_offer_long_appendage_ = value; }

const std::optional<NationalBestBidShortAppendage>& ShortQuoteMessage::national_best_bid_short_appendage() const { return national_best_bid_short_appendage_; }
std::optional<NationalBestBidShortAppendage>& ShortQuoteMessage::national_best_bid_short_appendage() { return national_best_bid_short_appendage_; }
void ShortQuoteMessage::set_national_best_bid_short_appendage(const std::optional<NationalBestBidShortAppendage>& value) { national_best_bid_short_appendage_ = value; }

const std::optional<NationalBestOfferShortAppendage>& ShortQuoteMessage::national_best_offer_short_appendage() const { return national_best_offer_short_appendage_; }
std::optional<NationalBestOfferShortAppendage>& ShortQuoteMessage::national_best_offer_short_appendage() { return national_best_offer_short_appendage_; }
void ShortQuoteMessage::set_national_best_offer_short_appendage(const std::optional<NationalBestOfferShortAppendage>& value) { national_best_offer_short_appendage_ = value; }

const std::optional<NationalBestBidAndOfferShortAppendage>& ShortQuoteMessage::national_best_bid_and_offer_short_appendage() const { return national_best_bid_and_offer_short_appendage_; }
std::optional<NationalBestBidAndOfferShortAppendage>& ShortQuoteMessage::national_best_bid_and_offer_short_appendage() { return national_best_bid_and_offer_short_appendage_; }
void ShortQuoteMessage::set_national_best_bid_and_offer_short_appendage(const std::optional<NationalBestBidAndOfferShortAppendage>& value) { national_best_bid_and_offer_short_appendage_ = value; }

QuoteMessagePayloadCode ShortQuoteMessage::type() const { return message_type; }

std::string_view ShortQuoteMessage::name() const { return "Short Quote Message"; }

std::size_t ShortQuoteMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("ShortQuoteMessage", offset + 1, length);
    participant_id_ = static_cast<ParticipantId>(wire::read_char(data + offset));
    offset += 1;

    offset += timestamp_1_.decode(data + offset, length - offset);

    wire::require("ShortQuoteMessage", offset + 1, length);
    message_id_ = wire::read_u8(data + offset);
    offset += 1;

    wire::require("ShortQuoteMessage", offset + 4, length);
    transaction_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("ShortQuoteMessage", offset + 8, length);
    participant_reference_number_ = wire::read_i64_be(data + offset);
    offset += 8;

    wire::require("ShortQuoteMessage", offset + 11, length);
    security_symbol_ = wire::read_text(data + offset, 11, ' ');
    offset += 11;

    wire::require("ShortQuoteMessage", offset + 2, length);
    bid_price_short_ = Decimal(static_cast<std::int64_t>(wire::read_u16_be(data + offset)), -2);
    offset += 2;

    wire::require("ShortQuoteMessage", offset + 2, length);
    bid_size_short_ = wire::read_u16_be(data + offset);
    offset += 2;

    wire::require("ShortQuoteMessage", offset + 2, length);
    offer_price_short_ = Decimal(static_cast<std::int64_t>(wire::read_u16_be(data + offset)), -2);
    offset += 2;

    wire::require("ShortQuoteMessage", offset + 2, length);
    offer_size_short_ = wire::read_u16_be(data + offset);
    offset += 2;

    wire::require("ShortQuoteMessage", offset + 1, length);
    primary_listing_market_participant_id_ = static_cast<PrimaryListingMarketParticipantId>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ShortQuoteMessage", offset + 1, length);
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

std::size_t ShortQuoteMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ShortQuoteMessage", encoded_size(), capacity);

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

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(bid_price_short_.mantissa()));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(bid_size_short_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(offer_price_short_.mantissa()));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(offer_size_short_));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(primary_listing_market_participant_id_));
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

std::size_t ShortQuoteMessage::encoded_size() const {
    return 1 + timestamp_1_.encoded_size() + 1 + 4 + 8 + 11 + 2 + 2 + 2 + 2 + 1 + 1 + (national_best_bid_long_appendage_ ? national_best_bid_long_appendage_->encoded_size() : 0) + (national_best_offer_long_appendage_ ? national_best_offer_long_appendage_->encoded_size() : 0) + (national_best_bid_and_offer_long_appendage_ ? national_best_bid_and_offer_long_appendage_->encoded_size() : 0) + (national_best_bid_short_appendage_ ? national_best_bid_short_appendage_->encoded_size() : 0) + (national_best_offer_short_appendage_ ? national_best_offer_short_appendage_->encoded_size() : 0) + (national_best_bid_and_offer_short_appendage_ ? national_best_bid_and_offer_short_appendage_->encoded_size() : 0);
}

void ShortQuoteMessage::accept(QuoteMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<QuoteMessagePayload> ShortQuoteMessage::clone() const {
    return std::make_unique<ShortQuoteMessage>(*this);
}

void ShortQuoteMessage::print(std::ostream& out) const {
    out << "ShortQuoteMessage{";
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
    out << ", bid_price_short=";
    out << bid_price_short_;
    out << ", bid_size_short=";
    out << bid_size_short_;
    out << ", offer_price_short=";
    out << offer_price_short_;
    out << ", offer_size_short=";
    out << offer_size_short_;
    out << ", primary_listing_market_participant_id=";
    out << primary_listing_market_participant_id_;
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

bool ShortQuoteMessage::equals(const QuoteMessagePayload& other) const {
    const auto* that = dynamic_cast<const ShortQuoteMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ShortQuoteMessage::operator==(const ShortQuoteMessage& other) const {
    return participant_id_ == other.participant_id_
        && timestamp_1_ == other.timestamp_1_
        && message_id_ == other.message_id_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && security_symbol_ == other.security_symbol_
        && bid_price_short_ == other.bid_price_short_
        && bid_size_short_ == other.bid_size_short_
        && offer_price_short_ == other.offer_price_short_
        && offer_size_short_ == other.offer_size_short_
        && primary_listing_market_participant_id_ == other.primary_listing_market_participant_id_
        && national_bbo_indicator_ == other.national_bbo_indicator_
        && national_best_bid_long_appendage_ == other.national_best_bid_long_appendage_
        && national_best_offer_long_appendage_ == other.national_best_offer_long_appendage_
        && national_best_bid_and_offer_long_appendage_ == other.national_best_bid_and_offer_long_appendage_
        && national_best_bid_short_appendage_ == other.national_best_bid_short_appendage_
        && national_best_offer_short_appendage_ == other.national_best_offer_short_appendage_
        && national_best_bid_and_offer_short_appendage_ == other.national_best_bid_and_offer_short_appendage_;
}

bool ShortQuoteMessage::operator!=(const ShortQuoteMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cqs::output::cta::v2_10_a
