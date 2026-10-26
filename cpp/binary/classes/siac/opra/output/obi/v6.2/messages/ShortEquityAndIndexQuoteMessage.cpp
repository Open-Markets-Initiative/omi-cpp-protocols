#include "ShortEquityAndIndexQuoteMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::opra::output::obi::v6_2 {

ShortEquityAndIndexQuoteMessage::ShortEquityAndIndexQuoteMessage(BboIndicator bbo_indicator, std::uint32_t transaction_id, std::uint32_t participant_reference_number, const std::string& security_symbol_short, const ExpirationBlock& expiration_block, Decimal strike_price_short, Decimal bid_price_short, std::uint16_t bid_size_short, Decimal offer_price_short, std::uint16_t offer_size_short, const std::optional<BestBidAppendage>& best_bid_appendage, const std::optional<BestOfferAppendage>& best_offer_appendage, const std::optional<BestBidAndOfferAppendage>& best_bid_and_offer_appendage)
  : bbo_indicator_(bbo_indicator), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), security_symbol_short_(security_symbol_short), expiration_block_(expiration_block), strike_price_short_(strike_price_short), bid_price_short_(bid_price_short), bid_size_short_(bid_size_short), offer_price_short_(offer_price_short), offer_size_short_(offer_size_short), best_bid_appendage_(best_bid_appendage), best_offer_appendage_(best_offer_appendage), best_bid_and_offer_appendage_(best_bid_and_offer_appendage) {}

BboIndicator ShortEquityAndIndexQuoteMessage::bbo_indicator() const { return bbo_indicator_; }
void ShortEquityAndIndexQuoteMessage::set_bbo_indicator(BboIndicator value) { bbo_indicator_ = value; }

std::uint32_t ShortEquityAndIndexQuoteMessage::transaction_id() const { return transaction_id_; }
void ShortEquityAndIndexQuoteMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::uint32_t ShortEquityAndIndexQuoteMessage::participant_reference_number() const { return participant_reference_number_; }
void ShortEquityAndIndexQuoteMessage::set_participant_reference_number(std::uint32_t value) { participant_reference_number_ = value; }

const std::string& ShortEquityAndIndexQuoteMessage::security_symbol_short() const { return security_symbol_short_; }
std::string& ShortEquityAndIndexQuoteMessage::security_symbol_short() { return security_symbol_short_; }
void ShortEquityAndIndexQuoteMessage::set_security_symbol_short(const std::string& value) { security_symbol_short_ = value; }

const ExpirationBlock& ShortEquityAndIndexQuoteMessage::expiration_block() const { return expiration_block_; }
ExpirationBlock& ShortEquityAndIndexQuoteMessage::expiration_block() { return expiration_block_; }
void ShortEquityAndIndexQuoteMessage::set_expiration_block(const ExpirationBlock& value) { expiration_block_ = value; }

Decimal ShortEquityAndIndexQuoteMessage::strike_price_short() const { return strike_price_short_; }
void ShortEquityAndIndexQuoteMessage::set_strike_price_short(Decimal value) { strike_price_short_ = value; }

Decimal ShortEquityAndIndexQuoteMessage::bid_price_short() const { return bid_price_short_; }
void ShortEquityAndIndexQuoteMessage::set_bid_price_short(Decimal value) { bid_price_short_ = value; }

std::uint16_t ShortEquityAndIndexQuoteMessage::bid_size_short() const { return bid_size_short_; }
void ShortEquityAndIndexQuoteMessage::set_bid_size_short(std::uint16_t value) { bid_size_short_ = value; }

Decimal ShortEquityAndIndexQuoteMessage::offer_price_short() const { return offer_price_short_; }
void ShortEquityAndIndexQuoteMessage::set_offer_price_short(Decimal value) { offer_price_short_ = value; }

std::uint16_t ShortEquityAndIndexQuoteMessage::offer_size_short() const { return offer_size_short_; }
void ShortEquityAndIndexQuoteMessage::set_offer_size_short(std::uint16_t value) { offer_size_short_ = value; }

const std::optional<BestBidAppendage>& ShortEquityAndIndexQuoteMessage::best_bid_appendage() const { return best_bid_appendage_; }
std::optional<BestBidAppendage>& ShortEquityAndIndexQuoteMessage::best_bid_appendage() { return best_bid_appendage_; }
void ShortEquityAndIndexQuoteMessage::set_best_bid_appendage(const std::optional<BestBidAppendage>& value) { best_bid_appendage_ = value; }

const std::optional<BestOfferAppendage>& ShortEquityAndIndexQuoteMessage::best_offer_appendage() const { return best_offer_appendage_; }
std::optional<BestOfferAppendage>& ShortEquityAndIndexQuoteMessage::best_offer_appendage() { return best_offer_appendage_; }
void ShortEquityAndIndexQuoteMessage::set_best_offer_appendage(const std::optional<BestOfferAppendage>& value) { best_offer_appendage_ = value; }

const std::optional<BestBidAndOfferAppendage>& ShortEquityAndIndexQuoteMessage::best_bid_and_offer_appendage() const { return best_bid_and_offer_appendage_; }
std::optional<BestBidAndOfferAppendage>& ShortEquityAndIndexQuoteMessage::best_bid_and_offer_appendage() { return best_bid_and_offer_appendage_; }
void ShortEquityAndIndexQuoteMessage::set_best_bid_and_offer_appendage(const std::optional<BestBidAndOfferAppendage>& value) { best_bid_and_offer_appendage_ = value; }

ShortEquityAndIndexQuoteMessagePayloadCode ShortEquityAndIndexQuoteMessage::type() const { return message_type; }

std::string_view ShortEquityAndIndexQuoteMessage::name() const { return "Short Equity And Index Quote Message"; }

std::size_t ShortEquityAndIndexQuoteMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("ShortEquityAndIndexQuoteMessage", offset + 1, length);
    bbo_indicator_ = static_cast<BboIndicator>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ShortEquityAndIndexQuoteMessage", offset + 4, length);
    transaction_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("ShortEquityAndIndexQuoteMessage", offset + 4, length);
    participant_reference_number_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("ShortEquityAndIndexQuoteMessage", offset + 4, length);
    security_symbol_short_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    offset += expiration_block_.decode(data + offset, length - offset);

    wire::require("ShortEquityAndIndexQuoteMessage", offset + 2, length);
    strike_price_short_ = Decimal(static_cast<std::int64_t>(wire::read_u16_be(data + offset)), -1);
    offset += 2;

    wire::require("ShortEquityAndIndexQuoteMessage", offset + 2, length);
    bid_price_short_ = Decimal(static_cast<std::int64_t>(wire::read_u16_be(data + offset)), -2);
    offset += 2;

    wire::require("ShortEquityAndIndexQuoteMessage", offset + 2, length);
    bid_size_short_ = wire::read_u16_be(data + offset);
    offset += 2;

    wire::require("ShortEquityAndIndexQuoteMessage", offset + 2, length);
    offer_price_short_ = Decimal(static_cast<std::int64_t>(wire::read_u16_be(data + offset)), -2);
    offset += 2;

    wire::require("ShortEquityAndIndexQuoteMessage", offset + 2, length);
    offer_size_short_ = wire::read_u16_be(data + offset);
    offset += 2;

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

std::size_t ShortEquityAndIndexQuoteMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ShortEquityAndIndexQuoteMessage", encoded_size(), capacity);

    wire::write_char(data + offset, static_cast<char>(bbo_indicator_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(transaction_id_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(participant_reference_number_));
    offset += 4;

    wire::write_text(data + offset, 4, ' ', security_symbol_short_);
    offset += 4;

    offset += expiration_block_.encode(data + offset, capacity - offset);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(strike_price_short_.mantissa()));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(bid_price_short_.mantissa()));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(bid_size_short_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(offer_price_short_.mantissa()));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(offer_size_short_));
    offset += 2;

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

std::size_t ShortEquityAndIndexQuoteMessage::encoded_size() const {
    return 1 + 4 + 4 + 4 + expiration_block_.encoded_size() + 2 + 2 + 2 + 2 + 2 + (best_bid_appendage_ ? best_bid_appendage_->encoded_size() : 0) + (best_offer_appendage_ ? best_offer_appendage_->encoded_size() : 0) + (best_bid_and_offer_appendage_ ? best_bid_and_offer_appendage_->encoded_size() : 0);
}

void ShortEquityAndIndexQuoteMessage::accept(ShortEquityAndIndexQuoteMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<ShortEquityAndIndexQuoteMessagePayload> ShortEquityAndIndexQuoteMessage::clone() const {
    return std::make_unique<ShortEquityAndIndexQuoteMessage>(*this);
}

void ShortEquityAndIndexQuoteMessage::print(std::ostream& out) const {
    out << "ShortEquityAndIndexQuoteMessage{";
    out << "bbo_indicator=";
    out << bbo_indicator_;
    out << ", transaction_id=";
    out << transaction_id_;
    out << ", participant_reference_number=";
    out << participant_reference_number_;
    out << ", security_symbol_short=";
    print::text(out, security_symbol_short_);
    out << ", expiration_block=";
    expiration_block_.print(out);
    out << ", strike_price_short=";
    out << strike_price_short_;
    out << ", bid_price_short=";
    out << bid_price_short_;
    out << ", bid_size_short=";
    out << bid_size_short_;
    out << ", offer_price_short=";
    out << offer_price_short_;
    out << ", offer_size_short=";
    out << offer_size_short_;
    out << ", best_bid_appendage=";
    print::optional(out, best_bid_appendage_);
    out << ", best_offer_appendage=";
    print::optional(out, best_offer_appendage_);
    out << ", best_bid_and_offer_appendage=";
    print::optional(out, best_bid_and_offer_appendage_);
    out << '}';
}

bool ShortEquityAndIndexQuoteMessage::equals(const ShortEquityAndIndexQuoteMessagePayload& other) const {
    const auto* that = dynamic_cast<const ShortEquityAndIndexQuoteMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ShortEquityAndIndexQuoteMessage::operator==(const ShortEquityAndIndexQuoteMessage& other) const {
    return bbo_indicator_ == other.bbo_indicator_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && security_symbol_short_ == other.security_symbol_short_
        && expiration_block_ == other.expiration_block_
        && strike_price_short_ == other.strike_price_short_
        && bid_price_short_ == other.bid_price_short_
        && bid_size_short_ == other.bid_size_short_
        && offer_price_short_ == other.offer_price_short_
        && offer_size_short_ == other.offer_size_short_
        && best_bid_appendage_ == other.best_bid_appendage_
        && best_offer_appendage_ == other.best_offer_appendage_
        && best_bid_and_offer_appendage_ == other.best_bid_and_offer_appendage_;
}

bool ShortEquityAndIndexQuoteMessage::operator!=(const ShortEquityAndIndexQuoteMessage& other) const {
    return !(*this == other);
}

} // namespace siac::opra::output::obi::v6_2
