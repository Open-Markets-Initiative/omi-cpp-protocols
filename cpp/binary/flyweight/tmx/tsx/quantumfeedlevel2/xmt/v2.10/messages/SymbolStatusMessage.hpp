// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: messages/SymbolStatusMessage.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/Currency.hpp"
#include "../common/Decimal.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

class SymbolStatusMessage {
  public:
    static constexpr const char* name = "SymbolStatusMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SymbolStatusMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SymbolStatusMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 41;
    static constexpr std::size_t fixed_size = 41;
    std::size_t encoded_size() const { return 41; }

    std::string_view symbol() const { return view::text(at(0), 9, ' '); }

    std::optional<std::uint8_t> stock_group() const { return wire::nullable(wire::read_u8(at(9)), static_cast<std::uint8_t>(0ULL)); }

    std::string_view cusip() const { return view::text(at(10), 12, ' '); }

    std::optional<std::uint16_t> board_lot() const { return wire::nullable(wire::read_u16_le(at(22)), static_cast<std::uint16_t>(0ULL)); }

    Currency currency() const { return static_cast<Currency>(wire::read_char(at(24))); }

    std::optional<Decimal> face_value() const { return wire::nullable_decimal(wire::read_u64_le(at(25)), static_cast<std::uint64_t>(0ULL), -6); }

    std::optional<Decimal> last_sale() const { return wire::nullable_decimal(wire::read_u64_le(at(33)), static_cast<std::uint64_t>(0ULL), -6); }

    void print(std::ostream& out) const {
        out << "SymbolStatusMessage{";
        out << "symbol=";
        print::text(out, symbol());
        out << ", stock_group=";
        print::optional(out, stock_group());
        out << ", cusip=";
        print::text(out, cusip());
        out << ", board_lot=";
        print::optional(out, board_lot());
        out << ", currency=";
        out << currency();
        out << ", face_value=";
        print::optional(out, face_value());
        out << ", last_sale=";
        print::optional(out, last_sale());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SymbolStatusMessage& value) {
    value.print(out);
    return out;
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
