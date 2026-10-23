#include "TimeReferenceMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

TimeReferenceMessage::TimeReferenceMessage(std::chrono::seconds midnight_reference, std::chrono::seconds time_reference, std::chrono::nanoseconds time_offset, std::uint32_t trade_date)
  : midnight_reference_(midnight_reference), time_reference_(time_reference), time_offset_(time_offset), trade_date_(trade_date) {}

std::chrono::seconds TimeReferenceMessage::midnight_reference() const { return midnight_reference_; }
void TimeReferenceMessage::set_midnight_reference(std::chrono::seconds value) { midnight_reference_ = value; }

std::chrono::seconds TimeReferenceMessage::time_reference() const { return time_reference_; }
void TimeReferenceMessage::set_time_reference(std::chrono::seconds value) { time_reference_ = value; }

std::chrono::nanoseconds TimeReferenceMessage::time_offset() const { return time_offset_; }
void TimeReferenceMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

std::uint32_t TimeReferenceMessage::trade_date() const { return trade_date_; }
void TimeReferenceMessage::set_trade_date(std::uint32_t value) { trade_date_ = value; }

MessageCode TimeReferenceMessage::type() const { return message_type; }

std::string_view TimeReferenceMessage::name() const { return "Time Reference Message"; }

std::size_t TimeReferenceMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TimeReferenceMessage", wire_size, length);

    midnight_reference_ = std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    time_reference_ = std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    trade_date_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t TimeReferenceMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TimeReferenceMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(midnight_reference_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_reference_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trade_date_));
    offset += 4;

    return offset;
}

std::size_t TimeReferenceMessage::encoded_size() const {
    return wire_size;
}

void TimeReferenceMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TimeReferenceMessage::clone() const {
    return std::make_unique<TimeReferenceMessage>(*this);
}

void TimeReferenceMessage::print(std::ostream& out) const {
    out << "TimeReferenceMessage{";
    out << "midnight_reference=";
    out << midnight_reference_.count();
    out << ", time_reference=";
    out << time_reference_.count();
    out << ", time_offset=";
    out << time_offset_.count();
    out << ", trade_date=";
    out << trade_date_;
    out << '}';
}

bool TimeReferenceMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TimeReferenceMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TimeReferenceMessage::operator==(const TimeReferenceMessage& other) const {
    return midnight_reference_ == other.midnight_reference_
        && time_reference_ == other.time_reference_
        && time_offset_ == other.time_offset_
        && trade_date_ == other.trade_date_;
}

bool TimeReferenceMessage::operator!=(const TimeReferenceMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
