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

namespace bse::bseindia::eobi::fbe::v1_4 {

// Carries the best bid and offer of a non crossed order book during an auction call phase.
class AuctionBestBidOfferMessage {
  public:
    static constexpr const char* name = "AuctionBestBidOfferMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AuctionBestBidOfferMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AuctionBestBidOfferMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    std::int64_t security_id() const { return wire::read_i64_le(at(8)); }

    std::optional<Decimal> bid_px() const { return wire::nullable_decimal(wire::read_i64_le(at(16)), static_cast<std::int64_t>(0x8000000000000000LL), -6); }

    std::optional<Decimal> offer_px() const { return wire::nullable_decimal(wire::read_i64_le(at(24)), static_cast<std::int64_t>(0x8000000000000000LL), -6); }

    void print(std::ostream& out) const {
        out << "AuctionBestBidOfferMessage{";
        out << "transact_time=";
        out << transact_time().count();
        out << ", security_id=";
        out << security_id();
        out << ", bid_px=";
        print::optional(out, bid_px());
        out << ", offer_px=";
        print::optional(out, offer_px());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AuctionBestBidOfferMessage& value) {
    value.print(out);
    return out;
}

} // namespace bse::bseindia::eobi::fbe::v1_4
