#include "SnapshotFullRefreshOrderBookGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

SnapshotFullRefreshOrderBookGroup::SnapshotFullRefreshOrderBookGroup(std::uint64_t order_id, std::optional<std::uint64_t> md_order_priority, Decimal md_entry_px_ex, std::int32_t md_display_qty, MdEntryTypeBook md_entry_type_book)
  : order_id_(order_id), md_order_priority_(md_order_priority), md_entry_px_ex_(md_entry_px_ex), md_display_qty_(md_display_qty), md_entry_type_book_(md_entry_type_book) {}

std::uint64_t SnapshotFullRefreshOrderBookGroup::order_id() const { return order_id_; }
void SnapshotFullRefreshOrderBookGroup::set_order_id(std::uint64_t value) { order_id_ = value; }

std::optional<std::uint64_t> SnapshotFullRefreshOrderBookGroup::md_order_priority() const { return md_order_priority_; }
void SnapshotFullRefreshOrderBookGroup::set_md_order_priority(std::optional<std::uint64_t> value) { md_order_priority_ = value; }

Decimal SnapshotFullRefreshOrderBookGroup::md_entry_px_ex() const { return md_entry_px_ex_; }
void SnapshotFullRefreshOrderBookGroup::set_md_entry_px_ex(Decimal value) { md_entry_px_ex_ = value; }

std::int32_t SnapshotFullRefreshOrderBookGroup::md_display_qty() const { return md_display_qty_; }
void SnapshotFullRefreshOrderBookGroup::set_md_display_qty(std::int32_t value) { md_display_qty_ = value; }

MdEntryTypeBook SnapshotFullRefreshOrderBookGroup::md_entry_type_book() const { return md_entry_type_book_; }
void SnapshotFullRefreshOrderBookGroup::set_md_entry_type_book(MdEntryTypeBook value) { md_entry_type_book_ = value; }

std::size_t SnapshotFullRefreshOrderBookGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SnapshotFullRefreshOrderBookGroup", wire_size, length);

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    md_order_priority_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    md_entry_px_ex_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -9);
    offset += 8;

    md_display_qty_ = wire::read_i32_le(data + offset);
    offset += 4;

    md_entry_type_book_ = static_cast<MdEntryTypeBook>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t SnapshotFullRefreshOrderBookGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SnapshotFullRefreshOrderBookGroup", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u64_le(data + offset, md_order_priority_.value_or(static_cast<std::uint64_t>(18446744073709551615ULL)));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(md_entry_px_ex_.mantissa()));
    offset += 8;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(md_display_qty_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(md_entry_type_book_));
    offset += 1;

    return offset;
}

std::size_t SnapshotFullRefreshOrderBookGroup::encoded_size() const {
    return wire_size;
}

void SnapshotFullRefreshOrderBookGroup::print(std::ostream& out) const {
    out << "SnapshotFullRefreshOrderBookGroup{";
    out << "order_id=";
    out << order_id_;
    out << ", md_order_priority=";
    print::optional(out, md_order_priority_);
    out << ", md_entry_px_ex=";
    out << md_entry_px_ex_;
    out << ", md_display_qty=";
    out << md_display_qty_;
    out << ", md_entry_type_book=";
    out << md_entry_type_book_;
    out << '}';
}

bool SnapshotFullRefreshOrderBookGroup::operator==(const SnapshotFullRefreshOrderBookGroup& other) const {
    return order_id_ == other.order_id_
        && md_order_priority_ == other.md_order_priority_
        && md_entry_px_ex_ == other.md_entry_px_ex_
        && md_display_qty_ == other.md_display_qty_
        && md_entry_type_book_ == other.md_entry_type_book_;
}

bool SnapshotFullRefreshOrderBookGroup::operator!=(const SnapshotFullRefreshOrderBookGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SnapshotFullRefreshOrderBookGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
