#include "BidAndOfferIndexMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cts::output::cta::v1_91 {

BidAndOfferIndexMessage::BidAndOfferIndexMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& index_symbol, Decimal bid_index_value, Decimal offer_index_value)
  : participant_id_(participant_id), timestamp_1_(timestamp_1), message_id_(message_id), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), index_symbol_(index_symbol), bid_index_value_(bid_index_value), offer_index_value_(offer_index_value) {}

ParticipantId BidAndOfferIndexMessage::participant_id() const { return participant_id_; }
void BidAndOfferIndexMessage::set_participant_id(ParticipantId value) { participant_id_ = value; }

const Timestamp1& BidAndOfferIndexMessage::timestamp_1() const { return timestamp_1_; }
Timestamp1& BidAndOfferIndexMessage::timestamp_1() { return timestamp_1_; }
void BidAndOfferIndexMessage::set_timestamp_1(const Timestamp1& value) { timestamp_1_ = value; }

std::uint8_t BidAndOfferIndexMessage::message_id() const { return message_id_; }
void BidAndOfferIndexMessage::set_message_id(std::uint8_t value) { message_id_ = value; }

std::uint32_t BidAndOfferIndexMessage::transaction_id() const { return transaction_id_; }
void BidAndOfferIndexMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::int64_t BidAndOfferIndexMessage::participant_reference_number() const { return participant_reference_number_; }
void BidAndOfferIndexMessage::set_participant_reference_number(std::int64_t value) { participant_reference_number_ = value; }

const std::string& BidAndOfferIndexMessage::index_symbol() const { return index_symbol_; }
std::string& BidAndOfferIndexMessage::index_symbol() { return index_symbol_; }
void BidAndOfferIndexMessage::set_index_symbol(const std::string& value) { index_symbol_ = value; }

Decimal BidAndOfferIndexMessage::bid_index_value() const { return bid_index_value_; }
void BidAndOfferIndexMessage::set_bid_index_value(Decimal value) { bid_index_value_ = value; }

Decimal BidAndOfferIndexMessage::offer_index_value() const { return offer_index_value_; }
void BidAndOfferIndexMessage::set_offer_index_value(Decimal value) { offer_index_value_ = value; }

IndicesMessagePayloadCode BidAndOfferIndexMessage::type() const { return message_type; }

std::string_view BidAndOfferIndexMessage::name() const { return "Bid And Offer Index Message"; }

std::size_t BidAndOfferIndexMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("BidAndOfferIndexMessage", wire_size, length);

    participant_id_ = static_cast<ParticipantId>(wire::read_char(data + offset));
    offset += 1;

    offset += timestamp_1_.decode(data + offset, length - offset);

    message_id_ = wire::read_u8(data + offset);
    offset += 1;

    transaction_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    participant_reference_number_ = wire::read_i64_be(data + offset);
    offset += 8;

    index_symbol_ = wire::read_text(data + offset, 11, ' ');
    offset += 11;

    bid_index_value_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -6);
    offset += 8;

    offer_index_value_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -6);
    offset += 8;

    return offset;
}

std::size_t BidAndOfferIndexMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("BidAndOfferIndexMessage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(participant_id_));
    offset += 1;

    offset += timestamp_1_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(message_id_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(transaction_id_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(participant_reference_number_));
    offset += 8;

    wire::write_text(data + offset, 11, ' ', index_symbol_);
    offset += 11;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(bid_index_value_.mantissa()));
    offset += 8;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(offer_index_value_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t BidAndOfferIndexMessage::encoded_size() const {
    return wire_size;
}

void BidAndOfferIndexMessage::accept(IndicesMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<IndicesMessagePayload> BidAndOfferIndexMessage::clone() const {
    return std::make_unique<BidAndOfferIndexMessage>(*this);
}

void BidAndOfferIndexMessage::print(std::ostream& out) const {
    out << "BidAndOfferIndexMessage{";
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
    out << ", index_symbol=";
    print::text(out, index_symbol_);
    out << ", bid_index_value=";
    out << bid_index_value_;
    out << ", offer_index_value=";
    out << offer_index_value_;
    out << '}';
}

bool BidAndOfferIndexMessage::equals(const IndicesMessagePayload& other) const {
    const auto* that = dynamic_cast<const BidAndOfferIndexMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool BidAndOfferIndexMessage::operator==(const BidAndOfferIndexMessage& other) const {
    return participant_id_ == other.participant_id_
        && timestamp_1_ == other.timestamp_1_
        && message_id_ == other.message_id_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && index_symbol_ == other.index_symbol_
        && bid_index_value_ == other.bid_index_value_
        && offer_index_value_ == other.offer_index_value_;
}

bool BidAndOfferIndexMessage::operator!=(const BidAndOfferIndexMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cts::output::cta::v1_91
