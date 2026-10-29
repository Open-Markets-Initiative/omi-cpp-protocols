#include "UdpPayloadTradingStateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

UdpPayloadTradingStateMessage::UdpPayloadTradingStateMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t orderbook_id, const std::string& group, TradingState trading_state)
  : nanoseconds_(nanoseconds), orderbook_id_(orderbook_id), group_(group), trading_state_(trading_state) {}

std::chrono::nanoseconds UdpPayloadTradingStateMessage::nanoseconds() const { return nanoseconds_; }
void UdpPayloadTradingStateMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t UdpPayloadTradingStateMessage::orderbook_id() const { return orderbook_id_; }
void UdpPayloadTradingStateMessage::set_orderbook_id(std::uint32_t value) { orderbook_id_ = value; }

const std::string& UdpPayloadTradingStateMessage::group() const { return group_; }
std::string& UdpPayloadTradingStateMessage::group() { return group_; }
void UdpPayloadTradingStateMessage::set_group(const std::string& value) { group_ = value; }

TradingState UdpPayloadTradingStateMessage::trading_state() const { return trading_state_; }
void UdpPayloadTradingStateMessage::set_trading_state(TradingState value) { trading_state_ = value; }

PacketMessageCode UdpPayloadTradingStateMessage::type() const { return message_type; }

std::string_view UdpPayloadTradingStateMessage::name() const { return "Trading State Message"; }

std::size_t UdpPayloadTradingStateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UdpPayloadTradingStateMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    orderbook_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    group_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    trading_state_ = static_cast<TradingState>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t UdpPayloadTradingStateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UdpPayloadTradingStateMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(orderbook_id_));
    offset += 4;

    wire::write_text(data + offset, 4, ' ', group_);
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(trading_state_));
    offset += 1;

    return offset;
}

std::size_t UdpPayloadTradingStateMessage::encoded_size() const {
    return wire_size;
}

void UdpPayloadTradingStateMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> UdpPayloadTradingStateMessage::clone() const {
    return std::make_unique<UdpPayloadTradingStateMessage>(*this);
}

void UdpPayloadTradingStateMessage::print(std::ostream& out) const {
    out << "UdpPayloadTradingStateMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", orderbook_id=";
    out << orderbook_id_;
    out << ", group=";
    print::text(out, group_);
    out << ", trading_state=";
    out << trading_state_;
    out << '}';
}

bool UdpPayloadTradingStateMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const UdpPayloadTradingStateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UdpPayloadTradingStateMessage::operator==(const UdpPayloadTradingStateMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && orderbook_id_ == other.orderbook_id_
        && group_ == other.group_
        && trading_state_ == other.trading_state_;
}

bool UdpPayloadTradingStateMessage::operator!=(const UdpPayloadTradingStateMessage& other) const {
    return !(*this == other);
}

} // namespace jnx::jnxequities::pts::itch::v1_7
