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
#include "../common/Decimal.hpp"
#include "../enums/OptionType.hpp"
#include "../enums/OptionClosingType.hpp"
#include "../enums/Tradable.hpp"
#include "../enums/Mpv.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// At the start of each trading day, the options system disseminates directory messages for all
// symbols eligible for the auction process in the options system.
class OptionsDirectoryMessage {
  public:
    static constexpr const char* name = "OptionsDirectoryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OptionsDirectoryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OptionsDirectoryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 39;
    static constexpr std::size_t fixed_size = 39;
    std::size_t encoded_size() const { return 39; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint32_t option_id() const { return wire::read_u32_be(at(4)); }

    std::string_view security_symbol() const { return view::text(at(8), 6, ' '); }

    std::uint8_t expiration_year() const { return wire::read_u8(at(14)); }

    std::uint8_t expiration_month() const { return wire::read_u8(at(15)); }

    std::uint8_t expiration_day() const { return wire::read_u8(at(16)); }

    Decimal strike_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i32_be(at(17))), -4); }

    OptionType option_type() const { return static_cast<OptionType>(wire::read_char(at(21))); }

    std::uint8_t source() const { return wire::read_u8(at(22)); }

    std::string_view underlying_symbol() const { return view::text(at(23), 13, ' '); }

    OptionClosingType option_closing_type() const { return static_cast<OptionClosingType>(wire::read_char(at(36))); }

    Tradable tradable() const { return static_cast<Tradable>(wire::read_char(at(37))); }

    Mpv mpv() const { return static_cast<Mpv>(wire::read_char(at(38))); }

    void print(std::ostream& out) const {
        out << "OptionsDirectoryMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", option_id=";
        out << option_id();
        out << ", security_symbol=";
        print::text(out, security_symbol());
        out << ", expiration_year=";
        out << static_cast<int>(expiration_year());
        out << ", expiration_month=";
        out << static_cast<int>(expiration_month());
        out << ", expiration_day=";
        out << static_cast<int>(expiration_day());
        out << ", strike_price=";
        out << strike_price();
        out << ", option_type=";
        out << option_type();
        out << ", source=";
        out << static_cast<int>(source());
        out << ", underlying_symbol=";
        print::text(out, underlying_symbol());
        out << ", option_closing_type=";
        out << option_closing_type();
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

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
