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
class NoteCodesBitField5 {
  public:
    static constexpr const char* name = "NoteCodesBitField5";

    // the bytes it reads, which it does not own: they must outlive it
    explicit NoteCodesBitField5(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    std::uint8_t raw() const { return wire::read_u8(bytes_.data()); }

    bool em_exceptional_circumstances_related_to_market_maker() const { return (raw() & static_cast<std::uint8_t>(0x1)) != 0; }

    bool un_underlying_not_quoted() const { return (raw() & static_cast<std::uint8_t>(0x2)) != 0; }

    bool da_digital_asset() const { return (raw() & static_cast<std::uint8_t>(0x4)) != 0; }

    bool kn_knockout_buy_back_into_next_trading_day() const { return (raw() & static_cast<std::uint8_t>(0x8)) != 0; }

    void print(std::ostream& out) const {
        out << "NoteCodesBitField5{";
        out << "em_exceptional_circumstances_related_to_market_maker=";
        out << (em_exceptional_circumstances_related_to_market_maker() ? "true" : "false");
        out << ", un_underlying_not_quoted=";
        out << (un_underlying_not_quoted() ? "true" : "false");
        out << ", da_digital_asset=";
        out << (da_digital_asset() ? "true" : "false");
        out << ", kn_knockout_buy_back_into_next_trading_day=";
        out << (kn_knockout_buy_back_into_next_trading_day() ? "true" : "false");
        out << '}';
    }

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const NoteCodesBitField5& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
