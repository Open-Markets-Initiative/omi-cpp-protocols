#include "OrderMassDelete.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

OrderMassDelete::OrderMassDelete(std::optional<std::int64_t> security_id, std::optional<std::chrono::nanoseconds> transact_time)
  : security_id_(security_id), transact_time_(transact_time) {}

std::optional<std::int64_t> OrderMassDelete::security_id() const { return security_id_; }
void OrderMassDelete::set_security_id(std::optional<std::int64_t> value) { security_id_ = value; }

std::optional<std::chrono::nanoseconds> OrderMassDelete::transact_time() const { return transact_time_; }
void OrderMassDelete::set_transact_time(std::optional<std::chrono::nanoseconds> value) { transact_time_ = value; }

MessageCode OrderMassDelete::type() const { return message_type; }

std::string_view OrderMassDelete::name() const { return "Order Mass Delete"; }

std::size_t OrderMassDelete::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderMassDelete", wire_size, length);

    security_id_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    transact_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    return offset;
}

std::size_t OrderMassDelete::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderMassDelete", wire_size, capacity);

    wire::write_i64_le(data + offset, security_id_.value_or(static_cast<std::int64_t>(0x8000000000000000LL)));
    offset += 8;

    wire::write_u64_le(data + offset, transact_time_ ? static_cast<std::uint64_t>(transact_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    return offset;
}

std::size_t OrderMassDelete::encoded_size() const {
    return wire_size;
}

void OrderMassDelete::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderMassDelete::clone() const {
    return std::make_unique<OrderMassDelete>(*this);
}

void OrderMassDelete::print(std::ostream& out) const {
    out << "OrderMassDelete{";
    out << "security_id=";
    print::optional(out, security_id_);
    out << ", transact_time=";
    print::optional_duration(out, transact_time_);
    out << '}';
}

bool OrderMassDelete::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderMassDelete*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderMassDelete::operator==(const OrderMassDelete& other) const {
    return security_id_ == other.security_id_
        && transact_time_ == other.transact_time_;
}

bool OrderMassDelete::operator!=(const OrderMassDelete& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v13_0
