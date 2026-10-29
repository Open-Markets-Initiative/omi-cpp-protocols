#include "EndOfTestCycleMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cqs::output::cta::v1_91 {

EndOfTestCycleMessage::EndOfTestCycleMessage(ParticipantId participant_id, const ParticipantTimestamp& participant_timestamp, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number)
  : participant_id_(participant_id), participant_timestamp_(participant_timestamp), message_id_(message_id), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number) {}

ParticipantId EndOfTestCycleMessage::participant_id() const { return participant_id_; }
void EndOfTestCycleMessage::set_participant_id(ParticipantId value) { participant_id_ = value; }

const ParticipantTimestamp& EndOfTestCycleMessage::participant_timestamp() const { return participant_timestamp_; }
ParticipantTimestamp& EndOfTestCycleMessage::participant_timestamp() { return participant_timestamp_; }
void EndOfTestCycleMessage::set_participant_timestamp(const ParticipantTimestamp& value) { participant_timestamp_ = value; }

std::uint8_t EndOfTestCycleMessage::message_id() const { return message_id_; }
void EndOfTestCycleMessage::set_message_id(std::uint8_t value) { message_id_ = value; }

std::uint32_t EndOfTestCycleMessage::transaction_id() const { return transaction_id_; }
void EndOfTestCycleMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::int64_t EndOfTestCycleMessage::participant_reference_number() const { return participant_reference_number_; }
void EndOfTestCycleMessage::set_participant_reference_number(std::int64_t value) { participant_reference_number_ = value; }

ControlMessagePayloadCode EndOfTestCycleMessage::type() const { return message_type; }

std::string_view EndOfTestCycleMessage::name() const { return "End Of Test Cycle Message"; }

std::size_t EndOfTestCycleMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("EndOfTestCycleMessage", wire_size, length);

    participant_id_ = static_cast<ParticipantId>(wire::read_char(data + offset));
    offset += 1;

    offset += participant_timestamp_.decode(data + offset, length - offset);

    message_id_ = wire::read_u8(data + offset);
    offset += 1;

    transaction_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    participant_reference_number_ = wire::read_i64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t EndOfTestCycleMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("EndOfTestCycleMessage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(participant_id_));
    offset += 1;

    offset += participant_timestamp_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(message_id_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(transaction_id_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(participant_reference_number_));
    offset += 8;

    return offset;
}

std::size_t EndOfTestCycleMessage::encoded_size() const {
    return wire_size;
}

void EndOfTestCycleMessage::accept(ControlMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<ControlMessagePayload> EndOfTestCycleMessage::clone() const {
    return std::make_unique<EndOfTestCycleMessage>(*this);
}

void EndOfTestCycleMessage::print(std::ostream& out) const {
    out << "EndOfTestCycleMessage{";
    out << "participant_id=";
    out << participant_id_;
    out << ", participant_timestamp=";
    participant_timestamp_.print(out);
    out << ", message_id=";
    out << static_cast<int>(message_id_);
    out << ", transaction_id=";
    out << transaction_id_;
    out << ", participant_reference_number=";
    out << participant_reference_number_;
    out << '}';
}

bool EndOfTestCycleMessage::equals(const ControlMessagePayload& other) const {
    const auto* that = dynamic_cast<const EndOfTestCycleMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool EndOfTestCycleMessage::operator==(const EndOfTestCycleMessage& other) const {
    return participant_id_ == other.participant_id_
        && participant_timestamp_ == other.participant_timestamp_
        && message_id_ == other.message_id_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_;
}

bool EndOfTestCycleMessage::operator!=(const EndOfTestCycleMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cqs::output::cta::v1_91
