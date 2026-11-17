// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: messages/LastSaleMessage.hpp
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

// used to disseminate trades that are resulting from executions on MIAX Futures Onyx during
// the current trading session
class LastSaleMessage {
  public:
    static constexpr const char* name = "LastSaleMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit LastSaleMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every LastSaleMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    std::uint32_t instrument_id() const { return wire::read_u32_le(at(8)); }

    std::uint64_t trade_id() const { return wire::read_u64_le(at(12)); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(20))), -9); }

    std::uint32_t size() const { return wire::read_u32_le(at(28)); }

    void print(std::ostream& out) const {
        out << "LastSaleMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", instrument_id=";
        out << instrument_id();
        out << ", trade_id=";
        out << trade_id();
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

inline std::ostream& operator<<(std::ostream& out, const LastSaleMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
