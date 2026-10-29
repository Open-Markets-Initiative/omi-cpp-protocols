#include "OrderModifyMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

OrderModifyMessage::OrderModifyMessage(std::optional<std::chrono::nanoseconds> trd_reg_ts_time_in, std::chrono::nanoseconds trd_reg_ts_prev_time_priority, Decimal prev_price, std::int64_t prev_display_qty, std::int64_t security_id, const OrderDetails& order_details)
  : trd_reg_ts_time_in_(trd_reg_ts_time_in), trd_reg_ts_prev_time_priority_(trd_reg_ts_prev_time_priority), prev_price_(prev_price), prev_display_qty_(prev_display_qty), security_id_(security_id), order_details_(order_details) {}

std::optional<std::chrono::nanoseconds> OrderModifyMessage::trd_reg_ts_time_in() const { return trd_reg_ts_time_in_; }
void OrderModifyMessage::set_trd_reg_ts_time_in(std::optional<std::chrono::nanoseconds> value) { trd_reg_ts_time_in_ = value; }

std::chrono::nanoseconds OrderModifyMessage::trd_reg_ts_prev_time_priority() const { return trd_reg_ts_prev_time_priority_; }
void OrderModifyMessage::set_trd_reg_ts_prev_time_priority(std::chrono::nanoseconds value) { trd_reg_ts_prev_time_priority_ = value; }

Decimal OrderModifyMessage::prev_price() const { return prev_price_; }
void OrderModifyMessage::set_prev_price(Decimal value) { prev_price_ = value; }

std::int64_t OrderModifyMessage::prev_display_qty() const { return prev_display_qty_; }
void OrderModifyMessage::set_prev_display_qty(std::int64_t value) { prev_display_qty_ = value; }

std::int64_t OrderModifyMessage::security_id() const { return security_id_; }
void OrderModifyMessage::set_security_id(std::int64_t value) { security_id_ = value; }

const OrderDetails& OrderModifyMessage::order_details() const { return order_details_; }
OrderDetails& OrderModifyMessage::order_details() { return order_details_; }
void OrderModifyMessage::set_order_details(const OrderDetails& value) { order_details_ = value; }

MessageCode OrderModifyMessage::type() const { return message_type; }

std::string_view OrderModifyMessage::name() const { return "Order Modify Message"; }

std::size_t OrderModifyMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderModifyMessage", wire_size, length);

    trd_reg_ts_time_in_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    trd_reg_ts_prev_time_priority_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    prev_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -6);
    offset += 8;

    prev_display_qty_ = wire::read_i64_le(data + offset);
    offset += 8;

    security_id_ = wire::read_i64_le(data + offset);
    offset += 8;

    offset += order_details_.decode(data + offset, length - offset);

    return offset;
}

std::size_t OrderModifyMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderModifyMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, trd_reg_ts_time_in_ ? static_cast<std::uint64_t>(trd_reg_ts_time_in_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(trd_reg_ts_prev_time_priority_.count()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(prev_price_.mantissa()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(prev_display_qty_));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(security_id_));
    offset += 8;

    offset += order_details_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t OrderModifyMessage::encoded_size() const {
    return wire_size;
}

void OrderModifyMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderModifyMessage::clone() const {
    return std::make_unique<OrderModifyMessage>(*this);
}

void OrderModifyMessage::print(std::ostream& out) const {
    out << "OrderModifyMessage{";
    out << "trd_reg_ts_time_in=";
    print::optional_duration(out, trd_reg_ts_time_in_);
    out << ", trd_reg_ts_prev_time_priority=";
    out << trd_reg_ts_prev_time_priority_.count();
    out << ", prev_price=";
    out << prev_price_;
    out << ", prev_display_qty=";
    out << prev_display_qty_;
    out << ", security_id=";
    out << security_id_;
    out << ", order_details=";
    order_details_.print(out);
    out << '}';
}

bool OrderModifyMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderModifyMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderModifyMessage::operator==(const OrderModifyMessage& other) const {
    return trd_reg_ts_time_in_ == other.trd_reg_ts_time_in_
        && trd_reg_ts_prev_time_priority_ == other.trd_reg_ts_prev_time_priority_
        && prev_price_ == other.prev_price_
        && prev_display_qty_ == other.prev_display_qty_
        && security_id_ == other.security_id_
        && order_details_ == other.order_details_;
}

bool OrderModifyMessage::operator!=(const OrderModifyMessage& other) const {
    return !(*this == other);
}

} // namespace bse::bseindia::eobi::fbe::v1_4
