#include "SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup::SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup(std::optional<Decimal> md_corporate_offset_price_optional, std::int64_t md_entry_size_quantity, const std::array<std::byte, 4>& offset_16_padding_4, std::optional<std::uint32_t> entering_firm, std::optional<std::chrono::nanoseconds> md_insert_timestamp, std::uint64_t secondary_order_id, MdEntryType md_entry_type, const MatchEventIndicator& match_event_indicator)
  : md_corporate_offset_price_optional_(md_corporate_offset_price_optional), md_entry_size_quantity_(md_entry_size_quantity), offset_16_padding_4_(offset_16_padding_4), entering_firm_(entering_firm), md_insert_timestamp_(md_insert_timestamp), secondary_order_id_(secondary_order_id), md_entry_type_(md_entry_type), match_event_indicator_(match_event_indicator) {}

std::optional<Decimal> SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup::md_corporate_offset_price_optional() const { return md_corporate_offset_price_optional_; }
void SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup::set_md_corporate_offset_price_optional(std::optional<Decimal> value) { md_corporate_offset_price_optional_ = value; }

std::int64_t SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup::md_entry_size_quantity() const { return md_entry_size_quantity_; }
void SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup::set_md_entry_size_quantity(std::int64_t value) { md_entry_size_quantity_ = value; }

const std::array<std::byte, 4>& SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup::offset_16_padding_4() const { return offset_16_padding_4_; }
std::array<std::byte, 4>& SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup::offset_16_padding_4() { return offset_16_padding_4_; }
void SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup::set_offset_16_padding_4(const std::array<std::byte, 4>& value) { offset_16_padding_4_ = value; }

std::optional<std::uint32_t> SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup::entering_firm() const { return entering_firm_; }
void SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup::set_entering_firm(std::optional<std::uint32_t> value) { entering_firm_ = value; }

std::optional<std::chrono::nanoseconds> SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup::md_insert_timestamp() const { return md_insert_timestamp_; }
void SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup::set_md_insert_timestamp(std::optional<std::chrono::nanoseconds> value) { md_insert_timestamp_ = value; }

std::uint64_t SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup::secondary_order_id() const { return secondary_order_id_; }
void SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup::set_secondary_order_id(std::uint64_t value) { secondary_order_id_ = value; }

MdEntryType SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup::md_entry_type() const { return md_entry_type_; }
void SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup::set_md_entry_type(MdEntryType value) { md_entry_type_ = value; }

const MatchEventIndicator& SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup::match_event_indicator() { return match_event_indicator_; }
void SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

std::size_t SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup", wire_size, length);

    md_corporate_offset_price_optional_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4);
    offset += 8;

    md_entry_size_quantity_ = wire::read_i64_le(data + offset);
    offset += 8;

    wire::read_bytes(data + offset, offset_16_padding_4_.data(), 4);
    offset += 4;

    entering_firm_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    md_insert_timestamp_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    secondary_order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    md_entry_type_ = static_cast<MdEntryType>(wire::read_char(data + offset));
    offset += 1;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    return offset;
}

std::size_t SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup", wire_size, capacity);

    wire::write_i64_le(data + offset, md_corporate_offset_price_optional_ ? static_cast<std::int64_t>(md_corporate_offset_price_optional_->mantissa()) : static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(md_entry_size_quantity_));
    offset += 8;

    wire::write_bytes(data + offset, offset_16_padding_4_.data(), 4);
    offset += 4;

    wire::write_u32_le(data + offset, entering_firm_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u64_le(data + offset, md_insert_timestamp_ ? static_cast<std::uint64_t>(md_insert_timestamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(secondary_order_id_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(md_entry_type_));
    offset += 1;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup::encoded_size() const {
    return wire_size;
}

void SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup::print(std::ostream& out) const {
    out << "SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup{";
    out << "md_corporate_offset_price_optional=";
    print::optional(out, md_corporate_offset_price_optional_);
    out << ", md_entry_size_quantity=";
    out << md_entry_size_quantity_;
    out << ", offset_16_padding_4=";
    print::hex(out, offset_16_padding_4_.data(), offset_16_padding_4_.size());
    out << ", entering_firm=";
    print::optional(out, entering_firm_);
    out << ", md_insert_timestamp=";
    print::optional_duration(out, md_insert_timestamp_);
    out << ", secondary_order_id=";
    out << secondary_order_id_;
    out << ", md_entry_type=";
    out << md_entry_type_;
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << '}';
}

bool SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup::operator==(const SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup& other) const {
    return md_corporate_offset_price_optional_ == other.md_corporate_offset_price_optional_
        && md_entry_size_quantity_ == other.md_entry_size_quantity_
        && offset_16_padding_4_ == other.offset_16_padding_4_
        && entering_firm_ == other.entering_firm_
        && md_insert_timestamp_ == other.md_insert_timestamp_
        && secondary_order_id_ == other.secondary_order_id_
        && md_entry_type_ == other.md_entry_type_
        && match_event_indicator_ == other.match_event_indicator_;
}

bool SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup::operator!=(const SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_2
