#include "PayloadOrderExecutedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

PayloadOrderExecutedMessage::PayloadOrderExecutedMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t order_reference_number, std::uint32_t executed_shares, std::uint64_t match_number)
  : nanoseconds_(nanoseconds), order_reference_number_(order_reference_number), executed_shares_(executed_shares), match_number_(match_number) {}

std::chrono::nanoseconds PayloadOrderExecutedMessage::nanoseconds() const { return nanoseconds_; }
void PayloadOrderExecutedMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint64_t PayloadOrderExecutedMessage::order_reference_number() const { return order_reference_number_; }
void PayloadOrderExecutedMessage::set_order_reference_number(std::uint64_t value) { order_reference_number_ = value; }

std::uint32_t PayloadOrderExecutedMessage::executed_shares() const { return executed_shares_; }
void PayloadOrderExecutedMessage::set_executed_shares(std::uint32_t value) { executed_shares_ = value; }

std::uint64_t PayloadOrderExecutedMessage::match_number() const { return match_number_; }
void PayloadOrderExecutedMessage::set_match_number(std::uint64_t value) { match_number_ = value; }

PacketMessageCode PayloadOrderExecutedMessage::type() const { return message_type; }

std::string_view PayloadOrderExecutedMessage::name() const { return "Order Executed Message"; }

std::size_t PayloadOrderExecutedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PayloadOrderExecutedMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    order_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    executed_shares_ = wire::read_u32_be(data + offset);
    offset += 4;

    match_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t PayloadOrderExecutedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PayloadOrderExecutedMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_reference_number_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(executed_shares_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(match_number_));
    offset += 8;

    return offset;
}

std::size_t PayloadOrderExecutedMessage::encoded_size() const {
    return wire_size;
}

void PayloadOrderExecutedMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> PayloadOrderExecutedMessage::clone() const {
    return std::make_unique<PayloadOrderExecutedMessage>(*this);
}

void PayloadOrderExecutedMessage::print(std::ostream& out) const {
    out << "PayloadOrderExecutedMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", order_reference_number=";
    out << order_reference_number_;
    out << ", executed_shares=";
    out << executed_shares_;
    out << ", match_number=";
    out << match_number_;
    out << '}';
}

bool PayloadOrderExecutedMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const PayloadOrderExecutedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PayloadOrderExecutedMessage::operator==(const PayloadOrderExecutedMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && order_reference_number_ == other.order_reference_number_
        && executed_shares_ == other.executed_shares_
        && match_number_ == other.match_number_;
}

bool PayloadOrderExecutedMessage::operator!=(const PayloadOrderExecutedMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
