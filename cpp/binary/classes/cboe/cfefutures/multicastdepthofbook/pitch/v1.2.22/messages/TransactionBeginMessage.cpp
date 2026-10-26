#include "TransactionBeginMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

TransactionBeginMessage::TransactionBeginMessage(std::chrono::nanoseconds time_offset)
  : time_offset_(time_offset) {}

std::chrono::nanoseconds TransactionBeginMessage::time_offset() const { return time_offset_; }
void TransactionBeginMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

MessageCode TransactionBeginMessage::type() const { return message_type; }

std::string_view TransactionBeginMessage::name() const { return "Transaction Begin Message"; }

std::size_t TransactionBeginMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TransactionBeginMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    return offset;
}

std::size_t TransactionBeginMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TransactionBeginMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    return offset;
}

std::size_t TransactionBeginMessage::encoded_size() const {
    return wire_size;
}

void TransactionBeginMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TransactionBeginMessage::clone() const {
    return std::make_unique<TransactionBeginMessage>(*this);
}

void TransactionBeginMessage::print(std::ostream& out) const {
    out << "TransactionBeginMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << '}';
}

bool TransactionBeginMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TransactionBeginMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TransactionBeginMessage::operator==(const TransactionBeginMessage& other) const {
    return time_offset_ == other.time_offset_;
}

bool TransactionBeginMessage::operator!=(const TransactionBeginMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
