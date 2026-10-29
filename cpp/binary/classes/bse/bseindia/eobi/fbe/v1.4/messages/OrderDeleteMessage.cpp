#include "OrderDeleteMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

OrderDeleteMessage::OrderDeleteMessage(std::optional<std::chrono::nanoseconds> trd_reg_ts_time_in, std::chrono::nanoseconds transact_time, std::int64_t security_id, const OrderDetails& order_details)
  : trd_reg_ts_time_in_(trd_reg_ts_time_in), transact_time_(transact_time), security_id_(security_id), order_details_(order_details) {}

std::optional<std::chrono::nanoseconds> OrderDeleteMessage::trd_reg_ts_time_in() const { return trd_reg_ts_time_in_; }
void OrderDeleteMessage::set_trd_reg_ts_time_in(std::optional<std::chrono::nanoseconds> value) { trd_reg_ts_time_in_ = value; }

std::chrono::nanoseconds OrderDeleteMessage::transact_time() const { return transact_time_; }
void OrderDeleteMessage::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

std::int64_t OrderDeleteMessage::security_id() const { return security_id_; }
void OrderDeleteMessage::set_security_id(std::int64_t value) { security_id_ = value; }

const OrderDetails& OrderDeleteMessage::order_details() const { return order_details_; }
OrderDetails& OrderDeleteMessage::order_details() { return order_details_; }
void OrderDeleteMessage::set_order_details(const OrderDetails& value) { order_details_ = value; }

MessageCode OrderDeleteMessage::type() const { return message_type; }

std::string_view OrderDeleteMessage::name() const { return "Order Delete Message"; }

std::size_t OrderDeleteMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderDeleteMessage", wire_size, length);

    trd_reg_ts_time_in_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    security_id_ = wire::read_i64_le(data + offset);
    offset += 8;

    offset += order_details_.decode(data + offset, length - offset);

    return offset;
}

std::size_t OrderDeleteMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderDeleteMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, trd_reg_ts_time_in_ ? static_cast<std::uint64_t>(trd_reg_ts_time_in_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(security_id_));
    offset += 8;

    offset += order_details_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t OrderDeleteMessage::encoded_size() const {
    return wire_size;
}

void OrderDeleteMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderDeleteMessage::clone() const {
    return std::make_unique<OrderDeleteMessage>(*this);
}

void OrderDeleteMessage::print(std::ostream& out) const {
    out << "OrderDeleteMessage{";
    out << "trd_reg_ts_time_in=";
    print::optional_duration(out, trd_reg_ts_time_in_);
    out << ", transact_time=";
    out << transact_time_.count();
    out << ", security_id=";
    out << security_id_;
    out << ", order_details=";
    order_details_.print(out);
    out << '}';
}

bool OrderDeleteMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderDeleteMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderDeleteMessage::operator==(const OrderDeleteMessage& other) const {
    return trd_reg_ts_time_in_ == other.trd_reg_ts_time_in_
        && transact_time_ == other.transact_time_
        && security_id_ == other.security_id_
        && order_details_ == other.order_details_;
}

bool OrderDeleteMessage::operator!=(const OrderDeleteMessage& other) const {
    return !(*this == other);
}

} // namespace bse::bseindia::eobi::fbe::v1_4
