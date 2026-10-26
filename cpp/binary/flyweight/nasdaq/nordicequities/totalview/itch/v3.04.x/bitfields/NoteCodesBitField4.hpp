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
class NoteCodesBitField4 {
  public:
    static constexpr const char* name = "NoteCodesBitField4";

    // the bytes it reads, which it does not own: they must outlive it
    explicit NoteCodesBitField4(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    std::uint8_t raw() const { return wire::read_u8(bytes_.data()); }

    bool bb_buy_back() const { return (raw() & static_cast<std::uint8_t>(0x1)) != 0; }

    bool ce_capped_by_esma() const { return (raw() & static_cast<std::uint8_t>(0x8)) != 0; }

    bool pd_price_discrepancy_historical_average_share_classes() const { return (raw() & static_cast<std::uint8_t>(0x20)) != 0; }

    bool sm_stressed_market() const { return (raw() & static_cast<std::uint8_t>(0x40)) != 0; }

    bool ew_marketwide_exceptional_circumstance() const { return (raw() & static_cast<std::uint8_t>(0x80)) != 0; }

    void print(std::ostream& out) const {
        out << "NoteCodesBitField4{";
        out << "bb_buy_back=";
        out << (bb_buy_back() ? "true" : "false");
        out << ", ce_capped_by_esma=";
        out << (ce_capped_by_esma() ? "true" : "false");
        out << ", pd_price_discrepancy_historical_average_share_classes=";
        out << (pd_price_discrepancy_historical_average_share_classes() ? "true" : "false");
        out << ", sm_stressed_market=";
        out << (sm_stressed_market() ? "true" : "false");
        out << ", ew_marketwide_exceptional_circumstance=";
        out << (ew_marketwide_exceptional_circumstance() ? "true" : "false");
        out << '}';
    }

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const NoteCodesBitField4& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
