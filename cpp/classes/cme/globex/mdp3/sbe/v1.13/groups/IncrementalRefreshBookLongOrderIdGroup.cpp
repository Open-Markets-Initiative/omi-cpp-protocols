#include "IncrementalRefreshBookLongOrderIdGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

IncrementalRefreshBookLongOrderIdGroup::IncrementalRefreshBookLongOrderIdGroup(std::uint64_t order_id, std::optional<std::uint64_t> md_order_priority_optional, std::optional<std::int32_t> md_display_qty_optional, std::optional<std::uint8_t> reference_id, OrderUpdateAction order_update_action, const std::array<std::byte, 2>& padding_2)
  : order_id_(order_id), md_order_priority_optional_(md_order_priority_optional), md_display_qty_optional_(md_display_qty_optional), reference_id_(reference_id), order_update_action_(order_update_action), padding_2_(padding_2) {}

std::uint64_t IncrementalRefreshBookLongOrderIdGroup::order_id() const { return order_id_; }
void IncrementalRefreshBookLongOrderIdGroup::set_order_id(std::uint64_t value) { order_id_ = value; }

std::optional<std::uint64_t> IncrementalRefreshBookLongOrderIdGroup::md_order_priority_optional() const { return md_order_priority_optional_; }
void IncrementalRefreshBookLongOrderIdGroup::set_md_order_priority_optional(std::optional<std::uint64_t> value) { md_order_priority_optional_ = value; }

std::optional<std::int32_t> IncrementalRefreshBookLongOrderIdGroup::md_display_qty_optional() const { return md_display_qty_optional_; }
void IncrementalRefreshBookLongOrderIdGroup::set_md_display_qty_optional(std::optional<std::int32_t> value) { md_display_qty_optional_ = value; }

std::optional<std::uint8_t> IncrementalRefreshBookLongOrderIdGroup::reference_id() const { return reference_id_; }
void IncrementalRefreshBookLongOrderIdGroup::set_reference_id(std::optional<std::uint8_t> value) { reference_id_ = value; }

OrderUpdateAction IncrementalRefreshBookLongOrderIdGroup::order_update_action() const { return order_update_action_; }
void IncrementalRefreshBookLongOrderIdGroup::set_order_update_action(OrderUpdateAction value) { order_update_action_ = value; }

const std::array<std::byte, 2>& IncrementalRefreshBookLongOrderIdGroup::padding_2() const { return padding_2_; }
std::array<std::byte, 2>& IncrementalRefreshBookLongOrderIdGroup::padding_2() { return padding_2_; }
void IncrementalRefreshBookLongOrderIdGroup::set_padding_2(const std::array<std::byte, 2>& value) { padding_2_ = value; }

std::size_t IncrementalRefreshBookLongOrderIdGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("IncrementalRefreshBookLongOrderIdGroup", wire_size, length);

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    md_order_priority_optional_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    md_display_qty_optional_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(2147483647LL));
    offset += 4;

    reference_id_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    order_update_action_ = static_cast<OrderUpdateAction>(wire::read_u8(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, padding_2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t IncrementalRefreshBookLongOrderIdGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("IncrementalRefreshBookLongOrderIdGroup", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u64_le(data + offset, md_order_priority_optional_.value_or(static_cast<std::uint64_t>(18446744073709551615ULL)));
    offset += 8;

    wire::write_i32_le(data + offset, md_display_qty_optional_.value_or(static_cast<std::int32_t>(2147483647LL)));
    offset += 4;

    wire::write_u8(data + offset, reference_id_.value_or(static_cast<std::uint8_t>(255ULL)));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(order_update_action_));
    offset += 1;

    wire::write_bytes(data + offset, padding_2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t IncrementalRefreshBookLongOrderIdGroup::encoded_size() const {
    return wire_size;
}

void IncrementalRefreshBookLongOrderIdGroup::print(std::ostream& out) const {
    out << "IncrementalRefreshBookLongOrderIdGroup{";
    out << "order_id=";
    out << order_id_;
    out << ", md_order_priority_optional=";
    print::optional(out, md_order_priority_optional_);
    out << ", md_display_qty_optional=";
    print::optional(out, md_display_qty_optional_);
    out << ", reference_id=";
    print::optional(out, reference_id_);
    out << ", order_update_action=";
    out << order_update_action_;
    out << ", padding_2=";
    print::hex(out, padding_2_.data(), padding_2_.size());
    out << '}';
}

bool IncrementalRefreshBookLongOrderIdGroup::operator==(const IncrementalRefreshBookLongOrderIdGroup& other) const {
    return order_id_ == other.order_id_
        && md_order_priority_optional_ == other.md_order_priority_optional_
        && md_display_qty_optional_ == other.md_display_qty_optional_
        && reference_id_ == other.reference_id_
        && order_update_action_ == other.order_update_action_
        && padding_2_ == other.padding_2_;
}

bool IncrementalRefreshBookLongOrderIdGroup::operator!=(const IncrementalRefreshBookLongOrderIdGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshBookLongOrderIdGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
