#include "OrderMassDeleteMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

OrderMassDeleteMessage::OrderMassDeleteMessage(std::int64_t security_id, std::chrono::nanoseconds transact_time)
  : security_id_(security_id), transact_time_(transact_time) {}

std::int64_t OrderMassDeleteMessage::security_id() const { return security_id_; }
void OrderMassDeleteMessage::set_security_id(std::int64_t value) { security_id_ = value; }

std::chrono::nanoseconds OrderMassDeleteMessage::transact_time() const { return transact_time_; }
void OrderMassDeleteMessage::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

MessageCode OrderMassDeleteMessage::type() const { return message_type; }

std::string_view OrderMassDeleteMessage::name() const { return "Order Mass Delete Message"; }

std::size_t OrderMassDeleteMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderMassDeleteMessage", wire_size, length);

    security_id_ = wire::read_i64_le(data + offset);
    offset += 8;

    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    return offset;
}

std::size_t OrderMassDeleteMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderMassDeleteMessage", wire_size, capacity);

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(security_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    return offset;
}

std::size_t OrderMassDeleteMessage::encoded_size() const {
    return wire_size;
}

void OrderMassDeleteMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderMassDeleteMessage::clone() const {
    return std::make_unique<OrderMassDeleteMessage>(*this);
}

void OrderMassDeleteMessage::print(std::ostream& out) const {
    out << "OrderMassDeleteMessage{";
    out << "security_id=";
    out << security_id_;
    out << ", transact_time=";
    out << transact_time_.count();
    out << '}';
}

bool OrderMassDeleteMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderMassDeleteMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderMassDeleteMessage::operator==(const OrderMassDeleteMessage& other) const {
    return security_id_ == other.security_id_
        && transact_time_ == other.transact_time_;
}

bool OrderMassDeleteMessage::operator!=(const OrderMassDeleteMessage& other) const {
    return !(*this == other);
}

} // namespace bse::bseindia::eobi::fbe::v1_4
