#include "QuoteDeleteMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

QuoteDeleteMessage::QuoteDeleteMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t bid_reference_number, std::uint64_t ask_reference_number)
  : tracking_number_(tracking_number), timestamp_(timestamp), bid_reference_number_(bid_reference_number), ask_reference_number_(ask_reference_number) {}

std::uint16_t QuoteDeleteMessage::tracking_number() const { return tracking_number_; }
void QuoteDeleteMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds QuoteDeleteMessage::timestamp() const { return timestamp_; }
void QuoteDeleteMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint64_t QuoteDeleteMessage::bid_reference_number() const { return bid_reference_number_; }
void QuoteDeleteMessage::set_bid_reference_number(std::uint64_t value) { bid_reference_number_ = value; }

std::uint64_t QuoteDeleteMessage::ask_reference_number() const { return ask_reference_number_; }
void QuoteDeleteMessage::set_ask_reference_number(std::uint64_t value) { ask_reference_number_ = value; }

SequencedMessageCode QuoteDeleteMessage::type() const { return message_type; }

std::string_view QuoteDeleteMessage::name() const { return "Quote Delete Message"; }

std::size_t QuoteDeleteMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("QuoteDeleteMessage", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    bid_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    ask_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t QuoteDeleteMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("QuoteDeleteMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(bid_reference_number_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(ask_reference_number_));
    offset += 8;

    return offset;
}

std::size_t QuoteDeleteMessage::encoded_size() const {
    return wire_size;
}

void QuoteDeleteMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> QuoteDeleteMessage::clone() const {
    return std::make_unique<QuoteDeleteMessage>(*this);
}

void QuoteDeleteMessage::print(std::ostream& out) const {
    out << "QuoteDeleteMessage{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", bid_reference_number=";
    out << bid_reference_number_;
    out << ", ask_reference_number=";
    out << ask_reference_number_;
    out << '}';
}

bool QuoteDeleteMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const QuoteDeleteMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool QuoteDeleteMessage::operator==(const QuoteDeleteMessage& other) const {
    return tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && bid_reference_number_ == other.bid_reference_number_
        && ask_reference_number_ == other.ask_reference_number_;
}

bool QuoteDeleteMessage::operator!=(const QuoteDeleteMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
