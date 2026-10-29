#include "AdministrativeUnformattedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cts::output::cta::v1_91 {

AdministrativeUnformattedMessage::AdministrativeUnformattedMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& text)
  : participant_id_(participant_id), timestamp_1_(timestamp_1), message_id_(message_id), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), text_(text) {}

ParticipantId AdministrativeUnformattedMessage::participant_id() const { return participant_id_; }
void AdministrativeUnformattedMessage::set_participant_id(ParticipantId value) { participant_id_ = value; }

const Timestamp1& AdministrativeUnformattedMessage::timestamp_1() const { return timestamp_1_; }
Timestamp1& AdministrativeUnformattedMessage::timestamp_1() { return timestamp_1_; }
void AdministrativeUnformattedMessage::set_timestamp_1(const Timestamp1& value) { timestamp_1_ = value; }

std::uint8_t AdministrativeUnformattedMessage::message_id() const { return message_id_; }
void AdministrativeUnformattedMessage::set_message_id(std::uint8_t value) { message_id_ = value; }

std::uint32_t AdministrativeUnformattedMessage::transaction_id() const { return transaction_id_; }
void AdministrativeUnformattedMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::int64_t AdministrativeUnformattedMessage::participant_reference_number() const { return participant_reference_number_; }
void AdministrativeUnformattedMessage::set_participant_reference_number(std::int64_t value) { participant_reference_number_ = value; }

const std::string& AdministrativeUnformattedMessage::text() const { return text_; }
std::string& AdministrativeUnformattedMessage::text() { return text_; }
void AdministrativeUnformattedMessage::set_text(const std::string& value) { text_ = value; }

AdministrativeMessagePayloadCode AdministrativeUnformattedMessage::type() const { return message_type; }

std::string_view AdministrativeUnformattedMessage::name() const { return "Administrative Unformatted Message"; }

std::size_t AdministrativeUnformattedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AdministrativeUnformattedMessage", wire_size, length);

    participant_id_ = static_cast<ParticipantId>(wire::read_char(data + offset));
    offset += 1;

    offset += timestamp_1_.decode(data + offset, length - offset);

    message_id_ = wire::read_u8(data + offset);
    offset += 1;

    transaction_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    participant_reference_number_ = wire::read_i64_be(data + offset);
    offset += 8;

    text_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    return offset;
}

std::size_t AdministrativeUnformattedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AdministrativeUnformattedMessage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(participant_id_));
    offset += 1;

    offset += timestamp_1_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(message_id_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(transaction_id_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(participant_reference_number_));
    offset += 8;

    wire::write_text(data + offset, 4, ' ', text_);
    offset += 4;

    return offset;
}

std::size_t AdministrativeUnformattedMessage::encoded_size() const {
    return wire_size;
}

void AdministrativeUnformattedMessage::accept(AdministrativeMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<AdministrativeMessagePayload> AdministrativeUnformattedMessage::clone() const {
    return std::make_unique<AdministrativeUnformattedMessage>(*this);
}

void AdministrativeUnformattedMessage::print(std::ostream& out) const {
    out << "AdministrativeUnformattedMessage{";
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
    out << ", text=";
    print::text(out, text_);
    out << '}';
}

bool AdministrativeUnformattedMessage::equals(const AdministrativeMessagePayload& other) const {
    const auto* that = dynamic_cast<const AdministrativeUnformattedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AdministrativeUnformattedMessage::operator==(const AdministrativeUnformattedMessage& other) const {
    return participant_id_ == other.participant_id_
        && timestamp_1_ == other.timestamp_1_
        && message_id_ == other.message_id_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && text_ == other.text_;
}

bool AdministrativeUnformattedMessage::operator!=(const AdministrativeUnformattedMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cts::output::cta::v1_91
