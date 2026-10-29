#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/CompactBid.hpp"
#include "../structs/CompactOffer.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// This is the message format that will be used to disseminate both sides of the MIAX top of
// market for strategies (cMBBO) with low net price and small aggregate size.
class CompactComplexDoubleSidedTopOfMarketMessage {
  public:
    static constexpr const char* name = "CompactComplexDoubleSidedTopOfMarketMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit CompactComplexDoubleSidedTopOfMarketMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every CompactComplexDoubleSidedTopOfMarketMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 22;
    static constexpr std::size_t fixed_size = 22;
    std::size_t encoded_size() const { return 22; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint32_t strategy_id() const { return wire::read_u32_le(at(4)); }

    CompactBid compact_bid() const { return CompactBid{ bytes_.subspan(8) }; }

    CompactOffer compact_offer() const { return CompactOffer{ bytes_.subspan(15) }; }

    void print(std::ostream& out) const {
        out << "CompactComplexDoubleSidedTopOfMarketMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", strategy_id=";
        out << strategy_id();
        out << ", compact_bid=";
        compact_bid().print(out);
        out << ", compact_offer=";
        compact_offer().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const CompactComplexDoubleSidedTopOfMarketMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
