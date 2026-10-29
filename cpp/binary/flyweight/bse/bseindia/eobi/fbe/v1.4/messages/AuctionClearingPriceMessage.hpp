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

namespace bse::bseindia::eobi::fbe::v1_4 {

// Published for a crossed order book in an auction, indicating the potential auction price.
class AuctionClearingPriceMessage {
  public:
    static constexpr const char* name = "AuctionClearingPriceMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AuctionClearingPriceMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AuctionClearingPriceMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    std::int64_t security_id() const { return wire::read_i64_le(at(8)); }

    Decimal last_px() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(16))), -6); }

    std::int64_t last_qty() const { return wire::read_i64_le(at(24)); }

    void print(std::ostream& out) const {
        out << "AuctionClearingPriceMessage{";
        out << "transact_time=";
        out << transact_time().count();
        out << ", security_id=";
        out << security_id();
        out << ", last_px=";
        out << last_px();
        out << ", last_qty=";
        out << last_qty();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AuctionClearingPriceMessage& value) {
    value.print(out);
    return out;
}

} // namespace bse::bseindia::eobi::fbe::v1_4
