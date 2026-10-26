#include "UnderlyingValueBidAndOfferMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::opra::output::obi::v6_2 {

UnderlyingValueBidAndOfferMessage::UnderlyingValueBidAndOfferMessage(char message_indicator, std::uint32_t transaction_id, std::uint32_t participant_reference_number, const std::string& security_symbol, const std::array<std::byte, 1>& reserved_1, IndexValueDenominatorCode index_value_denominator_code, std::int32_t bid_index_value, std::int64_t offer_index_value)
  : message_indicator_(message_indicator), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), security_symbol_(security_symbol), reserved_1_(reserved_1), index_value_denominator_code_(index_value_denominator_code), bid_index_value_(bid_index_value), offer_index_value_(offer_index_value) {}

char UnderlyingValueBidAndOfferMessage::message_indicator() const { return message_indicator_; }
void UnderlyingValueBidAndOfferMessage::set_message_indicator(char value) { message_indicator_ = value; }

std::uint32_t UnderlyingValueBidAndOfferMessage::transaction_id() const { return transaction_id_; }
void UnderlyingValueBidAndOfferMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::uint32_t UnderlyingValueBidAndOfferMessage::participant_reference_number() const { return participant_reference_number_; }
void UnderlyingValueBidAndOfferMessage::set_participant_reference_number(std::uint32_t value) { participant_reference_number_ = value; }

const std::string& UnderlyingValueBidAndOfferMessage::security_symbol() const { return security_symbol_; }
std::string& UnderlyingValueBidAndOfferMessage::security_symbol() { return security_symbol_; }
void UnderlyingValueBidAndOfferMessage::set_security_symbol(const std::string& value) { security_symbol_ = value; }

const std::array<std::byte, 1>& UnderlyingValueBidAndOfferMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& UnderlyingValueBidAndOfferMessage::reserved_1() { return reserved_1_; }
void UnderlyingValueBidAndOfferMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

IndexValueDenominatorCode UnderlyingValueBidAndOfferMessage::index_value_denominator_code() const { return index_value_denominator_code_; }
void UnderlyingValueBidAndOfferMessage::set_index_value_denominator_code(IndexValueDenominatorCode value) { index_value_denominator_code_ = value; }

std::int32_t UnderlyingValueBidAndOfferMessage::bid_index_value() const { return bid_index_value_; }
void UnderlyingValueBidAndOfferMessage::set_bid_index_value(std::int32_t value) { bid_index_value_ = value; }

std::int64_t UnderlyingValueBidAndOfferMessage::offer_index_value() const { return offer_index_value_; }
void UnderlyingValueBidAndOfferMessage::set_offer_index_value(std::int64_t value) { offer_index_value_ = value; }

UnderlyingValueMessagePayloadCode UnderlyingValueBidAndOfferMessage::type() const { return message_type; }

std::string_view UnderlyingValueBidAndOfferMessage::name() const { return "Underlying Value Bid And Offer Message"; }

std::size_t UnderlyingValueBidAndOfferMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UnderlyingValueBidAndOfferMessage", wire_size, length);

    message_indicator_ = wire::read_char(data + offset);
    offset += 1;

    transaction_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    participant_reference_number_ = wire::read_u32_be(data + offset);
    offset += 4;

    security_symbol_ = wire::read_text(data + offset, 5, ' ');
    offset += 5;

    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    index_value_denominator_code_ = static_cast<IndexValueDenominatorCode>(wire::read_char(data + offset));
    offset += 1;

    bid_index_value_ = wire::read_i32_be(data + offset);
    offset += 4;

    offer_index_value_ = wire::read_i64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t UnderlyingValueBidAndOfferMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UnderlyingValueBidAndOfferMessage", wire_size, capacity);

    wire::write_char(data + offset, message_indicator_);
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(transaction_id_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(participant_reference_number_));
    offset += 4;

    wire::write_text(data + offset, 5, ' ', security_symbol_);
    offset += 5;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(index_value_denominator_code_));
    offset += 1;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(bid_index_value_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(offer_index_value_));
    offset += 8;

    return offset;
}

std::size_t UnderlyingValueBidAndOfferMessage::encoded_size() const {
    return wire_size;
}

void UnderlyingValueBidAndOfferMessage::accept(UnderlyingValueMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<UnderlyingValueMessagePayload> UnderlyingValueBidAndOfferMessage::clone() const {
    return std::make_unique<UnderlyingValueBidAndOfferMessage>(*this);
}

void UnderlyingValueBidAndOfferMessage::print(std::ostream& out) const {
    out << "UnderlyingValueBidAndOfferMessage{";
    out << "message_indicator=";
    print::character(out, message_indicator_);
    out << ", transaction_id=";
    out << transaction_id_;
    out << ", participant_reference_number=";
    out << participant_reference_number_;
    out << ", security_symbol=";
    print::text(out, security_symbol_);
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
    out << ", index_value_denominator_code=";
    out << index_value_denominator_code_;
    out << ", bid_index_value=";
    out << bid_index_value_;
    out << ", offer_index_value=";
    out << offer_index_value_;
    out << '}';
}

bool UnderlyingValueBidAndOfferMessage::equals(const UnderlyingValueMessagePayload& other) const {
    const auto* that = dynamic_cast<const UnderlyingValueBidAndOfferMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UnderlyingValueBidAndOfferMessage::operator==(const UnderlyingValueBidAndOfferMessage& other) const {
    return message_indicator_ == other.message_indicator_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && security_symbol_ == other.security_symbol_
        && reserved_1_ == other.reserved_1_
        && index_value_denominator_code_ == other.index_value_denominator_code_
        && bid_index_value_ == other.bid_index_value_
        && offer_index_value_ == other.offer_index_value_;
}

bool UnderlyingValueBidAndOfferMessage::operator!=(const UnderlyingValueBidAndOfferMessage& other) const {
    return !(*this == other);
}

} // namespace siac::opra::output::obi::v6_2
