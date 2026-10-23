#include "StockTradingActionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

StockTradingActionMessage::StockTradingActionMessage(std::uint16_t tracking_number, std::chrono::nanoseconds time_stamp, const std::string& stock, SecurityClass security_class, CurrentTradingState current_trading_state, const std::string& reason)
  : tracking_number_(tracking_number), time_stamp_(time_stamp), stock_(stock), security_class_(security_class), current_trading_state_(current_trading_state), reason_(reason) {}

std::uint16_t StockTradingActionMessage::tracking_number() const { return tracking_number_; }
void StockTradingActionMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds StockTradingActionMessage::time_stamp() const { return time_stamp_; }
void StockTradingActionMessage::set_time_stamp(std::chrono::nanoseconds value) { time_stamp_ = value; }

const std::string& StockTradingActionMessage::stock() const { return stock_; }
std::string& StockTradingActionMessage::stock() { return stock_; }
void StockTradingActionMessage::set_stock(const std::string& value) { stock_ = value; }

SecurityClass StockTradingActionMessage::security_class() const { return security_class_; }
void StockTradingActionMessage::set_security_class(SecurityClass value) { security_class_ = value; }

CurrentTradingState StockTradingActionMessage::current_trading_state() const { return current_trading_state_; }
void StockTradingActionMessage::set_current_trading_state(CurrentTradingState value) { current_trading_state_ = value; }

const std::string& StockTradingActionMessage::reason() const { return reason_; }
std::string& StockTradingActionMessage::reason() { return reason_; }
void StockTradingActionMessage::set_reason(const std::string& value) { reason_ = value; }

MessageCode StockTradingActionMessage::type() const { return message_type; }

std::string_view StockTradingActionMessage::name() const { return "Stock Trading Action Message"; }

std::size_t StockTradingActionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("StockTradingActionMessage", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    time_stamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    stock_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    security_class_ = static_cast<SecurityClass>(wire::read_char(data + offset));
    offset += 1;

    current_trading_state_ = static_cast<CurrentTradingState>(wire::read_char(data + offset));
    offset += 1;

    reason_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    return offset;
}

std::size_t StockTradingActionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("StockTradingActionMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(time_stamp_.count()));
    offset += 6;

    wire::write_text(data + offset, 8, ' ', stock_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(security_class_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(current_trading_state_));
    offset += 1;

    wire::write_text(data + offset, 4, ' ', reason_);
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
    out << "tracking_number=";
    out << tracking_number_;
    out << ", time_stamp=";
    out << time_stamp_.count();
    out << ", stock=";
    print::text(out, stock_);
    out << ", security_class=";
    out << security_class_;
    out << ", current_trading_state=";
    out << current_trading_state_;
    out << ", reason=";
    print::text(out, reason_);
    out << '}';
}

bool StockTradingActionMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const StockTradingActionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool StockTradingActionMessage::operator==(const StockTradingActionMessage& other) const {
    return tracking_number_ == other.tracking_number_
        && time_stamp_ == other.time_stamp_
        && stock_ == other.stock_
        && security_class_ == other.security_class_
        && current_trading_state_ == other.current_trading_state_
        && reason_ == other.reason_;
}

bool StockTradingActionMessage::operator!=(const StockTradingActionMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
