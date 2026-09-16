#include "SystemEventMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

SystemEventMessage::SystemEventMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, EventCode event_code)
  : stock_locate_(stock_locate), tracking_number_(tracking_number), timestamp_(timestamp), event_code_(event_code) {}

std::uint16_t SystemEventMessage::stock_locate() const { return stock_locate_; }
void SystemEventMessage::set_stock_locate(std::uint16_t value) { stock_locate_ = value; }

std::uint16_t SystemEventMessage::tracking_number() const { return tracking_number_; }
void SystemEventMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds SystemEventMessage::timestamp() const { return timestamp_; }
void SystemEventMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

EventCode SystemEventMessage::event_code() const { return event_code_; }
void SystemEventMessage::set_event_code(EventCode value) { event_code_ = value; }

MessageCode SystemEventMessage::type() const { return message_type; }

std::string_view SystemEventMessage::name() const { return "System Event Message"; }

std::size_t SystemEventMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SystemEventMessage", wire_size, length);

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

std::size_t SystemEventMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SystemEventMessage", wire_size, capacity);

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

std::size_t SystemEventMessage::encoded_size() const {
    return wire_size;
}

void SystemEventMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SystemEventMessage::clone() const {
    return std::make_unique<SystemEventMessage>(*this);
}

void SystemEventMessage::print(std::ostream& out) const {
    out << "SystemEventMessage{";
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

bool SystemEventMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SystemEventMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SystemEventMessage::operator==(const SystemEventMessage& other) const {
    return stock_locate_ == other.stock_locate_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && event_code_ == other.event_code_;
}

bool SystemEventMessage::operator!=(const SystemEventMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
