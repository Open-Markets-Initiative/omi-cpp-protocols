#include "TradingStatusMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

TradingStatusMessage::TradingStatusMessage(std::chrono::nanoseconds time_offset, const std::string& symbol, const std::string& reserved_2, TradingStatus trading_status, const std::string& reserved_3)
  : time_offset_(time_offset), symbol_(symbol), reserved_2_(reserved_2), trading_status_(trading_status), reserved_3_(reserved_3) {}

std::chrono::nanoseconds TradingStatusMessage::time_offset() const { return time_offset_; }
void TradingStatusMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

const std::string& TradingStatusMessage::symbol() const { return symbol_; }
std::string& TradingStatusMessage::symbol() { return symbol_; }
void TradingStatusMessage::set_symbol(const std::string& value) { symbol_ = value; }

const std::string& TradingStatusMessage::reserved_2() const { return reserved_2_; }
std::string& TradingStatusMessage::reserved_2() { return reserved_2_; }
void TradingStatusMessage::set_reserved_2(const std::string& value) { reserved_2_ = value; }

TradingStatus TradingStatusMessage::trading_status() const { return trading_status_; }
void TradingStatusMessage::set_trading_status(TradingStatus value) { trading_status_ = value; }

const std::string& TradingStatusMessage::reserved_3() const { return reserved_3_; }
std::string& TradingStatusMessage::reserved_3() { return reserved_3_; }
void TradingStatusMessage::set_reserved_3(const std::string& value) { reserved_3_ = value; }

MessageCode TradingStatusMessage::type() const { return message_type; }

std::string_view TradingStatusMessage::name() const { return "Trading Status Message"; }

std::size_t TradingStatusMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradingStatusMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    symbol_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    reserved_2_ = wire::read_text(data + offset, 2, ' ');
    offset += 2;

    trading_status_ = static_cast<TradingStatus>(wire::read_char(data + offset));
    offset += 1;

    reserved_3_ = wire::read_text(data + offset, 3, ' ');
    offset += 3;

    return offset;
}

std::size_t TradingStatusMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradingStatusMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_text(data + offset, 6, ' ', symbol_);
    offset += 6;

    wire::write_text(data + offset, 2, ' ', reserved_2_);
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(trading_status_));
    offset += 1;

    wire::write_text(data + offset, 3, ' ', reserved_3_);
    offset += 3;

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
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", reserved_2=";
    print::text(out, reserved_2_);
    out << ", trading_status=";
    out << trading_status_;
    out << ", reserved_3=";
    print::text(out, reserved_3_);
    out << '}';
}

bool TradingStatusMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradingStatusMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradingStatusMessage::operator==(const TradingStatusMessage& other) const {
    return time_offset_ == other.time_offset_
        && symbol_ == other.symbol_
        && reserved_2_ == other.reserved_2_
        && trading_status_ == other.trading_status_
        && reserved_3_ == other.reserved_3_;
}

bool TradingStatusMessage::operator!=(const TradingStatusMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
