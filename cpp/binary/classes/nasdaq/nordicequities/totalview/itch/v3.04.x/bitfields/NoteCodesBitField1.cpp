#include "NoteCodesBitField1.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

NoteCodesBitField1::NoteCodesBitField1(std::uint8_t raw) : raw_(raw) {}

bool NoteCodesBitField1::nm_new_market_company() const { return (raw_ & static_cast<std::uint8_t>(0x1)) != 0; }
void NoteCodesBitField1::set_nm_new_market_company(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x1)) : (raw_ & ~static_cast<std::uint8_t>(0x1))); }

bool NoteCodesBitField1::xr_excluding_participating_in_rights() const { return (raw_ & static_cast<std::uint8_t>(0x2)) != 0; }
void NoteCodesBitField1::set_xr_excluding_participating_in_rights(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x2)) : (raw_ & ~static_cast<std::uint8_t>(0x2))); }

bool NoteCodesBitField1::sp_excluding_participating_in_split() const { return (raw_ & static_cast<std::uint8_t>(0x4)) != 0; }
void NoteCodesBitField1::set_sp_excluding_participating_in_split(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x4)) : (raw_ & ~static_cast<std::uint8_t>(0x4))); }

bool NoteCodesBitField1::po_company_subject_to_public_offer() const { return (raw_ & static_cast<std::uint8_t>(0x8)) != 0; }
void NoteCodesBitField1::set_po_company_subject_to_public_offer(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x8)) : (raw_ & ~static_cast<std::uint8_t>(0x8))); }

bool NoteCodesBitField1::ud_under_drawing() const { return (raw_ & static_cast<std::uint8_t>(0x10)) != 0; }
void NoteCodesBitField1::set_ud_under_drawing(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x10)) : (raw_ & ~static_cast<std::uint8_t>(0x10))); }

bool NoteCodesBitField1::sr_excluding_comb_split_and_issue_rights() const { return (raw_ & static_cast<std::uint8_t>(0x20)) != 0; }
void NoteCodesBitField1::set_sr_excluding_comb_split_and_issue_rights(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x20)) : (raw_ & ~static_cast<std::uint8_t>(0x20))); }

bool NoteCodesBitField1::ul_un_listed() const { return (raw_ & static_cast<std::uint8_t>(0x40)) != 0; }
void NoteCodesBitField1::set_ul_un_listed(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x40)) : (raw_ & ~static_cast<std::uint8_t>(0x40))); }

bool NoteCodesBitField1::wi_when_issued() const { return (raw_ & static_cast<std::uint8_t>(0x80)) != 0; }
void NoteCodesBitField1::set_wi_when_issued(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x80)) : (raw_ & ~static_cast<std::uint8_t>(0x80))); }

std::uint8_t NoteCodesBitField1::raw() const { return raw_; }
void NoteCodesBitField1::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t NoteCodesBitField1::decode(const std::byte* data, std::size_t length) {
    wire::require("NoteCodesBitField1", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t NoteCodesBitField1::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("NoteCodesBitField1", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t NoteCodesBitField1::encoded_size() const {
    return wire_size;
}

void NoteCodesBitField1::print(std::ostream& out) const {
    out << "NoteCodesBitField1{";
    out << "nm_new_market_company=";
    out << (nm_new_market_company() ? "true" : "false");
    out << ", xr_excluding_participating_in_rights=";
    out << (xr_excluding_participating_in_rights() ? "true" : "false");
    out << ", sp_excluding_participating_in_split=";
    out << (sp_excluding_participating_in_split() ? "true" : "false");
    out << ", po_company_subject_to_public_offer=";
    out << (po_company_subject_to_public_offer() ? "true" : "false");
    out << ", ud_under_drawing=";
    out << (ud_under_drawing() ? "true" : "false");
    out << ", sr_excluding_comb_split_and_issue_rights=";
    out << (sr_excluding_comb_split_and_issue_rights() ? "true" : "false");
    out << ", ul_un_listed=";
    out << (ul_un_listed() ? "true" : "false");
    out << ", wi_when_issued=";
    out << (wi_when_issued() ? "true" : "false");
    out << '}';
}

bool NoteCodesBitField1::operator==(const NoteCodesBitField1& other) const {
    return raw_ == other.raw_;
}

bool NoteCodesBitField1::operator!=(const NoteCodesBitField1& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const NoteCodesBitField1& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
