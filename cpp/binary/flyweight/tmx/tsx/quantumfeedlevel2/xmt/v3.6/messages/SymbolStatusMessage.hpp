// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/SymbolStatusMessage.hpp
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
#include "../enums/ListingMarket.hpp"
#include "../enums/ProductType.hpp"
#include "../enums/StockState.hpp"
#include "../enums/TestSymbol.hpp"
#include "../enums/MocEligible.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

class SymbolStatusMessage {
  public:
    static constexpr const char* name = "SymbolStatusMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SymbolStatusMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SymbolStatusMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 66;
    static constexpr std::size_t fixed_size = 66;
    std::size_t encoded_size() const { return 66; }

    std::string_view symbol() const { return view::text(at(0), 12, ' '); }

    std::optional<std::uint8_t> stock_group() const { return wire::nullable(wire::read_u8(at(12)), static_cast<std::uint8_t>(0ULL)); }

    std::string_view cusip() const { return view::text(at(13), 12, ' '); }

    std::optional<std::uint16_t> board_lot() const { return wire::nullable(wire::read_u16_le(at(25)), static_cast<std::uint16_t>(0ULL)); }

    Currency currency() const { return static_cast<Currency>(wire::read_char(at(27))); }

    std::optional<Decimal> face_value() const { return wire::nullable_decimal(wire::read_u64_le(at(28)), static_cast<std::uint64_t>(0ULL), -6); }

    std::optional<Decimal> last_sale() const { return wire::nullable_decimal(wire::read_u64_le(at(36)), static_cast<std::uint64_t>(0ULL), -6); }

    ListingMarket listing_market() const { return static_cast<ListingMarket>(wire::read_char(at(44))); }

    ProductType product_type() const { return static_cast<ProductType>(wire::read_char(at(45))); }

    std::optional<std::uint32_t> buy_maximum_quantity() const { return wire::nullable(wire::read_u32_le(at(46)), static_cast<std::uint32_t>(0ULL)); }

    std::optional<std::uint32_t> buy_minimum_quantity() const { return wire::nullable(wire::read_u32_le(at(50)), static_cast<std::uint32_t>(0ULL)); }

    std::optional<std::uint32_t> sell_maximum_quantity() const { return wire::nullable(wire::read_u32_le(at(54)), static_cast<std::uint32_t>(0ULL)); }

    std::optional<std::uint32_t> sell_minimum_quantity() const { return wire::nullable(wire::read_u32_le(at(58)), static_cast<std::uint32_t>(0ULL)); }

    std::string_view stock_state() const { return view::text(at(62), 2, ' '); }

    TestSymbol test_symbol() const { return static_cast<TestSymbol>(wire::read_char(at(64))); }

    MocEligible moc_eligible() const { return static_cast<MocEligible>(wire::read_char(at(65))); }

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
        out << ", listing_market=";
        out << listing_market();
        out << ", product_type=";
        out << product_type();
        out << ", buy_maximum_quantity=";
        print::optional(out, buy_maximum_quantity());
        out << ", buy_minimum_quantity=";
        print::optional(out, buy_minimum_quantity());
        out << ", sell_maximum_quantity=";
        print::optional(out, sell_maximum_quantity());
        out << ", sell_minimum_quantity=";
        print::optional(out, sell_minimum_quantity());
        out << ", stock_state=";
        print::text(out, stock_state());
        out << ", test_symbol=";
        out << test_symbol();
        out << ", moc_eligible=";
        out << moc_eligible();
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

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
