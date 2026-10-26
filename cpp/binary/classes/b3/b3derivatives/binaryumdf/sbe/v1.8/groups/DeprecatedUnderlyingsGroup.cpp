#include "DeprecatedUnderlyingsGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

DeprecatedUnderlyingsGroup::DeprecatedUnderlyingsGroup(std::uint64_t underlying_security_id, std::optional<Decimal> index_pct, std::optional<Decimal> index_theoretical_qty, const std::string& underlying_symbol)
  : underlying_security_id_(underlying_security_id), index_pct_(index_pct), index_theoretical_qty_(index_theoretical_qty), underlying_symbol_(underlying_symbol) {}

std::uint64_t DeprecatedUnderlyingsGroup::underlying_security_id() const { return underlying_security_id_; }
void DeprecatedUnderlyingsGroup::set_underlying_security_id(std::uint64_t value) { underlying_security_id_ = value; }

std::optional<Decimal> DeprecatedUnderlyingsGroup::index_pct() const { return index_pct_; }
void DeprecatedUnderlyingsGroup::set_index_pct(std::optional<Decimal> value) { index_pct_ = value; }

std::optional<Decimal> DeprecatedUnderlyingsGroup::index_theoretical_qty() const { return index_theoretical_qty_; }
void DeprecatedUnderlyingsGroup::set_index_theoretical_qty(std::optional<Decimal> value) { index_theoretical_qty_ = value; }

const std::string& DeprecatedUnderlyingsGroup::underlying_symbol() const { return underlying_symbol_; }
std::string& DeprecatedUnderlyingsGroup::underlying_symbol() { return underlying_symbol_; }
void DeprecatedUnderlyingsGroup::set_underlying_symbol(const std::string& value) { underlying_symbol_ = value; }

std::size_t DeprecatedUnderlyingsGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("DeprecatedUnderlyingsGroup", wire_size, length);

    underlying_security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    index_pct_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0LL), -9);
    offset += 8;

    index_theoretical_qty_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -8);
    offset += 8;

    underlying_symbol_ = wire::read_text(data + offset, 20, '\0');
    offset += 20;

    return offset;
}

std::size_t DeprecatedUnderlyingsGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("DeprecatedUnderlyingsGroup", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(underlying_security_id_));
    offset += 8;

    wire::write_i64_le(data + offset, index_pct_ ? static_cast<std::int64_t>(index_pct_->mantissa()) : static_cast<std::int64_t>(0LL));
    offset += 8;

    wire::write_i64_le(data + offset, index_theoretical_qty_ ? static_cast<std::int64_t>(index_theoretical_qty_->mantissa()) : static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::write_text(data + offset, 20, '\0', underlying_symbol_);
    offset += 20;

    return offset;
}

std::size_t DeprecatedUnderlyingsGroup::encoded_size() const {
    return wire_size;
}

void DeprecatedUnderlyingsGroup::print(std::ostream& out) const {
    out << "DeprecatedUnderlyingsGroup{";
    out << "underlying_security_id=";
    out << underlying_security_id_;
    out << ", index_pct=";
    print::optional(out, index_pct_);
    out << ", index_theoretical_qty=";
    print::optional(out, index_theoretical_qty_);
    out << ", underlying_symbol=";
    print::text(out, underlying_symbol_);
    out << '}';
}

bool DeprecatedUnderlyingsGroup::operator==(const DeprecatedUnderlyingsGroup& other) const {
    return underlying_security_id_ == other.underlying_security_id_
        && index_pct_ == other.index_pct_
        && index_theoretical_qty_ == other.index_theoretical_qty_
        && underlying_symbol_ == other.underlying_symbol_;
}

bool DeprecatedUnderlyingsGroup::operator!=(const DeprecatedUnderlyingsGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const DeprecatedUnderlyingsGroup& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
