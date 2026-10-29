#include "MarketStatusMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"
#include "../Factory.hpp"

namespace siac::cts::output::cta::v2_10 {

MarketStatusMessage::MarketStatusMessage(const MarketStatusMessage& other)
  : market_status_message_type_(other.market_status_message_type_), market_status_message_payload_(other.market_status_message_payload_ ? other.market_status_message_payload_->clone() : nullptr) {}

MarketStatusMessage& MarketStatusMessage::operator=(const MarketStatusMessage& other) {
    if (this != &other) {
        market_status_message_type_ = other.market_status_message_type_;
        market_status_message_payload_ = other.market_status_message_payload_ ? other.market_status_message_payload_->clone() : nullptr;
    }
    return *this;
}

MarketStatusMessageType MarketStatusMessage::market_status_message_type() const { return market_status_message_type_; }
void MarketStatusMessage::set_market_status_message_type(MarketStatusMessageType value) { market_status_message_type_ = value; }

const MarketStatusMessagePayload* MarketStatusMessage::market_status_message_payload() const { return market_status_message_payload_.get(); }
MarketStatusMessagePayload* MarketStatusMessage::market_status_message_payload() { return market_status_message_payload_.get(); }
void MarketStatusMessage::set_market_status_message_payload(std::unique_ptr<MarketStatusMessagePayload> value) { market_status_message_payload_ = std::move(value); }

MessageCode MarketStatusMessage::type() const { return message_type; }

std::string_view MarketStatusMessage::name() const { return "Market Status Message"; }

std::size_t MarketStatusMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("MarketStatusMessage", offset + 1, length);
    market_status_message_type_ = static_cast<MarketStatusMessageType>(wire::read_char(data + offset));
    offset += 1;

    {
        auto selected = MarketStatusMessagePayloadFactory::create(market_status_message_type_);
        offset += selected->decode(data + offset, length - offset);
        market_status_message_payload_ = std::move(selected);
    }

    return offset;
}

std::size_t MarketStatusMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    if (!market_status_message_payload_) { throw EncodeError("MarketStatusMessage", "no market_status_message_payload"); }
    wire::require_capacity("MarketStatusMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto market_status_message_type = market_status_message_type_;
    market_status_message_type = market_status_message_payload_->type();

    wire::write_char(data + offset, static_cast<char>(market_status_message_type));
    offset += 1;

    offset += market_status_message_payload_->encode(data + offset, capacity - offset);

    return offset;
}

std::size_t MarketStatusMessage::encoded_size() const {
    return 1 + (market_status_message_payload_ ? market_status_message_payload_->encoded_size() : 0);
}

void MarketStatusMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> MarketStatusMessage::clone() const {
    return std::make_unique<MarketStatusMessage>(*this);
}

void MarketStatusMessage::print(std::ostream& out) const {
    out << "MarketStatusMessage{";
    out << "market_status_message_type=";
    out << market_status_message_type_;
    out << ", market_status_message_payload=";
    if (market_status_message_payload_) { market_status_message_payload_->print(out); } else { out << "null"; }
    out << '}';
}

bool MarketStatusMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const MarketStatusMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool MarketStatusMessage::operator==(const MarketStatusMessage& other) const {
    return market_status_message_type_ == other.market_status_message_type_
        && ((market_status_message_payload_ == nullptr) == (other.market_status_message_payload_ == nullptr) && (!market_status_message_payload_ || market_status_message_payload_->equals(*other.market_status_message_payload_)));
}

bool MarketStatusMessage::operator!=(const MarketStatusMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cts::output::cta::v2_10
