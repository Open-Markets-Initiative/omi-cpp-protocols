#include "StartOfDayMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cts::output::cta::v2_11_b {

StartOfDayMessage::StartOfDayMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number)
  : participant_id_(participant_id), timestamp_1_(timestamp_1), message_id_(message_id), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number) {}

ParticipantId StartOfDayMessage::participant_id() const { return participant_id_; }
void StartOfDayMessage::set_participant_id(ParticipantId value) { participant_id_ = value; }

const Timestamp1& StartOfDayMessage::timestamp_1() const { return timestamp_1_; }
Timestamp1& StartOfDayMessage::timestamp_1() { return timestamp_1_; }
void StartOfDayMessage::set_timestamp_1(const Timestamp1& value) { timestamp_1_ = value; }

std::uint8_t StartOfDayMessage::message_id() const { return message_id_; }
void StartOfDayMessage::set_message_id(std::uint8_t value) { message_id_ = value; }

std::uint32_t StartOfDayMessage::transaction_id() const { return transaction_id_; }
void StartOfDayMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::int64_t StartOfDayMessage::participant_reference_number() const { return participant_reference_number_; }
void StartOfDayMessage::set_participant_reference_number(std::int64_t value) { participant_reference_number_ = value; }

ControlMessagePayloadCode StartOfDayMessage::type() const { return message_type; }

std::string_view StartOfDayMessage::name() const { return "Start Of Day Message"; }

std::size_t StartOfDayMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("StartOfDayMessage", wire_size, length);

    participant_id_ = static_cast<ParticipantId>(wire::read_char(data + offset));
    offset += 1;

    offset += timestamp_1_.decode(data + offset, length - offset);

    message_id_ = wire::read_u8(data + offset);
    offset += 1;

    transaction_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    participant_reference_number_ = wire::read_i64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t StartOfDayMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("StartOfDayMessage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(participant_id_));
    offset += 1;

    offset += timestamp_1_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(message_id_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(transaction_id_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(participant_reference_number_));
    offset += 8;

    return offset;
}

std::size_t StartOfDayMessage::encoded_size() const {
    return wire_size;
}

void StartOfDayMessage::accept(ControlMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<ControlMessagePayload> StartOfDayMessage::clone() const {
    return std::make_unique<StartOfDayMessage>(*this);
}

void StartOfDayMessage::print(std::ostream& out) const {
    out << "StartOfDayMessage{";
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
    out << '}';
}

bool StartOfDayMessage::equals(const ControlMessagePayload& other) const {
    const auto* that = dynamic_cast<const StartOfDayMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool StartOfDayMessage::operator==(const StartOfDayMessage& other) const {
    return participant_id_ == other.participant_id_
        && timestamp_1_ == other.timestamp_1_
        && message_id_ == other.message_id_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_;
}

bool StartOfDayMessage::operator!=(const StartOfDayMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cts::output::cta::v2_11_b
