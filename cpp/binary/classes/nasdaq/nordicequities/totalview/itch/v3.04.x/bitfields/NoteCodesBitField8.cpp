#include "NoteCodesBitField8.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

NoteCodesBitField8::NoteCodesBitField8(std::uint8_t raw) : raw_(raw) {}

std::uint8_t NoteCodesBitField8::raw() const { return raw_; }
void NoteCodesBitField8::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t NoteCodesBitField8::decode(const std::byte* data, std::size_t length) {
    wire::require("NoteCodesBitField8", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t NoteCodesBitField8::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("NoteCodesBitField8", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t NoteCodesBitField8::encoded_size() const {
    return wire_size;
}

void NoteCodesBitField8::print(std::ostream& out) const {
    out << "NoteCodesBitField8{";
    out << '}';
}

bool NoteCodesBitField8::operator==(const NoteCodesBitField8& other) const {
    return raw_ == other.raw_;
}

bool NoteCodesBitField8::operator!=(const NoteCodesBitField8& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const NoteCodesBitField8& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
