#include "TradingStatusMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

TradingStatusMessage::TradingStatusMessage(std::chrono::nanoseconds time_offset, const std::string& complex_symbol_id, const std::array<std::byte, 2>& unused, TradingStatus trading_status, const std::array<std::byte, 1>& reserved_1, GthTradingStatus gth_trading_status, const std::array<std::byte, 1>& padding)
  : time_offset_(time_offset), complex_symbol_id_(complex_symbol_id), unused_(unused), trading_status_(trading_status), reserved_1_(reserved_1), gth_trading_status_(gth_trading_status), padding_(padding) {}

std::chrono::nanoseconds TradingStatusMessage::time_offset() const { return time_offset_; }
void TradingStatusMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

const std::string& TradingStatusMessage::complex_symbol_id() const { return complex_symbol_id_; }
std::string& TradingStatusMessage::complex_symbol_id() { return complex_symbol_id_; }
void TradingStatusMessage::set_complex_symbol_id(const std::string& value) { complex_symbol_id_ = value; }

const std::array<std::byte, 2>& TradingStatusMessage::unused() const { return unused_; }
std::array<std::byte, 2>& TradingStatusMessage::unused() { return unused_; }
void TradingStatusMessage::set_unused(const std::array<std::byte, 2>& value) { unused_ = value; }

TradingStatus TradingStatusMessage::trading_status() const { return trading_status_; }
void TradingStatusMessage::set_trading_status(TradingStatus value) { trading_status_ = value; }

const std::array<std::byte, 1>& TradingStatusMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& TradingStatusMessage::reserved_1() { return reserved_1_; }
void TradingStatusMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

GthTradingStatus TradingStatusMessage::gth_trading_status() const { return gth_trading_status_; }
void TradingStatusMessage::set_gth_trading_status(GthTradingStatus value) { gth_trading_status_ = value; }

const std::array<std::byte, 1>& TradingStatusMessage::padding() const { return padding_; }
std::array<std::byte, 1>& TradingStatusMessage::padding() { return padding_; }
void TradingStatusMessage::set_padding(const std::array<std::byte, 1>& value) { padding_ = value; }

MessageCode TradingStatusMessage::type() const { return message_type; }

std::string_view TradingStatusMessage::name() const { return "Trading Status Message"; }

std::size_t TradingStatusMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradingStatusMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    complex_symbol_id_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    wire::read_bytes(data + offset, unused_.data(), 2);
    offset += 2;

    trading_status_ = static_cast<TradingStatus>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    gth_trading_status_ = static_cast<GthTradingStatus>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, padding_.data(), 1);
    offset += 1;

    return offset;
}

std::size_t TradingStatusMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradingStatusMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_text(data + offset, 6, ' ', complex_symbol_id_);
    offset += 6;

    wire::write_bytes(data + offset, unused_.data(), 2);
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(trading_status_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(gth_trading_status_));
    offset += 1;

    wire::write_bytes(data + offset, padding_.data(), 1);
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
    out << ", complex_symbol_id=";
    print::text(out, complex_symbol_id_);
    out << ", unused=";
    print::hex(out, unused_.data(), unused_.size());
    out << ", trading_status=";
    out << trading_status_;
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
    out << ", gth_trading_status=";
    out << gth_trading_status_;
    out << ", padding=";
    print::hex(out, padding_.data(), padding_.size());
    out << '}';
}

bool TradingStatusMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradingStatusMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradingStatusMessage::operator==(const TradingStatusMessage& other) const {
    return time_offset_ == other.time_offset_
        && complex_symbol_id_ == other.complex_symbol_id_
        && unused_ == other.unused_
        && trading_status_ == other.trading_status_
        && reserved_1_ == other.reserved_1_
        && gth_trading_status_ == other.gth_trading_status_
        && padding_ == other.padding_;
}

bool TradingStatusMessage::operator!=(const TradingStatusMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::c1options::complex::pitch::v2_1_18
