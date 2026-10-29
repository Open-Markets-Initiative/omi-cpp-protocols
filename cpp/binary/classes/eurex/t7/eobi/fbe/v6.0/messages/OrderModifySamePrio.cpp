#include "OrderModifySamePrio.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

OrderModifySamePrio::OrderModifySamePrio(std::optional<std::chrono::nanoseconds> trd_reg_ts_time_in, std::optional<std::chrono::nanoseconds> transact_time, std::optional<std::int32_t> prev_display_qty, const std::array<std::byte, 4>& pad4, std::optional<std::int64_t> security_id, const OrderDetailsComp& order_details_comp)
  : trd_reg_ts_time_in_(trd_reg_ts_time_in), transact_time_(transact_time), prev_display_qty_(prev_display_qty), pad4_(pad4), security_id_(security_id), order_details_comp_(order_details_comp) {}

std::optional<std::chrono::nanoseconds> OrderModifySamePrio::trd_reg_ts_time_in() const { return trd_reg_ts_time_in_; }
void OrderModifySamePrio::set_trd_reg_ts_time_in(std::optional<std::chrono::nanoseconds> value) { trd_reg_ts_time_in_ = value; }

std::optional<std::chrono::nanoseconds> OrderModifySamePrio::transact_time() const { return transact_time_; }
void OrderModifySamePrio::set_transact_time(std::optional<std::chrono::nanoseconds> value) { transact_time_ = value; }

std::optional<std::int32_t> OrderModifySamePrio::prev_display_qty() const { return prev_display_qty_; }
void OrderModifySamePrio::set_prev_display_qty(std::optional<std::int32_t> value) { prev_display_qty_ = value; }

const std::array<std::byte, 4>& OrderModifySamePrio::pad4() const { return pad4_; }
std::array<std::byte, 4>& OrderModifySamePrio::pad4() { return pad4_; }
void OrderModifySamePrio::set_pad4(const std::array<std::byte, 4>& value) { pad4_ = value; }

std::optional<std::int64_t> OrderModifySamePrio::security_id() const { return security_id_; }
void OrderModifySamePrio::set_security_id(std::optional<std::int64_t> value) { security_id_ = value; }

const OrderDetailsComp& OrderModifySamePrio::order_details_comp() const { return order_details_comp_; }
OrderDetailsComp& OrderModifySamePrio::order_details_comp() { return order_details_comp_; }
void OrderModifySamePrio::set_order_details_comp(const OrderDetailsComp& value) { order_details_comp_ = value; }

MessageCode OrderModifySamePrio::type() const { return message_type; }

std::string_view OrderModifySamePrio::name() const { return "Order Modify Same Prio"; }

std::size_t OrderModifySamePrio::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderModifySamePrio", wire_size, length);

    trd_reg_ts_time_in_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    transact_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
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

std::size_t OrderModifySamePrio::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderModifySamePrio", wire_size, capacity);

    wire::write_u64_le(data + offset, trd_reg_ts_time_in_ ? static_cast<std::uint64_t>(trd_reg_ts_time_in_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_u64_le(data + offset, transact_time_ ? static_cast<std::uint64_t>(transact_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
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

std::size_t OrderModifySamePrio::encoded_size() const {
    return wire_size;
}

void OrderModifySamePrio::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderModifySamePrio::clone() const {
    return std::make_unique<OrderModifySamePrio>(*this);
}

void OrderModifySamePrio::print(std::ostream& out) const {
    out << "OrderModifySamePrio{";
    out << "trd_reg_ts_time_in=";
    print::optional_duration(out, trd_reg_ts_time_in_);
    out << ", transact_time=";
    print::optional_duration(out, transact_time_);
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

bool OrderModifySamePrio::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderModifySamePrio*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderModifySamePrio::operator==(const OrderModifySamePrio& other) const {
    return trd_reg_ts_time_in_ == other.trd_reg_ts_time_in_
        && transact_time_ == other.transact_time_
        && prev_display_qty_ == other.prev_display_qty_
        && pad4_ == other.pad4_
        && security_id_ == other.security_id_
        && order_details_comp_ == other.order_details_comp_;
}

bool OrderModifySamePrio::operator!=(const OrderModifySamePrio& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v6_0
