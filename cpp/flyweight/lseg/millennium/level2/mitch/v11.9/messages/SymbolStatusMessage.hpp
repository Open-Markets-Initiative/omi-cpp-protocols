#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/TradingStatus.hpp"
#include "../bitfields/SymbolStatusFlags.hpp"
#include "../enums/SessionChangeReason.hpp"
#include "../enums/BookType.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// Indicates the trading session (pre-opening, regular trading, etc.) that currently applies to
// an instrument.
class SymbolStatusMessage {
  public:
    static constexpr const char* name = "SymbolStatusMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SymbolStatusMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SymbolStatusMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 26;
    static constexpr std::size_t fixed_size = 26;
    std::size_t encoded_size() const { return 26; }

    std::uint32_t nanosecond() const { return wire::read_u32_le(at(0)); }

    std::uint32_t instrument_id() const { return wire::read_u32_le(at(4)); }

    std::span<const std::byte, 1> reserved_a() const { return bytes_.subspan(8).template first<1>(); }

    std::span<const std::byte, 1> reserved_b() const { return bytes_.subspan(9).template first<1>(); }

    TradingStatus trading_status() const { return static_cast<TradingStatus>(wire::read_char(at(10))); }

    SymbolStatusFlags symbol_status_flags() const { return SymbolStatusFlags{ bytes_.subspan(11) }; }

    std::string_view reason() const { return view::text(at(12), 4, ' '); }

    SessionChangeReason session_change_reason() const { return static_cast<SessionChangeReason>(wire::read_u8(at(16))); }

    std::string_view new_end_time() const { return view::text(at(17), 8, ' '); }

    BookType book_type() const { return static_cast<BookType>(wire::read_u8(at(25))); }

    void print(std::ostream& out) const {
        out << "SymbolStatusMessage{";
        out << "nanosecond=";
        out << nanosecond();
        out << ", instrument_id=";
        out << instrument_id();
        out << ", reserved_a=";
        print::hex(out, reserved_a().data(), reserved_a().size());
        out << ", reserved_b=";
        print::hex(out, reserved_b().data(), reserved_b().size());
        out << ", trading_status=";
        out << trading_status();
        out << ", symbol_status_flags=";
        symbol_status_flags().print(out);
        out << ", reason=";
        print::text(out, reason());
        out << ", session_change_reason=";
        out << session_change_reason();
        out << ", new_end_time=";
        print::text(out, new_end_time());
        out << ", book_type=";
        out << book_type();
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

} // namespace lseg::millennium::level2::mitch::v11_9
