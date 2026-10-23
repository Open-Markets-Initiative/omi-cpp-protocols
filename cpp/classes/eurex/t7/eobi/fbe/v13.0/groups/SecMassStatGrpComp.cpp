#include "SecMassStatGrpComp.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

SecMassStatGrpComp::SecMassStatGrpComp(std::optional<std::int64_t> security_id, std::optional<Decimal> high_px, std::optional<Decimal> low_px, std::optional<SecurityStatus> security_status, std::optional<SecurityTradingStatus> security_trading_status, std::optional<MarketCondition> market_condition, std::optional<SecurityTradingEvent> security_trading_event, std::optional<SoldOutIndicator> sold_out_indicator, std::optional<TesSecurityStatus> tes_security_status, const std::array<std::byte, 2>& pad2)
  : security_id_(security_id), high_px_(high_px), low_px_(low_px), security_status_(security_status), security_trading_status_(security_trading_status), market_condition_(market_condition), security_trading_event_(security_trading_event), sold_out_indicator_(sold_out_indicator), tes_security_status_(tes_security_status), pad2_(pad2) {}

std::optional<std::int64_t> SecMassStatGrpComp::security_id() const { return security_id_; }
void SecMassStatGrpComp::set_security_id(std::optional<std::int64_t> value) { security_id_ = value; }

std::optional<Decimal> SecMassStatGrpComp::high_px() const { return high_px_; }
void SecMassStatGrpComp::set_high_px(std::optional<Decimal> value) { high_px_ = value; }

std::optional<Decimal> SecMassStatGrpComp::low_px() const { return low_px_; }
void SecMassStatGrpComp::set_low_px(std::optional<Decimal> value) { low_px_ = value; }

std::optional<SecurityStatus> SecMassStatGrpComp::security_status() const { return security_status_; }
void SecMassStatGrpComp::set_security_status(std::optional<SecurityStatus> value) { security_status_ = value; }

std::optional<SecurityTradingStatus> SecMassStatGrpComp::security_trading_status() const { return security_trading_status_; }
void SecMassStatGrpComp::set_security_trading_status(std::optional<SecurityTradingStatus> value) { security_trading_status_ = value; }

std::optional<MarketCondition> SecMassStatGrpComp::market_condition() const { return market_condition_; }
void SecMassStatGrpComp::set_market_condition(std::optional<MarketCondition> value) { market_condition_ = value; }

std::optional<SecurityTradingEvent> SecMassStatGrpComp::security_trading_event() const { return security_trading_event_; }
void SecMassStatGrpComp::set_security_trading_event(std::optional<SecurityTradingEvent> value) { security_trading_event_ = value; }

std::optional<SoldOutIndicator> SecMassStatGrpComp::sold_out_indicator() const { return sold_out_indicator_; }
void SecMassStatGrpComp::set_sold_out_indicator(std::optional<SoldOutIndicator> value) { sold_out_indicator_ = value; }

std::optional<TesSecurityStatus> SecMassStatGrpComp::tes_security_status() const { return tes_security_status_; }
void SecMassStatGrpComp::set_tes_security_status(std::optional<TesSecurityStatus> value) { tes_security_status_ = value; }

const std::array<std::byte, 2>& SecMassStatGrpComp::pad2() const { return pad2_; }
std::array<std::byte, 2>& SecMassStatGrpComp::pad2() { return pad2_; }
void SecMassStatGrpComp::set_pad2(const std::array<std::byte, 2>& value) { pad2_ = value; }

std::size_t SecMassStatGrpComp::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SecMassStatGrpComp", wire_size, length);

    security_id_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    high_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -8);
    offset += 8;

    low_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -8);
    offset += 8;

    security_status_ = wire::nullable_enum<SecurityStatus>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    security_trading_status_ = wire::nullable_enum<SecurityTradingStatus>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    market_condition_ = wire::nullable_enum<MarketCondition>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    security_trading_event_ = wire::nullable_enum<SecurityTradingEvent>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    sold_out_indicator_ = wire::nullable_enum<SoldOutIndicator>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    tes_security_status_ = wire::nullable_enum<TesSecurityStatus>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::read_bytes(data + offset, pad2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t SecMassStatGrpComp::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecMassStatGrpComp", wire_size, capacity);

    wire::write_i64_le(data + offset, security_id_.value_or(static_cast<std::int64_t>(0x8000000000000000LL)));
    offset += 8;

    wire::write_i64_le(data + offset, high_px_ ? static_cast<std::int64_t>(high_px_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_i64_le(data + offset, low_px_ ? static_cast<std::int64_t>(low_px_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_u8(data + offset, security_status_ ? static_cast<std::uint8_t>(*security_status_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, security_trading_status_ ? static_cast<std::uint8_t>(*security_trading_status_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, market_condition_ ? static_cast<std::uint8_t>(*market_condition_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, security_trading_event_ ? static_cast<std::uint8_t>(*security_trading_event_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, sold_out_indicator_ ? static_cast<std::uint8_t>(*sold_out_indicator_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, tes_security_status_ ? static_cast<std::uint8_t>(*tes_security_status_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_bytes(data + offset, pad2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t SecMassStatGrpComp::encoded_size() const {
    return wire_size;
}

void SecMassStatGrpComp::print(std::ostream& out) const {
    out << "SecMassStatGrpComp{";
    out << "security_id=";
    print::optional(out, security_id_);
    out << ", high_px=";
    print::optional(out, high_px_);
    out << ", low_px=";
    print::optional(out, low_px_);
    out << ", security_status=";
    print::optional(out, security_status_);
    out << ", security_trading_status=";
    print::optional(out, security_trading_status_);
    out << ", market_condition=";
    print::optional(out, market_condition_);
    out << ", security_trading_event=";
    print::optional(out, security_trading_event_);
    out << ", sold_out_indicator=";
    print::optional(out, sold_out_indicator_);
    out << ", tes_security_status=";
    print::optional(out, tes_security_status_);
    out << ", pad2=";
    print::hex(out, pad2_.data(), pad2_.size());
    out << '}';
}

bool SecMassStatGrpComp::operator==(const SecMassStatGrpComp& other) const {
    return security_id_ == other.security_id_
        && high_px_ == other.high_px_
        && low_px_ == other.low_px_
        && security_status_ == other.security_status_
        && security_trading_status_ == other.security_trading_status_
        && market_condition_ == other.market_condition_
        && security_trading_event_ == other.security_trading_event_
        && sold_out_indicator_ == other.sold_out_indicator_
        && tes_security_status_ == other.tes_security_status_
        && pad2_ == other.pad2_;
}

bool SecMassStatGrpComp::operator!=(const SecMassStatGrpComp& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SecMassStatGrpComp& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v13_0
