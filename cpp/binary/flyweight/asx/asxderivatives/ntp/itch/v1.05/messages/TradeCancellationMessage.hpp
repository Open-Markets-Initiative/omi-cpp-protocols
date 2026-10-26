#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

// This message is sent whenever a trade is cancelled by ASX
class TradeCancellationMessage {
  public:
    static constexpr const char* name = "TradeCancellationMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeCancellationMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeCancellationMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 18;
    static constexpr std::size_t fixed_size = 18;
    std::size_t encoded_size() const { return 18; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint16_t trade_date() const { return wire::read_u16_be(at(4)); }

    std::uint32_t tradeable_instrument_id() const { return wire::read_u32_be(at(6)); }

    std::uint64_t trade_id() const { return wire::read_u64_be(at(10)); }

    void print(std::ostream& out) const {
        out << "TradeCancellationMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", trade_date=";
        out << trade_date();
        out << ", tradeable_instrument_id=";
        out << tradeable_instrument_id();
        out << ", trade_id=";
        out << trade_id();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradeCancellationMessage& value) {
    value.print(out);
    return out;
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
