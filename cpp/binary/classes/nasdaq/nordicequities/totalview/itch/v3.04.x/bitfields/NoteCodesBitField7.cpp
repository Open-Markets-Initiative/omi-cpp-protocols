#include "NoteCodesBitField7.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

NoteCodesBitField7::NoteCodesBitField7(std::uint8_t raw) : raw_(raw) {}

std::uint8_t NoteCodesBitField7::raw() const { return raw_; }
void NoteCodesBitField7::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t NoteCodesBitField7::decode(const std::byte* data, std::size_t length) {
    wire::require("NoteCodesBitField7", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t NoteCodesBitField7::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("NoteCodesBitField7", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t NoteCodesBitField7::encoded_size() const {
    return wire_size;
}

void NoteCodesBitField7::print(std::ostream& out) const {
    out << "NoteCodesBitField7{";
    out << '}';
}

bool NoteCodesBitField7::operator==(const NoteCodesBitField7& other) const {
    return raw_ == other.raw_;
}

bool NoteCodesBitField7::operator!=(const NoteCodesBitField7& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const NoteCodesBitField7& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
