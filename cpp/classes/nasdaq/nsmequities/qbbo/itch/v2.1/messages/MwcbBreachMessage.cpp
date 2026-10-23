#include "MwcbBreachMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

MwcbBreachMessage::MwcbBreachMessage(std::uint16_t tracking_number, std::chrono::nanoseconds time_stamp, BreachedLevel breached_level)
  : tracking_number_(tracking_number), time_stamp_(time_stamp), breached_level_(breached_level) {}

std::uint16_t MwcbBreachMessage::tracking_number() const { return tracking_number_; }
void MwcbBreachMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds MwcbBreachMessage::time_stamp() const { return time_stamp_; }
void MwcbBreachMessage::set_time_stamp(std::chrono::nanoseconds value) { time_stamp_ = value; }

BreachedLevel MwcbBreachMessage::breached_level() const { return breached_level_; }
void MwcbBreachMessage::set_breached_level(BreachedLevel value) { breached_level_ = value; }

MessageCode MwcbBreachMessage::type() const { return message_type; }

std::string_view MwcbBreachMessage::name() const { return "Mwcb Breach Message"; }

std::size_t MwcbBreachMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MwcbBreachMessage", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    time_stamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    breached_level_ = static_cast<BreachedLevel>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t MwcbBreachMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MwcbBreachMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(time_stamp_.count()));
    offset += 6;

    wire::write_char(data + offset, static_cast<char>(breached_level_));
    offset += 1;

    return offset;
}

std::size_t MwcbBreachMessage::encoded_size() const {
    return wire_size;
}

void MwcbBreachMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> MwcbBreachMessage::clone() const {
    return std::make_unique<MwcbBreachMessage>(*this);
}

void MwcbBreachMessage::print(std::ostream& out) const {
    out << "MwcbBreachMessage{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", time_stamp=";
    out << time_stamp_.count();
    out << ", breached_level=";
    out << breached_level_;
    out << '}';
}

bool MwcbBreachMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const MwcbBreachMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool MwcbBreachMessage::operator==(const MwcbBreachMessage& other) const {
    return tracking_number_ == other.tracking_number_
        && time_stamp_ == other.time_stamp_
        && breached_level_ == other.breached_level_;
}

bool MwcbBreachMessage::operator!=(const MwcbBreachMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
