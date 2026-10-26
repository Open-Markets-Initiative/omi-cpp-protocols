#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Note codes, logical Or is used to identify multiple note codes
class NoteCodesBitField5 {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    NoteCodesBitField5() = default;
    explicit NoteCodesBitField5(std::uint8_t raw);

    // Em Exceptional Circumstances Related To Market Maker:
    bool em_exceptional_circumstances_related_to_market_maker() const;
    void set_em_exceptional_circumstances_related_to_market_maker(bool value);

    // Un Underlying Not Quoted:
    bool un_underlying_not_quoted() const;
    void set_un_underlying_not_quoted(bool value);

    // Da Digital Asset:
    bool da_digital_asset() const;
    void set_da_digital_asset(bool value);

    // Kn Knockout Buy Back Into Next Trading Day:
    bool kn_knockout_buy_back_into_next_trading_day() const;
    void set_kn_knockout_buy_back_into_next_trading_day(bool value);

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

    bool operator==(const NoteCodesBitField5& other) const;
    bool operator!=(const NoteCodesBitField5& other) const;

  private:
    std::uint8_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const NoteCodesBitField5& value);

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
