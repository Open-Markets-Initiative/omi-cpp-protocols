#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/WideBid.hpp"
#include "../structs/WideOffer.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// This is the message format that will be used to disseminate both sides of the MIAX top of
// market for strategies (cMBBO) with net prices or aggregate sizes which cannot be specified
// in the compact format.
class WideComplexDoubleSidedTopOfMarketMessage {
  public:
    static constexpr const char* name = "WideComplexDoubleSidedTopOfMarketMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit WideComplexDoubleSidedTopOfMarketMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every WideComplexDoubleSidedTopOfMarketMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 42;
    static constexpr std::size_t fixed_size = 42;
    std::size_t encoded_size() const { return 42; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint32_t strategy_id() const { return wire::read_u32_le(at(4)); }

    WideBid wide_bid() const { return WideBid{ bytes_.subspan(8) }; }

    WideOffer wide_offer() const { return WideOffer{ bytes_.subspan(25) }; }

    void print(std::ostream& out) const {
        out << "WideComplexDoubleSidedTopOfMarketMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", strategy_id=";
        out << strategy_id();
        out << ", wide_bid=";
        wide_bid().print(out);
        out << ", wide_offer=";
        wide_offer().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const WideComplexDoubleSidedTopOfMarketMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
