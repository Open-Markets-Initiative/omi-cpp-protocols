// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: messages/BestBidAndOfferMessage.hpp
#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// used to publish MIAX Futures Onyx Best Bid and Offer (MBBO) of a Simple Instrument or
// Complex Instrument
class BestBidAndOfferMessage {
  public:
    static constexpr const char* name = "BestBidAndOfferMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit BestBidAndOfferMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every BestBidAndOfferMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 36;
    static constexpr std::size_t fixed_size = 36;
    std::size_t encoded_size() const { return 36; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    std::uint32_t instrument_id() const { return wire::read_u32_le(at(8)); }

    std::optional<Decimal> mbb_price() const { return wire::nullable_decimal(wire::read_i64_le(at(12)), static_cast<std::int64_t>(-999999999999999999LL), -9); }

    std::uint32_t mbb_size() const { return wire::read_u32_le(at(20)); }

    std::optional<Decimal> mbo_price() const { return wire::nullable_decimal(wire::read_i64_le(at(24)), static_cast<std::int64_t>(999999999999999999LL), -9); }

    std::uint32_t mbo_size() const { return wire::read_u32_le(at(32)); }

    void print(std::ostream& out) const {
        out << "BestBidAndOfferMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", instrument_id=";
        out << instrument_id();
        out << ", mbb_price=";
        print::optional(out, mbb_price());
        out << ", mbb_size=";
        out << mbb_size();
        out << ", mbo_price=";
        print::optional(out, mbo_price());
        out << ", mbo_size=";
        out << mbo_size();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const BestBidAndOfferMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
