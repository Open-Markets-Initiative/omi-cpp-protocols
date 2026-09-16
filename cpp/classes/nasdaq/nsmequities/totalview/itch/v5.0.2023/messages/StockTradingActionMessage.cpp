#include "StockTradingActionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

StockTradingActionMessage::StockTradingActionMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, const std::string& stock, TradingState trading_state, char reserved, const std::string& reason_code)
  : stock_locate_(stock_locate), tracking_number_(tracking_number), timestamp_(timestamp), stock_(stock), trading_state_(trading_state), reserved_(reserved), reason_code_(reason_code) {}

std::uint16_t StockTradingActionMessage::stock_locate() const { return stock_locate_; }
void StockTradingActionMessage::set_stock_locate(std::uint16_t value) { stock_locate_ = value; }

std::uint16_t StockTradingActionMessage::tracking_number() const { return tracking_number_; }
void StockTradingActionMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds StockTradingActionMessage::timestamp() const { return timestamp_; }
void StockTradingActionMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

const std::string& StockTradingActionMessage::stock() const { return stock_; }
std::string& StockTradingActionMessage::stock() { return stock_; }
void StockTradingActionMessage::set_stock(const std::string& value) { stock_ = value; }

TradingState StockTradingActionMessage::trading_state() const { return trading_state_; }
void StockTradingActionMessage::set_trading_state(TradingState value) { trading_state_ = value; }

char StockTradingActionMessage::reserved() const { return reserved_; }
void StockTradingActionMessage::set_reserved(char value) { reserved_ = value; }

const std::string& StockTradingActionMessage::reason_code() const { return reason_code_; }
std::string& StockTradingActionMessage::reason_code() { return reason_code_; }
void StockTradingActionMessage::set_reason_code(const std::string& value) { reason_code_ = value; }

MessageCode StockTradingActionMessage::type() const { return message_type; }

std::string_view StockTradingActionMessage::name() const { return "Stock Trading Action Message"; }

std::size_t StockTradingActionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("StockTradingActionMessage", wire_size, length);

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

std::size_t StockTradingActionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("StockTradingActionMessage", wire_size, capacity);

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

std::size_t StockTradingActionMessage::encoded_size() const {
    return wire_size;
}

void StockTradingActionMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> StockTradingActionMessage::clone() const {
    return std::make_unique<StockTradingActionMessage>(*this);
}

void StockTradingActionMessage::print(std::ostream& out) const {
    out << "StockTradingActionMessage{";
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

bool StockTradingActionMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const StockTradingActionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool StockTradingActionMessage::operator==(const StockTradingActionMessage& other) const {
    return stock_locate_ == other.stock_locate_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && stock_ == other.stock_
        && trading_state_ == other.trading_state_
        && reserved_ == other.reserved_
        && reason_code_ == other.reason_code_;
}

bool StockTradingActionMessage::operator!=(const StockTradingActionMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
