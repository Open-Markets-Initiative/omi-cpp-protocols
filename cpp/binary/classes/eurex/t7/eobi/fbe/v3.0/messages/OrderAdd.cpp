#include "OrderAdd.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

OrderAdd::OrderAdd(std::optional<std::chrono::nanoseconds> trd_reg_ts_time_in, std::optional<std::int64_t> security_id, const OrderDetailsComp& order_details_comp)
  : trd_reg_ts_time_in_(trd_reg_ts_time_in), security_id_(security_id), order_details_comp_(order_details_comp) {}

std::optional<std::chrono::nanoseconds> OrderAdd::trd_reg_ts_time_in() const { return trd_reg_ts_time_in_; }
void OrderAdd::set_trd_reg_ts_time_in(std::optional<std::chrono::nanoseconds> value) { trd_reg_ts_time_in_ = value; }

std::optional<std::int64_t> OrderAdd::security_id() const { return security_id_; }
void OrderAdd::set_security_id(std::optional<std::int64_t> value) { security_id_ = value; }

const OrderDetailsComp& OrderAdd::order_details_comp() const { return order_details_comp_; }
OrderDetailsComp& OrderAdd::order_details_comp() { return order_details_comp_; }
void OrderAdd::set_order_details_comp(const OrderDetailsComp& value) { order_details_comp_ = value; }

MessageCode OrderAdd::type() const { return message_type; }

std::string_view OrderAdd::name() const { return "Order Add"; }

std::size_t OrderAdd::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderAdd", wire_size, length);

    trd_reg_ts_time_in_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    security_id_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    offset += order_details_comp_.decode(data + offset, length - offset);

    return offset;
}

std::size_t OrderAdd::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderAdd", wire_size, capacity);

    wire::write_u64_le(data + offset, trd_reg_ts_time_in_ ? static_cast<std::uint64_t>(trd_reg_ts_time_in_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_i64_le(data + offset, security_id_.value_or(static_cast<std::int64_t>(0x8000000000000000LL)));
    offset += 8;

    offset += order_details_comp_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t OrderAdd::encoded_size() const {
    return wire_size;
}

void OrderAdd::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderAdd::clone() const {
    return std::make_unique<OrderAdd>(*this);
}

void OrderAdd::print(std::ostream& out) const {
    out << "OrderAdd{";
    out << "trd_reg_ts_time_in=";
    print::optional_duration(out, trd_reg_ts_time_in_);
    out << ", security_id=";
    print::optional(out, security_id_);
    out << ", order_details_comp=";
    order_details_comp_.print(out);
    out << '}';
}

bool OrderAdd::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderAdd*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderAdd::operator==(const OrderAdd& other) const {
    return trd_reg_ts_time_in_ == other.trd_reg_ts_time_in_
        && security_id_ == other.security_id_
        && order_details_comp_ == other.order_details_comp_;
}

bool OrderAdd::operator!=(const OrderAdd& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v3_0
