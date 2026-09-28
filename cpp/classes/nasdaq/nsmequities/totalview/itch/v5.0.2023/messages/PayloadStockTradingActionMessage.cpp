#include "PayloadStockTradingActionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

PayloadStockTradingActionMessage::PayloadStockTradingActionMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, const std::string& stock, TradingState trading_state, char reserved, const std::string& reason_code)
  : stock_locate_(stock_locate), tracking_number_(tracking_number), timestamp_(timestamp), stock_(stock), trading_state_(trading_state), reserved_(reserved), reason_code_(reason_code) {}

std::uint16_t PayloadStockTradingActionMessage::stock_locate() const { return stock_locate_; }
void PayloadStockTradingActionMessage::set_stock_locate(std::uint16_t value) { stock_locate_ = value; }

std::uint16_t PayloadStockTradingActionMessage::tracking_number() const { return tracking_number_; }
void PayloadStockTradingActionMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds PayloadStockTradingActionMessage::timestamp() const { return timestamp_; }
void PayloadStockTradingActionMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

const std::string& PayloadStockTradingActionMessage::stock() const { return stock_; }
std::string& PayloadStockTradingActionMessage::stock() { return stock_; }
void PayloadStockTradingActionMessage::set_stock(const std::string& value) { stock_ = value; }

TradingState PayloadStockTradingActionMessage::trading_state() const { return trading_state_; }
void PayloadStockTradingActionMessage::set_trading_state(TradingState value) { trading_state_ = value; }

char PayloadStockTradingActionMessage::reserved() const { return reserved_; }
void PayloadStockTradingActionMessage::set_reserved(char value) { reserved_ = value; }

const std::string& PayloadStockTradingActionMessage::reason_code() const { return reason_code_; }
std::string& PayloadStockTradingActionMessage::reason_code() { return reason_code_; }
void PayloadStockTradingActionMessage::set_reason_code(const std::string& value) { reason_code_ = value; }

PacketMessageCode PayloadStockTradingActionMessage::type() const { return message_type; }

std::string_view PayloadStockTradingActionMessage::name() const { return "Stock Trading Action Message"; }

std::size_t PayloadStockTradingActionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PayloadStockTradingActionMessage", wire_size, length);

    stock_locate_ = wire::read_u16_be(data + offset);
    offset += 2;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    stock_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    trading_state_ = static_cast<TradingState>(wire::read_char(data + offset));
    offset += 1;

    reserved_ = wire::read_char(data + offset);
    offset += 1;

    reason_code_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    return offset;
}

std::size_t PayloadStockTradingActionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PayloadStockTradingActionMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(stock_locate_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_text(data + offset, 8, ' ', stock_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(trading_state_));
    offset += 1;

    wire::write_char(data + offset, reserved_);
    offset += 1;

    wire::write_text(data + offset, 4, ' ', reason_code_);
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
    out << "stock_locate=";
    out << stock_locate_;
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", stock=";
    print::text(out, stock_);
    out << ", trading_state=";
    out << trading_state_;
    out << ", reserved=";
    print::character(out, reserved_);
    out << ", reason_code=";
    print::text(out, reason_code_);
    out << '}';
}

bool PayloadStockTradingActionMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const PayloadStockTradingActionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PayloadStockTradingActionMessage::operator==(const PayloadStockTradingActionMessage& other) const {
    return stock_locate_ == other.stock_locate_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && stock_ == other.stock_
        && trading_state_ == other.trading_state_
        && reserved_ == other.reserved_
        && reason_code_ == other.reason_code_;
}

bool PayloadStockTradingActionMessage::operator!=(const PayloadStockTradingActionMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
