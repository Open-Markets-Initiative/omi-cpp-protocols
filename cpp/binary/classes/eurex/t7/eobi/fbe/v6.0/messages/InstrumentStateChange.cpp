#include "InstrumentStateChange.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

InstrumentStateChange::InstrumentStateChange(std::optional<std::int64_t> security_id, std::optional<SecurityStatus> security_status, std::optional<SecurityTradingStatus> security_trading_status, std::optional<MarketCondition> market_condition, std::optional<FastMarketIndicator> fast_market_indicator, std::optional<SecurityTradingEvent> security_trading_event, const std::array<std::byte, 3>& pad3, std::optional<std::chrono::nanoseconds> transact_time)
  : security_id_(security_id), security_status_(security_status), security_trading_status_(security_trading_status), market_condition_(market_condition), fast_market_indicator_(fast_market_indicator), security_trading_event_(security_trading_event), pad3_(pad3), transact_time_(transact_time) {}

std::optional<std::int64_t> InstrumentStateChange::security_id() const { return security_id_; }
void InstrumentStateChange::set_security_id(std::optional<std::int64_t> value) { security_id_ = value; }

std::optional<SecurityStatus> InstrumentStateChange::security_status() const { return security_status_; }
void InstrumentStateChange::set_security_status(std::optional<SecurityStatus> value) { security_status_ = value; }

std::optional<SecurityTradingStatus> InstrumentStateChange::security_trading_status() const { return security_trading_status_; }
void InstrumentStateChange::set_security_trading_status(std::optional<SecurityTradingStatus> value) { security_trading_status_ = value; }

std::optional<MarketCondition> InstrumentStateChange::market_condition() const { return market_condition_; }
void InstrumentStateChange::set_market_condition(std::optional<MarketCondition> value) { market_condition_ = value; }

std::optional<FastMarketIndicator> InstrumentStateChange::fast_market_indicator() const { return fast_market_indicator_; }
void InstrumentStateChange::set_fast_market_indicator(std::optional<FastMarketIndicator> value) { fast_market_indicator_ = value; }

std::optional<SecurityTradingEvent> InstrumentStateChange::security_trading_event() const { return security_trading_event_; }
void InstrumentStateChange::set_security_trading_event(std::optional<SecurityTradingEvent> value) { security_trading_event_ = value; }

const std::array<std::byte, 3>& InstrumentStateChange::pad3() const { return pad3_; }
std::array<std::byte, 3>& InstrumentStateChange::pad3() { return pad3_; }
void InstrumentStateChange::set_pad3(const std::array<std::byte, 3>& value) { pad3_ = value; }

std::optional<std::chrono::nanoseconds> InstrumentStateChange::transact_time() const { return transact_time_; }
void InstrumentStateChange::set_transact_time(std::optional<std::chrono::nanoseconds> value) { transact_time_ = value; }

MessageCode InstrumentStateChange::type() const { return message_type; }

std::string_view InstrumentStateChange::name() const { return "Instrument State Change"; }

std::size_t InstrumentStateChange::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("InstrumentStateChange", wire_size, length);

    security_id_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    security_status_ = wire::nullable_enum<SecurityStatus>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    security_trading_status_ = wire::nullable_enum<SecurityTradingStatus>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    market_condition_ = wire::nullable_enum<MarketCondition>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    fast_market_indicator_ = wire::nullable_enum<FastMarketIndicator>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    security_trading_event_ = wire::nullable_enum<SecurityTradingEvent>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::read_bytes(data + offset, pad3_.data(), 3);
    offset += 3;

    transact_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    return offset;
}

std::size_t InstrumentStateChange::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("InstrumentStateChange", wire_size, capacity);

    wire::write_i64_le(data + offset, security_id_.value_or(static_cast<std::int64_t>(0x8000000000000000LL)));
    offset += 8;

    wire::write_u8(data + offset, security_status_ ? static_cast<std::uint8_t>(*security_status_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, security_trading_status_ ? static_cast<std::uint8_t>(*security_trading_status_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, market_condition_ ? static_cast<std::uint8_t>(*market_condition_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, fast_market_indicator_ ? static_cast<std::uint8_t>(*fast_market_indicator_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, security_trading_event_ ? static_cast<std::uint8_t>(*security_trading_event_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_bytes(data + offset, pad3_.data(), 3);
    offset += 3;

    wire::write_u64_le(data + offset, transact_time_ ? static_cast<std::uint64_t>(transact_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    return offset;
}

std::size_t InstrumentStateChange::encoded_size() const {
    return wire_size;
}

void InstrumentStateChange::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> InstrumentStateChange::clone() const {
    return std::make_unique<InstrumentStateChange>(*this);
}

void InstrumentStateChange::print(std::ostream& out) const {
    out << "InstrumentStateChange{";
    out << "security_id=";
    print::optional(out, security_id_);
    out << ", security_status=";
    print::optional(out, security_status_);
    out << ", security_trading_status=";
    print::optional(out, security_trading_status_);
    out << ", market_condition=";
    print::optional(out, market_condition_);
    out << ", fast_market_indicator=";
    print::optional(out, fast_market_indicator_);
    out << ", security_trading_event=";
    print::optional(out, security_trading_event_);
    out << ", pad3=";
    print::hex(out, pad3_.data(), pad3_.size());
    out << ", transact_time=";
    print::optional_duration(out, transact_time_);
    out << '}';
}

bool InstrumentStateChange::equals(const Message& other) const {
    const auto* that = dynamic_cast<const InstrumentStateChange*>(&other);
    return that != nullptr && *this == *that;
}

bool InstrumentStateChange::operator==(const InstrumentStateChange& other) const {
    return security_id_ == other.security_id_
        && security_status_ == other.security_status_
        && security_trading_status_ == other.security_trading_status_
        && market_condition_ == other.market_condition_
        && fast_market_indicator_ == other.fast_market_indicator_
        && security_trading_event_ == other.security_trading_event_
        && pad3_ == other.pad3_
        && transact_time_ == other.transact_time_;
}

bool InstrumentStateChange::operator!=(const InstrumentStateChange& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v6_0
