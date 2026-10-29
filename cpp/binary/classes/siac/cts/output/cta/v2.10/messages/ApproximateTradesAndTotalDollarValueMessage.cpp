#include "ApproximateTradesAndTotalDollarValueMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cts::output::cta::v2_10 {

ApproximateTradesAndTotalDollarValueMessage::ApproximateTradesAndTotalDollarValueMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, std::uint32_t total_trades, Decimal dollar_value)
  : participant_id_(participant_id), timestamp_1_(timestamp_1), message_id_(message_id), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), total_trades_(total_trades), dollar_value_(dollar_value) {}

ParticipantId ApproximateTradesAndTotalDollarValueMessage::participant_id() const { return participant_id_; }
void ApproximateTradesAndTotalDollarValueMessage::set_participant_id(ParticipantId value) { participant_id_ = value; }

const Timestamp1& ApproximateTradesAndTotalDollarValueMessage::timestamp_1() const { return timestamp_1_; }
Timestamp1& ApproximateTradesAndTotalDollarValueMessage::timestamp_1() { return timestamp_1_; }
void ApproximateTradesAndTotalDollarValueMessage::set_timestamp_1(const Timestamp1& value) { timestamp_1_ = value; }

std::uint8_t ApproximateTradesAndTotalDollarValueMessage::message_id() const { return message_id_; }
void ApproximateTradesAndTotalDollarValueMessage::set_message_id(std::uint8_t value) { message_id_ = value; }

std::uint32_t ApproximateTradesAndTotalDollarValueMessage::transaction_id() const { return transaction_id_; }
void ApproximateTradesAndTotalDollarValueMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::int64_t ApproximateTradesAndTotalDollarValueMessage::participant_reference_number() const { return participant_reference_number_; }
void ApproximateTradesAndTotalDollarValueMessage::set_participant_reference_number(std::int64_t value) { participant_reference_number_ = value; }

std::uint32_t ApproximateTradesAndTotalDollarValueMessage::total_trades() const { return total_trades_; }
void ApproximateTradesAndTotalDollarValueMessage::set_total_trades(std::uint32_t value) { total_trades_ = value; }

Decimal ApproximateTradesAndTotalDollarValueMessage::dollar_value() const { return dollar_value_; }
void ApproximateTradesAndTotalDollarValueMessage::set_dollar_value(Decimal value) { dollar_value_ = value; }

MarketStatusMessagePayloadCode ApproximateTradesAndTotalDollarValueMessage::type() const { return message_type; }

std::string_view ApproximateTradesAndTotalDollarValueMessage::name() const { return "Approximate Trades And Total Dollar Value Message"; }

std::size_t ApproximateTradesAndTotalDollarValueMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ApproximateTradesAndTotalDollarValueMessage", wire_size, length);

    participant_id_ = static_cast<ParticipantId>(wire::read_char(data + offset));
    offset += 1;

    offset += timestamp_1_.decode(data + offset, length - offset);

    message_id_ = wire::read_u8(data + offset);
    offset += 1;

    transaction_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    participant_reference_number_ = wire::read_i64_be(data + offset);
    offset += 8;

    total_trades_ = wire::read_u32_be(data + offset);
    offset += 4;

    dollar_value_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    return offset;
}

std::size_t ApproximateTradesAndTotalDollarValueMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ApproximateTradesAndTotalDollarValueMessage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(participant_id_));
    offset += 1;

    offset += timestamp_1_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(message_id_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(transaction_id_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(participant_reference_number_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(total_trades_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(dollar_value_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t ApproximateTradesAndTotalDollarValueMessage::encoded_size() const {
    return wire_size;
}

void ApproximateTradesAndTotalDollarValueMessage::accept(MarketStatusMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<MarketStatusMessagePayload> ApproximateTradesAndTotalDollarValueMessage::clone() const {
    return std::make_unique<ApproximateTradesAndTotalDollarValueMessage>(*this);
}

void ApproximateTradesAndTotalDollarValueMessage::print(std::ostream& out) const {
    out << "ApproximateTradesAndTotalDollarValueMessage{";
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
    out << ", total_trades=";
    out << total_trades_;
    out << ", dollar_value=";
    out << dollar_value_;
    out << '}';
}

bool ApproximateTradesAndTotalDollarValueMessage::equals(const MarketStatusMessagePayload& other) const {
    const auto* that = dynamic_cast<const ApproximateTradesAndTotalDollarValueMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ApproximateTradesAndTotalDollarValueMessage::operator==(const ApproximateTradesAndTotalDollarValueMessage& other) const {
    return participant_id_ == other.participant_id_
        && timestamp_1_ == other.timestamp_1_
        && message_id_ == other.message_id_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && total_trades_ == other.total_trades_
        && dollar_value_ == other.dollar_value_;
}

bool ApproximateTradesAndTotalDollarValueMessage::operator!=(const ApproximateTradesAndTotalDollarValueMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cts::output::cta::v2_10
