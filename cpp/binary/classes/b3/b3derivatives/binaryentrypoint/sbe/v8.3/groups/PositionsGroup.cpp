#include "PositionsGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

PositionsGroup::PositionsGroup(PosType pos_type, std::optional<std::uint64_t> long_qty_optional, std::optional<std::uint64_t> short_qty)
  : pos_type_(pos_type), long_qty_optional_(long_qty_optional), short_qty_(short_qty) {}

PosType PositionsGroup::pos_type() const { return pos_type_; }
void PositionsGroup::set_pos_type(PosType value) { pos_type_ = value; }

std::optional<std::uint64_t> PositionsGroup::long_qty_optional() const { return long_qty_optional_; }
void PositionsGroup::set_long_qty_optional(std::optional<std::uint64_t> value) { long_qty_optional_ = value; }

std::optional<std::uint64_t> PositionsGroup::short_qty() const { return short_qty_; }
void PositionsGroup::set_short_qty(std::optional<std::uint64_t> value) { short_qty_ = value; }

std::size_t PositionsGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PositionsGroup", wire_size, length);

    pos_type_ = static_cast<PosType>(wire::read_char(data + offset));
    offset += 1;

    long_qty_optional_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    short_qty_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t PositionsGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PositionsGroup", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(pos_type_));
    offset += 1;

    wire::write_u64_le(data + offset, long_qty_optional_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u64_le(data + offset, short_qty_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    return offset;
}

std::size_t PositionsGroup::encoded_size() const {
    return wire_size;
}

void PositionsGroup::print(std::ostream& out) const {
    out << "PositionsGroup{";
    out << "pos_type=";
    out << pos_type_;
    out << ", long_qty_optional=";
    print::optional(out, long_qty_optional_);
    out << ", short_qty=";
    print::optional(out, short_qty_);
    out << '}';
}

bool PositionsGroup::operator==(const PositionsGroup& other) const {
    return pos_type_ == other.pos_type_
        && long_qty_optional_ == other.long_qty_optional_
        && short_qty_ == other.short_qty_;
}

bool PositionsGroup::operator!=(const PositionsGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const PositionsGroup& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
