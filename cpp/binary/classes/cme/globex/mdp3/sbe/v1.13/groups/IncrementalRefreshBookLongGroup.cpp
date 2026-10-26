#include "IncrementalRefreshBookLongGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

IncrementalRefreshBookLongGroup::IncrementalRefreshBookLongGroup(std::optional<Decimal> md_entry_px_optional_ex, std::optional<std::uint64_t> md_entry_size_optional, std::int32_t security_id, std::uint32_t rpt_seq, std::optional<std::int32_t> number_of_orders_optional, std::uint8_t md_price_level, MdUpdateAction md_update_action, MdEntryTypeBook md_entry_type_book, const std::array<std::byte, 1>& padding_1)
  : md_entry_px_optional_ex_(md_entry_px_optional_ex), md_entry_size_optional_(md_entry_size_optional), security_id_(security_id), rpt_seq_(rpt_seq), number_of_orders_optional_(number_of_orders_optional), md_price_level_(md_price_level), md_update_action_(md_update_action), md_entry_type_book_(md_entry_type_book), padding_1_(padding_1) {}

std::optional<Decimal> IncrementalRefreshBookLongGroup::md_entry_px_optional_ex() const { return md_entry_px_optional_ex_; }
void IncrementalRefreshBookLongGroup::set_md_entry_px_optional_ex(std::optional<Decimal> value) { md_entry_px_optional_ex_ = value; }

std::optional<std::uint64_t> IncrementalRefreshBookLongGroup::md_entry_size_optional() const { return md_entry_size_optional_; }
void IncrementalRefreshBookLongGroup::set_md_entry_size_optional(std::optional<std::uint64_t> value) { md_entry_size_optional_ = value; }

std::int32_t IncrementalRefreshBookLongGroup::security_id() const { return security_id_; }
void IncrementalRefreshBookLongGroup::set_security_id(std::int32_t value) { security_id_ = value; }

std::uint32_t IncrementalRefreshBookLongGroup::rpt_seq() const { return rpt_seq_; }
void IncrementalRefreshBookLongGroup::set_rpt_seq(std::uint32_t value) { rpt_seq_ = value; }

std::optional<std::int32_t> IncrementalRefreshBookLongGroup::number_of_orders_optional() const { return number_of_orders_optional_; }
void IncrementalRefreshBookLongGroup::set_number_of_orders_optional(std::optional<std::int32_t> value) { number_of_orders_optional_ = value; }

std::uint8_t IncrementalRefreshBookLongGroup::md_price_level() const { return md_price_level_; }
void IncrementalRefreshBookLongGroup::set_md_price_level(std::uint8_t value) { md_price_level_ = value; }

MdUpdateAction IncrementalRefreshBookLongGroup::md_update_action() const { return md_update_action_; }
void IncrementalRefreshBookLongGroup::set_md_update_action(MdUpdateAction value) { md_update_action_ = value; }

MdEntryTypeBook IncrementalRefreshBookLongGroup::md_entry_type_book() const { return md_entry_type_book_; }
void IncrementalRefreshBookLongGroup::set_md_entry_type_book(MdEntryTypeBook value) { md_entry_type_book_ = value; }

const std::array<std::byte, 1>& IncrementalRefreshBookLongGroup::padding_1() const { return padding_1_; }
std::array<std::byte, 1>& IncrementalRefreshBookLongGroup::padding_1() { return padding_1_; }
void IncrementalRefreshBookLongGroup::set_padding_1(const std::array<std::byte, 1>& value) { padding_1_ = value; }

std::size_t IncrementalRefreshBookLongGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("IncrementalRefreshBookLongGroup", wire_size, length);

    md_entry_px_optional_ex_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    md_entry_size_optional_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    rpt_seq_ = wire::read_u32_le(data + offset);
    offset += 4;

    number_of_orders_optional_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(2147483647LL));
    offset += 4;

    md_price_level_ = wire::read_u8(data + offset);
    offset += 1;

    md_update_action_ = static_cast<MdUpdateAction>(wire::read_u8(data + offset));
    offset += 1;

    md_entry_type_book_ = static_cast<MdEntryTypeBook>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, padding_1_.data(), 1);
    offset += 1;

    return offset;
}

std::size_t IncrementalRefreshBookLongGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("IncrementalRefreshBookLongGroup", wire_size, capacity);

    wire::write_i64_le(data + offset, md_entry_px_optional_ex_ ? static_cast<std::int64_t>(md_entry_px_optional_ex_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_u64_le(data + offset, md_entry_size_optional_.value_or(static_cast<std::uint64_t>(18446744073709551615ULL)));
    offset += 8;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(security_id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(rpt_seq_));
    offset += 4;

    wire::write_i32_le(data + offset, number_of_orders_optional_.value_or(static_cast<std::int32_t>(2147483647LL)));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(md_price_level_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(md_update_action_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(md_entry_type_book_));
    offset += 1;

    wire::write_bytes(data + offset, padding_1_.data(), 1);
    offset += 1;

    return offset;
}

std::size_t IncrementalRefreshBookLongGroup::encoded_size() const {
    return wire_size;
}

void IncrementalRefreshBookLongGroup::print(std::ostream& out) const {
    out << "IncrementalRefreshBookLongGroup{";
    out << "md_entry_px_optional_ex=";
    print::optional(out, md_entry_px_optional_ex_);
    out << ", md_entry_size_optional=";
    print::optional(out, md_entry_size_optional_);
    out << ", security_id=";
    out << security_id_;
    out << ", rpt_seq=";
    out << rpt_seq_;
    out << ", number_of_orders_optional=";
    print::optional(out, number_of_orders_optional_);
    out << ", md_price_level=";
    out << static_cast<int>(md_price_level_);
    out << ", md_update_action=";
    out << md_update_action_;
    out << ", md_entry_type_book=";
    out << md_entry_type_book_;
    out << ", padding_1=";
    print::hex(out, padding_1_.data(), padding_1_.size());
    out << '}';
}

bool IncrementalRefreshBookLongGroup::operator==(const IncrementalRefreshBookLongGroup& other) const {
    return md_entry_px_optional_ex_ == other.md_entry_px_optional_ex_
        && md_entry_size_optional_ == other.md_entry_size_optional_
        && security_id_ == other.security_id_
        && rpt_seq_ == other.rpt_seq_
        && number_of_orders_optional_ == other.number_of_orders_optional_
        && md_price_level_ == other.md_price_level_
        && md_update_action_ == other.md_update_action_
        && md_entry_type_book_ == other.md_entry_type_book_
        && padding_1_ == other.padding_1_;
}

bool IncrementalRefreshBookLongGroup::operator!=(const IncrementalRefreshBookLongGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshBookLongGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
