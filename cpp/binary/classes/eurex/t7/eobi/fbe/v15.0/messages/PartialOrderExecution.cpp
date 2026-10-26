#include "PartialOrderExecution.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

PartialOrderExecution::PartialOrderExecution(std::optional<Side> side, std::optional<OrdType> ord_type, std::optional<AlgorithmicTradeIndicator> algorithmic_trade_indicator, std::optional<HhiIndicator> hhi_indicator, std::optional<std::uint32_t> trd_match_id, std::optional<Decimal> price, std::optional<std::chrono::nanoseconds> trd_reg_ts_time_priority, std::optional<std::int64_t> security_id, std::optional<Decimal> last_qty, std::optional<Decimal> last_px)
  : side_(side), ord_type_(ord_type), algorithmic_trade_indicator_(algorithmic_trade_indicator), hhi_indicator_(hhi_indicator), trd_match_id_(trd_match_id), price_(price), trd_reg_ts_time_priority_(trd_reg_ts_time_priority), security_id_(security_id), last_qty_(last_qty), last_px_(last_px) {}

std::optional<Side> PartialOrderExecution::side() const { return side_; }
void PartialOrderExecution::set_side(std::optional<Side> value) { side_ = value; }

std::optional<OrdType> PartialOrderExecution::ord_type() const { return ord_type_; }
void PartialOrderExecution::set_ord_type(std::optional<OrdType> value) { ord_type_ = value; }

std::optional<AlgorithmicTradeIndicator> PartialOrderExecution::algorithmic_trade_indicator() const { return algorithmic_trade_indicator_; }
void PartialOrderExecution::set_algorithmic_trade_indicator(std::optional<AlgorithmicTradeIndicator> value) { algorithmic_trade_indicator_ = value; }

std::optional<HhiIndicator> PartialOrderExecution::hhi_indicator() const { return hhi_indicator_; }
void PartialOrderExecution::set_hhi_indicator(std::optional<HhiIndicator> value) { hhi_indicator_ = value; }

std::optional<std::uint32_t> PartialOrderExecution::trd_match_id() const { return trd_match_id_; }
void PartialOrderExecution::set_trd_match_id(std::optional<std::uint32_t> value) { trd_match_id_ = value; }

std::optional<Decimal> PartialOrderExecution::price() const { return price_; }
void PartialOrderExecution::set_price(std::optional<Decimal> value) { price_ = value; }

std::optional<std::chrono::nanoseconds> PartialOrderExecution::trd_reg_ts_time_priority() const { return trd_reg_ts_time_priority_; }
void PartialOrderExecution::set_trd_reg_ts_time_priority(std::optional<std::chrono::nanoseconds> value) { trd_reg_ts_time_priority_ = value; }

std::optional<std::int64_t> PartialOrderExecution::security_id() const { return security_id_; }
void PartialOrderExecution::set_security_id(std::optional<std::int64_t> value) { security_id_ = value; }

std::optional<Decimal> PartialOrderExecution::last_qty() const { return last_qty_; }
void PartialOrderExecution::set_last_qty(std::optional<Decimal> value) { last_qty_ = value; }

std::optional<Decimal> PartialOrderExecution::last_px() const { return last_px_; }
void PartialOrderExecution::set_last_px(std::optional<Decimal> value) { last_px_ = value; }

MessageCode PartialOrderExecution::type() const { return message_type; }

std::string_view PartialOrderExecution::name() const { return "Partial Order Execution"; }

std::size_t PartialOrderExecution::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PartialOrderExecution", wire_size, length);

    side_ = wire::nullable_enum<Side>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    ord_type_ = wire::nullable_enum<OrdType>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    algorithmic_trade_indicator_ = wire::nullable_enum<AlgorithmicTradeIndicator>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    hhi_indicator_ = wire::nullable_enum<HhiIndicator>(wire::read_i8(data + offset), static_cast<std::int8_t>(0x80LL));
    offset += 1;

    trd_match_id_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0xFFFFFFFFULL));
    offset += 4;

    price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -8);
    offset += 8;

    trd_reg_ts_time_priority_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    security_id_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    last_qty_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -4);
    offset += 8;

    last_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -8);
    offset += 8;

    return offset;
}

std::size_t PartialOrderExecution::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PartialOrderExecution", wire_size, capacity);

    wire::write_u8(data + offset, side_ ? static_cast<std::uint8_t>(*side_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, ord_type_ ? static_cast<std::uint8_t>(*ord_type_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, algorithmic_trade_indicator_ ? static_cast<std::uint8_t>(*algorithmic_trade_indicator_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_i8(data + offset, hhi_indicator_ ? static_cast<std::int8_t>(*hhi_indicator_) : static_cast<std::int8_t>(0x80LL));
    offset += 1;

    wire::write_u32_le(data + offset, trd_match_id_.value_or(static_cast<std::uint32_t>(0xFFFFFFFFULL)));
    offset += 4;

    wire::write_i64_le(data + offset, price_ ? static_cast<std::int64_t>(price_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_u64_le(data + offset, trd_reg_ts_time_priority_ ? static_cast<std::uint64_t>(trd_reg_ts_time_priority_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_i64_le(data + offset, security_id_.value_or(static_cast<std::int64_t>(0x8000000000000000LL)));
    offset += 8;

    wire::write_i64_le(data + offset, last_qty_ ? static_cast<std::int64_t>(last_qty_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_i64_le(data + offset, last_px_ ? static_cast<std::int64_t>(last_px_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    return offset;
}

std::size_t PartialOrderExecution::encoded_size() const {
    return wire_size;
}

void PartialOrderExecution::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> PartialOrderExecution::clone() const {
    return std::make_unique<PartialOrderExecution>(*this);
}

void PartialOrderExecution::print(std::ostream& out) const {
    out << "PartialOrderExecution{";
    out << "side=";
    print::optional(out, side_);
    out << ", ord_type=";
    print::optional(out, ord_type_);
    out << ", algorithmic_trade_indicator=";
    print::optional(out, algorithmic_trade_indicator_);
    out << ", hhi_indicator=";
    print::optional(out, hhi_indicator_);
    out << ", trd_match_id=";
    print::optional(out, trd_match_id_);
    out << ", price=";
    print::optional(out, price_);
    out << ", trd_reg_ts_time_priority=";
    print::optional_duration(out, trd_reg_ts_time_priority_);
    out << ", security_id=";
    print::optional(out, security_id_);
    out << ", last_qty=";
    print::optional(out, last_qty_);
    out << ", last_px=";
    print::optional(out, last_px_);
    out << '}';
}

bool PartialOrderExecution::equals(const Message& other) const {
    const auto* that = dynamic_cast<const PartialOrderExecution*>(&other);
    return that != nullptr && *this == *that;
}

bool PartialOrderExecution::operator==(const PartialOrderExecution& other) const {
    return side_ == other.side_
        && ord_type_ == other.ord_type_
        && algorithmic_trade_indicator_ == other.algorithmic_trade_indicator_
        && hhi_indicator_ == other.hhi_indicator_
        && trd_match_id_ == other.trd_match_id_
        && price_ == other.price_
        && trd_reg_ts_time_priority_ == other.trd_reg_ts_time_priority_
        && security_id_ == other.security_id_
        && last_qty_ == other.last_qty_
        && last_px_ == other.last_px_;
}

bool PartialOrderExecution::operator!=(const PartialOrderExecution& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v15_0
