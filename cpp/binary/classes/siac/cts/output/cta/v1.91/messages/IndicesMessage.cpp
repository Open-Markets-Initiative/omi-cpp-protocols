#include "IndicesMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"
#include "../Factory.hpp"

namespace siac::cts::output::cta::v1_91 {

IndicesMessage::IndicesMessage(const IndicesMessage& other)
  : indices_message_type_(other.indices_message_type_), indices_message_payload_(other.indices_message_payload_ ? other.indices_message_payload_->clone() : nullptr) {}

IndicesMessage& IndicesMessage::operator=(const IndicesMessage& other) {
    if (this != &other) {
        indices_message_type_ = other.indices_message_type_;
        indices_message_payload_ = other.indices_message_payload_ ? other.indices_message_payload_->clone() : nullptr;
    }
    return *this;
}

IndicesMessageType IndicesMessage::indices_message_type() const { return indices_message_type_; }
void IndicesMessage::set_indices_message_type(IndicesMessageType value) { indices_message_type_ = value; }

const IndicesMessagePayload* IndicesMessage::indices_message_payload() const { return indices_message_payload_.get(); }
IndicesMessagePayload* IndicesMessage::indices_message_payload() { return indices_message_payload_.get(); }
void IndicesMessage::set_indices_message_payload(std::unique_ptr<IndicesMessagePayload> value) { indices_message_payload_ = std::move(value); }

MessageCode IndicesMessage::type() const { return message_type; }

std::string_view IndicesMessage::name() const { return "Indices Message"; }

std::size_t IndicesMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("IndicesMessage", offset + 1, length);
    indices_message_type_ = static_cast<IndicesMessageType>(wire::read_char(data + offset));
    offset += 1;

    {
        auto selected = IndicesMessagePayloadFactory::create(indices_message_type_);
        offset += selected->decode(data + offset, length - offset);
        indices_message_payload_ = std::move(selected);
    }

    return offset;
}

std::size_t IndicesMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    if (!indices_message_payload_) { throw EncodeError("IndicesMessage", "no indices_message_payload"); }
    wire::require_capacity("IndicesMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto indices_message_type = indices_message_type_;
    indices_message_type = indices_message_payload_->type();

    wire::write_char(data + offset, static_cast<char>(indices_message_type));
    offset += 1;

    offset += indices_message_payload_->encode(data + offset, capacity - offset);

    return offset;
}

std::size_t IndicesMessage::encoded_size() const {
    return 1 + (indices_message_payload_ ? indices_message_payload_->encoded_size() : 0);
}

void IndicesMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> IndicesMessage::clone() const {
    return std::make_unique<IndicesMessage>(*this);
}

void IndicesMessage::print(std::ostream& out) const {
    out << "IndicesMessage{";
    out << "indices_message_type=";
    out << indices_message_type_;
    out << ", indices_message_payload=";
    if (indices_message_payload_) { indices_message_payload_->print(out); } else { out << "null"; }
    out << '}';
}

bool IndicesMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const IndicesMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool IndicesMessage::operator==(const IndicesMessage& other) const {
    return indices_message_type_ == other.indices_message_type_
        && ((indices_message_payload_ == nullptr) == (other.indices_message_payload_ == nullptr) && (!indices_message_payload_ || indices_message_payload_->equals(*other.indices_message_payload_)));
}

bool IndicesMessage::operator!=(const IndicesMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cts::output::cta::v1_91
