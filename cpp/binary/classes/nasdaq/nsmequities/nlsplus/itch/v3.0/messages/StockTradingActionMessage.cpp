#include "StockTradingActionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

StockTradingActionMessage::StockTradingActionMessage(char reserved, const std::string& issue_symbol, SecurityClass security_class, CurrentTradingState current_trading_state, const std::string& reason)
  : reserved_(reserved), issue_symbol_(issue_symbol), security_class_(security_class), current_trading_state_(current_trading_state), reason_(reason) {}

char StockTradingActionMessage::reserved() const { return reserved_; }
void StockTradingActionMessage::set_reserved(char value) { reserved_ = value; }

const std::string& StockTradingActionMessage::issue_symbol() const { return issue_symbol_; }
std::string& StockTradingActionMessage::issue_symbol() { return issue_symbol_; }
void StockTradingActionMessage::set_issue_symbol(const std::string& value) { issue_symbol_ = value; }

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

    reserved_ = wire::read_char(data + offset);
    offset += 1;

    issue_symbol_ = wire::read_text(data + offset, 8, ' ');
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

    wire::write_char(data + offset, reserved_);
    offset += 1;

    wire::write_text(data + offset, 8, ' ', issue_symbol_);
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
    out << "reserved=";
    print::character(out, reserved_);
    out << ", issue_symbol=";
    print::text(out, issue_symbol_);
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
    return reserved_ == other.reserved_
        && issue_symbol_ == other.issue_symbol_
        && security_class_ == other.security_class_
        && current_trading_state_ == other.current_trading_state_
        && reason_ == other.reason_;
}

bool StockTradingActionMessage::operator!=(const StockTradingActionMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
