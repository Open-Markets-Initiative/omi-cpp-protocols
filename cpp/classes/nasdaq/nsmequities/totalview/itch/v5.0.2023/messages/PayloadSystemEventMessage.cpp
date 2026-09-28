#include "PayloadSystemEventMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

PayloadSystemEventMessage::PayloadSystemEventMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, EventCode event_code)
  : stock_locate_(stock_locate), tracking_number_(tracking_number), timestamp_(timestamp), event_code_(event_code) {}

std::uint16_t PayloadSystemEventMessage::stock_locate() const { return stock_locate_; }
void PayloadSystemEventMessage::set_stock_locate(std::uint16_t value) { stock_locate_ = value; }

std::uint16_t PayloadSystemEventMessage::tracking_number() const { return tracking_number_; }
void PayloadSystemEventMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds PayloadSystemEventMessage::timestamp() const { return timestamp_; }
void PayloadSystemEventMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

EventCode PayloadSystemEventMessage::event_code() const { return event_code_; }
void PayloadSystemEventMessage::set_event_code(EventCode value) { event_code_ = value; }

PacketMessageCode PayloadSystemEventMessage::type() const { return message_type; }

std::string_view PayloadSystemEventMessage::name() const { return "System Event Message"; }

std::size_t PayloadSystemEventMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PayloadSystemEventMessage", wire_size, length);

    stock_locate_ = wire::read_u16_be(data + offset);
    offset += 2;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    event_code_ = static_cast<EventCode>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t PayloadSystemEventMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PayloadSystemEventMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(stock_locate_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_char(data + offset, static_cast<char>(event_code_));
    offset += 1;

    return offset;
}

std::size_t PayloadSystemEventMessage::encoded_size() const {
    return wire_size;
}

void PayloadSystemEventMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> PayloadSystemEventMessage::clone() const {
    return std::make_unique<PayloadSystemEventMessage>(*this);
}

void PayloadSystemEventMessage::print(std::ostream& out) const {
    out << "PayloadSystemEventMessage{";
    out << "stock_locate=";
    out << stock_locate_;
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", event_code=";
    out << event_code_;
    out << '}';
}

bool PayloadSystemEventMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const PayloadSystemEventMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PayloadSystemEventMessage::operator==(const PayloadSystemEventMessage& other) const {
    return stock_locate_ == other.stock_locate_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && event_code_ == other.event_code_;
}

bool PayloadSystemEventMessage::operator!=(const PayloadSystemEventMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
