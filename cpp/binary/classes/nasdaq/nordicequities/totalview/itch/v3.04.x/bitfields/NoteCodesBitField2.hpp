#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Note codes, logical Or is used to identify multiple note codes
class NoteCodesBitField2 {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    NoteCodesBitField2() = default;
    explicit NoteCodesBitField2(std::uint8_t raw);

    // Br Company Bankruptcy:
    bool br_company_bankruptcy() const;
    void set_br_company_bankruptcy(bool value);

    // Su Suspension:
    bool su_suspension() const;
    void set_su_suspension(bool value);

    // Rl Removal From Listing In Process:
    bool rl_removal_from_listing_in_process() const;
    void set_rl_removal_from_listing_in_process(bool value);

    // Sl Other Surveillance List Reason:
    bool sl_other_surveillance_list_reason() const;
    void set_sl_other_surveillance_list_reason(bool value);

    // To A Significant Reverse Takeover Pending:
    bool to_a_significant_reverse_takeover_pending() const;
    void set_to_a_significant_reverse_takeover_pending(bool value);

    // Cs Cent Shares:
    bool cs_cent_shares() const;
    void set_cs_cent_shares(bool value);

    // Rs Reversed Split:
    bool rs_reversed_split() const;
    void set_rs_reversed_split(bool value);

    // Bs Excluding Comb Bonus Split:
    bool bs_excluding_comb_bonus_split() const;
    void set_bs_excluding_comb_bonus_split(bool value);

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

    bool operator==(const NoteCodesBitField2& other) const;
    bool operator!=(const NoteCodesBitField2& other) const;

  private:
    std::uint8_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const NoteCodesBitField2& value);

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
