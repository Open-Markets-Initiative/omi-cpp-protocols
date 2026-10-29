#include "ControlMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"
#include "../Factory.hpp"

namespace siac::cts::output::cta::v1_91 {

ControlMessage::ControlMessage(const ControlMessage& other)
  : control_message_type_(other.control_message_type_), control_message_payload_(other.control_message_payload_ ? other.control_message_payload_->clone() : nullptr) {}

ControlMessage& ControlMessage::operator=(const ControlMessage& other) {
    if (this != &other) {
        control_message_type_ = other.control_message_type_;
        control_message_payload_ = other.control_message_payload_ ? other.control_message_payload_->clone() : nullptr;
    }
    return *this;
}

ControlMessageType ControlMessage::control_message_type() const { return control_message_type_; }
void ControlMessage::set_control_message_type(ControlMessageType value) { control_message_type_ = value; }

const ControlMessagePayload* ControlMessage::control_message_payload() const { return control_message_payload_.get(); }
ControlMessagePayload* ControlMessage::control_message_payload() { return control_message_payload_.get(); }
void ControlMessage::set_control_message_payload(std::unique_ptr<ControlMessagePayload> value) { control_message_payload_ = std::move(value); }

MessageCode ControlMessage::type() const { return message_type; }

std::string_view ControlMessage::name() const { return "Control Message"; }

std::size_t ControlMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("ControlMessage", offset + 1, length);
    control_message_type_ = static_cast<ControlMessageType>(wire::read_char(data + offset));
    offset += 1;

    {
        auto selected = ControlMessagePayloadFactory::create(control_message_type_);
        offset += selected->decode(data + offset, length - offset);
        control_message_payload_ = std::move(selected);
    }

    return offset;
}

std::size_t ControlMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    if (!control_message_payload_) { throw EncodeError("ControlMessage", "no control_message_payload"); }
    wire::require_capacity("ControlMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto control_message_type = control_message_type_;
    control_message_type = control_message_payload_->type();

    wire::write_char(data + offset, static_cast<char>(control_message_type));
    offset += 1;

    offset += control_message_payload_->encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ControlMessage::encoded_size() const {
    return 1 + (control_message_payload_ ? control_message_payload_->encoded_size() : 0);
}

void ControlMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ControlMessage::clone() const {
    return std::make_unique<ControlMessage>(*this);
}

void ControlMessage::print(std::ostream& out) const {
    out << "ControlMessage{";
    out << "control_message_type=";
    out << control_message_type_;
    out << ", control_message_payload=";
    if (control_message_payload_) { control_message_payload_->print(out); } else { out << "null"; }
    out << '}';
}

bool ControlMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ControlMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ControlMessage::operator==(const ControlMessage& other) const {
    return control_message_type_ == other.control_message_type_
        && ((control_message_payload_ == nullptr) == (other.control_message_payload_ == nullptr) && (!control_message_payload_ || control_message_payload_->equals(*other.control_message_payload_)));
}

bool ControlMessage::operator!=(const ControlMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cts::output::cta::v1_91
