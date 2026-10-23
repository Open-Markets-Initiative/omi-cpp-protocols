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
#include "../enums/IsTestSymbol.hpp"
#include "../common/Decimal.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// InstrumentDirectoryMessage
class InstrumentDirectoryMessage {
  public:
    static constexpr const char* name = "InstrumentDirectoryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit InstrumentDirectoryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every InstrumentDirectoryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 36;
    static constexpr std::size_t fixed_size = 36;
    std::size_t encoded_size() const { return 36; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(at(0)))); }

    std::uint16_t security_id() const { return wire::read_u16_be(at(8)); }

    std::string_view symbol() const { return view::text(at(10), 6, '\0'); }

    std::string_view symbol_sfx() const { return view::text(at(16), 6, '\0'); }

    std::uint32_t round_lot() const { return wire::read_u32_be(at(22)); }

    std::uint8_t reserved() const { return wire::read_u8(at(26)); }

    IsTestSymbol is_test_symbol() const { return static_cast<IsTestSymbol>(wire::read_u8(at(27))); }

    Decimal mpv() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_be(at(28))), -6); }

    void print(std::ostream& out) const {
        out << "InstrumentDirectoryMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", security_id=";
        out << security_id();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", symbol_sfx=";
        print::text(out, symbol_sfx());
        out << ", round_lot=";
        out << round_lot();
        out << ", reserved=";
        out << static_cast<int>(reserved());
        out << ", is_test_symbol=";
        out << is_test_symbol();
        out << ", mpv=";
        out << mpv();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const InstrumentDirectoryMessage& value) {
    value.print(out);
    return out;
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
