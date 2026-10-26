#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Note codes, logical Or is used to identify multiple note codes
class NoteCodesBitField3 {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    NoteCodesBitField3() = default;
    explicit NoteCodesBitField3(std::uint8_t raw);

    // Ss Excluding Comb Split Redemption Share:
    bool ss_excluding_comb_split_redemption_share() const;
    void set_ss_excluding_comb_split_redemption_share(bool value);

    // Fn First North Company:
    bool fn_first_north_company() const;
    void set_fn_first_north_company(bool value);

    // Ob Observation Status:
    bool ob_observation_status() const;
    void set_ob_observation_status(bool value);

    // Xd Excluding Dividend:
    bool xd_excluding_dividend() const;
    void set_xd_excluding_dividend(bool value);

    // Fe Foreign Non Eueea Entity:
    bool fe_foreign_non_eueea_entity() const;
    void set_fe_foreign_non_eueea_entity(bool value);

    // So Sold Out Buy Back:
    bool so_sold_out_buy_back() const;
    void set_so_sold_out_buy_back(bool value);

    // Sk Soft Knock:
    bool sk_soft_knock() const;
    void set_sk_soft_knock(bool value);

    // Kb Knock Out Buy Back:
    bool kb_knock_out_buy_back() const;
    void set_kb_knock_out_buy_back(bool value);

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

    bool operator==(const NoteCodesBitField3& other) const;
    bool operator!=(const NoteCodesBitField3& other) const;

  private:
    std::uint8_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const NoteCodesBitField3& value);

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
