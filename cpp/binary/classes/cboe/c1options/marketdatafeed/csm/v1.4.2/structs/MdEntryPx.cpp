#include "MdEntryPx.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

MdEntryPx::MdEntryPx(std::int8_t md_entry_px_exponent, std::int32_t md_entry_px_mantissa)
  : md_entry_px_exponent_(md_entry_px_exponent), md_entry_px_mantissa_(md_entry_px_mantissa) {}

std::int8_t MdEntryPx::md_entry_px_exponent() const { return md_entry_px_exponent_; }
void MdEntryPx::set_md_entry_px_exponent(std::int8_t value) { md_entry_px_exponent_ = value; }

std::int32_t MdEntryPx::md_entry_px_mantissa() const { return md_entry_px_mantissa_; }
void MdEntryPx::set_md_entry_px_mantissa(std::int32_t value) { md_entry_px_mantissa_ = value; }

std::size_t MdEntryPx::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MdEntryPx", wire_size, length);

    md_entry_px_exponent_ = wire::read_i8(data + offset);
    offset += 1;

    md_entry_px_mantissa_ = wire::read_i32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t MdEntryPx::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MdEntryPx", wire_size, capacity);

    wire::write_i8(data + offset, static_cast<std::int8_t>(md_entry_px_exponent_));
    offset += 1;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(md_entry_px_mantissa_));
    offset += 4;

    return offset;
}

std::size_t MdEntryPx::encoded_size() const {
    return wire_size;
}

void MdEntryPx::print(std::ostream& out) const {
    out << "MdEntryPx{";
    out << "md_entry_px_exponent=";
    out << static_cast<int>(md_entry_px_exponent_);
    out << ", md_entry_px_mantissa=";
    out << md_entry_px_mantissa_;
    out << '}';
}

bool MdEntryPx::operator==(const MdEntryPx& other) const {
    return md_entry_px_exponent_ == other.md_entry_px_exponent_
        && md_entry_px_mantissa_ == other.md_entry_px_mantissa_;
}

bool MdEntryPx::operator!=(const MdEntryPx& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const MdEntryPx& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
