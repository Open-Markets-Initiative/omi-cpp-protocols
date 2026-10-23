#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Trade Flags
class TradeFlags {
  public:
    static constexpr const char* name = "TradeFlags";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeFlags(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    std::uint8_t raw() const { return wire::read_u8(bytes_.data()); }

    bool trade_cancellation() const { return (raw() & static_cast<std::uint8_t>(0x1)) != 0; }

    bool trade_correction() const { return (raw() & static_cast<std::uint8_t>(0x2)) != 0; }

    void print(std::ostream& out) const {
        out << "TradeFlags{";
        out << "trade_cancellation=";
        out << (trade_cancellation() ? "true" : "false");
        out << ", trade_correction=";
        out << (trade_correction() ? "true" : "false");
        out << '}';
    }

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradeFlags& value) {
    value.print(out);
    return out;
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
