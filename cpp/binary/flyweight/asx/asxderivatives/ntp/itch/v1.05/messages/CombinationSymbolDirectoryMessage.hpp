#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/PriceMethod.hpp"
#include "../groups/CombinationLeg.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

// The Combination Symbol Directory is a specialised reference data message used for defining
// combinations with up to 6 legs. It represents both standard combinations defined by ASX and
// user defined combinations created by participants
class CombinationSymbolDirectoryMessage {
  public:
    static constexpr const char* name = "CombinationSymbolDirectoryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit CombinationSymbolDirectoryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every CombinationSymbolDirectoryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 221;
    static constexpr std::size_t fixed_size = 221;
    std::size_t encoded_size() const { return 221; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint16_t trade_date() const { return wire::read_u16_be(at(4)); }

    std::uint32_t tradeable_instrument_id() const { return wire::read_u32_be(at(6)); }

    std::string_view symbol_name() const { return view::text(at(10), 32, ' '); }

    std::string_view long_name() const { return view::text(at(42), 60, ' '); }

    std::string_view cfi_code() const { return view::text(at(102), 6, ' '); }

    PriceMethod price_method() const { return static_cast<PriceMethod>(wire::read_u8(at(108))); }

    std::uint8_t price_display_decimals() const { return wire::read_u8(at(109)); }

    std::uint32_t price_fractional_denominator() const { return wire::read_u32_be(at(110)); }

    std::uint32_t price_minimum_tick() const { return wire::read_u32_be(at(114)); }

    std::uint8_t legs() const { return wire::read_u8(at(118)); }

    view::entries<CombinationLeg> combination_leg() const { return view::entries<CombinationLeg>{ bytes_.subspan(119), 6 }; }

    void print(std::ostream& out) const {
        out << "CombinationSymbolDirectoryMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", trade_date=";
        out << trade_date();
        out << ", tradeable_instrument_id=";
        out << tradeable_instrument_id();
        out << ", symbol_name=";
        print::text(out, symbol_name());
        out << ", long_name=";
        print::text(out, long_name());
        out << ", cfi_code=";
        print::text(out, cfi_code());
        out << ", price_method=";
        out << price_method();
        out << ", price_display_decimals=";
        out << static_cast<int>(price_display_decimals());
        out << ", price_fractional_denominator=";
        out << price_fractional_denominator();
        out << ", price_minimum_tick=";
        out << price_minimum_tick();
        out << ", legs=";
        out << static_cast<int>(legs());
        out << ", combination_leg=";
        print::sequence(out, combination_leg());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const CombinationSymbolDirectoryMessage& value) {
    value.print(out);
    return out;
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
