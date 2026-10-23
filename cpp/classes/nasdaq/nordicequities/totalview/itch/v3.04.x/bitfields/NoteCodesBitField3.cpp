#include "NoteCodesBitField3.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

NoteCodesBitField3::NoteCodesBitField3(std::uint8_t raw) : raw_(raw) {}

bool NoteCodesBitField3::ss_excluding_comb_split_redemption_share() const { return (raw_ & static_cast<std::uint8_t>(0x1)) != 0; }
void NoteCodesBitField3::set_ss_excluding_comb_split_redemption_share(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x1)) : (raw_ & ~static_cast<std::uint8_t>(0x1))); }

bool NoteCodesBitField3::fn_first_north_company() const { return (raw_ & static_cast<std::uint8_t>(0x2)) != 0; }
void NoteCodesBitField3::set_fn_first_north_company(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x2)) : (raw_ & ~static_cast<std::uint8_t>(0x2))); }

bool NoteCodesBitField3::ob_observation_status() const { return (raw_ & static_cast<std::uint8_t>(0x4)) != 0; }
void NoteCodesBitField3::set_ob_observation_status(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x4)) : (raw_ & ~static_cast<std::uint8_t>(0x4))); }

bool NoteCodesBitField3::xd_excluding_dividend() const { return (raw_ & static_cast<std::uint8_t>(0x8)) != 0; }
void NoteCodesBitField3::set_xd_excluding_dividend(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x8)) : (raw_ & ~static_cast<std::uint8_t>(0x8))); }

bool NoteCodesBitField3::fe_foreign_non_eueea_entity() const { return (raw_ & static_cast<std::uint8_t>(0x10)) != 0; }
void NoteCodesBitField3::set_fe_foreign_non_eueea_entity(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x10)) : (raw_ & ~static_cast<std::uint8_t>(0x10))); }

bool NoteCodesBitField3::so_sold_out_buy_back() const { return (raw_ & static_cast<std::uint8_t>(0x20)) != 0; }
void NoteCodesBitField3::set_so_sold_out_buy_back(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x20)) : (raw_ & ~static_cast<std::uint8_t>(0x20))); }

bool NoteCodesBitField3::sk_soft_knock() const { return (raw_ & static_cast<std::uint8_t>(0x40)) != 0; }
void NoteCodesBitField3::set_sk_soft_knock(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x40)) : (raw_ & ~static_cast<std::uint8_t>(0x40))); }

bool NoteCodesBitField3::kb_knock_out_buy_back() const { return (raw_ & static_cast<std::uint8_t>(0x80)) != 0; }
void NoteCodesBitField3::set_kb_knock_out_buy_back(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x80)) : (raw_ & ~static_cast<std::uint8_t>(0x80))); }

std::uint8_t NoteCodesBitField3::raw() const { return raw_; }
void NoteCodesBitField3::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t NoteCodesBitField3::decode(const std::byte* data, std::size_t length) {
    wire::require("NoteCodesBitField3", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t NoteCodesBitField3::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("NoteCodesBitField3", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t NoteCodesBitField3::encoded_size() const {
    return wire_size;
}

void NoteCodesBitField3::print(std::ostream& out) const {
    out << "NoteCodesBitField3{";
    out << "ss_excluding_comb_split_redemption_share=";
    out << (ss_excluding_comb_split_redemption_share() ? "true" : "false");
    out << ", fn_first_north_company=";
    out << (fn_first_north_company() ? "true" : "false");
    out << ", ob_observation_status=";
    out << (ob_observation_status() ? "true" : "false");
    out << ", xd_excluding_dividend=";
    out << (xd_excluding_dividend() ? "true" : "false");
    out << ", fe_foreign_non_eueea_entity=";
    out << (fe_foreign_non_eueea_entity() ? "true" : "false");
    out << ", so_sold_out_buy_back=";
    out << (so_sold_out_buy_back() ? "true" : "false");
    out << ", sk_soft_knock=";
    out << (sk_soft_knock() ? "true" : "false");
    out << ", kb_knock_out_buy_back=";
    out << (kb_knock_out_buy_back() ? "true" : "false");
    out << '}';
}

bool NoteCodesBitField3::operator==(const NoteCodesBitField3& other) const {
    return raw_ == other.raw_;
}

bool NoteCodesBitField3::operator!=(const NoteCodesBitField3& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const NoteCodesBitField3& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
