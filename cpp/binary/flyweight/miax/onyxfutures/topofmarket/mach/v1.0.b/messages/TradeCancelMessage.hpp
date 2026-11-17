// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: messages/TradeCancelMessage.hpp
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

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// used to publish cancellation of a Simple Instrument trade which was previously published via
// an Order Execution Message
class TradeCancelMessage {
  public:
    static constexpr const char* name = "TradeCancelMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeCancelMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeCancelMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 35;
    static constexpr std::size_t fixed_size = 35;
    std::size_t encoded_size() const { return 35; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    std::uint16_t trade_date() const { return wire::read_u16_le(at(8)); }

    std::uint32_t instrument_id() const { return wire::read_u32_le(at(10)); }

    std::uint64_t trade_id() const { return wire::read_u64_le(at(14)); }

    std::uint8_t correction_number() const { return wire::read_u8(at(22)); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(23))), -9); }

    std::uint32_t size() const { return wire::read_u32_le(at(31)); }

    void print(std::ostream& out) const {
        out << "TradeCancelMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", trade_date=";
        out << trade_date();
        out << ", instrument_id=";
        out << instrument_id();
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

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
