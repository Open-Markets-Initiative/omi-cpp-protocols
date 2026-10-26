#include "NoteCodesBitField6.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

NoteCodesBitField6::NoteCodesBitField6(std::uint8_t raw) : raw_(raw) {}

std::uint8_t NoteCodesBitField6::raw() const { return raw_; }
void NoteCodesBitField6::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t NoteCodesBitField6::decode(const std::byte* data, std::size_t length) {
    wire::require("NoteCodesBitField6", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t NoteCodesBitField6::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("NoteCodesBitField6", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t NoteCodesBitField6::encoded_size() const {
    return wire_size;
}

void NoteCodesBitField6::print(std::ostream& out) const {
    out << "NoteCodesBitField6{";
    out << '}';
}

bool NoteCodesBitField6::operator==(const NoteCodesBitField6& other) const {
    return raw_ == other.raw_;
}

bool NoteCodesBitField6::operator!=(const NoteCodesBitField6& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const NoteCodesBitField6& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
