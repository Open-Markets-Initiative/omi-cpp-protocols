#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// This message format is used to publish cancellation of a trade which was previously
// published via an Order Execution Message or a Trade Message.
class TradeCancelMessage {
  public:
    static constexpr const char* name = "TradeCancelMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeCancelMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeCancelMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 29;
    static constexpr std::size_t fixed_size = 29;
    std::size_t encoded_size() const { return 29; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint32_t symbol_id() const { return wire::read_u32_le(at(4)); }

    std::uint64_t trade_id() const { return wire::read_u64_le(at(8)); }

    std::uint8_t correction_number() const { return wire::read_u8(at(16)); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(17))), -6); }

    std::uint32_t size() const { return wire::read_u32_le(at(25)); }

    void print(std::ostream& out) const {
        out << "TradeCancelMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", symbol_id=";
        out << symbol_id();
        out << ", trade_id=";
        out << trade_id();
        out << ", correction_number=";
        out << static_cast<int>(correction_number());
        out << ", price=";
        out << price();
        out << ", size=";
        out << size();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradeCancelMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
