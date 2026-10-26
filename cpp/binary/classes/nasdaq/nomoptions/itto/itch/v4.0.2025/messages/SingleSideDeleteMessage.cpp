#include "SingleSideDeleteMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

SingleSideDeleteMessage::SingleSideDeleteMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t reference_number)
  : tracking_number_(tracking_number), timestamp_(timestamp), reference_number_(reference_number) {}

std::uint16_t SingleSideDeleteMessage::tracking_number() const { return tracking_number_; }
void SingleSideDeleteMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds SingleSideDeleteMessage::timestamp() const { return timestamp_; }
void SingleSideDeleteMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t SingleSideDeleteMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint64_t SingleSideDeleteMessage::reference_number() const { return reference_number_; }
void SingleSideDeleteMessage::set_reference_number(std::uint64_t value) { reference_number_ = value; }

SequencedMessageCode SingleSideDeleteMessage::type() const { return message_type; }

std::string_view SingleSideDeleteMessage::name() const { return "Single Side Delete Message"; }

std::size_t SingleSideDeleteMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SingleSideDeleteMessage", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t SingleSideDeleteMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SingleSideDeleteMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(reference_number_));
    offset += 8;

    return offset;
}

std::size_t SingleSideDeleteMessage::encoded_size() const {
    return wire_size;
}

void SingleSideDeleteMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> SingleSideDeleteMessage::clone() const {
    return std::make_unique<SingleSideDeleteMessage>(*this);
}

void SingleSideDeleteMessage::print(std::ostream& out) const {
    out << "SingleSideDeleteMessage{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    calendar::print(out, timestamp_.count(), 1, "America/New_York");
    out << ", reference_number=";
    out << reference_number_;
    out << '}';
}

bool SingleSideDeleteMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const SingleSideDeleteMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SingleSideDeleteMessage::operator==(const SingleSideDeleteMessage& other) const {
    return tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && reference_number_ == other.reference_number_;
}

bool SingleSideDeleteMessage::operator!=(const SingleSideDeleteMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
