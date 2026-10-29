#include "OrderModify.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

OrderModify::OrderModify(std::optional<std::chrono::nanoseconds> trd_reg_ts_time_in, std::optional<std::chrono::nanoseconds> trd_reg_ts_prev_time_priority, std::optional<Decimal> prev_price, std::optional<std::int32_t> prev_display_qty, const std::array<std::byte, 4>& pad4, std::optional<std::int64_t> security_id, const OrderDetailsComp& order_details_comp)
  : trd_reg_ts_time_in_(trd_reg_ts_time_in), trd_reg_ts_prev_time_priority_(trd_reg_ts_prev_time_priority), prev_price_(prev_price), prev_display_qty_(prev_display_qty), pad4_(pad4), security_id_(security_id), order_details_comp_(order_details_comp) {}

std::optional<std::chrono::nanoseconds> OrderModify::trd_reg_ts_time_in() const { return trd_reg_ts_time_in_; }
void OrderModify::set_trd_reg_ts_time_in(std::optional<std::chrono::nanoseconds> value) { trd_reg_ts_time_in_ = value; }

std::optional<std::chrono::nanoseconds> OrderModify::trd_reg_ts_prev_time_priority() const { return trd_reg_ts_prev_time_priority_; }
void OrderModify::set_trd_reg_ts_prev_time_priority(std::optional<std::chrono::nanoseconds> value) { trd_reg_ts_prev_time_priority_ = value; }

std::optional<Decimal> OrderModify::prev_price() const { return prev_price_; }
void OrderModify::set_prev_price(std::optional<Decimal> value) { prev_price_ = value; }

std::optional<std::int32_t> OrderModify::prev_display_qty() const { return prev_display_qty_; }
void OrderModify::set_prev_display_qty(std::optional<std::int32_t> value) { prev_display_qty_ = value; }

const std::array<std::byte, 4>& OrderModify::pad4() const { return pad4_; }
std::array<std::byte, 4>& OrderModify::pad4() { return pad4_; }
void OrderModify::set_pad4(const std::array<std::byte, 4>& value) { pad4_ = value; }

std::optional<std::int64_t> OrderModify::security_id() const { return security_id_; }
void OrderModify::set_security_id(std::optional<std::int64_t> value) { security_id_ = value; }

const OrderDetailsComp& OrderModify::order_details_comp() const { return order_details_comp_; }
OrderDetailsComp& OrderModify::order_details_comp() { return order_details_comp_; }
void OrderModify::set_order_details_comp(const OrderDetailsComp& value) { order_details_comp_ = value; }

MessageCode OrderModify::type() const { return message_type; }

std::string_view OrderModify::name() const { return "Order Modify"; }

std::size_t OrderModify::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderModify", wire_size, length);

    trd_reg_ts_time_in_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    trd_reg_ts_prev_time_priority_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    prev_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -8);
    offset += 8;

    prev_display_qty_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(0x80000000LL));
    offset += 4;

    wire::read_bytes(data + offset, pad4_.data(), 4);
    offset += 4;

    security_id_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    offset += order_details_comp_.decode(data + offset, length - offset);

    return offset;
}

std::size_t OrderModify::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderModify", wire_size, capacity);

    wire::write_u64_le(data + offset, trd_reg_ts_time_in_ ? static_cast<std::uint64_t>(trd_reg_ts_time_in_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_u64_le(data + offset, trd_reg_ts_prev_time_priority_ ? static_cast<std::uint64_t>(trd_reg_ts_prev_time_priority_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_i64_le(data + offset, prev_price_ ? static_cast<std::int64_t>(prev_price_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_i32_le(data + offset, prev_display_qty_.value_or(static_cast<std::int32_t>(0x80000000LL)));
    offset += 4;

    wire::write_bytes(data + offset, pad4_.data(), 4);
    offset += 4;

    wire::write_i64_le(data + offset, security_id_.value_or(static_cast<std::int64_t>(0x8000000000000000LL)));
    offset += 8;

    offset += order_details_comp_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t OrderModify::encoded_size() const {
    return wire_size;
}

void OrderModify::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderModify::clone() const {
    return std::make_unique<OrderModify>(*this);
}

void OrderModify::print(std::ostream& out) const {
    out << "OrderModify{";
    out << "trd_reg_ts_time_in=";
    print::optional_duration(out, trd_reg_ts_time_in_);
    out << ", trd_reg_ts_prev_time_priority=";
    print::optional_duration(out, trd_reg_ts_prev_time_priority_);
    out << ", prev_price=";
    print::optional(out, prev_price_);
    out << ", prev_display_qty=";
    print::optional(out, prev_display_qty_);
    out << ", pad4=";
    print::hex(out, pad4_.data(), pad4_.size());
    out << ", security_id=";
    print::optional(out, security_id_);
    out << ", order_details_comp=";
    order_details_comp_.print(out);
    out << '}';
}

bool OrderModify::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderModify*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderModify::operator==(const OrderModify& other) const {
    return trd_reg_ts_time_in_ == other.trd_reg_ts_time_in_
        && trd_reg_ts_prev_time_priority_ == other.trd_reg_ts_prev_time_priority_
        && prev_price_ == other.prev_price_
        && prev_display_qty_ == other.prev_display_qty_
        && pad4_ == other.pad4_
        && security_id_ == other.security_id_
        && order_details_comp_ == other.order_details_comp_;
}

bool OrderModify::operator!=(const OrderModify& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v6_0
