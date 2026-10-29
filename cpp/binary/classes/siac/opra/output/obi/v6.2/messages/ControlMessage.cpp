#include "ControlMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::opra::output::obi::v6_2 {

ControlMessage::ControlMessage(char message_indicator, std::uint32_t transaction_id, std::uint32_t participant_reference_number)
  : message_indicator_(message_indicator), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number) {}

char ControlMessage::message_indicator() const { return message_indicator_; }
void ControlMessage::set_message_indicator(char value) { message_indicator_ = value; }

std::uint32_t ControlMessage::transaction_id() const { return transaction_id_; }
void ControlMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::uint32_t ControlMessage::participant_reference_number() const { return participant_reference_number_; }
void ControlMessage::set_participant_reference_number(std::uint32_t value) { participant_reference_number_ = value; }

ControlMessagePayloadCode ControlMessage::type() const { return type_; }
void ControlMessage::set_type(ControlMessagePayloadCode value) { type_ = value; }

std::string_view ControlMessage::name() const { return "Control Message"; }

std::size_t ControlMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ControlMessage", wire_size, length);

    message_indicator_ = wire::read_char(data + offset);
    offset += 1;

    transaction_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    participant_reference_number_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t ControlMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ControlMessage", wire_size, capacity);

    wire::write_char(data + offset, message_indicator_);
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(transaction_id_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(participant_reference_number_));
    offset += 4;

    return offset;
}

std::size_t ControlMessage::encoded_size() const {
    return wire_size;
}

void ControlMessage::accept(ControlMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<ControlMessagePayload> ControlMessage::clone() const {
    return std::make_unique<ControlMessage>(*this);
}

void ControlMessage::print(std::ostream& out) const {
    out << "ControlMessage{";
    out << "message_indicator=";
    print::character(out, message_indicator_);
    out << ", transaction_id=";
    out << transaction_id_;
    out << ", participant_reference_number=";
    out << participant_reference_number_;
    out << '}';
}

bool ControlMessage::equals(const ControlMessagePayload& other) const {
    const auto* that = dynamic_cast<const ControlMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ControlMessage::operator==(const ControlMessage& other) const {
    return message_indicator_ == other.message_indicator_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && type_ == other.type_;
}

bool ControlMessage::operator!=(const ControlMessage& other) const {
    return !(*this == other);
}

} // namespace siac::opra::output::obi::v6_2
