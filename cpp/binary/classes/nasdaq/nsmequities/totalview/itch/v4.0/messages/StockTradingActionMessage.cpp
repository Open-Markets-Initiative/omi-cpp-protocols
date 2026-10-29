#include "StockTradingActionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

StockTradingActionMessage::StockTradingActionMessage(std::chrono::nanoseconds nanoseconds, const std::string& stock, TradingState trading_state, char reserved, const std::string& reason)
  : nanoseconds_(nanoseconds), stock_(stock), trading_state_(trading_state), reserved_(reserved), reason_(reason) {}

std::chrono::nanoseconds StockTradingActionMessage::nanoseconds() const { return nanoseconds_; }
void StockTradingActionMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

const std::string& StockTradingActionMessage::stock() const { return stock_; }
std::string& StockTradingActionMessage::stock() { return stock_; }
void StockTradingActionMessage::set_stock(const std::string& value) { stock_ = value; }

TradingState StockTradingActionMessage::trading_state() const { return trading_state_; }
void StockTradingActionMessage::set_trading_state(TradingState value) { trading_state_ = value; }

char StockTradingActionMessage::reserved() const { return reserved_; }
void StockTradingActionMessage::set_reserved(char value) { reserved_ = value; }

const std::string& StockTradingActionMessage::reason() const { return reason_; }
std::string& StockTradingActionMessage::reason() { return reason_; }
void StockTradingActionMessage::set_reason(const std::string& value) { reason_ = value; }

SequencedMessageCode StockTradingActionMessage::type() const { return message_type; }

std::string_view StockTradingActionMessage::name() const { return "Stock Trading Action Message"; }

std::size_t StockTradingActionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("StockTradingActionMessage", wire_size, length);

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

std::size_t StockTradingActionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("StockTradingActionMessage", wire_size, capacity);

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

std::size_t StockTradingActionMessage::encoded_size() const {
    return wire_size;
}

void StockTradingActionMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> StockTradingActionMessage::clone() const {
    return std::make_unique<StockTradingActionMessage>(*this);
}

void StockTradingActionMessage::print(std::ostream& out) const {
    out << "StockTradingActionMessage{";
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

bool StockTradingActionMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const StockTradingActionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool StockTradingActionMessage::operator==(const StockTradingActionMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && stock_ == other.stock_
        && trading_state_ == other.trading_state_
        && reserved_ == other.reserved_
        && reason_ == other.reason_;
}

bool StockTradingActionMessage::operator!=(const StockTradingActionMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
