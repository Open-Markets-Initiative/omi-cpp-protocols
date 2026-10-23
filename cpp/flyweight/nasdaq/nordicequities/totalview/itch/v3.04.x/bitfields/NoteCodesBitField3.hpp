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
class NoteCodesBitField3 {
  public:
    static constexpr const char* name = "NoteCodesBitField3";

    // the bytes it reads, which it does not own: they must outlive it
    explicit NoteCodesBitField3(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    std::uint8_t raw() const { return wire::read_u8(bytes_.data()); }

    bool ss_excluding_comb_split_redemption_share() const { return (raw() & static_cast<std::uint8_t>(0x1)) != 0; }

    bool fn_first_north_company() const { return (raw() & static_cast<std::uint8_t>(0x2)) != 0; }

    bool ob_observation_status() const { return (raw() & static_cast<std::uint8_t>(0x4)) != 0; }

    bool xd_excluding_dividend() const { return (raw() & static_cast<std::uint8_t>(0x8)) != 0; }

    bool fe_foreign_non_eueea_entity() const { return (raw() & static_cast<std::uint8_t>(0x10)) != 0; }

    bool so_sold_out_buy_back() const { return (raw() & static_cast<std::uint8_t>(0x20)) != 0; }

    bool sk_soft_knock() const { return (raw() & static_cast<std::uint8_t>(0x40)) != 0; }

    bool kb_knock_out_buy_back() const { return (raw() & static_cast<std::uint8_t>(0x80)) != 0; }

    void print(std::ostream& out) const {
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

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const NoteCodesBitField3& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
