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
#include "../enums/TradingStatus.hpp"
#include "../enums/GthTradingStatus.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

// The Trading Status message is used to indicate the current trading status of a complex
// instrument.
class TradingStatusMessage {
  public:
    static constexpr const char* name = "TradingStatusMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradingStatusMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradingStatusMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 16;
    static constexpr std::size_t fixed_size = 16;
    std::size_t encoded_size() const { return 16; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::string_view complex_symbol_id() const { return view::text(at(4), 6, ' '); }

    std::span<const std::byte, 2> unused() const { return bytes_.subspan(10).template first<2>(); }

    TradingStatus trading_status() const { return static_cast<TradingStatus>(wire::read_char(at(12))); }

    std::span<const std::byte, 1> reserved_1() const { return bytes_.subspan(13).template first<1>(); }

    GthTradingStatus gth_trading_status() const { return static_cast<GthTradingStatus>(wire::read_char(at(14))); }

    std::span<const std::byte, 1> padding() const { return bytes_.subspan(15).template first<1>(); }

    void print(std::ostream& out) const {
        out << "TradingStatusMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", complex_symbol_id=";
        print::text(out, complex_symbol_id());
        out << ", unused=";
        print::hex(out, unused().data(), unused().size());
        out << ", trading_status=";
        out << trading_status();
        out << ", reserved_1=";
        print::hex(out, reserved_1().data(), reserved_1().size());
        out << ", gth_trading_status=";
        out << gth_trading_status();
        out << ", padding=";
        print::hex(out, padding().data(), padding().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradingStatusMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::complex::pitch::v2_1_18
