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
#include "../enums/ExpiryMonth.hpp"
#include "../enums/OptionType.hpp"
#include "../common/Decimal.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

// The Options Symbol Directory message describes options and warrants contracts.
class OptionsSymbolDirectoryMessage {
  public:
    static constexpr const char* name = "OptionsSymbolDirectoryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OptionsSymbolDirectoryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OptionsSymbolDirectoryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 219;
    static constexpr std::size_t fixed_size = 219;
    std::size_t encoded_size() const { return 219; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint16_t trade_date() const { return wire::read_u16_be(at(4)); }

    std::uint32_t tradeable_instrument_id() const { return wire::read_u32_be(at(6)); }

    std::string_view symbol_name() const { return view::text(at(10), 32, ' '); }

    std::string_view long_name() const { return view::text(at(42), 60, ' '); }

    std::string_view isin() const { return view::text(at(102), 12, ' '); }

    std::string_view exchange() const { return view::text(at(114), 6, ' '); }

    std::string_view instrument() const { return view::text(at(120), 6, ' '); }

    std::string_view cfi_code() const { return view::text(at(126), 6, ' '); }

    std::uint16_t expiry_year() const { return wire::read_u16_be(at(132)); }

    ExpiryMonth expiry_month() const { return static_cast<ExpiryMonth>(wire::read_u8(at(134))); }

    OptionType option_type() const { return static_cast<OptionType>(wire::read_char(at(135))); }

    Decimal strike() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_be(at(136))), -2); }

    std::uint32_t underlying_tradeable_instrument_id() const { return wire::read_u32_be(at(144)); }

    std::uint8_t price_display_decimals() const { return wire::read_u8(at(148)); }

    std::uint32_t price_fractional_denominator() const { return wire::read_u32_be(at(149)); }

    std::uint32_t price_minimum_tick() const { return wire::read_u32_be(at(153)); }

    std::uint8_t strike_price_decimal_position() const { return wire::read_u8(at(157)); }

    std::uint32_t strike_price_fractional_denominator() const { return wire::read_u32_be(at(158)); }

    std::uint32_t strike_price_minimum_tick() const { return wire::read_u32_be(at(162)); }

    std::uint32_t last_trading_date() const { return wire::read_u32_be(at(166)); }

    Decimal prior_day_settlement() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_be(at(170))), -2); }

    std::uint64_t volatility() const { return wire::read_u64_be(at(178)); }

    std::string_view currency() const { return view::text(at(186), 3, ' '); }

    std::uint64_t lot_size_or_face_value() const { return wire::read_u64_be(at(189)); }

    std::uint8_t maturity_value() const { return wire::read_u8(at(197)); }

    std::uint16_t coupon_rate() const { return wire::read_u16_be(at(198)); }

    std::uint8_t payments_per_year() const { return wire::read_u8(at(200)); }

    std::uint32_t block_lot_size() const { return wire::read_u32_be(at(201)); }

    std::uint32_t expiry_date() const { return wire::read_u32_be(at(205)); }

    std::string_view basis_of_quotation() const { return view::text(at(209), 10, ' '); }

    void print(std::ostream& out) const {
        out << "OptionsSymbolDirectoryMessage{";
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
        out << ", isin=";
        print::text(out, isin());
        out << ", exchange=";
        print::text(out, exchange());
        out << ", instrument=";
        print::text(out, instrument());
        out << ", cfi_code=";
        print::text(out, cfi_code());
        out << ", expiry_year=";
        out << expiry_year();
        out << ", expiry_month=";
        out << expiry_month();
        out << ", option_type=";
        out << option_type();
        out << ", strike=";
        out << strike();
        out << ", underlying_tradeable_instrument_id=";
        out << underlying_tradeable_instrument_id();
        out << ", price_display_decimals=";
        out << static_cast<int>(price_display_decimals());
        out << ", price_fractional_denominator=";
        out << price_fractional_denominator();
        out << ", price_minimum_tick=";
        out << price_minimum_tick();
        out << ", strike_price_decimal_position=";
        out << static_cast<int>(strike_price_decimal_position());
        out << ", strike_price_fractional_denominator=";
        out << strike_price_fractional_denominator();
        out << ", strike_price_minimum_tick=";
        out << strike_price_minimum_tick();
        out << ", last_trading_date=";
        out << last_trading_date();
        out << ", prior_day_settlement=";
        out << prior_day_settlement();
        out << ", volatility=";
        out << volatility();
        out << ", currency=";
        print::text(out, currency());
        out << ", lot_size_or_face_value=";
        out << lot_size_or_face_value();
        out << ", maturity_value=";
        out << static_cast<int>(maturity_value());
        out << ", coupon_rate=";
        out << coupon_rate();
        out << ", payments_per_year=";
        out << static_cast<int>(payments_per_year());
        out << ", block_lot_size=";
        out << block_lot_size();
        out << ", expiry_date=";
        out << expiry_date();
        out << ", basis_of_quotation=";
        print::text(out, basis_of_quotation());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OptionsSymbolDirectoryMessage& value) {
    value.print(out);
    return out;
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
