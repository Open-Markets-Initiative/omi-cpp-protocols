#include "NoteCodesBitField5.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

NoteCodesBitField5::NoteCodesBitField5(std::uint8_t raw) : raw_(raw) {}

bool NoteCodesBitField5::em_exceptional_circumstances_related_to_market_maker() const { return (raw_ & static_cast<std::uint8_t>(0x1)) != 0; }
void NoteCodesBitField5::set_em_exceptional_circumstances_related_to_market_maker(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x1)) : (raw_ & ~static_cast<std::uint8_t>(0x1))); }

bool NoteCodesBitField5::un_underlying_not_quoted() const { return (raw_ & static_cast<std::uint8_t>(0x2)) != 0; }
void NoteCodesBitField5::set_un_underlying_not_quoted(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x2)) : (raw_ & ~static_cast<std::uint8_t>(0x2))); }

bool NoteCodesBitField5::da_digital_asset() const { return (raw_ & static_cast<std::uint8_t>(0x4)) != 0; }
void NoteCodesBitField5::set_da_digital_asset(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x4)) : (raw_ & ~static_cast<std::uint8_t>(0x4))); }

bool NoteCodesBitField5::kn_knockout_buy_back_into_next_trading_day() const { return (raw_ & static_cast<std::uint8_t>(0x8)) != 0; }
void NoteCodesBitField5::set_kn_knockout_buy_back_into_next_trading_day(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x8)) : (raw_ & ~static_cast<std::uint8_t>(0x8))); }

std::uint8_t NoteCodesBitField5::raw() const { return raw_; }
void NoteCodesBitField5::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t NoteCodesBitField5::decode(const std::byte* data, std::size_t length) {
    wire::require("NoteCodesBitField5", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t NoteCodesBitField5::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("NoteCodesBitField5", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t NoteCodesBitField5::encoded_size() const {
    return wire_size;
}

void NoteCodesBitField5::print(std::ostream& out) const {
    out << "NoteCodesBitField5{";
    out << "em_exceptional_circumstances_related_to_market_maker=";
    out << (em_exceptional_circumstances_related_to_market_maker() ? "true" : "false");
    out << ", un_underlying_not_quoted=";
    out << (un_underlying_not_quoted() ? "true" : "false");
    out << ", da_digital_asset=";
    out << (da_digital_asset() ? "true" : "false");
    out << ", kn_knockout_buy_back_into_next_trading_day=";
    out << (kn_knockout_buy_back_into_next_trading_day() ? "true" : "false");
    out << '}';
}

bool NoteCodesBitField5::operator==(const NoteCodesBitField5& other) const {
    return raw_ == other.raw_;
}

bool NoteCodesBitField5::operator!=(const NoteCodesBitField5& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const NoteCodesBitField5& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
