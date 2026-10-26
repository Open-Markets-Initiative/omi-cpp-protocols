#include "NoteCodesBitField2.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

NoteCodesBitField2::NoteCodesBitField2(std::uint8_t raw) : raw_(raw) {}

bool NoteCodesBitField2::br_company_bankruptcy() const { return (raw_ & static_cast<std::uint8_t>(0x1)) != 0; }
void NoteCodesBitField2::set_br_company_bankruptcy(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x1)) : (raw_ & ~static_cast<std::uint8_t>(0x1))); }

bool NoteCodesBitField2::su_suspension() const { return (raw_ & static_cast<std::uint8_t>(0x2)) != 0; }
void NoteCodesBitField2::set_su_suspension(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x2)) : (raw_ & ~static_cast<std::uint8_t>(0x2))); }

bool NoteCodesBitField2::rl_removal_from_listing_in_process() const { return (raw_ & static_cast<std::uint8_t>(0x4)) != 0; }
void NoteCodesBitField2::set_rl_removal_from_listing_in_process(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x4)) : (raw_ & ~static_cast<std::uint8_t>(0x4))); }

bool NoteCodesBitField2::sl_other_surveillance_list_reason() const { return (raw_ & static_cast<std::uint8_t>(0x8)) != 0; }
void NoteCodesBitField2::set_sl_other_surveillance_list_reason(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x8)) : (raw_ & ~static_cast<std::uint8_t>(0x8))); }

bool NoteCodesBitField2::to_a_significant_reverse_takeover_pending() const { return (raw_ & static_cast<std::uint8_t>(0x10)) != 0; }
void NoteCodesBitField2::set_to_a_significant_reverse_takeover_pending(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x10)) : (raw_ & ~static_cast<std::uint8_t>(0x10))); }

bool NoteCodesBitField2::cs_cent_shares() const { return (raw_ & static_cast<std::uint8_t>(0x20)) != 0; }
void NoteCodesBitField2::set_cs_cent_shares(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x20)) : (raw_ & ~static_cast<std::uint8_t>(0x20))); }

bool NoteCodesBitField2::rs_reversed_split() const { return (raw_ & static_cast<std::uint8_t>(0x40)) != 0; }
void NoteCodesBitField2::set_rs_reversed_split(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x40)) : (raw_ & ~static_cast<std::uint8_t>(0x40))); }

bool NoteCodesBitField2::bs_excluding_comb_bonus_split() const { return (raw_ & static_cast<std::uint8_t>(0x80)) != 0; }
void NoteCodesBitField2::set_bs_excluding_comb_bonus_split(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x80)) : (raw_ & ~static_cast<std::uint8_t>(0x80))); }

std::uint8_t NoteCodesBitField2::raw() const { return raw_; }
void NoteCodesBitField2::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t NoteCodesBitField2::decode(const std::byte* data, std::size_t length) {
    wire::require("NoteCodesBitField2", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t NoteCodesBitField2::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("NoteCodesBitField2", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t NoteCodesBitField2::encoded_size() const {
    return wire_size;
}

void NoteCodesBitField2::print(std::ostream& out) const {
    out << "NoteCodesBitField2{";
    out << "br_company_bankruptcy=";
    out << (br_company_bankruptcy() ? "true" : "false");
    out << ", su_suspension=";
    out << (su_suspension() ? "true" : "false");
    out << ", rl_removal_from_listing_in_process=";
    out << (rl_removal_from_listing_in_process() ? "true" : "false");
    out << ", sl_other_surveillance_list_reason=";
    out << (sl_other_surveillance_list_reason() ? "true" : "false");
    out << ", to_a_significant_reverse_takeover_pending=";
    out << (to_a_significant_reverse_takeover_pending() ? "true" : "false");
    out << ", cs_cent_shares=";
    out << (cs_cent_shares() ? "true" : "false");
    out << ", rs_reversed_split=";
    out << (rs_reversed_split() ? "true" : "false");
    out << ", bs_excluding_comb_bonus_split=";
    out << (bs_excluding_comb_bonus_split() ? "true" : "false");
    out << '}';
}

bool NoteCodesBitField2::operator==(const NoteCodesBitField2& other) const {
    return raw_ == other.raw_;
}

bool NoteCodesBitField2::operator!=(const NoteCodesBitField2& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const NoteCodesBitField2& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
