#include "TradingStatusMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace iex::iexequities::tops::snap::v1_6 {

TradingStatusMessage::TradingStatusMessage(TradingStatus trading_status, std::chrono::nanoseconds timestamp, const std::string& symbol, const std::string& reason)
  : trading_status_(trading_status), timestamp_(timestamp), symbol_(symbol), reason_(reason) {}

TradingStatus TradingStatusMessage::trading_status() const { return trading_status_; }
void TradingStatusMessage::set_trading_status(TradingStatus value) { trading_status_ = value; }

std::chrono::nanoseconds TradingStatusMessage::timestamp() const { return timestamp_; }
void TradingStatusMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

const std::string& TradingStatusMessage::symbol() const { return symbol_; }
std::string& TradingStatusMessage::symbol() { return symbol_; }
void TradingStatusMessage::set_symbol(const std::string& value) { symbol_ = value; }

const std::string& TradingStatusMessage::reason() const { return reason_; }
std::string& TradingStatusMessage::reason() { return reason_; }
void TradingStatusMessage::set_reason(const std::string& value) { reason_ = value; }

IexTpMessageDataCode TradingStatusMessage::type() const { return message_type; }

std::string_view TradingStatusMessage::name() const { return "Trading Status Message"; }

std::size_t TradingStatusMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradingStatusMessage", wire_size, length);

    trading_status_ = static_cast<TradingStatus>(wire::read_char(data + offset));
    offset += 1;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_i64_le(data + offset)));
    offset += 8;

    symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    reason_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    return offset;
}

std::size_t TradingStatusMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradingStatusMessage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(trading_status_));
    offset += 1;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(timestamp_.count()));
    offset += 8;

    wire::write_text(data + offset, 8, ' ', symbol_);
    offset += 8;

    wire::write_text(data + offset, 4, ' ', reason_);
    offset += 4;

    return offset;
}

std::size_t TradingStatusMessage::encoded_size() const {
    return wire_size;
}

void TradingStatusMessage::accept(IexTpMessageDataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<IexTpMessageData> TradingStatusMessage::clone() const {
    return std::make_unique<TradingStatusMessage>(*this);
}

void TradingStatusMessage::print(std::ostream& out) const {
    out << "TradingStatusMessage{";
    out << "trading_status=";
    out << trading_status_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", reason=";
    print::text(out, reason_);
    out << '}';
}

bool TradingStatusMessage::equals(const IexTpMessageData& other) const {
    const auto* that = dynamic_cast<const TradingStatusMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradingStatusMessage::operator==(const TradingStatusMessage& other) const {
    return trading_status_ == other.trading_status_
        && timestamp_ == other.timestamp_
        && symbol_ == other.symbol_
        && reason_ == other.reason_;
}

bool TradingStatusMessage::operator!=(const TradingStatusMessage& other) const {
    return !(*this == other);
}

} // namespace iex::iexequities::tops::snap::v1_6
