#include "LongEquityAndIndexQuoteMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::opra::output::obi::v6_2 {

LongEquityAndIndexQuoteMessage::LongEquityAndIndexQuoteMessage(BboIndicator bbo_indicator, std::uint32_t transaction_id, std::uint32_t participant_reference_number, const std::string& security_symbol, const std::array<std::byte, 1>& reserved_1, const ExpirationBlock& expiration_block, StrikePriceDenominatorCode strike_price_denominator_code, Decimal strike_price, PremiumPriceDenominatorCode premium_price_denominator_code, std::int32_t bid_price, std::uint32_t bid_size, std::int32_t offer_price, std::uint32_t offer_size, const std::optional<BestBidAppendage>& best_bid_appendage, const std::optional<BestOfferAppendage>& best_offer_appendage, const std::optional<BestBidAndOfferAppendage>& best_bid_and_offer_appendage)
  : bbo_indicator_(bbo_indicator), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), security_symbol_(security_symbol), reserved_1_(reserved_1), expiration_block_(expiration_block), strike_price_denominator_code_(strike_price_denominator_code), strike_price_(strike_price), premium_price_denominator_code_(premium_price_denominator_code), bid_price_(bid_price), bid_size_(bid_size), offer_price_(offer_price), offer_size_(offer_size), best_bid_appendage_(best_bid_appendage), best_offer_appendage_(best_offer_appendage), best_bid_and_offer_appendage_(best_bid_and_offer_appendage) {}

BboIndicator LongEquityAndIndexQuoteMessage::bbo_indicator() const { return bbo_indicator_; }
void LongEquityAndIndexQuoteMessage::set_bbo_indicator(BboIndicator value) { bbo_indicator_ = value; }

std::uint32_t LongEquityAndIndexQuoteMessage::transaction_id() const { return transaction_id_; }
void LongEquityAndIndexQuoteMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::uint32_t LongEquityAndIndexQuoteMessage::participant_reference_number() const { return participant_reference_number_; }
void LongEquityAndIndexQuoteMessage::set_participant_reference_number(std::uint32_t value) { participant_reference_number_ = value; }

const std::string& LongEquityAndIndexQuoteMessage::security_symbol() const { return security_symbol_; }
std::string& LongEquityAndIndexQuoteMessage::security_symbol() { return security_symbol_; }
void LongEquityAndIndexQuoteMessage::set_security_symbol(const std::string& value) { security_symbol_ = value; }

const std::array<std::byte, 1>& LongEquityAndIndexQuoteMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& LongEquityAndIndexQuoteMessage::reserved_1() { return reserved_1_; }
void LongEquityAndIndexQuoteMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

const ExpirationBlock& LongEquityAndIndexQuoteMessage::expiration_block() const { return expiration_block_; }
ExpirationBlock& LongEquityAndIndexQuoteMessage::expiration_block() { return expiration_block_; }
void LongEquityAndIndexQuoteMessage::set_expiration_block(const ExpirationBlock& value) { expiration_block_ = value; }

StrikePriceDenominatorCode LongEquityAndIndexQuoteMessage::strike_price_denominator_code() const { return strike_price_denominator_code_; }
void LongEquityAndIndexQuoteMessage::set_strike_price_denominator_code(StrikePriceDenominatorCode value) { strike_price_denominator_code_ = value; }

Decimal LongEquityAndIndexQuoteMessage::strike_price() const { return strike_price_; }
void LongEquityAndIndexQuoteMessage::set_strike_price(Decimal value) { strike_price_ = value; }
int LongEquityAndIndexQuoteMessage::strike_price_exponent(char code) {
    switch (code) {
        case 'A': return -1;
        case 'B': return -2;
        case 'C': return -3;
        case 'D': return -4;
        case 'E': return -5;
        case 'I': return 0;
        default: return 0;
    }
}

PremiumPriceDenominatorCode LongEquityAndIndexQuoteMessage::premium_price_denominator_code() const { return premium_price_denominator_code_; }
void LongEquityAndIndexQuoteMessage::set_premium_price_denominator_code(PremiumPriceDenominatorCode value) { premium_price_denominator_code_ = value; }

std::int32_t LongEquityAndIndexQuoteMessage::bid_price() const { return bid_price_; }
void LongEquityAndIndexQuoteMessage::set_bid_price(std::int32_t value) { bid_price_ = value; }

std::uint32_t LongEquityAndIndexQuoteMessage::bid_size() const { return bid_size_; }
void LongEquityAndIndexQuoteMessage::set_bid_size(std::uint32_t value) { bid_size_ = value; }

std::int32_t LongEquityAndIndexQuoteMessage::offer_price() const { return offer_price_; }
void LongEquityAndIndexQuoteMessage::set_offer_price(std::int32_t value) { offer_price_ = value; }

std::uint32_t LongEquityAndIndexQuoteMessage::offer_size() const { return offer_size_; }
void LongEquityAndIndexQuoteMessage::set_offer_size(std::uint32_t value) { offer_size_ = value; }

const std::optional<BestBidAppendage>& LongEquityAndIndexQuoteMessage::best_bid_appendage() const { return best_bid_appendage_; }
std::optional<BestBidAppendage>& LongEquityAndIndexQuoteMessage::best_bid_appendage() { return best_bid_appendage_; }
void LongEquityAndIndexQuoteMessage::set_best_bid_appendage(const std::optional<BestBidAppendage>& value) { best_bid_appendage_ = value; }

const std::optional<BestOfferAppendage>& LongEquityAndIndexQuoteMessage::best_offer_appendage() const { return best_offer_appendage_; }
std::optional<BestOfferAppendage>& LongEquityAndIndexQuoteMessage::best_offer_appendage() { return best_offer_appendage_; }
void LongEquityAndIndexQuoteMessage::set_best_offer_appendage(const std::optional<BestOfferAppendage>& value) { best_offer_appendage_ = value; }

const std::optional<BestBidAndOfferAppendage>& LongEquityAndIndexQuoteMessage::best_bid_and_offer_appendage() const { return best_bid_and_offer_appendage_; }
std::optional<BestBidAndOfferAppendage>& LongEquityAndIndexQuoteMessage::best_bid_and_offer_appendage() { return best_bid_and_offer_appendage_; }
void LongEquityAndIndexQuoteMessage::set_best_bid_and_offer_appendage(const std::optional<BestBidAndOfferAppendage>& value) { best_bid_and_offer_appendage_ = value; }

LongEquityAndIndexQuoteMessagePayloadCode LongEquityAndIndexQuoteMessage::type() const { return message_type; }

std::string_view LongEquityAndIndexQuoteMessage::name() const { return "Long Equity And Index Quote Message"; }

std::size_t LongEquityAndIndexQuoteMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("LongEquityAndIndexQuoteMessage", offset + 1, length);
    bbo_indicator_ = static_cast<BboIndicator>(wire::read_char(data + offset));
    offset += 1;

    wire::require("LongEquityAndIndexQuoteMessage", offset + 4, length);
    transaction_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("LongEquityAndIndexQuoteMessage", offset + 4, length);
    participant_reference_number_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("LongEquityAndIndexQuoteMessage", offset + 5, length);
    security_symbol_ = wire::read_text(data + offset, 5, ' ');
    offset += 5;

    wire::require("LongEquityAndIndexQuoteMessage", offset + 1, length);
    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    offset += expiration_block_.decode(data + offset, length - offset);

    wire::require("LongEquityAndIndexQuoteMessage", offset + 1, length);
    strike_price_denominator_code_ = static_cast<StrikePriceDenominatorCode>(wire::read_char(data + offset));
    offset += 1;

    wire::require("LongEquityAndIndexQuoteMessage", offset + 4, length);
    strike_price_ = Decimal(static_cast<std::int64_t>(wire::read_i32_be(data + offset)), strike_price_exponent(static_cast<char>(strike_price_denominator_code_)));
    offset += 4;

    wire::require("LongEquityAndIndexQuoteMessage", offset + 1, length);
    premium_price_denominator_code_ = static_cast<PremiumPriceDenominatorCode>(wire::read_char(data + offset));
    offset += 1;

    wire::require("LongEquityAndIndexQuoteMessage", offset + 4, length);
    bid_price_ = wire::read_i32_be(data + offset);
    offset += 4;

    wire::require("LongEquityAndIndexQuoteMessage", offset + 4, length);
    bid_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("LongEquityAndIndexQuoteMessage", offset + 4, length);
    offer_price_ = wire::read_i32_be(data + offset);
    offset += 4;

    wire::require("LongEquityAndIndexQuoteMessage", offset + 4, length);
    offer_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    if (static_cast<char>(bbo_indicator_) == 'M') {
        BestBidAppendage value;
        offset += value.decode(data + offset, length - offset);
        best_bid_appendage_ = std::move(value);
    } else {
        best_bid_appendage_.reset();
    }

    if (static_cast<char>(bbo_indicator_) == 'C') {
        BestOfferAppendage value;
        offset += value.decode(data + offset, length - offset);
        best_offer_appendage_ = std::move(value);
    } else {
        best_offer_appendage_.reset();
    }

    if (static_cast<char>(bbo_indicator_) == 'O') {
        BestBidAndOfferAppendage value;
        offset += value.decode(data + offset, length - offset);
        best_bid_and_offer_appendage_ = std::move(value);
    } else {
        best_bid_and_offer_appendage_.reset();
    }

    return offset;
}

std::size_t LongEquityAndIndexQuoteMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LongEquityAndIndexQuoteMessage", encoded_size(), capacity);

    wire::write_char(data + offset, static_cast<char>(bbo_indicator_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(transaction_id_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(participant_reference_number_));
    offset += 4;

    wire::write_text(data + offset, 5, ' ', security_symbol_);
    offset += 5;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    offset += expiration_block_.encode(data + offset, capacity - offset);

    wire::write_char(data + offset, static_cast<char>(strike_price_denominator_code_));
    offset += 1;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(strike_price_.mantissa()));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(premium_price_denominator_code_));
    offset += 1;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(bid_price_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(bid_size_));
    offset += 4;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(offer_price_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(offer_size_));
    offset += 4;

    if (best_bid_appendage_) {
        offset += best_bid_appendage_->encode(data + offset, capacity - offset);
    }

    if (best_offer_appendage_) {
        offset += best_offer_appendage_->encode(data + offset, capacity - offset);
    }

    if (best_bid_and_offer_appendage_) {
        offset += best_bid_and_offer_appendage_->encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t LongEquityAndIndexQuoteMessage::encoded_size() const {
    return 1 + 4 + 4 + 5 + 1 + expiration_block_.encoded_size() + 1 + 4 + 1 + 4 + 4 + 4 + 4 + (best_bid_appendage_ ? best_bid_appendage_->encoded_size() : 0) + (best_offer_appendage_ ? best_offer_appendage_->encoded_size() : 0) + (best_bid_and_offer_appendage_ ? best_bid_and_offer_appendage_->encoded_size() : 0);
}

void LongEquityAndIndexQuoteMessage::accept(LongEquityAndIndexQuoteMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<LongEquityAndIndexQuoteMessagePayload> LongEquityAndIndexQuoteMessage::clone() const {
    return std::make_unique<LongEquityAndIndexQuoteMessage>(*this);
}

void LongEquityAndIndexQuoteMessage::print(std::ostream& out) const {
    out << "LongEquityAndIndexQuoteMessage{";
    out << "bbo_indicator=";
    out << bbo_indicator_;
    out << ", transaction_id=";
    out << transaction_id_;
    out << ", participant_reference_number=";
    out << participant_reference_number_;
    out << ", security_symbol=";
    print::text(out, security_symbol_);
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
    out << ", expiration_block=";
    expiration_block_.print(out);
    out << ", strike_price_denominator_code=";
    out << strike_price_denominator_code_;
    out << ", strike_price=";
    out << strike_price_;
    out << ", premium_price_denominator_code=";
    out << premium_price_denominator_code_;
    out << ", bid_price=";
    out << bid_price_;
    out << ", bid_size=";
    out << bid_size_;
    out << ", offer_price=";
    out << offer_price_;
    out << ", offer_size=";
    out << offer_size_;
    out << ", best_bid_appendage=";
    print::optional(out, best_bid_appendage_);
    out << ", best_offer_appendage=";
    print::optional(out, best_offer_appendage_);
    out << ", best_bid_and_offer_appendage=";
    print::optional(out, best_bid_and_offer_appendage_);
    out << '}';
}

bool LongEquityAndIndexQuoteMessage::equals(const LongEquityAndIndexQuoteMessagePayload& other) const {
    const auto* that = dynamic_cast<const LongEquityAndIndexQuoteMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool LongEquityAndIndexQuoteMessage::operator==(const LongEquityAndIndexQuoteMessage& other) const {
    return bbo_indicator_ == other.bbo_indicator_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && security_symbol_ == other.security_symbol_
        && reserved_1_ == other.reserved_1_
        && expiration_block_ == other.expiration_block_
        && strike_price_denominator_code_ == other.strike_price_denominator_code_
        && strike_price_ == other.strike_price_
        && premium_price_denominator_code_ == other.premium_price_denominator_code_
        && bid_price_ == other.bid_price_
        && bid_size_ == other.bid_size_
        && offer_price_ == other.offer_price_
        && offer_size_ == other.offer_size_
        && best_bid_appendage_ == other.best_bid_appendage_
        && best_offer_appendage_ == other.best_offer_appendage_
        && best_bid_and_offer_appendage_ == other.best_bid_and_offer_appendage_;
}

bool LongEquityAndIndexQuoteMessage::operator!=(const LongEquityAndIndexQuoteMessage& other) const {
    return !(*this == other);
}

} // namespace siac::opra::output::obi::v6_2
