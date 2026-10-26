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
class NoteCodesBitField2 {
  public:
    static constexpr const char* name = "NoteCodesBitField2";

    // the bytes it reads, which it does not own: they must outlive it
    explicit NoteCodesBitField2(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    std::uint8_t raw() const { return wire::read_u8(bytes_.data()); }

    bool br_company_bankruptcy() const { return (raw() & static_cast<std::uint8_t>(0x1)) != 0; }

    bool su_suspension() const { return (raw() & static_cast<std::uint8_t>(0x2)) != 0; }

    bool rl_removal_from_listing_in_process() const { return (raw() & static_cast<std::uint8_t>(0x4)) != 0; }

    bool sl_other_surveillance_list_reason() const { return (raw() & static_cast<std::uint8_t>(0x8)) != 0; }

    bool to_a_significant_reverse_takeover_pending() const { return (raw() & static_cast<std::uint8_t>(0x10)) != 0; }

    bool cs_cent_shares() const { return (raw() & static_cast<std::uint8_t>(0x20)) != 0; }

    bool rs_reversed_split() const { return (raw() & static_cast<std::uint8_t>(0x40)) != 0; }

    bool bs_excluding_comb_bonus_split() const { return (raw() & static_cast<std::uint8_t>(0x80)) != 0; }

    void print(std::ostream& out) const {
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

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const NoteCodesBitField2& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
