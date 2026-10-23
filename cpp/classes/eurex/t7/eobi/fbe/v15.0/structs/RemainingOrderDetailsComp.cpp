#include "RemainingOrderDetailsComp.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

RemainingOrderDetailsComp::RemainingOrderDetailsComp(std::optional<std::chrono::nanoseconds> trd_reg_ts_prev_time_priority, std::optional<Decimal> display_qty, std::optional<Decimal> price)
  : trd_reg_ts_prev_time_priority_(trd_reg_ts_prev_time_priority), display_qty_(display_qty), price_(price) {}

std::optional<std::chrono::nanoseconds> RemainingOrderDetailsComp::trd_reg_ts_prev_time_priority() const { return trd_reg_ts_prev_time_priority_; }
void RemainingOrderDetailsComp::set_trd_reg_ts_prev_time_priority(std::optional<std::chrono::nanoseconds> value) { trd_reg_ts_prev_time_priority_ = value; }

std::optional<Decimal> RemainingOrderDetailsComp::display_qty() const { return display_qty_; }
void RemainingOrderDetailsComp::set_display_qty(std::optional<Decimal> value) { display_qty_ = value; }

std::optional<Decimal> RemainingOrderDetailsComp::price() const { return price_; }
void RemainingOrderDetailsComp::set_price(std::optional<Decimal> value) { price_ = value; }

std::size_t RemainingOrderDetailsComp::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RemainingOrderDetailsComp", wire_size, length);

    trd_reg_ts_prev_time_priority_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    display_qty_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -4);
    offset += 8;

    price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -8);
    offset += 8;

    return offset;
}

std::size_t RemainingOrderDetailsComp::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RemainingOrderDetailsComp", wire_size, capacity);

    wire::write_u64_le(data + offset, trd_reg_ts_prev_time_priority_ ? static_cast<std::uint64_t>(trd_reg_ts_prev_time_priority_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_i64_le(data + offset, display_qty_ ? static_cast<std::int64_t>(display_qty_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_i64_le(data + offset, price_ ? static_cast<std::int64_t>(price_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    return offset;
}

std::size_t RemainingOrderDetailsComp::encoded_size() const {
    return wire_size;
}

void RemainingOrderDetailsComp::print(std::ostream& out) const {
    out << "RemainingOrderDetailsComp{";
    out << "trd_reg_ts_prev_time_priority=";
    print::optional_duration(out, trd_reg_ts_prev_time_priority_);
    out << ", display_qty=";
    print::optional(out, display_qty_);
    out << ", price=";
    print::optional(out, price_);
    out << '}';
}

bool RemainingOrderDetailsComp::operator==(const RemainingOrderDetailsComp& other) const {
    return trd_reg_ts_prev_time_priority_ == other.trd_reg_ts_prev_time_priority_
        && display_qty_ == other.display_qty_
        && price_ == other.price_;
}

bool RemainingOrderDetailsComp::operator!=(const RemainingOrderDetailsComp& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const RemainingOrderDetailsComp& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v15_0
