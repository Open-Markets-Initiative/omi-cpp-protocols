#include "TimestampMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

TimestampMessage::TimestampMessage(std::chrono::seconds second)
  : second_(second) {}

std::chrono::seconds TimestampMessage::second() const { return second_; }
void TimestampMessage::set_second(std::chrono::seconds value) { second_ = value; }

SequencedMessageCode TimestampMessage::type() const { return message_type; }

std::string_view TimestampMessage::name() const { return "Timestamp Message"; }

std::size_t TimestampMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TimestampMessage", wire_size, length);

    second_ = std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    return offset;
}

std::size_t TimestampMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TimestampMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(second_.count()));
    offset += 4;

    return offset;
}

std::size_t TimestampMessage::encoded_size() const {
    return wire_size;
}

void TimestampMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> TimestampMessage::clone() const {
    return std::make_unique<TimestampMessage>(*this);
}

void TimestampMessage::print(std::ostream& out) const {
    out << "TimestampMessage{";
    out << "second=";
    out << second_.count();
    out << '}';
}

bool TimestampMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const TimestampMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TimestampMessage::operator==(const TimestampMessage& other) const {
    return second_ == other.second_;
}

bool TimestampMessage::operator!=(const TimestampMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
