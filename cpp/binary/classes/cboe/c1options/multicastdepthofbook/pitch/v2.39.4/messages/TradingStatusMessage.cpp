#include "TradingStatusMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

TradingStatusMessage::TradingStatusMessage(std::chrono::nanoseconds time_offset, const std::string& expanded_symbol, TradingStatus trading_status, RegShoAction reg_sho_action, const std::array<std::byte, 1>& reserved_1, const std::array<std::byte, 1>& second_reserved_1)
  : time_offset_(time_offset), expanded_symbol_(expanded_symbol), trading_status_(trading_status), reg_sho_action_(reg_sho_action), reserved_1_(reserved_1), second_reserved_1_(second_reserved_1) {}

std::chrono::nanoseconds TradingStatusMessage::time_offset() const { return time_offset_; }
void TradingStatusMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

const std::string& TradingStatusMessage::expanded_symbol() const { return expanded_symbol_; }
std::string& TradingStatusMessage::expanded_symbol() { return expanded_symbol_; }
void TradingStatusMessage::set_expanded_symbol(const std::string& value) { expanded_symbol_ = value; }

TradingStatus TradingStatusMessage::trading_status() const { return trading_status_; }
void TradingStatusMessage::set_trading_status(TradingStatus value) { trading_status_ = value; }

RegShoAction TradingStatusMessage::reg_sho_action() const { return reg_sho_action_; }
void TradingStatusMessage::set_reg_sho_action(RegShoAction value) { reg_sho_action_ = value; }

const std::array<std::byte, 1>& TradingStatusMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& TradingStatusMessage::reserved_1() { return reserved_1_; }
void TradingStatusMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

const std::array<std::byte, 1>& TradingStatusMessage::second_reserved_1() const { return second_reserved_1_; }
std::array<std::byte, 1>& TradingStatusMessage::second_reserved_1() { return second_reserved_1_; }
void TradingStatusMessage::set_second_reserved_1(const std::array<std::byte, 1>& value) { second_reserved_1_ = value; }

MessageCode TradingStatusMessage::type() const { return message_type; }

std::string_view TradingStatusMessage::name() const { return "Trading Status Message"; }

std::size_t TradingStatusMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradingStatusMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    expanded_symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    trading_status_ = static_cast<TradingStatus>(wire::read_char(data + offset));
    offset += 1;

    reg_sho_action_ = static_cast<RegShoAction>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    wire::read_bytes(data + offset, second_reserved_1_.data(), 1);
    offset += 1;

    return offset;
}

std::size_t TradingStatusMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradingStatusMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_text(data + offset, 8, ' ', expanded_symbol_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(trading_status_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(reg_sho_action_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    wire::write_bytes(data + offset, second_reserved_1_.data(), 1);
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
    out << ", expanded_symbol=";
    print::text(out, expanded_symbol_);
    out << ", trading_status=";
    out << trading_status_;
    out << ", reg_sho_action=";
    out << reg_sho_action_;
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
    out << ", second_reserved_1=";
    print::hex(out, second_reserved_1_.data(), second_reserved_1_.size());
    out << '}';
}

bool TradingStatusMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradingStatusMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradingStatusMessage::operator==(const TradingStatusMessage& other) const {
    return time_offset_ == other.time_offset_
        && expanded_symbol_ == other.expanded_symbol_
        && trading_status_ == other.trading_status_
        && reg_sho_action_ == other.reg_sho_action_
        && reserved_1_ == other.reserved_1_
        && second_reserved_1_ == other.second_reserved_1_;
}

bool TradingStatusMessage::operator!=(const TradingStatusMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
