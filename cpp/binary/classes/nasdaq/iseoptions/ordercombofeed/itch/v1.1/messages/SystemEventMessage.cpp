#include "SystemEventMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

SystemEventMessage::SystemEventMessage(std::chrono::nanoseconds timestamp, EventCode event_code, std::uint16_t current_year, std::uint8_t current_month, std::uint8_t current_day, std::uint8_t version, std::uint8_t sub_version)
  : timestamp_(timestamp), event_code_(event_code), current_year_(current_year), current_month_(current_month), current_day_(current_day), version_(version), sub_version_(sub_version) {}

std::chrono::nanoseconds SystemEventMessage::timestamp() const { return timestamp_; }
void SystemEventMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t SystemEventMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp_.count())); }

EventCode SystemEventMessage::event_code() const { return event_code_; }
void SystemEventMessage::set_event_code(EventCode value) { event_code_ = value; }

std::uint16_t SystemEventMessage::current_year() const { return current_year_; }
void SystemEventMessage::set_current_year(std::uint16_t value) { current_year_ = value; }

std::uint8_t SystemEventMessage::current_month() const { return current_month_; }
void SystemEventMessage::set_current_month(std::uint8_t value) { current_month_ = value; }

std::uint8_t SystemEventMessage::current_day() const { return current_day_; }
void SystemEventMessage::set_current_day(std::uint8_t value) { current_day_ = value; }

std::uint8_t SystemEventMessage::version() const { return version_; }
void SystemEventMessage::set_version(std::uint8_t value) { version_ = value; }

std::uint8_t SystemEventMessage::sub_version() const { return sub_version_; }
void SystemEventMessage::set_sub_version(std::uint8_t value) { sub_version_ = value; }

MessageCode SystemEventMessage::type() const { return message_type; }

std::string_view SystemEventMessage::name() const { return "System Event Message"; }

std::size_t SystemEventMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SystemEventMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    event_code_ = static_cast<EventCode>(wire::read_char(data + offset));
    offset += 1;

    current_year_ = wire::read_u16_be(data + offset);
    offset += 2;

    current_month_ = wire::read_u8(data + offset);
    offset += 1;

    current_day_ = wire::read_u8(data + offset);
    offset += 1;

    version_ = wire::read_u8(data + offset);
    offset += 1;

    sub_version_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t SystemEventMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SystemEventMessage", wire_size, capacity);

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_char(data + offset, static_cast<char>(event_code_));
    offset += 1;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(current_year_));
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(current_month_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(current_day_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(version_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(sub_version_));
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
    out << "timestamp=";
    calendar::print(out, timestamp_.count(), 1, "America/New_York");
    out << ", event_code=";
    out << event_code_;
    out << ", current_year=";
    out << current_year_;
    out << ", current_month=";
    out << static_cast<int>(current_month_);
    out << ", current_day=";
    out << static_cast<int>(current_day_);
    out << ", version=";
    out << static_cast<int>(version_);
    out << ", sub_version=";
    out << static_cast<int>(sub_version_);
    out << '}';
}

bool SystemEventMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SystemEventMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SystemEventMessage::operator==(const SystemEventMessage& other) const {
    return timestamp_ == other.timestamp_
        && event_code_ == other.event_code_
        && current_year_ == other.current_year_
        && current_month_ == other.current_month_
        && current_day_ == other.current_day_
        && version_ == other.version_
        && sub_version_ == other.sub_version_;
}

bool SystemEventMessage::operator!=(const SystemEventMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
