#include "CrossingSessionSummaryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cts::output::cta::v2_11_b {

CrossingSessionSummaryMessage::CrossingSessionSummaryMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, std::uint64_t crossing_session_i_total_trades_volume, Decimal crossing_session_ii_dollar_value, std::uint64_t crossing_session_ii_total_trades_volume)
  : participant_id_(participant_id), timestamp_1_(timestamp_1), message_id_(message_id), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), crossing_session_i_total_trades_volume_(crossing_session_i_total_trades_volume), crossing_session_ii_dollar_value_(crossing_session_ii_dollar_value), crossing_session_ii_total_trades_volume_(crossing_session_ii_total_trades_volume) {}

ParticipantId CrossingSessionSummaryMessage::participant_id() const { return participant_id_; }
void CrossingSessionSummaryMessage::set_participant_id(ParticipantId value) { participant_id_ = value; }

const Timestamp1& CrossingSessionSummaryMessage::timestamp_1() const { return timestamp_1_; }
Timestamp1& CrossingSessionSummaryMessage::timestamp_1() { return timestamp_1_; }
void CrossingSessionSummaryMessage::set_timestamp_1(const Timestamp1& value) { timestamp_1_ = value; }

std::uint8_t CrossingSessionSummaryMessage::message_id() const { return message_id_; }
void CrossingSessionSummaryMessage::set_message_id(std::uint8_t value) { message_id_ = value; }

std::uint32_t CrossingSessionSummaryMessage::transaction_id() const { return transaction_id_; }
void CrossingSessionSummaryMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::int64_t CrossingSessionSummaryMessage::participant_reference_number() const { return participant_reference_number_; }
void CrossingSessionSummaryMessage::set_participant_reference_number(std::int64_t value) { participant_reference_number_ = value; }

std::uint64_t CrossingSessionSummaryMessage::crossing_session_i_total_trades_volume() const { return crossing_session_i_total_trades_volume_; }
void CrossingSessionSummaryMessage::set_crossing_session_i_total_trades_volume(std::uint64_t value) { crossing_session_i_total_trades_volume_ = value; }

Decimal CrossingSessionSummaryMessage::crossing_session_ii_dollar_value() const { return crossing_session_ii_dollar_value_; }
void CrossingSessionSummaryMessage::set_crossing_session_ii_dollar_value(Decimal value) { crossing_session_ii_dollar_value_ = value; }

std::uint64_t CrossingSessionSummaryMessage::crossing_session_ii_total_trades_volume() const { return crossing_session_ii_total_trades_volume_; }
void CrossingSessionSummaryMessage::set_crossing_session_ii_total_trades_volume(std::uint64_t value) { crossing_session_ii_total_trades_volume_ = value; }

MarketStatusMessagePayloadCode CrossingSessionSummaryMessage::type() const { return message_type; }

std::string_view CrossingSessionSummaryMessage::name() const { return "Crossing Session Summary Message"; }

std::size_t CrossingSessionSummaryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CrossingSessionSummaryMessage", wire_size, length);

    participant_id_ = static_cast<ParticipantId>(wire::read_char(data + offset));
    offset += 1;

    offset += timestamp_1_.decode(data + offset, length - offset);

    message_id_ = wire::read_u8(data + offset);
    offset += 1;

    transaction_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    participant_reference_number_ = wire::read_i64_be(data + offset);
    offset += 8;

    crossing_session_i_total_trades_volume_ = wire::read_u64_be(data + offset);
    offset += 8;

    crossing_session_ii_dollar_value_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    crossing_session_ii_total_trades_volume_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t CrossingSessionSummaryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CrossingSessionSummaryMessage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(participant_id_));
    offset += 1;

    offset += timestamp_1_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(message_id_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(transaction_id_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(participant_reference_number_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(crossing_session_i_total_trades_volume_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(crossing_session_ii_dollar_value_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(crossing_session_ii_total_trades_volume_));
    offset += 8;

    return offset;
}

std::size_t CrossingSessionSummaryMessage::encoded_size() const {
    return wire_size;
}

void CrossingSessionSummaryMessage::accept(MarketStatusMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<MarketStatusMessagePayload> CrossingSessionSummaryMessage::clone() const {
    return std::make_unique<CrossingSessionSummaryMessage>(*this);
}

void CrossingSessionSummaryMessage::print(std::ostream& out) const {
    out << "CrossingSessionSummaryMessage{";
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
    out << ", crossing_session_i_total_trades_volume=";
    out << crossing_session_i_total_trades_volume_;
    out << ", crossing_session_ii_dollar_value=";
    out << crossing_session_ii_dollar_value_;
    out << ", crossing_session_ii_total_trades_volume=";
    out << crossing_session_ii_total_trades_volume_;
    out << '}';
}

bool CrossingSessionSummaryMessage::equals(const MarketStatusMessagePayload& other) const {
    const auto* that = dynamic_cast<const CrossingSessionSummaryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool CrossingSessionSummaryMessage::operator==(const CrossingSessionSummaryMessage& other) const {
    return participant_id_ == other.participant_id_
        && timestamp_1_ == other.timestamp_1_
        && message_id_ == other.message_id_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && crossing_session_i_total_trades_volume_ == other.crossing_session_i_total_trades_volume_
        && crossing_session_ii_dollar_value_ == other.crossing_session_ii_dollar_value_
        && crossing_session_ii_total_trades_volume_ == other.crossing_session_ii_total_trades_volume_;
}

bool CrossingSessionSummaryMessage::operator!=(const CrossingSessionSummaryMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cts::output::cta::v2_11_b
