#include "InstrumentStateChange.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

InstrumentStateChange::InstrumentStateChange(std::optional<std::int64_t> security_id, std::optional<SecurityStatus> security_status, std::optional<SecurityTradingStatus> security_trading_status, std::optional<MarketCondition> market_condition, std::optional<FastMarketIndicator> fast_market_indicator, std::optional<SecurityTradingEvent> security_trading_event, std::optional<SoldOutIndicator> sold_out_indicator, const std::array<std::byte, 2>& pad2, std::optional<Decimal> high_px, std::optional<Decimal> low_px, std::optional<std::chrono::nanoseconds> transact_time, std::optional<TesSecurityStatus> tes_security_status, const std::array<std::byte, 7>& pad7)
  : security_id_(security_id), security_status_(security_status), security_trading_status_(security_trading_status), market_condition_(market_condition), fast_market_indicator_(fast_market_indicator), security_trading_event_(security_trading_event), sold_out_indicator_(sold_out_indicator), pad2_(pad2), high_px_(high_px), low_px_(low_px), transact_time_(transact_time), tes_security_status_(tes_security_status), pad7_(pad7) {}

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

std::optional<SoldOutIndicator> InstrumentStateChange::sold_out_indicator() const { return sold_out_indicator_; }
void InstrumentStateChange::set_sold_out_indicator(std::optional<SoldOutIndicator> value) { sold_out_indicator_ = value; }

const std::array<std::byte, 2>& InstrumentStateChange::pad2() const { return pad2_; }
std::array<std::byte, 2>& InstrumentStateChange::pad2() { return pad2_; }
void InstrumentStateChange::set_pad2(const std::array<std::byte, 2>& value) { pad2_ = value; }

std::optional<Decimal> InstrumentStateChange::high_px() const { return high_px_; }
void InstrumentStateChange::set_high_px(std::optional<Decimal> value) { high_px_ = value; }

std::optional<Decimal> InstrumentStateChange::low_px() const { return low_px_; }
void InstrumentStateChange::set_low_px(std::optional<Decimal> value) { low_px_ = value; }

std::optional<std::chrono::nanoseconds> InstrumentStateChange::transact_time() const { return transact_time_; }
void InstrumentStateChange::set_transact_time(std::optional<std::chrono::nanoseconds> value) { transact_time_ = value; }

std::optional<TesSecurityStatus> InstrumentStateChange::tes_security_status() const { return tes_security_status_; }
void InstrumentStateChange::set_tes_security_status(std::optional<TesSecurityStatus> value) { tes_security_status_ = value; }

const std::array<std::byte, 7>& InstrumentStateChange::pad7() const { return pad7_; }
std::array<std::byte, 7>& InstrumentStateChange::pad7() { return pad7_; }
void InstrumentStateChange::set_pad7(const std::array<std::byte, 7>& value) { pad7_ = value; }

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

    sold_out_indicator_ = wire::nullable_enum<SoldOutIndicator>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::read_bytes(data + offset, pad2_.data(), 2);
    offset += 2;

    high_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -8);
    offset += 8;

    low_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -8);
    offset += 8;

    transact_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    tes_security_status_ = wire::nullable_enum<TesSecurityStatus>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::read_bytes(data + offset, pad7_.data(), 7);
    offset += 7;

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

    wire::write_u8(data + offset, sold_out_indicator_ ? static_cast<std::uint8_t>(*sold_out_indicator_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_bytes(data + offset, pad2_.data(), 2);
    offset += 2;

    wire::write_i64_le(data + offset, high_px_ ? static_cast<std::int64_t>(high_px_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_i64_le(data + offset, low_px_ ? static_cast<std::int64_t>(low_px_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_u64_le(data + offset, transact_time_ ? static_cast<std::uint64_t>(transact_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_u8(data + offset, tes_security_status_ ? static_cast<std::uint8_t>(*tes_security_status_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_bytes(data + offset, pad7_.data(), 7);
    offset += 7;

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
    out << ", sold_out_indicator=";
    print::optional(out, sold_out_indicator_);
    out << ", pad2=";
    print::hex(out, pad2_.data(), pad2_.size());
    out << ", high_px=";
    print::optional(out, high_px_);
    out << ", low_px=";
    print::optional(out, low_px_);
    out << ", transact_time=";
    print::optional_duration(out, transact_time_);
    out << ", tes_security_status=";
    print::optional(out, tes_security_status_);
    out << ", pad7=";
    print::hex(out, pad7_.data(), pad7_.size());
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
        && sold_out_indicator_ == other.sold_out_indicator_
        && pad2_ == other.pad2_
        && high_px_ == other.high_px_
        && low_px_ == other.low_px_
        && transact_time_ == other.transact_time_
        && tes_security_status_ == other.tes_security_status_
        && pad7_ == other.pad7_;
}

bool InstrumentStateChange::operator!=(const InstrumentStateChange& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v13_0
