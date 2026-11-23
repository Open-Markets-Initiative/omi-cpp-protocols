// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: groups/CopOrder.cpp
#include "CopOrder.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

CopOrder::CopOrder(std::optional<std::uint16_t> broker_number, std::optional<std::uint64_t> order_id)
  : broker_number_(broker_number), order_id_(order_id) {}

std::optional<std::uint16_t> CopOrder::broker_number() const { return broker_number_; }
void CopOrder::set_broker_number(std::optional<std::uint16_t> value) { broker_number_ = value; }

std::optional<std::uint64_t> CopOrder::order_id() const { return order_id_; }
void CopOrder::set_order_id(std::optional<std::uint64_t> value) { order_id_ = value; }

std::size_t CopOrder::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CopOrder", wire_size, length);

    broker_number_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0ULL));
    offset += 2;

    order_id_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t CopOrder::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CopOrder", wire_size, capacity);

    wire::write_u16_le(data + offset, broker_number_.value_or(static_cast<std::uint16_t>(0ULL)));
    offset += 2;

    wire::write_u64_le(data + offset, order_id_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    return offset;
}

std::size_t CopOrder::encoded_size() const {
    return wire_size;
}

void CopOrder::print(std::ostream& out) const {
    out << "CopOrder{";
    out << "broker_number=";
    print::optional(out, broker_number_);
    out << ", order_id=";
    print::optional(out, order_id_);
    out << '}';
}

bool CopOrder::operator==(const CopOrder& other) const {
    return broker_number_ == other.broker_number_
        && order_id_ == other.order_id_;
}

bool CopOrder::operator!=(const CopOrder& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const CopOrder& value) {
    value.print(out);
    return out;
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
