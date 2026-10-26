#include "NoteCodesBitField4.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

NoteCodesBitField4::NoteCodesBitField4(std::uint8_t raw) : raw_(raw) {}

bool NoteCodesBitField4::bb_buy_back() const { return (raw_ & static_cast<std::uint8_t>(0x1)) != 0; }
void NoteCodesBitField4::set_bb_buy_back(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x1)) : (raw_ & ~static_cast<std::uint8_t>(0x1))); }

bool NoteCodesBitField4::ce_capped_by_esma() const { return (raw_ & static_cast<std::uint8_t>(0x8)) != 0; }
void NoteCodesBitField4::set_ce_capped_by_esma(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x8)) : (raw_ & ~static_cast<std::uint8_t>(0x8))); }

bool NoteCodesBitField4::pd_price_discrepancy_historical_average_share_classes() const { return (raw_ & static_cast<std::uint8_t>(0x20)) != 0; }
void NoteCodesBitField4::set_pd_price_discrepancy_historical_average_share_classes(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x20)) : (raw_ & ~static_cast<std::uint8_t>(0x20))); }

bool NoteCodesBitField4::sm_stressed_market() const { return (raw_ & static_cast<std::uint8_t>(0x40)) != 0; }
void NoteCodesBitField4::set_sm_stressed_market(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x40)) : (raw_ & ~static_cast<std::uint8_t>(0x40))); }

bool NoteCodesBitField4::ew_marketwide_exceptional_circumstance() const { return (raw_ & static_cast<std::uint8_t>(0x80)) != 0; }
void NoteCodesBitField4::set_ew_marketwide_exceptional_circumstance(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x80)) : (raw_ & ~static_cast<std::uint8_t>(0x80))); }

std::uint8_t NoteCodesBitField4::raw() const { return raw_; }
void NoteCodesBitField4::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t NoteCodesBitField4::decode(const std::byte* data, std::size_t length) {
    wire::require("NoteCodesBitField4", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t NoteCodesBitField4::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("NoteCodesBitField4", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t NoteCodesBitField4::encoded_size() const {
    return wire_size;
}

void NoteCodesBitField4::print(std::ostream& out) const {
    out << "NoteCodesBitField4{";
    out << "bb_buy_back=";
    out << (bb_buy_back() ? "true" : "false");
    out << ", ce_capped_by_esma=";
    out << (ce_capped_by_esma() ? "true" : "false");
    out << ", pd_price_discrepancy_historical_average_share_classes=";
    out << (pd_price_discrepancy_historical_average_share_classes() ? "true" : "false");
    out << ", sm_stressed_market=";
    out << (sm_stressed_market() ? "true" : "false");
    out << ", ew_marketwide_exceptional_circumstance=";
    out << (ew_marketwide_exceptional_circumstance() ? "true" : "false");
    out << '}';
}

bool NoteCodesBitField4::operator==(const NoteCodesBitField4& other) const {
    return raw_ == other.raw_;
}

bool NoteCodesBitField4::operator!=(const NoteCodesBitField4& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const NoteCodesBitField4& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
