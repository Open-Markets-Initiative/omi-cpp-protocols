#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/MarketId.hpp"
#include "../enums/ExchangeCode.hpp"
#include "../enums/SecurityType.hpp"
#include "../enums/PriceResolution.hpp"
#include "../enums/RoundLot.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

// This message is published over the real-time data channels at system startup or in the
// context of a refresh sequence after a Matching Engine or XDP Publisher failover. It provides
// referential data for a single specified symbol.
class SymbolIndexMappingMessage {
  public:
    static constexpr const char* name = "SymbolIndexMappingMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SymbolIndexMappingMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SymbolIndexMappingMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 40;
    static constexpr std::size_t fixed_size = 40;
    std::size_t encoded_size() const { return 40; }

    std::uint32_t symbol_index() const { return wire::read_u32_le(at(0)); }

    std::string_view symbol() const { return view::text(at(4), 11, '\0'); }

    std::span<const std::byte, 1> reserved_1() const { return bytes_.subspan(15).template first<1>(); }

    MarketId market_id() const { return static_cast<MarketId>(wire::read_u16_le(at(16))); }

    std::uint8_t system_id() const { return wire::read_u8(at(18)); }

    ExchangeCode exchange_code() const { return static_cast<ExchangeCode>(wire::read_char(at(19))); }

    std::uint8_t price_scale_code() const { return wire::read_u8(at(20)); }

    SecurityType security_type() const { return static_cast<SecurityType>(wire::read_char(at(21))); }

    std::uint16_t lot_size() const { return wire::read_u16_le(at(22)); }

    std::uint32_t prev_close_price() const { return wire::read_u32_le(at(24)); }

    std::uint32_t prev_close_volume() const { return wire::read_u32_le(at(28)); }

    PriceResolution price_resolution() const { return static_cast<PriceResolution>(wire::read_u8(at(32))); }

    RoundLot round_lot() const { return static_cast<RoundLot>(wire::read_char(at(33))); }

    std::uint16_t mpv() const { return wire::read_u16_le(at(34)); }

    std::uint16_t unit_of_trade() const { return wire::read_u16_le(at(36)); }

    std::span<const std::byte, 2> reserved_2() const { return bytes_.subspan(38).template first<2>(); }

    void print(std::ostream& out) const {
        out << "SymbolIndexMappingMessage{";
        out << "symbol_index=";
        out << symbol_index();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", reserved_1=";
        print::hex(out, reserved_1().data(), reserved_1().size());
        out << ", market_id=";
        out << market_id();
        out << ", system_id=";
        out << static_cast<int>(system_id());
        out << ", exchange_code=";
        out << exchange_code();
        out << ", price_scale_code=";
        out << static_cast<int>(price_scale_code());
        out << ", security_type=";
        out << security_type();
        out << ", lot_size=";
        out << lot_size();
        out << ", prev_close_price=";
        out << prev_close_price();
        out << ", prev_close_volume=";
        out << prev_close_volume();
        out << ", price_resolution=";
        out << price_resolution();
        out << ", round_lot=";
        out << round_lot();
        out << ", mpv=";
        out << mpv();
        out << ", unit_of_trade=";
        out << unit_of_trade();
        out << ", reserved_2=";
        print::hex(out, reserved_2().data(), reserved_2().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SymbolIndexMappingMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g
