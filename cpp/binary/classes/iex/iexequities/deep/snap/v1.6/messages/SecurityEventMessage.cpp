#include "SecurityEventMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace iex::iexequities::deep::snap::v1_6 {

SecurityEventMessage::SecurityEventMessage(SecurityEvent security_event, std::chrono::nanoseconds timestamp, const std::string& symbol)
  : security_event_(security_event), timestamp_(timestamp), symbol_(symbol) {}

SecurityEvent SecurityEventMessage::security_event() const { return security_event_; }
void SecurityEventMessage::set_security_event(SecurityEvent value) { security_event_ = value; }

std::chrono::nanoseconds SecurityEventMessage::timestamp() const { return timestamp_; }
void SecurityEventMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

const std::string& SecurityEventMessage::symbol() const { return symbol_; }
std::string& SecurityEventMessage::symbol() { return symbol_; }
void SecurityEventMessage::set_symbol(const std::string& value) { symbol_ = value; }

IexTpMessageDataCode SecurityEventMessage::type() const { return message_type; }

std::string_view SecurityEventMessage::name() const { return "Security Event Message"; }

std::size_t SecurityEventMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SecurityEventMessage", wire_size, length);

    security_event_ = static_cast<SecurityEvent>(wire::read_char(data + offset));
    offset += 1;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_i64_le(data + offset)));
    offset += 8;

    symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    return offset;
}

std::size_t SecurityEventMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecurityEventMessage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(security_event_));
    offset += 1;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(timestamp_.count()));
    offset += 8;

    wire::write_text(data + offset, 8, ' ', symbol_);
    offset += 8;

    return offset;
}

std::size_t SecurityEventMessage::encoded_size() const {
    return wire_size;
}

void SecurityEventMessage::accept(IexTpMessageDataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<IexTpMessageData> SecurityEventMessage::clone() const {
    return std::make_unique<SecurityEventMessage>(*this);
}

void SecurityEventMessage::print(std::ostream& out) const {
    out << "SecurityEventMessage{";
    out << "security_event=";
    out << security_event_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", symbol=";
    print::text(out, symbol_);
    out << '}';
}

bool SecurityEventMessage::equals(const IexTpMessageData& other) const {
    const auto* that = dynamic_cast<const SecurityEventMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SecurityEventMessage::operator==(const SecurityEventMessage& other) const {
    return security_event_ == other.security_event_
        && timestamp_ == other.timestamp_
        && symbol_ == other.symbol_;
}

bool SecurityEventMessage::operator!=(const SecurityEventMessage& other) const {
    return !(*this == other);
}

} // namespace iex::iexequities::deep::snap::v1_6
