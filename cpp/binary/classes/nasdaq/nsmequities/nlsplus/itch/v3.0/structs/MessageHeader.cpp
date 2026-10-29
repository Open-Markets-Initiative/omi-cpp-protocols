#include "MessageHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

MessageHeader::MessageHeader(std::uint16_t message_length, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, MessageType message_type)
  : message_length_(message_length), tracking_number_(tracking_number), timestamp_(timestamp), message_type_(message_type) {}

std::uint16_t MessageHeader::message_length() const { return message_length_; }
void MessageHeader::set_message_length(std::uint16_t value) { message_length_ = value; }

std::uint16_t MessageHeader::tracking_number() const { return tracking_number_; }
void MessageHeader::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds MessageHeader::timestamp() const { return timestamp_; }
void MessageHeader::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t MessageHeader::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp_.count())); }

MessageType MessageHeader::message_type() const { return message_type_; }
void MessageHeader::set_message_type(MessageType value) { message_type_ = value; }

std::size_t MessageHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MessageHeader", wire_size, length);

    message_length_ = wire::read_u16_be(data + offset);
    offset += 2;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    message_type_ = static_cast<MessageType>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t MessageHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MessageHeader", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(message_length_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_char(data + offset, static_cast<char>(message_type_));
    offset += 1;

    return offset;
}

std::size_t MessageHeader::encoded_size() const {
    return wire_size;
}

void MessageHeader::print(std::ostream& out) const {
    out << "MessageHeader{";
    out << "message_length=";
    out << message_length_;
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    calendar::print(out, timestamp_.count(), 1, "America/New_York");
    out << ", message_type=";
    out << message_type_;
    out << '}';
}

bool MessageHeader::operator==(const MessageHeader& other) const {
    return message_length_ == other.message_length_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && message_type_ == other.message_type_;
}

bool MessageHeader::operator!=(const MessageHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const MessageHeader& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
