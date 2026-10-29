#include "InstrumentStateChangeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

InstrumentStateChangeMessage::InstrumentStateChangeMessage(std::int64_t security_id, SecurityStatus security_status, SecurityTradingStatus security_trading_status, FastMarketIndicator fast_market_indicator, const std::array<std::byte, 5>& pad_5, std::chrono::nanoseconds transact_time)
  : security_id_(security_id), security_status_(security_status), security_trading_status_(security_trading_status), fast_market_indicator_(fast_market_indicator), pad_5_(pad_5), transact_time_(transact_time) {}

std::int64_t InstrumentStateChangeMessage::security_id() const { return security_id_; }
void InstrumentStateChangeMessage::set_security_id(std::int64_t value) { security_id_ = value; }

SecurityStatus InstrumentStateChangeMessage::security_status() const { return security_status_; }
void InstrumentStateChangeMessage::set_security_status(SecurityStatus value) { security_status_ = value; }

SecurityTradingStatus InstrumentStateChangeMessage::security_trading_status() const { return security_trading_status_; }
void InstrumentStateChangeMessage::set_security_trading_status(SecurityTradingStatus value) { security_trading_status_ = value; }

FastMarketIndicator InstrumentStateChangeMessage::fast_market_indicator() const { return fast_market_indicator_; }
void InstrumentStateChangeMessage::set_fast_market_indicator(FastMarketIndicator value) { fast_market_indicator_ = value; }

const std::array<std::byte, 5>& InstrumentStateChangeMessage::pad_5() const { return pad_5_; }
std::array<std::byte, 5>& InstrumentStateChangeMessage::pad_5() { return pad_5_; }
void InstrumentStateChangeMessage::set_pad_5(const std::array<std::byte, 5>& value) { pad_5_ = value; }

std::chrono::nanoseconds InstrumentStateChangeMessage::transact_time() const { return transact_time_; }
void InstrumentStateChangeMessage::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

MessageCode InstrumentStateChangeMessage::type() const { return message_type; }

std::string_view InstrumentStateChangeMessage::name() const { return "Instrument State Change Message"; }

std::size_t InstrumentStateChangeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("InstrumentStateChangeMessage", wire_size, length);

    security_id_ = wire::read_i64_le(data + offset);
    offset += 8;

    security_status_ = static_cast<SecurityStatus>(wire::read_u8(data + offset));
    offset += 1;

    security_trading_status_ = static_cast<SecurityTradingStatus>(wire::read_u8(data + offset));
    offset += 1;

    fast_market_indicator_ = static_cast<FastMarketIndicator>(wire::read_u8(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, pad_5_.data(), 5);
    offset += 5;

    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    return offset;
}

std::size_t InstrumentStateChangeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("InstrumentStateChangeMessage", wire_size, capacity);

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(security_id_));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(security_status_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(security_trading_status_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(fast_market_indicator_));
    offset += 1;

    wire::write_bytes(data + offset, pad_5_.data(), 5);
    offset += 5;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    return offset;
}

std::size_t InstrumentStateChangeMessage::encoded_size() const {
    return wire_size;
}

void InstrumentStateChangeMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> InstrumentStateChangeMessage::clone() const {
    return std::make_unique<InstrumentStateChangeMessage>(*this);
}

void InstrumentStateChangeMessage::print(std::ostream& out) const {
    out << "InstrumentStateChangeMessage{";
    out << "security_id=";
    out << security_id_;
    out << ", security_status=";
    out << security_status_;
    out << ", security_trading_status=";
    out << security_trading_status_;
    out << ", fast_market_indicator=";
    out << fast_market_indicator_;
    out << ", pad_5=";
    print::hex(out, pad_5_.data(), pad_5_.size());
    out << ", transact_time=";
    out << transact_time_.count();
    out << '}';
}

bool InstrumentStateChangeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const InstrumentStateChangeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool InstrumentStateChangeMessage::operator==(const InstrumentStateChangeMessage& other) const {
    return security_id_ == other.security_id_
        && security_status_ == other.security_status_
        && security_trading_status_ == other.security_trading_status_
        && fast_market_indicator_ == other.fast_market_indicator_
        && pad_5_ == other.pad_5_
        && transact_time_ == other.transact_time_;
}

bool InstrumentStateChangeMessage::operator!=(const InstrumentStateChangeMessage& other) const {
    return !(*this == other);
}

} // namespace bse::bseindia::eobi::fbe::v1_4
