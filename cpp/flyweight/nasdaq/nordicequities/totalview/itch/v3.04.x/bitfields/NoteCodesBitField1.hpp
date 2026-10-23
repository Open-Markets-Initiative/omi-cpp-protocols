#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Note codes, logical Or is used to identify multiple note codes
class NoteCodesBitField1 {
  public:
    static constexpr const char* name = "NoteCodesBitField1";

    // the bytes it reads, which it does not own: they must outlive it
    explicit NoteCodesBitField1(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    std::uint8_t raw() const { return wire::read_u8(bytes_.data()); }

    bool nm_new_market_company() const { return (raw() & static_cast<std::uint8_t>(0x1)) != 0; }

    bool xr_excluding_participating_in_rights() const { return (raw() & static_cast<std::uint8_t>(0x2)) != 0; }

    bool sp_excluding_participating_in_split() const { return (raw() & static_cast<std::uint8_t>(0x4)) != 0; }

    bool po_company_subject_to_public_offer() const { return (raw() & static_cast<std::uint8_t>(0x8)) != 0; }

    bool ud_under_drawing() const { return (raw() & static_cast<std::uint8_t>(0x10)) != 0; }

    bool sr_excluding_comb_split_and_issue_rights() const { return (raw() & static_cast<std::uint8_t>(0x20)) != 0; }

    bool ul_un_listed() const { return (raw() & static_cast<std::uint8_t>(0x40)) != 0; }

    bool wi_when_issued() const { return (raw() & static_cast<std::uint8_t>(0x80)) != 0; }

    void print(std::ostream& out) const {
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

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const NoteCodesBitField1& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
