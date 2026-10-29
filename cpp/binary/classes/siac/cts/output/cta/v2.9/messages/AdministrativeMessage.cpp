#include "AdministrativeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"
#include "../Factory.hpp"

namespace siac::cts::output::cta::v2_9 {

AdministrativeMessage::AdministrativeMessage(const AdministrativeMessage& other)
  : administrative_message_type_(other.administrative_message_type_), administrative_message_payload_(other.administrative_message_payload_ ? other.administrative_message_payload_->clone() : nullptr) {}

AdministrativeMessage& AdministrativeMessage::operator=(const AdministrativeMessage& other) {
    if (this != &other) {
        administrative_message_type_ = other.administrative_message_type_;
        administrative_message_payload_ = other.administrative_message_payload_ ? other.administrative_message_payload_->clone() : nullptr;
    }
    return *this;
}

AdministrativeMessageType AdministrativeMessage::administrative_message_type() const { return administrative_message_type_; }
void AdministrativeMessage::set_administrative_message_type(AdministrativeMessageType value) { administrative_message_type_ = value; }

const AdministrativeMessagePayload* AdministrativeMessage::administrative_message_payload() const { return administrative_message_payload_.get(); }
AdministrativeMessagePayload* AdministrativeMessage::administrative_message_payload() { return administrative_message_payload_.get(); }
void AdministrativeMessage::set_administrative_message_payload(std::unique_ptr<AdministrativeMessagePayload> value) { administrative_message_payload_ = std::move(value); }

MessageCode AdministrativeMessage::type() const { return message_type; }

std::string_view AdministrativeMessage::name() const { return "Administrative Message"; }

std::size_t AdministrativeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("AdministrativeMessage", offset + 1, length);
    administrative_message_type_ = static_cast<AdministrativeMessageType>(wire::read_char(data + offset));
    offset += 1;

    {
        auto selected = AdministrativeMessagePayloadFactory::create(administrative_message_type_);
        offset += selected->decode(data + offset, length - offset);
        administrative_message_payload_ = std::move(selected);
    }

    return offset;
}

std::size_t AdministrativeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    if (!administrative_message_payload_) { throw EncodeError("AdministrativeMessage", "no administrative_message_payload"); }
    wire::require_capacity("AdministrativeMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto administrative_message_type = administrative_message_type_;
    administrative_message_type = administrative_message_payload_->type();

    wire::write_char(data + offset, static_cast<char>(administrative_message_type));
    offset += 1;

    offset += administrative_message_payload_->encode(data + offset, capacity - offset);

    return offset;
}

std::size_t AdministrativeMessage::encoded_size() const {
    return 1 + (administrative_message_payload_ ? administrative_message_payload_->encoded_size() : 0);
}

void AdministrativeMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AdministrativeMessage::clone() const {
    return std::make_unique<AdministrativeMessage>(*this);
}

void AdministrativeMessage::print(std::ostream& out) const {
    out << "AdministrativeMessage{";
    out << "administrative_message_type=";
    out << administrative_message_type_;
    out << ", administrative_message_payload=";
    if (administrative_message_payload_) { administrative_message_payload_->print(out); } else { out << "null"; }
    out << '}';
}

bool AdministrativeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AdministrativeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AdministrativeMessage::operator==(const AdministrativeMessage& other) const {
    return administrative_message_type_ == other.administrative_message_type_
        && ((administrative_message_payload_ == nullptr) == (other.administrative_message_payload_ == nullptr) && (!administrative_message_payload_ || administrative_message_payload_->equals(*other.administrative_message_payload_)));
}

bool AdministrativeMessage::operator!=(const AdministrativeMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cts::output::cta::v2_9
