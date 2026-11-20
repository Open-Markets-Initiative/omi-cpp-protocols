// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: groups/CopLimit.cpp
#include "CopLimit.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

CopLimit::CopLimit(std::optional<std::uint16_t> broker_number, std::optional<std::uint64_t> order_id, std::optional<Decimal> price)
  : broker_number_(broker_number), order_id_(order_id), price_(price) {}

std::optional<std::uint16_t> CopLimit::broker_number() const { return broker_number_; }
void CopLimit::set_broker_number(std::optional<std::uint16_t> value) { broker_number_ = value; }

std::optional<std::uint64_t> CopLimit::order_id() const { return order_id_; }
void CopLimit::set_order_id(std::optional<std::uint64_t> value) { order_id_ = value; }

std::optional<Decimal> CopLimit::price() const { return price_; }
void CopLimit::set_price(std::optional<Decimal> value) { price_ = value; }

std::size_t CopLimit::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CopLimit", wire_size, length);

    broker_number_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0ULL));
    offset += 2;

    order_id_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    price_ = wire::nullable_decimal(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL), -6);
    offset += 8;

    return offset;
}

std::size_t CopLimit::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CopLimit", wire_size, capacity);

    wire::write_u16_le(data + offset, broker_number_.value_or(static_cast<std::uint16_t>(0ULL)));
    offset += 2;

    wire::write_u64_le(data + offset, order_id_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u64_le(data + offset, price_ ? static_cast<std::uint64_t>(price_->mantissa()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t CopLimit::encoded_size() const {
    return wire_size;
}

void CopLimit::print(std::ostream& out) const {
    out << "CopLimit{";
    out << "broker_number=";
    print::optional(out, broker_number_);
    out << ", order_id=";
    print::optional(out, order_id_);
    out << ", price=";
    print::optional(out, price_);
    out << '}';
}

bool CopLimit::operator==(const CopLimit& other) const {
    return broker_number_ == other.broker_number_
        && order_id_ == other.order_id_
        && price_ == other.price_;
}

bool CopLimit::operator!=(const CopLimit& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const CopLimit& value) {
    value.print(out);
    return out;
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
