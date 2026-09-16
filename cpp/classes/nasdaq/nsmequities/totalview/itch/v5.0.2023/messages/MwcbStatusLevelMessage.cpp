#include "MwcbStatusLevelMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

MwcbStatusLevelMessage::MwcbStatusLevelMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, BreachedLevel breached_level)
  : stock_locate_(stock_locate), tracking_number_(tracking_number), timestamp_(timestamp), breached_level_(breached_level) {}

std::uint16_t MwcbStatusLevelMessage::stock_locate() const { return stock_locate_; }
void MwcbStatusLevelMessage::set_stock_locate(std::uint16_t value) { stock_locate_ = value; }

std::uint16_t MwcbStatusLevelMessage::tracking_number() const { return tracking_number_; }
void MwcbStatusLevelMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds MwcbStatusLevelMessage::timestamp() const { return timestamp_; }
void MwcbStatusLevelMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

BreachedLevel MwcbStatusLevelMessage::breached_level() const { return breached_level_; }
void MwcbStatusLevelMessage::set_breached_level(BreachedLevel value) { breached_level_ = value; }

MessageCode MwcbStatusLevelMessage::type() const { return message_type; }

std::string_view MwcbStatusLevelMessage::name() const { return "Mwcb Status Level Message"; }

std::size_t MwcbStatusLevelMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MwcbStatusLevelMessage", wire_size, length);

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

std::size_t MwcbStatusLevelMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MwcbStatusLevelMessage", wire_size, capacity);

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

std::size_t MwcbStatusLevelMessage::encoded_size() const {
    return wire_size;
}

void MwcbStatusLevelMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> MwcbStatusLevelMessage::clone() const {
    return std::make_unique<MwcbStatusLevelMessage>(*this);
}

void MwcbStatusLevelMessage::print(std::ostream& out) const {
    out << "MwcbStatusLevelMessage{";
    out << "stock_locate=";
    out << stock_locate_;
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", breached_level=";
    out << breached_level_;
    out << '}';
}

bool MwcbStatusLevelMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const MwcbStatusLevelMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool MwcbStatusLevelMessage::operator==(const MwcbStatusLevelMessage& other) const {
    return stock_locate_ == other.stock_locate_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && breached_level_ == other.breached_level_;
}

bool MwcbStatusLevelMessage::operator!=(const MwcbStatusLevelMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
