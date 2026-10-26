#include "TransactionEndMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

TransactionEndMessage::TransactionEndMessage(std::chrono::nanoseconds time_offset)
  : time_offset_(time_offset) {}

std::chrono::nanoseconds TransactionEndMessage::time_offset() const { return time_offset_; }
void TransactionEndMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

MessageCode TransactionEndMessage::type() const { return message_type; }

std::string_view TransactionEndMessage::name() const { return "Transaction End Message"; }

std::size_t TransactionEndMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TransactionEndMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    return offset;
}

std::size_t TransactionEndMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TransactionEndMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    return offset;
}

std::size_t TransactionEndMessage::encoded_size() const {
    return wire_size;
}

void TransactionEndMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TransactionEndMessage::clone() const {
    return std::make_unique<TransactionEndMessage>(*this);
}

void TransactionEndMessage::print(std::ostream& out) const {
    out << "TransactionEndMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << '}';
}

bool TransactionEndMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TransactionEndMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TransactionEndMessage::operator==(const TransactionEndMessage& other) const {
    return time_offset_ == other.time_offset_;
}

bool TransactionEndMessage::operator!=(const TransactionEndMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
