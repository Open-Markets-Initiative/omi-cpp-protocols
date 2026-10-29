#include "PayloadStockTradingActionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

PayloadStockTradingActionMessage::PayloadStockTradingActionMessage(std::chrono::nanoseconds nanoseconds, const std::string& stock, TradingState trading_state, char reserved, const std::string& reason)
  : nanoseconds_(nanoseconds), stock_(stock), trading_state_(trading_state), reserved_(reserved), reason_(reason) {}

std::chrono::nanoseconds PayloadStockTradingActionMessage::nanoseconds() const { return nanoseconds_; }
void PayloadStockTradingActionMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

const std::string& PayloadStockTradingActionMessage::stock() const { return stock_; }
std::string& PayloadStockTradingActionMessage::stock() { return stock_; }
void PayloadStockTradingActionMessage::set_stock(const std::string& value) { stock_ = value; }

TradingState PayloadStockTradingActionMessage::trading_state() const { return trading_state_; }
void PayloadStockTradingActionMessage::set_trading_state(TradingState value) { trading_state_ = value; }

char PayloadStockTradingActionMessage::reserved() const { return reserved_; }
void PayloadStockTradingActionMessage::set_reserved(char value) { reserved_ = value; }

const std::string& PayloadStockTradingActionMessage::reason() const { return reason_; }
std::string& PayloadStockTradingActionMessage::reason() { return reason_; }
void PayloadStockTradingActionMessage::set_reason(const std::string& value) { reason_ = value; }

PacketMessageCode PayloadStockTradingActionMessage::type() const { return message_type; }

std::string_view PayloadStockTradingActionMessage::name() const { return "Stock Trading Action Message"; }

std::size_t PayloadStockTradingActionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PayloadStockTradingActionMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    stock_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    trading_state_ = static_cast<TradingState>(wire::read_char(data + offset));
    offset += 1;

    reserved_ = wire::read_char(data + offset);
    offset += 1;

    reason_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    return offset;
}

std::size_t PayloadStockTradingActionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PayloadStockTradingActionMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_text(data + offset, 6, ' ', stock_);
    offset += 6;

    wire::write_char(data + offset, static_cast<char>(trading_state_));
    offset += 1;

    wire::write_char(data + offset, reserved_);
    offset += 1;

    wire::write_text(data + offset, 4, ' ', reason_);
    offset += 4;

    return offset;
}

std::size_t PayloadStockTradingActionMessage::encoded_size() const {
    return wire_size;
}

void PayloadStockTradingActionMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> PayloadStockTradingActionMessage::clone() const {
    return std::make_unique<PayloadStockTradingActionMessage>(*this);
}

void PayloadStockTradingActionMessage::print(std::ostream& out) const {
    out << "PayloadStockTradingActionMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", stock=";
    print::text(out, stock_);
    out << ", trading_state=";
    out << trading_state_;
    out << ", reserved=";
    print::character(out, reserved_);
    out << ", reason=";
    print::text(out, reason_);
    out << '}';
}

bool PayloadStockTradingActionMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const PayloadStockTradingActionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PayloadStockTradingActionMessage::operator==(const PayloadStockTradingActionMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && stock_ == other.stock_
        && trading_state_ == other.trading_state_
        && reserved_ == other.reserved_
        && reason_ == other.reason_;
}

bool PayloadStockTradingActionMessage::operator!=(const PayloadStockTradingActionMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
