#include "BrokenDatesGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

BrokenDatesGroup::BrokenDatesGroup(std::uint64_t broken_date_guid, std::int32_t broken_date_security_id, std::optional<std::uint16_t> broken_date_start, std::optional<std::uint16_t> broken_date_end)
  : broken_date_guid_(broken_date_guid), broken_date_security_id_(broken_date_security_id), broken_date_start_(broken_date_start), broken_date_end_(broken_date_end) {}

std::uint64_t BrokenDatesGroup::broken_date_guid() const { return broken_date_guid_; }
void BrokenDatesGroup::set_broken_date_guid(std::uint64_t value) { broken_date_guid_ = value; }

std::int32_t BrokenDatesGroup::broken_date_security_id() const { return broken_date_security_id_; }
void BrokenDatesGroup::set_broken_date_security_id(std::int32_t value) { broken_date_security_id_ = value; }

std::optional<std::uint16_t> BrokenDatesGroup::broken_date_start() const { return broken_date_start_; }
void BrokenDatesGroup::set_broken_date_start(std::optional<std::uint16_t> value) { broken_date_start_ = value; }

std::optional<std::uint16_t> BrokenDatesGroup::broken_date_end() const { return broken_date_end_; }
void BrokenDatesGroup::set_broken_date_end(std::optional<std::uint16_t> value) { broken_date_end_ = value; }

std::size_t BrokenDatesGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("BrokenDatesGroup", wire_size, length);

    broken_date_guid_ = wire::read_u64_le(data + offset);
    offset += 8;

    broken_date_security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    broken_date_start_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    broken_date_end_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    return offset;
}

std::size_t BrokenDatesGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("BrokenDatesGroup", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(broken_date_guid_));
    offset += 8;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(broken_date_security_id_));
    offset += 4;

    wire::write_u16_le(data + offset, broken_date_start_.value_or(static_cast<std::uint16_t>(65535ULL)));
    offset += 2;

    wire::write_u16_le(data + offset, broken_date_end_.value_or(static_cast<std::uint16_t>(65535ULL)));
    offset += 2;

    return offset;
}

std::size_t BrokenDatesGroup::encoded_size() const {
    return wire_size;
}

void BrokenDatesGroup::print(std::ostream& out) const {
    out << "BrokenDatesGroup{";
    out << "broken_date_guid=";
    out << broken_date_guid_;
    out << ", broken_date_security_id=";
    out << broken_date_security_id_;
    out << ", broken_date_start=";
    print::optional(out, broken_date_start_);
    out << ", broken_date_end=";
    print::optional(out, broken_date_end_);
    out << '}';
}

bool BrokenDatesGroup::operator==(const BrokenDatesGroup& other) const {
    return broken_date_guid_ == other.broken_date_guid_
        && broken_date_security_id_ == other.broken_date_security_id_
        && broken_date_start_ == other.broken_date_start_
        && broken_date_end_ == other.broken_date_end_;
}

bool BrokenDatesGroup::operator!=(const BrokenDatesGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const BrokenDatesGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
