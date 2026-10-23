#include "IncrementalRefreshOrderBookGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

IncrementalRefreshOrderBookGroup::IncrementalRefreshOrderBookGroup(std::optional<std::uint64_t> order_id_optional, std::optional<std::uint64_t> md_order_priority, std::optional<Decimal> md_entry_px_optional_ex, std::optional<std::int32_t> md_display_qty_optional, std::int32_t security_id, MdUpdateAction md_update_action, MdEntryTypeBook md_entry_type_book, const std::array<std::byte, 6>& padding_6)
  : order_id_optional_(order_id_optional), md_order_priority_(md_order_priority), md_entry_px_optional_ex_(md_entry_px_optional_ex), md_display_qty_optional_(md_display_qty_optional), security_id_(security_id), md_update_action_(md_update_action), md_entry_type_book_(md_entry_type_book), padding_6_(padding_6) {}

std::optional<std::uint64_t> IncrementalRefreshOrderBookGroup::order_id_optional() const { return order_id_optional_; }
void IncrementalRefreshOrderBookGroup::set_order_id_optional(std::optional<std::uint64_t> value) { order_id_optional_ = value; }

std::optional<std::uint64_t> IncrementalRefreshOrderBookGroup::md_order_priority() const { return md_order_priority_; }
void IncrementalRefreshOrderBookGroup::set_md_order_priority(std::optional<std::uint64_t> value) { md_order_priority_ = value; }

std::optional<Decimal> IncrementalRefreshOrderBookGroup::md_entry_px_optional_ex() const { return md_entry_px_optional_ex_; }
void IncrementalRefreshOrderBookGroup::set_md_entry_px_optional_ex(std::optional<Decimal> value) { md_entry_px_optional_ex_ = value; }

std::optional<std::int32_t> IncrementalRefreshOrderBookGroup::md_display_qty_optional() const { return md_display_qty_optional_; }
void IncrementalRefreshOrderBookGroup::set_md_display_qty_optional(std::optional<std::int32_t> value) { md_display_qty_optional_ = value; }

std::int32_t IncrementalRefreshOrderBookGroup::security_id() const { return security_id_; }
void IncrementalRefreshOrderBookGroup::set_security_id(std::int32_t value) { security_id_ = value; }

MdUpdateAction IncrementalRefreshOrderBookGroup::md_update_action() const { return md_update_action_; }
void IncrementalRefreshOrderBookGroup::set_md_update_action(MdUpdateAction value) { md_update_action_ = value; }

MdEntryTypeBook IncrementalRefreshOrderBookGroup::md_entry_type_book() const { return md_entry_type_book_; }
void IncrementalRefreshOrderBookGroup::set_md_entry_type_book(MdEntryTypeBook value) { md_entry_type_book_ = value; }

const std::array<std::byte, 6>& IncrementalRefreshOrderBookGroup::padding_6() const { return padding_6_; }
std::array<std::byte, 6>& IncrementalRefreshOrderBookGroup::padding_6() { return padding_6_; }
void IncrementalRefreshOrderBookGroup::set_padding_6(const std::array<std::byte, 6>& value) { padding_6_ = value; }

std::size_t IncrementalRefreshOrderBookGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("IncrementalRefreshOrderBookGroup", wire_size, length);

    order_id_optional_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    md_order_priority_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    md_entry_px_optional_ex_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    md_display_qty_optional_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(2147483647LL));
    offset += 4;

    security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    md_update_action_ = static_cast<MdUpdateAction>(wire::read_u8(data + offset));
    offset += 1;

    md_entry_type_book_ = static_cast<MdEntryTypeBook>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, padding_6_.data(), 6);
    offset += 6;

    return offset;
}

std::size_t IncrementalRefreshOrderBookGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("IncrementalRefreshOrderBookGroup", wire_size, capacity);

    wire::write_u64_le(data + offset, order_id_optional_.value_or(static_cast<std::uint64_t>(18446744073709551615ULL)));
    offset += 8;

    wire::write_u64_le(data + offset, md_order_priority_.value_or(static_cast<std::uint64_t>(18446744073709551615ULL)));
    offset += 8;

    wire::write_i64_le(data + offset, md_entry_px_optional_ex_ ? static_cast<std::int64_t>(md_entry_px_optional_ex_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i32_le(data + offset, md_display_qty_optional_.value_or(static_cast<std::int32_t>(2147483647LL)));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(security_id_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(md_update_action_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(md_entry_type_book_));
    offset += 1;

    wire::write_bytes(data + offset, padding_6_.data(), 6);
    offset += 6;

    return offset;
}

std::size_t IncrementalRefreshOrderBookGroup::encoded_size() const {
    return wire_size;
}

void IncrementalRefreshOrderBookGroup::print(std::ostream& out) const {
    out << "IncrementalRefreshOrderBookGroup{";
    out << "order_id_optional=";
    print::optional(out, order_id_optional_);
    out << ", md_order_priority=";
    print::optional(out, md_order_priority_);
    out << ", md_entry_px_optional_ex=";
    print::optional(out, md_entry_px_optional_ex_);
    out << ", md_display_qty_optional=";
    print::optional(out, md_display_qty_optional_);
    out << ", security_id=";
    out << security_id_;
    out << ", md_update_action=";
    out << md_update_action_;
    out << ", md_entry_type_book=";
    out << md_entry_type_book_;
    out << ", padding_6=";
    print::hex(out, padding_6_.data(), padding_6_.size());
    out << '}';
}

bool IncrementalRefreshOrderBookGroup::operator==(const IncrementalRefreshOrderBookGroup& other) const {
    return order_id_optional_ == other.order_id_optional_
        && md_order_priority_ == other.md_order_priority_
        && md_entry_px_optional_ex_ == other.md_entry_px_optional_ex_
        && md_display_qty_optional_ == other.md_display_qty_optional_
        && security_id_ == other.security_id_
        && md_update_action_ == other.md_update_action_
        && md_entry_type_book_ == other.md_entry_type_book_
        && padding_6_ == other.padding_6_;
}

bool IncrementalRefreshOrderBookGroup::operator!=(const IncrementalRefreshOrderBookGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshOrderBookGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
