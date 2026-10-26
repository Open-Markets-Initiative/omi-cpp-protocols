#include "OrderModifySamePrio.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

OrderModifySamePrio::OrderModifySamePrio(std::optional<std::chrono::nanoseconds> request_time, std::optional<std::chrono::nanoseconds> transact_time, std::optional<Decimal> prev_display_qty, std::optional<std::int64_t> security_id, const OrderDetailsComp& order_details_comp)
  : request_time_(request_time), transact_time_(transact_time), prev_display_qty_(prev_display_qty), security_id_(security_id), order_details_comp_(order_details_comp) {}

std::optional<std::chrono::nanoseconds> OrderModifySamePrio::request_time() const { return request_time_; }
void OrderModifySamePrio::set_request_time(std::optional<std::chrono::nanoseconds> value) { request_time_ = value; }

std::optional<std::chrono::nanoseconds> OrderModifySamePrio::transact_time() const { return transact_time_; }
void OrderModifySamePrio::set_transact_time(std::optional<std::chrono::nanoseconds> value) { transact_time_ = value; }

std::optional<Decimal> OrderModifySamePrio::prev_display_qty() const { return prev_display_qty_; }
void OrderModifySamePrio::set_prev_display_qty(std::optional<Decimal> value) { prev_display_qty_ = value; }

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

    request_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    transact_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    prev_display_qty_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -4);
    offset += 8;

    security_id_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    offset += order_details_comp_.decode(data + offset, length - offset);

    return offset;
}

std::size_t OrderModifySamePrio::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderModifySamePrio", wire_size, capacity);

    wire::write_u64_le(data + offset, request_time_ ? static_cast<std::uint64_t>(request_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_u64_le(data + offset, transact_time_ ? static_cast<std::uint64_t>(transact_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_i64_le(data + offset, prev_display_qty_ ? static_cast<std::int64_t>(prev_display_qty_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

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
    out << "request_time=";
    print::optional_duration(out, request_time_);
    out << ", transact_time=";
    print::optional_duration(out, transact_time_);
    out << ", prev_display_qty=";
    print::optional(out, prev_display_qty_);
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
    return request_time_ == other.request_time_
        && transact_time_ == other.transact_time_
        && prev_display_qty_ == other.prev_display_qty_
        && security_id_ == other.security_id_
        && order_details_comp_ == other.order_details_comp_;
}

bool OrderModifySamePrio::operator!=(const OrderModifySamePrio& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v13_0
