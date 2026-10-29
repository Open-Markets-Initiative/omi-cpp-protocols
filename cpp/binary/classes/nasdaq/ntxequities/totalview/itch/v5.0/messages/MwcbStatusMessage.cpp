#include "MwcbStatusMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

MwcbStatusMessage::MwcbStatusMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, BreachedLevel breached_level)
  : stock_locate_(stock_locate), tracking_number_(tracking_number), timestamp_(timestamp), breached_level_(breached_level) {}

std::uint16_t MwcbStatusMessage::stock_locate() const { return stock_locate_; }
void MwcbStatusMessage::set_stock_locate(std::uint16_t value) { stock_locate_ = value; }

std::uint16_t MwcbStatusMessage::tracking_number() const { return tracking_number_; }
void MwcbStatusMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds MwcbStatusMessage::timestamp() const { return timestamp_; }
void MwcbStatusMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t MwcbStatusMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp_.count())); }

BreachedLevel MwcbStatusMessage::breached_level() const { return breached_level_; }
void MwcbStatusMessage::set_breached_level(BreachedLevel value) { breached_level_ = value; }

MessageCode MwcbStatusMessage::type() const { return message_type; }

std::string_view MwcbStatusMessage::name() const { return "Mwcb Status Message"; }

std::size_t MwcbStatusMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MwcbStatusMessage", wire_size, length);

    stock_locate_ = wire::read_u16_be(data + offset);
    offset += 2;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    breached_level_ = static_cast<BreachedLevel>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t MwcbStatusMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MwcbStatusMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(stock_locate_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_char(data + offset, static_cast<char>(breached_level_));
    offset += 1;

    return offset;
}

std::size_t MwcbStatusMessage::encoded_size() const {
    return wire_size;
}

void MwcbStatusMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> MwcbStatusMessage::clone() const {
    return std::make_unique<MwcbStatusMessage>(*this);
}

void MwcbStatusMessage::print(std::ostream& out) const {
    out << "MwcbStatusMessage{";
    out << "stock_locate=";
    out << stock_locate_;
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    calendar::print(out, timestamp_.count(), 1, "America/New_York");
    out << ", breached_level=";
    out << breached_level_;
    out << '}';
}

bool MwcbStatusMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const MwcbStatusMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool MwcbStatusMessage::operator==(const MwcbStatusMessage& other) const {
    return stock_locate_ == other.stock_locate_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && breached_level_ == other.breached_level_;
}

bool MwcbStatusMessage::operator!=(const MwcbStatusMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::ntxequities::totalview::itch::v5_0
