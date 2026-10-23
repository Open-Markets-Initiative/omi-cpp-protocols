#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SymbolStatus.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// Used to disseminate information (symbol, segment, ISIN, underlying, etc.) on each instrument
class SymbolDirectoryMessage {
  public:
    static constexpr const char* name = "SymbolDirectoryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SymbolDirectoryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SymbolDirectoryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 63;
    static constexpr std::size_t fixed_size = 63;
    std::size_t encoded_size() const { return 63; }

    std::uint32_t nanosecond() const { return wire::read_u32_le(at(0)); }

    std::uint32_t instrument_id() const { return wire::read_u32_le(at(4)); }

    std::span<const std::byte, 1> reserved_a() const { return bytes_.subspan(8).template first<1>(); }

    std::span<const std::byte, 1> reserved_b() const { return bytes_.subspan(9).template first<1>(); }

    SymbolStatus symbol_status() const { return static_cast<SymbolStatus>(wire::read_char(at(10))); }

    std::string_view isin() const { return view::text(at(11), 12, ' '); }

    std::string_view sedol() const { return view::text(at(23), 12, ' '); }

    std::string_view segment() const { return view::text(at(35), 6, ' '); }

    std::string_view underlying() const { return view::text(at(41), 6, ' '); }

    std::string_view currency() const { return view::text(at(47), 3, ' '); }

    std::span<const std::byte, 1> reserved_byte() const { return bytes_.subspan(50).template first<1>(); }

    std::span<const std::byte, 4> reserved_4() const { return bytes_.subspan(51).template first<4>(); }

    std::int64_t previous_close_price() const { return wire::read_i64_le(at(55)); }

    void print(std::ostream& out) const {
        out << "SymbolDirectoryMessage{";
        out << "nanosecond=";
        out << nanosecond();
        out << ", instrument_id=";
        out << instrument_id();
        out << ", reserved_a=";
        print::hex(out, reserved_a().data(), reserved_a().size());
        out << ", reserved_b=";
        print::hex(out, reserved_b().data(), reserved_b().size());
        out << ", symbol_status=";
        out << symbol_status();
        out << ", isin=";
        print::text(out, isin());
        out << ", sedol=";
        print::text(out, sedol());
        out << ", segment=";
        print::text(out, segment());
        out << ", underlying=";
        print::text(out, underlying());
        out << ", currency=";
        print::text(out, currency());
        out << ", reserved_byte=";
        print::hex(out, reserved_byte().data(), reserved_byte().size());
        out << ", reserved_4=";
        print::hex(out, reserved_4().data(), reserved_4().size());
        out << ", previous_close_price=";
        out << previous_close_price();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SymbolDirectoryMessage& value) {
    value.print(out);
    return out;
}

} // namespace lseg::millennium::level2::mitch::v11_9
