#include "OrderAddMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

OrderAddMessage::OrderAddMessage(std::optional<std::chrono::nanoseconds> trd_reg_ts_time_in, std::int64_t security_id, const OrderDetails& order_details)
  : trd_reg_ts_time_in_(trd_reg_ts_time_in), security_id_(security_id), order_details_(order_details) {}

std::optional<std::chrono::nanoseconds> OrderAddMessage::trd_reg_ts_time_in() const { return trd_reg_ts_time_in_; }
void OrderAddMessage::set_trd_reg_ts_time_in(std::optional<std::chrono::nanoseconds> value) { trd_reg_ts_time_in_ = value; }

std::int64_t OrderAddMessage::security_id() const { return security_id_; }
void OrderAddMessage::set_security_id(std::int64_t value) { security_id_ = value; }

const OrderDetails& OrderAddMessage::order_details() const { return order_details_; }
OrderDetails& OrderAddMessage::order_details() { return order_details_; }
void OrderAddMessage::set_order_details(const OrderDetails& value) { order_details_ = value; }

MessageCode OrderAddMessage::type() const { return message_type; }

std::string_view OrderAddMessage::name() const { return "Order Add Message"; }

std::size_t OrderAddMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderAddMessage", wire_size, length);

    trd_reg_ts_time_in_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    security_id_ = wire::read_i64_le(data + offset);
    offset += 8;

    offset += order_details_.decode(data + offset, length - offset);

    return offset;
}

std::size_t OrderAddMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderAddMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, trd_reg_ts_time_in_ ? static_cast<std::uint64_t>(trd_reg_ts_time_in_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(security_id_));
    offset += 8;

    offset += order_details_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t OrderAddMessage::encoded_size() const {
    return wire_size;
}

void OrderAddMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderAddMessage::clone() const {
    return std::make_unique<OrderAddMessage>(*this);
}

void OrderAddMessage::print(std::ostream& out) const {
    out << "OrderAddMessage{";
    out << "trd_reg_ts_time_in=";
    print::optional_duration(out, trd_reg_ts_time_in_);
    out << ", security_id=";
    out << security_id_;
    out << ", order_details=";
    order_details_.print(out);
    out << '}';
}

bool OrderAddMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderAddMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderAddMessage::operator==(const OrderAddMessage& other) const {
    return trd_reg_ts_time_in_ == other.trd_reg_ts_time_in_
        && security_id_ == other.security_id_
        && order_details_ == other.order_details_;
}

bool OrderAddMessage::operator!=(const OrderAddMessage& other) const {
    return !(*this == other);
}

} // namespace bse::bseindia::eobi::fbe::v1_4
