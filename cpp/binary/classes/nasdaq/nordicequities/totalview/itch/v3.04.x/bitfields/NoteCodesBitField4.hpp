#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Note codes, logical Or is used to identify multiple note codes
class NoteCodesBitField4 {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    NoteCodesBitField4() = default;
    explicit NoteCodesBitField4(std::uint8_t raw);

    // Bb Buy Back:
    bool bb_buy_back() const;
    void set_bb_buy_back(bool value);

    // Ce Capped By Esma:
    bool ce_capped_by_esma() const;
    void set_ce_capped_by_esma(bool value);

    // Pd Price Discrepancy Historical Average Share Classes:
    bool pd_price_discrepancy_historical_average_share_classes() const;
    void set_pd_price_discrepancy_historical_average_share_classes(bool value);

    // Sm Stressed Market:
    bool sm_stressed_market() const;
    void set_sm_stressed_market(bool value);

    // Ew Market Wide Exceptional Circumstance:
    bool ew_market_wide_exceptional_circumstance() const;
    void set_ew_market_wide_exceptional_circumstance(bool value);

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

    bool operator==(const NoteCodesBitField4& other) const;
    bool operator!=(const NoteCodesBitField4& other) const;

  private:
    std::uint8_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const NoteCodesBitField4& value);

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
