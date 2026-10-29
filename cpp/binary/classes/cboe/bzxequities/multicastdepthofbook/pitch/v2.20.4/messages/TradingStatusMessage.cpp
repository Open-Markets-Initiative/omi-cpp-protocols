#include "TradingStatusMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

TradingStatusMessage::TradingStatusMessage(std::chrono::nanoseconds time_offset, const std::string& symbol_long, TradingStatus trading_status, RegShoAction reg_sho_action, char reserved_1, char second_reserved_1)
  : time_offset_(time_offset), symbol_long_(symbol_long), trading_status_(trading_status), reg_sho_action_(reg_sho_action), reserved_1_(reserved_1), second_reserved_1_(second_reserved_1) {}

std::chrono::nanoseconds TradingStatusMessage::time_offset() const { return time_offset_; }
void TradingStatusMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

const std::string& TradingStatusMessage::symbol_long() const { return symbol_long_; }
std::string& TradingStatusMessage::symbol_long() { return symbol_long_; }
void TradingStatusMessage::set_symbol_long(const std::string& value) { symbol_long_ = value; }

TradingStatus TradingStatusMessage::trading_status() const { return trading_status_; }
void TradingStatusMessage::set_trading_status(TradingStatus value) { trading_status_ = value; }

RegShoAction TradingStatusMessage::reg_sho_action() const { return reg_sho_action_; }
void TradingStatusMessage::set_reg_sho_action(RegShoAction value) { reg_sho_action_ = value; }

char TradingStatusMessage::reserved_1() const { return reserved_1_; }
void TradingStatusMessage::set_reserved_1(char value) { reserved_1_ = value; }

char TradingStatusMessage::second_reserved_1() const { return second_reserved_1_; }
void TradingStatusMessage::set_second_reserved_1(char value) { second_reserved_1_ = value; }

MessageCode TradingStatusMessage::type() const { return message_type; }

std::string_view TradingStatusMessage::name() const { return "Trading Status Message"; }

std::size_t TradingStatusMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradingStatusMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    symbol_long_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    trading_status_ = static_cast<TradingStatus>(wire::read_char(data + offset));
    offset += 1;

    reg_sho_action_ = static_cast<RegShoAction>(wire::read_char(data + offset));
    offset += 1;

    reserved_1_ = wire::read_char(data + offset);
    offset += 1;

    second_reserved_1_ = wire::read_char(data + offset);
    offset += 1;

    return offset;
}

std::size_t TradingStatusMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradingStatusMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_text(data + offset, 8, ' ', symbol_long_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(trading_status_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(reg_sho_action_));
    offset += 1;

    wire::write_char(data + offset, reserved_1_);
    offset += 1;

    wire::write_char(data + offset, second_reserved_1_);
    offset += 1;

    return offset;
}

std::size_t TradingStatusMessage::encoded_size() const {
    return wire_size;
}

void TradingStatusMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradingStatusMessage::clone() const {
    return std::make_unique<TradingStatusMessage>(*this);
}

void TradingStatusMessage::print(std::ostream& out) const {
    out << "TradingStatusMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << ", symbol_long=";
    print::text(out, symbol_long_);
    out << ", trading_status=";
    out << trading_status_;
    out << ", reg_sho_action=";
    out << reg_sho_action_;
    out << ", reserved_1=";
    print::character(out, reserved_1_);
    out << ", second_reserved_1=";
    print::character(out, second_reserved_1_);
    out << '}';
}

bool TradingStatusMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradingStatusMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradingStatusMessage::operator==(const TradingStatusMessage& other) const {
    return time_offset_ == other.time_offset_
        && symbol_long_ == other.symbol_long_
        && trading_status_ == other.trading_status_
        && reg_sho_action_ == other.reg_sho_action_
        && reserved_1_ == other.reserved_1_
        && second_reserved_1_ == other.second_reserved_1_;
}

bool TradingStatusMessage::operator!=(const TradingStatusMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
