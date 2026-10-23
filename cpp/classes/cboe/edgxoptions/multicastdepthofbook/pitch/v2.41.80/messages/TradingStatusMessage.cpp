#include "TradingStatusMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

TradingStatusMessage::TradingStatusMessage(std::chrono::nanoseconds time_offset, const std::string& symbol, const std::array<std::byte, 2>& reserved_2, TradingStatus trading_status, const std::array<std::byte, 1>& reserved_1, GthTradingStatus gth_trading_status, const std::array<std::byte, 1>& second_reserved_1)
  : time_offset_(time_offset), symbol_(symbol), reserved_2_(reserved_2), trading_status_(trading_status), reserved_1_(reserved_1), gth_trading_status_(gth_trading_status), second_reserved_1_(second_reserved_1) {}

std::chrono::nanoseconds TradingStatusMessage::time_offset() const { return time_offset_; }
void TradingStatusMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

const std::string& TradingStatusMessage::symbol() const { return symbol_; }
std::string& TradingStatusMessage::symbol() { return symbol_; }
void TradingStatusMessage::set_symbol(const std::string& value) { symbol_ = value; }

const std::array<std::byte, 2>& TradingStatusMessage::reserved_2() const { return reserved_2_; }
std::array<std::byte, 2>& TradingStatusMessage::reserved_2() { return reserved_2_; }
void TradingStatusMessage::set_reserved_2(const std::array<std::byte, 2>& value) { reserved_2_ = value; }

TradingStatus TradingStatusMessage::trading_status() const { return trading_status_; }
void TradingStatusMessage::set_trading_status(TradingStatus value) { trading_status_ = value; }

const std::array<std::byte, 1>& TradingStatusMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& TradingStatusMessage::reserved_1() { return reserved_1_; }
void TradingStatusMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

GthTradingStatus TradingStatusMessage::gth_trading_status() const { return gth_trading_status_; }
void TradingStatusMessage::set_gth_trading_status(GthTradingStatus value) { gth_trading_status_ = value; }

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

    symbol_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    wire::read_bytes(data + offset, reserved_2_.data(), 2);
    offset += 2;

    trading_status_ = static_cast<TradingStatus>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    gth_trading_status_ = static_cast<GthTradingStatus>(wire::read_char(data + offset));
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

    wire::write_text(data + offset, 6, ' ', symbol_);
    offset += 6;

    wire::write_bytes(data + offset, reserved_2_.data(), 2);
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(trading_status_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(gth_trading_status_));
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
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", reserved_2=";
    print::hex(out, reserved_2_.data(), reserved_2_.size());
    out << ", trading_status=";
    out << trading_status_;
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
    out << ", gth_trading_status=";
    out << gth_trading_status_;
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
        && symbol_ == other.symbol_
        && reserved_2_ == other.reserved_2_
        && trading_status_ == other.trading_status_
        && reserved_1_ == other.reserved_1_
        && gth_trading_status_ == other.gth_trading_status_
        && second_reserved_1_ == other.second_reserved_1_;
}

bool TradingStatusMessage::operator!=(const TradingStatusMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
