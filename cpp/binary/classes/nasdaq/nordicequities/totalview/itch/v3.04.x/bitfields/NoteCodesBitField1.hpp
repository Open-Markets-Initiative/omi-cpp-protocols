#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Note codes, logical Or is used to identify multiple note codes
class NoteCodesBitField1 {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    NoteCodesBitField1() = default;
    explicit NoteCodesBitField1(std::uint8_t raw);

    // Nm New Market Company:
    bool nm_new_market_company() const;
    void set_nm_new_market_company(bool value);

    // Xr Excluding Participating In Rights:
    bool xr_excluding_participating_in_rights() const;
    void set_xr_excluding_participating_in_rights(bool value);

    // Sp Excluding Participating In Split:
    bool sp_excluding_participating_in_split() const;
    void set_sp_excluding_participating_in_split(bool value);

    // Po Company Subject To Public Offer:
    bool po_company_subject_to_public_offer() const;
    void set_po_company_subject_to_public_offer(bool value);

    // Ud Under Drawing:
    bool ud_under_drawing() const;
    void set_ud_under_drawing(bool value);

    // Sr Excluding Comb Split And Issue Rights:
    bool sr_excluding_comb_split_and_issue_rights() const;
    void set_sr_excluding_comb_split_and_issue_rights(bool value);

    // Ul Un Listed:
    bool ul_un_listed() const;
    void set_ul_un_listed(bool value);

    // Wi When Issued:
    bool wi_when_issued() const;
    void set_wi_when_issued(bool value);

    // The whole bitfield as its wire integer
    std::uint8_t raw() const;
    void set_raw(std::uint8_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const NoteCodesBitField1& other) const;
    bool operator!=(const NoteCodesBitField1& other) const;

  private:
    std::uint8_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const NoteCodesBitField1& value);

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
