#include "TradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"
#include "../Factory.hpp"

namespace siac::cts::output::cta::v1_91 {

TradeMessage::TradeMessage(const TradeMessage& other)
  : trade_message_type_(other.trade_message_type_), trade_message_payload_(other.trade_message_payload_ ? other.trade_message_payload_->clone() : nullptr) {}

TradeMessage& TradeMessage::operator=(const TradeMessage& other) {
    if (this != &other) {
        trade_message_type_ = other.trade_message_type_;
        trade_message_payload_ = other.trade_message_payload_ ? other.trade_message_payload_->clone() : nullptr;
    }
    return *this;
}

TradeMessageType TradeMessage::trade_message_type() const { return trade_message_type_; }
void TradeMessage::set_trade_message_type(TradeMessageType value) { trade_message_type_ = value; }

const TradeMessagePayload* TradeMessage::trade_message_payload() const { return trade_message_payload_.get(); }
TradeMessagePayload* TradeMessage::trade_message_payload() { return trade_message_payload_.get(); }
void TradeMessage::set_trade_message_payload(std::unique_ptr<TradeMessagePayload> value) { trade_message_payload_ = std::move(value); }

MessageCode TradeMessage::type() const { return message_type; }

std::string_view TradeMessage::name() const { return "Trade Message"; }

std::size_t TradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("TradeMessage", offset + 1, length);
    trade_message_type_ = static_cast<TradeMessageType>(wire::read_char(data + offset));
    offset += 1;

    {
        auto selected = TradeMessagePayloadFactory::create(trade_message_type_);
        offset += selected->decode(data + offset, length - offset);
        trade_message_payload_ = std::move(selected);
    }

    return offset;
}

std::size_t TradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    if (!trade_message_payload_) { throw EncodeError("TradeMessage", "no trade_message_payload"); }
    wire::require_capacity("TradeMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto trade_message_type = trade_message_type_;
    trade_message_type = trade_message_payload_->type();

    wire::write_char(data + offset, static_cast<char>(trade_message_type));
    offset += 1;

    offset += trade_message_payload_->encode(data + offset, capacity - offset);

    return offset;
}

std::size_t TradeMessage::encoded_size() const {
    return 1 + (trade_message_payload_ ? trade_message_payload_->encoded_size() : 0);
}

void TradeMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradeMessage::clone() const {
    return std::make_unique<TradeMessage>(*this);
}

void TradeMessage::print(std::ostream& out) const {
    out << "TradeMessage{";
    out << "trade_message_type=";
    out << trade_message_type_;
    out << ", trade_message_payload=";
    if (trade_message_payload_) { trade_message_payload_->print(out); } else { out << "null"; }
    out << '}';
}

bool TradeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeMessage::operator==(const TradeMessage& other) const {
    return trade_message_type_ == other.trade_message_type_
        && ((trade_message_payload_ == nullptr) == (other.trade_message_payload_ == nullptr) && (!trade_message_payload_ || trade_message_payload_->equals(*other.trade_message_payload_)));
}

bool TradeMessage::operator!=(const TradeMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cts::output::cta::v1_91
