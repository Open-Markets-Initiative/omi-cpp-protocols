#include "TradingStateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

TradingStateMessage::TradingStateMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t orderbook_id, const std::string& group, TradingState trading_state)
  : nanoseconds_(nanoseconds), orderbook_id_(orderbook_id), group_(group), trading_state_(trading_state) {}

std::chrono::nanoseconds TradingStateMessage::nanoseconds() const { return nanoseconds_; }
void TradingStateMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t TradingStateMessage::orderbook_id() const { return orderbook_id_; }
void TradingStateMessage::set_orderbook_id(std::uint32_t value) { orderbook_id_ = value; }

const std::string& TradingStateMessage::group() const { return group_; }
std::string& TradingStateMessage::group() { return group_; }
void TradingStateMessage::set_group(const std::string& value) { group_ = value; }

TradingState TradingStateMessage::trading_state() const { return trading_state_; }
void TradingStateMessage::set_trading_state(TradingState value) { trading_state_ = value; }

SequencedMessageCode TradingStateMessage::type() const { return message_type; }

std::string_view TradingStateMessage::name() const { return "Trading State Message"; }

std::size_t TradingStateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradingStateMessage", wire_size, length);

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

std::size_t TradingStateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradingStateMessage", wire_size, capacity);

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

std::size_t TradingStateMessage::encoded_size() const {
    return wire_size;
}

void TradingStateMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> TradingStateMessage::clone() const {
    return std::make_unique<TradingStateMessage>(*this);
}

void TradingStateMessage::print(std::ostream& out) const {
    out << "TradingStateMessage{";
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

bool TradingStateMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const TradingStateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradingStateMessage::operator==(const TradingStateMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && orderbook_id_ == other.orderbook_id_
        && group_ == other.group_
        && trading_state_ == other.trading_state_;
}

bool TradingStateMessage::operator!=(const TradingStateMessage& other) const {
    return !(*this == other);
}

} // namespace jnx::jnxequities::pts::itch::v1_7
