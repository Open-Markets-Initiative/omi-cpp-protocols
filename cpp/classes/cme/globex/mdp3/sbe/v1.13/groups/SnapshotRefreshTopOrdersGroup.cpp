#include "SnapshotRefreshTopOrdersGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

SnapshotRefreshTopOrdersGroup::SnapshotRefreshTopOrdersGroup(std::uint64_t order_id, std::uint64_t md_order_priority, Decimal md_entry_px_ex, std::int32_t md_display_qty, MdEntryTypeBook md_entry_type_book)
  : order_id_(order_id), md_order_priority_(md_order_priority), md_entry_px_ex_(md_entry_px_ex), md_display_qty_(md_display_qty), md_entry_type_book_(md_entry_type_book) {}

std::uint64_t SnapshotRefreshTopOrdersGroup::order_id() const { return order_id_; }
void SnapshotRefreshTopOrdersGroup::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint64_t SnapshotRefreshTopOrdersGroup::md_order_priority() const { return md_order_priority_; }
void SnapshotRefreshTopOrdersGroup::set_md_order_priority(std::uint64_t value) { md_order_priority_ = value; }

Decimal SnapshotRefreshTopOrdersGroup::md_entry_px_ex() const { return md_entry_px_ex_; }
void SnapshotRefreshTopOrdersGroup::set_md_entry_px_ex(Decimal value) { md_entry_px_ex_ = value; }

std::int32_t SnapshotRefreshTopOrdersGroup::md_display_qty() const { return md_display_qty_; }
void SnapshotRefreshTopOrdersGroup::set_md_display_qty(std::int32_t value) { md_display_qty_ = value; }

MdEntryTypeBook SnapshotRefreshTopOrdersGroup::md_entry_type_book() const { return md_entry_type_book_; }
void SnapshotRefreshTopOrdersGroup::set_md_entry_type_book(MdEntryTypeBook value) { md_entry_type_book_ = value; }

std::size_t SnapshotRefreshTopOrdersGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SnapshotRefreshTopOrdersGroup", wire_size, length);

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    md_order_priority_ = wire::read_u64_le(data + offset);
    offset += 8;

    md_entry_px_ex_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -9);
    offset += 8;

    md_display_qty_ = wire::read_i32_le(data + offset);
    offset += 4;

    md_entry_type_book_ = static_cast<MdEntryTypeBook>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t SnapshotRefreshTopOrdersGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SnapshotRefreshTopOrdersGroup", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(md_order_priority_));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(md_entry_px_ex_.mantissa()));
    offset += 8;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(md_display_qty_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(md_entry_type_book_));
    offset += 1;

    return offset;
}

std::size_t SnapshotRefreshTopOrdersGroup::encoded_size() const {
    return wire_size;
}

void SnapshotRefreshTopOrdersGroup::print(std::ostream& out) const {
    out << "SnapshotRefreshTopOrdersGroup{";
    out << "order_id=";
    out << order_id_;
    out << ", md_order_priority=";
    out << md_order_priority_;
    out << ", md_entry_px_ex=";
    out << md_entry_px_ex_;
    out << ", md_display_qty=";
    out << md_display_qty_;
    out << ", md_entry_type_book=";
    out << md_entry_type_book_;
    out << '}';
}

bool SnapshotRefreshTopOrdersGroup::operator==(const SnapshotRefreshTopOrdersGroup& other) const {
    return order_id_ == other.order_id_
        && md_order_priority_ == other.md_order_priority_
        && md_entry_px_ex_ == other.md_entry_px_ex_
        && md_display_qty_ == other.md_display_qty_
        && md_entry_type_book_ == other.md_entry_type_book_;
}

bool SnapshotRefreshTopOrdersGroup::operator!=(const SnapshotRefreshTopOrdersGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SnapshotRefreshTopOrdersGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
