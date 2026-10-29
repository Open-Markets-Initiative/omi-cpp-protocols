#include "OrderDelete.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

OrderDelete::OrderDelete(std::optional<std::chrono::nanoseconds> trd_reg_ts_time_in, std::optional<std::chrono::nanoseconds> transact_time, std::optional<std::int64_t> security_id, const OrderDetailsComp& order_details_comp)
  : trd_reg_ts_time_in_(trd_reg_ts_time_in), transact_time_(transact_time), security_id_(security_id), order_details_comp_(order_details_comp) {}

std::optional<std::chrono::nanoseconds> OrderDelete::trd_reg_ts_time_in() const { return trd_reg_ts_time_in_; }
void OrderDelete::set_trd_reg_ts_time_in(std::optional<std::chrono::nanoseconds> value) { trd_reg_ts_time_in_ = value; }

std::optional<std::chrono::nanoseconds> OrderDelete::transact_time() const { return transact_time_; }
void OrderDelete::set_transact_time(std::optional<std::chrono::nanoseconds> value) { transact_time_ = value; }

std::optional<std::int64_t> OrderDelete::security_id() const { return security_id_; }
void OrderDelete::set_security_id(std::optional<std::int64_t> value) { security_id_ = value; }

const OrderDetailsComp& OrderDelete::order_details_comp() const { return order_details_comp_; }
OrderDetailsComp& OrderDelete::order_details_comp() { return order_details_comp_; }
void OrderDelete::set_order_details_comp(const OrderDetailsComp& value) { order_details_comp_ = value; }

MessageCode OrderDelete::type() const { return message_type; }

std::string_view OrderDelete::name() const { return "Order Delete"; }

std::size_t OrderDelete::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderDelete", wire_size, length);

    trd_reg_ts_time_in_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    transact_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    security_id_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    offset += order_details_comp_.decode(data + offset, length - offset);

    return offset;
}

std::size_t OrderDelete::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderDelete", wire_size, capacity);

    wire::write_u64_le(data + offset, trd_reg_ts_time_in_ ? static_cast<std::uint64_t>(trd_reg_ts_time_in_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_u64_le(data + offset, transact_time_ ? static_cast<std::uint64_t>(transact_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_i64_le(data + offset, security_id_.value_or(static_cast<std::int64_t>(0x8000000000000000LL)));
    offset += 8;

    offset += order_details_comp_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t OrderDelete::encoded_size() const {
    return wire_size;
}

void OrderDelete::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderDelete::clone() const {
    return std::make_unique<OrderDelete>(*this);
}

void OrderDelete::print(std::ostream& out) const {
    out << "OrderDelete{";
    out << "trd_reg_ts_time_in=";
    print::optional_duration(out, trd_reg_ts_time_in_);
    out << ", transact_time=";
    print::optional_duration(out, transact_time_);
    out << ", security_id=";
    print::optional(out, security_id_);
    out << ", order_details_comp=";
    order_details_comp_.print(out);
    out << '}';
}

bool OrderDelete::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderDelete*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderDelete::operator==(const OrderDelete& other) const {
    return trd_reg_ts_time_in_ == other.trd_reg_ts_time_in_
        && transact_time_ == other.transact_time_
        && security_id_ == other.security_id_
        && order_details_comp_ == other.order_details_comp_;
}

bool OrderDelete::operator!=(const OrderDelete& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v3_0
