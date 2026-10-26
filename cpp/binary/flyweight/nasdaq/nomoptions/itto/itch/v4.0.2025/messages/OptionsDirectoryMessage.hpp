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
#include "../common/Day.hpp"
#include "../common/Decimal.hpp"
#include "../enums/OptionType.hpp"
#include "../enums/OptionsClosingType.hpp"
#include "../enums/Tradable.hpp"
#include "../enums/Mpv.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// At the start of each trading day, NASDAQ disseminates options symbol directory messages for
// all active options symbols in the NASDAQ option system.
class OptionsDirectoryMessage {
  public:
    static constexpr const char* name = "OptionsDirectoryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OptionsDirectoryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OptionsDirectoryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 43;
    static constexpr std::size_t fixed_size = 43;
    std::size_t encoded_size() const { return 43; }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(0)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(2)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::uint32_t option_id() const { return wire::read_u32_be(at(8)); }

    std::string_view security_symbol() const { return view::text(at(12), 6, ' '); }

    std::uint8_t expiration_year() const { return wire::read_u8(at(18)); }

    std::uint8_t expiration_month() const { return wire::read_u8(at(19)); }

    std::uint8_t expiration_date() const { return wire::read_u8(at(20)); }

    Decimal explicit_strike_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(21))), -4); }

    OptionType option_type() const { return static_cast<OptionType>(wire::read_char(at(25))); }

    std::uint8_t source() const { return wire::read_u8(at(26)); }

    std::string_view underlying_symbol() const { return view::text(at(27), 13, ' '); }

    OptionsClosingType options_closing_type() const { return static_cast<OptionsClosingType>(wire::read_char(at(40))); }

    Tradable tradable() const { return static_cast<Tradable>(wire::read_char(at(41))); }

    Mpv mpv() const { return static_cast<Mpv>(wire::read_char(at(42))); }

    void print(std::ostream& out) const {
        out << "OptionsDirectoryMessage{";
        out << "tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        calendar::print(out, timestamp().count(), 1, "America/New_York");
        out << ", option_id=";
        out << option_id();
        out << ", security_symbol=";
        print::text(out, security_symbol());
        out << ", expiration_year=";
        out << static_cast<int>(expiration_year());
        out << ", expiration_month=";
        out << static_cast<int>(expiration_month());
        out << ", expiration_date=";
        out << static_cast<int>(expiration_date());
        out << ", explicit_strike_price=";
        out << explicit_strike_price();
        out << ", option_type=";
        out << option_type();
        out << ", source=";
        out << static_cast<int>(source());
        out << ", underlying_symbol=";
        print::text(out, underlying_symbol());
        out << ", options_closing_type=";
        out << options_closing_type();
        out << ", tradable=";
        out << tradable();
        out << ", mpv=";
        out << mpv();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OptionsDirectoryMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
