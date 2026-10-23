#include "QuoteMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"
#include "../Factory.hpp"

namespace siac::cqs::output::cta::v2_10_a {

QuoteMessage::QuoteMessage(const QuoteMessage& other)
  : quote_message_type_(other.quote_message_type_), quote_message_payload_(other.quote_message_payload_ ? other.quote_message_payload_->clone() : nullptr) {}

QuoteMessage& QuoteMessage::operator=(const QuoteMessage& other) {
    if (this != &other) {
        quote_message_type_ = other.quote_message_type_;
        quote_message_payload_ = other.quote_message_payload_ ? other.quote_message_payload_->clone() : nullptr;
    }
    return *this;
}

QuoteMessageType QuoteMessage::quote_message_type() const { return quote_message_type_; }
void QuoteMessage::set_quote_message_type(QuoteMessageType value) { quote_message_type_ = value; }

const QuoteMessagePayload* QuoteMessage::quote_message_payload() const { return quote_message_payload_.get(); }
QuoteMessagePayload* QuoteMessage::quote_message_payload() { return quote_message_payload_.get(); }
void QuoteMessage::set_quote_message_payload(std::unique_ptr<QuoteMessagePayload> value) { quote_message_payload_ = std::move(value); }

MessageCode QuoteMessage::type() const { return message_type; }

std::string_view QuoteMessage::name() const { return "Quote Message"; }

std::size_t QuoteMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("QuoteMessage", offset + 1, length);
    quote_message_type_ = static_cast<QuoteMessageType>(wire::read_char(data + offset));
    offset += 1;

    {
        auto selected = QuoteMessagePayloadFactory::create(quote_message_type_);
        offset += selected->decode(data + offset, length - offset);
        quote_message_payload_ = std::move(selected);
    }

    return offset;
}

std::size_t QuoteMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    if (!quote_message_payload_) { throw EncodeError("QuoteMessage", "no quote_message_payload"); }
    wire::require_capacity("QuoteMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto quote_message_type = quote_message_type_;
    quote_message_type = quote_message_payload_->type();

    wire::write_char(data + offset, static_cast<char>(quote_message_type));
    offset += 1;

    offset += quote_message_payload_->encode(data + offset, capacity - offset);

    return offset;
}

std::size_t QuoteMessage::encoded_size() const {
    return 1 + (quote_message_payload_ ? quote_message_payload_->encoded_size() : 0);
}

void QuoteMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> QuoteMessage::clone() const {
    return std::make_unique<QuoteMessage>(*this);
}

void QuoteMessage::print(std::ostream& out) const {
    out << "QuoteMessage{";
    out << "quote_message_type=";
    out << quote_message_type_;
    out << ", quote_message_payload=";
    if (quote_message_payload_) { quote_message_payload_->print(out); } else { out << "null"; }
    out << '}';
}

bool QuoteMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const QuoteMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool QuoteMessage::operator==(const QuoteMessage& other) const {
    return quote_message_type_ == other.quote_message_type_
        && ((quote_message_payload_ == nullptr) == (other.quote_message_payload_ == nullptr) && (!quote_message_payload_ || quote_message_payload_->equals(*other.quote_message_payload_)));
}

bool QuoteMessage::operator!=(const QuoteMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cqs::output::cta::v2_10_a
