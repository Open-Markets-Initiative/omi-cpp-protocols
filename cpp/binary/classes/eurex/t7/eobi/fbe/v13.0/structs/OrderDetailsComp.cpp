#include "OrderDetailsComp.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

OrderDetailsComp::OrderDetailsComp(std::optional<std::chrono::nanoseconds> trd_reg_ts_time_priority, std::optional<Decimal> display_qty, std::optional<Side> side, std::optional<OrdType> ord_type, std::optional<HhiIndicator> hhi_indicator, const std::array<std::byte, 5>& pad5, std::optional<Decimal> price)
  : trd_reg_ts_time_priority_(trd_reg_ts_time_priority), display_qty_(display_qty), side_(side), ord_type_(ord_type), hhi_indicator_(hhi_indicator), pad5_(pad5), price_(price) {}

std::optional<std::chrono::nanoseconds> OrderDetailsComp::trd_reg_ts_time_priority() const { return trd_reg_ts_time_priority_; }
void OrderDetailsComp::set_trd_reg_ts_time_priority(std::optional<std::chrono::nanoseconds> value) { trd_reg_ts_time_priority_ = value; }

std::optional<Decimal> OrderDetailsComp::display_qty() const { return display_qty_; }
void OrderDetailsComp::set_display_qty(std::optional<Decimal> value) { display_qty_ = value; }

std::optional<Side> OrderDetailsComp::side() const { return side_; }
void OrderDetailsComp::set_side(std::optional<Side> value) { side_ = value; }

std::optional<OrdType> OrderDetailsComp::ord_type() const { return ord_type_; }
void OrderDetailsComp::set_ord_type(std::optional<OrdType> value) { ord_type_ = value; }

std::optional<HhiIndicator> OrderDetailsComp::hhi_indicator() const { return hhi_indicator_; }
void OrderDetailsComp::set_hhi_indicator(std::optional<HhiIndicator> value) { hhi_indicator_ = value; }

const std::array<std::byte, 5>& OrderDetailsComp::pad5() const { return pad5_; }
std::array<std::byte, 5>& OrderDetailsComp::pad5() { return pad5_; }
void OrderDetailsComp::set_pad5(const std::array<std::byte, 5>& value) { pad5_ = value; }

std::optional<Decimal> OrderDetailsComp::price() const { return price_; }
void OrderDetailsComp::set_price(std::optional<Decimal> value) { price_ = value; }

std::size_t OrderDetailsComp::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderDetailsComp", wire_size, length);

    trd_reg_ts_time_priority_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    display_qty_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -4);
    offset += 8;

    side_ = wire::nullable_enum<Side>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    ord_type_ = wire::nullable_enum<OrdType>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    hhi_indicator_ = wire::nullable_enum<HhiIndicator>(wire::read_i8(data + offset), static_cast<std::int8_t>(0x80LL));
    offset += 1;

    wire::read_bytes(data + offset, pad5_.data(), 5);
    offset += 5;

    price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -8);
    offset += 8;

    return offset;
}

std::size_t OrderDetailsComp::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderDetailsComp", wire_size, capacity);

    wire::write_u64_le(data + offset, trd_reg_ts_time_priority_ ? static_cast<std::uint64_t>(trd_reg_ts_time_priority_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_i64_le(data + offset, display_qty_ ? static_cast<std::int64_t>(display_qty_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_u8(data + offset, side_ ? static_cast<std::uint8_t>(*side_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, ord_type_ ? static_cast<std::uint8_t>(*ord_type_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_i8(data + offset, hhi_indicator_ ? static_cast<std::int8_t>(*hhi_indicator_) : static_cast<std::int8_t>(0x80LL));
    offset += 1;

    wire::write_bytes(data + offset, pad5_.data(), 5);
    offset += 5;

    wire::write_i64_le(data + offset, price_ ? static_cast<std::int64_t>(price_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    return offset;
}

std::size_t OrderDetailsComp::encoded_size() const {
    return wire_size;
}

void OrderDetailsComp::print(std::ostream& out) const {
    out << "OrderDetailsComp{";
    out << "trd_reg_ts_time_priority=";
    print::optional_duration(out, trd_reg_ts_time_priority_);
    out << ", display_qty=";
    print::optional(out, display_qty_);
    out << ", side=";
    print::optional(out, side_);
    out << ", ord_type=";
    print::optional(out, ord_type_);
    out << ", hhi_indicator=";
    print::optional(out, hhi_indicator_);
    out << ", pad5=";
    print::hex(out, pad5_.data(), pad5_.size());
    out << ", price=";
    print::optional(out, price_);
    out << '}';
}

bool OrderDetailsComp::operator==(const OrderDetailsComp& other) const {
    return trd_reg_ts_time_priority_ == other.trd_reg_ts_time_priority_
        && display_qty_ == other.display_qty_
        && side_ == other.side_
        && ord_type_ == other.ord_type_
        && hhi_indicator_ == other.hhi_indicator_
        && pad5_ == other.pad5_
        && price_ == other.price_;
}

bool OrderDetailsComp::operator!=(const OrderDetailsComp& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const OrderDetailsComp& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v13_0
