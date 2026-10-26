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
#include "../enums/TestSecurityIndicator.hpp"
#include "../enums/PrimaryMarketCode.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// This is the message format that will be used to disseminate all security symbols traded on
// MIAX Pearl Equities for the current trading session. The Symbol ID sent in this message will
// be disseminated in Depth of Market messages.
class SymbolUpdateMessage {
  public:
    static constexpr const char* name = "SymbolUpdateMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SymbolUpdateMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SymbolUpdateMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 41;
    static constexpr std::size_t fixed_size = 41;
    std::size_t encoded_size() const { return 41; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint32_t symbol_id() const { return wire::read_u32_le(at(4)); }

    std::string_view ticker_symbol() const { return view::text(at(8), 11, ' '); }

    std::span<const std::byte, 1> reserved_1() const { return bytes_.subspan(19).template first<1>(); }

    TestSecurityIndicator test_security_indicator() const { return static_cast<TestSecurityIndicator>(wire::read_char(at(20))); }

    std::span<const std::byte, 1> second_reserved_1() const { return bytes_.subspan(21).template first<1>(); }

    std::uint16_t lot_size() const { return wire::read_u16_le(at(22)); }

    std::string_view opening_time() const { return view::text(at(24), 8, ' '); }

    std::string_view closing_time() const { return view::text(at(32), 8, ' '); }

    PrimaryMarketCode primary_market_code() const { return static_cast<PrimaryMarketCode>(wire::read_char(at(40))); }

    void print(std::ostream& out) const {
        out << "SymbolUpdateMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", symbol_id=";
        out << symbol_id();
        out << ", ticker_symbol=";
        print::text(out, ticker_symbol());
        out << ", reserved_1=";
        print::hex(out, reserved_1().data(), reserved_1().size());
        out << ", test_security_indicator=";
        out << test_security_indicator();
        out << ", second_reserved_1=";
        print::hex(out, second_reserved_1().data(), second_reserved_1().size());
        out << ", lot_size=";
        out << lot_size();
        out << ", opening_time=";
        print::text(out, opening_time());
        out << ", closing_time=";
        print::text(out, closing_time());
        out << ", primary_market_code=";
        out << primary_market_code();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SymbolUpdateMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
