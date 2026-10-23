#include "BrokenTradeOrderExecutedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

BrokenTradeOrderExecutedMessage::BrokenTradeOrderExecutedMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint32_t cross_number, std::uint32_t match_number)
  : tracking_number_(tracking_number), timestamp_(timestamp), cross_number_(cross_number), match_number_(match_number) {}

std::uint16_t BrokenTradeOrderExecutedMessage::tracking_number() const { return tracking_number_; }
void BrokenTradeOrderExecutedMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds BrokenTradeOrderExecutedMessage::timestamp() const { return timestamp_; }
void BrokenTradeOrderExecutedMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint32_t BrokenTradeOrderExecutedMessage::cross_number() const { return cross_number_; }
void BrokenTradeOrderExecutedMessage::set_cross_number(std::uint32_t value) { cross_number_ = value; }

std::uint32_t BrokenTradeOrderExecutedMessage::match_number() const { return match_number_; }
void BrokenTradeOrderExecutedMessage::set_match_number(std::uint32_t value) { match_number_ = value; }

SequencedMessageCode BrokenTradeOrderExecutedMessage::type() const { return message_type; }

std::string_view BrokenTradeOrderExecutedMessage::name() const { return "Broken Trade Order Executed Message"; }

std::size_t BrokenTradeOrderExecutedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("BrokenTradeOrderExecutedMessage", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    cross_number_ = wire::read_u32_be(data + offset);
    offset += 4;

    match_number_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t BrokenTradeOrderExecutedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("BrokenTradeOrderExecutedMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(cross_number_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(match_number_));
    offset += 4;

    return offset;
}

std::size_t BrokenTradeOrderExecutedMessage::encoded_size() const {
    return wire_size;
}

void BrokenTradeOrderExecutedMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> BrokenTradeOrderExecutedMessage::clone() const {
    return std::make_unique<BrokenTradeOrderExecutedMessage>(*this);
}

void BrokenTradeOrderExecutedMessage::print(std::ostream& out) const {
    out << "BrokenTradeOrderExecutedMessage{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", cross_number=";
    out << cross_number_;
    out << ", match_number=";
    out << match_number_;
    out << '}';
}

bool BrokenTradeOrderExecutedMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const BrokenTradeOrderExecutedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool BrokenTradeOrderExecutedMessage::operator==(const BrokenTradeOrderExecutedMessage& other) const {
    return tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && cross_number_ == other.cross_number_
        && match_number_ == other.match_number_;
}

bool BrokenTradeOrderExecutedMessage::operator!=(const BrokenTradeOrderExecutedMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
