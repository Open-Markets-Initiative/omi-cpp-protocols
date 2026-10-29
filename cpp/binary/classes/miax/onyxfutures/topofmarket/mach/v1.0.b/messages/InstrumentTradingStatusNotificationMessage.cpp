#include "InstrumentTradingStatusNotificationMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

InstrumentTradingStatusNotificationMessage::InstrumentTradingStatusNotificationMessage(std::chrono::nanoseconds timestamp, std::uint32_t instrument_id, TradingStatus trading_status, MarketState market_state)
  : timestamp_(timestamp), instrument_id_(instrument_id), trading_status_(trading_status), market_state_(market_state) {}

std::chrono::nanoseconds InstrumentTradingStatusNotificationMessage::timestamp() const { return timestamp_; }
void InstrumentTradingStatusNotificationMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint32_t InstrumentTradingStatusNotificationMessage::instrument_id() const { return instrument_id_; }
void InstrumentTradingStatusNotificationMessage::set_instrument_id(std::uint32_t value) { instrument_id_ = value; }

TradingStatus InstrumentTradingStatusNotificationMessage::trading_status() const { return trading_status_; }
void InstrumentTradingStatusNotificationMessage::set_trading_status(TradingStatus value) { trading_status_ = value; }

MarketState InstrumentTradingStatusNotificationMessage::market_state() const { return market_state_; }
void InstrumentTradingStatusNotificationMessage::set_market_state(MarketState value) { market_state_ = value; }

DataCode InstrumentTradingStatusNotificationMessage::type() const { return message_type; }

std::string_view InstrumentTradingStatusNotificationMessage::name() const { return "Instrument Trading Status Notification Message"; }

std::size_t InstrumentTradingStatusNotificationMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("InstrumentTradingStatusNotificationMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    instrument_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    trading_status_ = static_cast<TradingStatus>(wire::read_u8(data + offset));
    offset += 1;

    market_state_ = static_cast<MarketState>(wire::read_u8(data + offset));
    offset += 1;

    return offset;
}

std::size_t InstrumentTradingStatusNotificationMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("InstrumentTradingStatusNotificationMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(instrument_id_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(trading_status_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(market_state_));
    offset += 1;

    return offset;
}

std::size_t InstrumentTradingStatusNotificationMessage::encoded_size() const {
    return wire_size;
}

void InstrumentTradingStatusNotificationMessage::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> InstrumentTradingStatusNotificationMessage::clone() const {
    return std::make_unique<InstrumentTradingStatusNotificationMessage>(*this);
}

void InstrumentTradingStatusNotificationMessage::print(std::ostream& out) const {
    out << "InstrumentTradingStatusNotificationMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", instrument_id=";
    out << instrument_id_;
    out << ", trading_status=";
    out << trading_status_;
    out << ", market_state=";
    out << market_state_;
    out << '}';
}

bool InstrumentTradingStatusNotificationMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const InstrumentTradingStatusNotificationMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool InstrumentTradingStatusNotificationMessage::operator==(const InstrumentTradingStatusNotificationMessage& other) const {
    return timestamp_ == other.timestamp_
        && instrument_id_ == other.instrument_id_
        && trading_status_ == other.trading_status_
        && market_state_ == other.market_state_;
}

bool InstrumentTradingStatusNotificationMessage::operator!=(const InstrumentTradingStatusNotificationMessage& other) const {
    return !(*this == other);
}

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
