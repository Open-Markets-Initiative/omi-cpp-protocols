#include "PayloadTradingActionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

PayloadTradingActionMessage::PayloadTradingActionMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t option_id, CurrentTradingState current_trading_state)
  : nanoseconds_(nanoseconds), option_id_(option_id), current_trading_state_(current_trading_state) {}

std::chrono::nanoseconds PayloadTradingActionMessage::nanoseconds() const { return nanoseconds_; }
void PayloadTradingActionMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t PayloadTradingActionMessage::option_id() const { return option_id_; }
void PayloadTradingActionMessage::set_option_id(std::uint32_t value) { option_id_ = value; }

CurrentTradingState PayloadTradingActionMessage::current_trading_state() const { return current_trading_state_; }
void PayloadTradingActionMessage::set_current_trading_state(CurrentTradingState value) { current_trading_state_ = value; }

PacketMessageCode PayloadTradingActionMessage::type() const { return message_type; }

std::string_view PayloadTradingActionMessage::name() const { return "Trading Action Message"; }

std::size_t PayloadTradingActionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PayloadTradingActionMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    option_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    current_trading_state_ = static_cast<CurrentTradingState>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t PayloadTradingActionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PayloadTradingActionMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(option_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(current_trading_state_));
    offset += 1;

    return offset;
}

std::size_t PayloadTradingActionMessage::encoded_size() const {
    return wire_size;
}

void PayloadTradingActionMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> PayloadTradingActionMessage::clone() const {
    return std::make_unique<PayloadTradingActionMessage>(*this);
}

void PayloadTradingActionMessage::print(std::ostream& out) const {
    out << "PayloadTradingActionMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", option_id=";
    out << option_id_;
    out << ", current_trading_state=";
    out << current_trading_state_;
    out << '}';
}

bool PayloadTradingActionMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const PayloadTradingActionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PayloadTradingActionMessage::operator==(const PayloadTradingActionMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && option_id_ == other.option_id_
        && current_trading_state_ == other.current_trading_state_;
}

bool PayloadTradingActionMessage::operator!=(const PayloadTradingActionMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
