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
#include "../enums/RegShoAction.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// The Trading Status message is used to indicate the current trading status of a security. A
// Trading Status message will be sent whenever a security’s trading status changes.
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

    std::string_view expanded_symbol() const { return view::text(at(4), 8, ' '); }

    TradingStatus trading_status() const { return static_cast<TradingStatus>(wire::read_char(at(12))); }

    RegShoAction reg_sho_action() const { return static_cast<RegShoAction>(wire::read_char(at(13))); }

    std::span<const std::byte, 1> reserved_1() const { return bytes_.subspan(14).template first<1>(); }

    std::span<const std::byte, 1> second_reserved_1() const { return bytes_.subspan(15).template first<1>(); }

    void print(std::ostream& out) const {
        out << "TradingStatusMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", expanded_symbol=";
        print::text(out, expanded_symbol());
        out << ", trading_status=";
        out << trading_status();
        out << ", reg_sho_action=";
        out << reg_sho_action();
        out << ", reserved_1=";
        print::hex(out, reserved_1().data(), reserved_1().size());
        out << ", second_reserved_1=";
        print::hex(out, second_reserved_1().data(), second_reserved_1().size());
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

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
