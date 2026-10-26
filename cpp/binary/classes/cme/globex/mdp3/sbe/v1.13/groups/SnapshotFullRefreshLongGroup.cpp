#include "SnapshotFullRefreshLongGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

SnapshotFullRefreshLongGroup::SnapshotFullRefreshLongGroup(std::optional<Decimal> md_entry_px_optional_ex, std::optional<std::uint64_t> md_entry_size_optional, std::optional<std::int32_t> number_of_orders_optional, std::optional<std::uint8_t> md_price_level_unsigned_optional, std::optional<OpenCloseSettlFlag> open_close_settl_flag, MdEntryType md_entry_type)
  : md_entry_px_optional_ex_(md_entry_px_optional_ex), md_entry_size_optional_(md_entry_size_optional), number_of_orders_optional_(number_of_orders_optional), md_price_level_unsigned_optional_(md_price_level_unsigned_optional), open_close_settl_flag_(open_close_settl_flag), md_entry_type_(md_entry_type) {}

std::optional<Decimal> SnapshotFullRefreshLongGroup::md_entry_px_optional_ex() const { return md_entry_px_optional_ex_; }
void SnapshotFullRefreshLongGroup::set_md_entry_px_optional_ex(std::optional<Decimal> value) { md_entry_px_optional_ex_ = value; }

std::optional<std::uint64_t> SnapshotFullRefreshLongGroup::md_entry_size_optional() const { return md_entry_size_optional_; }
void SnapshotFullRefreshLongGroup::set_md_entry_size_optional(std::optional<std::uint64_t> value) { md_entry_size_optional_ = value; }

std::optional<std::int32_t> SnapshotFullRefreshLongGroup::number_of_orders_optional() const { return number_of_orders_optional_; }
void SnapshotFullRefreshLongGroup::set_number_of_orders_optional(std::optional<std::int32_t> value) { number_of_orders_optional_ = value; }

std::optional<std::uint8_t> SnapshotFullRefreshLongGroup::md_price_level_unsigned_optional() const { return md_price_level_unsigned_optional_; }
void SnapshotFullRefreshLongGroup::set_md_price_level_unsigned_optional(std::optional<std::uint8_t> value) { md_price_level_unsigned_optional_ = value; }

std::optional<OpenCloseSettlFlag> SnapshotFullRefreshLongGroup::open_close_settl_flag() const { return open_close_settl_flag_; }
void SnapshotFullRefreshLongGroup::set_open_close_settl_flag(std::optional<OpenCloseSettlFlag> value) { open_close_settl_flag_ = value; }

MdEntryType SnapshotFullRefreshLongGroup::md_entry_type() const { return md_entry_type_; }
void SnapshotFullRefreshLongGroup::set_md_entry_type(MdEntryType value) { md_entry_type_ = value; }

std::size_t SnapshotFullRefreshLongGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SnapshotFullRefreshLongGroup", wire_size, length);

    md_entry_px_optional_ex_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    md_entry_size_optional_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    number_of_orders_optional_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(2147483647LL));
    offset += 4;

    md_price_level_unsigned_optional_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    open_close_settl_flag_ = wire::nullable_enum<OpenCloseSettlFlag>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    md_entry_type_ = static_cast<MdEntryType>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t SnapshotFullRefreshLongGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SnapshotFullRefreshLongGroup", wire_size, capacity);

    wire::write_i64_le(data + offset, md_entry_px_optional_ex_ ? static_cast<std::int64_t>(md_entry_px_optional_ex_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_u64_le(data + offset, md_entry_size_optional_.value_or(static_cast<std::uint64_t>(18446744073709551615ULL)));
    offset += 8;

    wire::write_i32_le(data + offset, number_of_orders_optional_.value_or(static_cast<std::int32_t>(2147483647LL)));
    offset += 4;

    wire::write_u8(data + offset, md_price_level_unsigned_optional_.value_or(static_cast<std::uint8_t>(255ULL)));
    offset += 1;

    wire::write_u8(data + offset, open_close_settl_flag_ ? static_cast<std::uint8_t>(*open_close_settl_flag_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(md_entry_type_));
    offset += 1;

    return offset;
}

std::size_t SnapshotFullRefreshLongGroup::encoded_size() const {
    return wire_size;
}

void SnapshotFullRefreshLongGroup::print(std::ostream& out) const {
    out << "SnapshotFullRefreshLongGroup{";
    out << "md_entry_px_optional_ex=";
    print::optional(out, md_entry_px_optional_ex_);
    out << ", md_entry_size_optional=";
    print::optional(out, md_entry_size_optional_);
    out << ", number_of_orders_optional=";
    print::optional(out, number_of_orders_optional_);
    out << ", md_price_level_unsigned_optional=";
    print::optional(out, md_price_level_unsigned_optional_);
    out << ", open_close_settl_flag=";
    print::optional(out, open_close_settl_flag_);
    out << ", md_entry_type=";
    out << md_entry_type_;
    out << '}';
}

bool SnapshotFullRefreshLongGroup::operator==(const SnapshotFullRefreshLongGroup& other) const {
    return md_entry_px_optional_ex_ == other.md_entry_px_optional_ex_
        && md_entry_size_optional_ == other.md_entry_size_optional_
        && number_of_orders_optional_ == other.number_of_orders_optional_
        && md_price_level_unsigned_optional_ == other.md_price_level_unsigned_optional_
        && open_close_settl_flag_ == other.open_close_settl_flag_
        && md_entry_type_ == other.md_entry_type_;
}

bool SnapshotFullRefreshLongGroup::operator!=(const SnapshotFullRefreshLongGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SnapshotFullRefreshLongGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
