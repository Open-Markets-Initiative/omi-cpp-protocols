#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"
#include "../enums/BidCondition.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Wide Bid
class WideBid {
  public:
    static constexpr const char* name = "WideBid";

    // the bytes it reads, which it does not own: they must outlive it
    explicit WideBid(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every WideBid has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 17;
    static constexpr std::size_t fixed_size = 17;
    std::size_t encoded_size() const { return 17; }

    Decimal wide_bid_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(0))), -4); }

    std::uint32_t wide_bid_size() const { return wire::read_u32_le(at(8)); }

    std::span<const std::byte, 4> reserved_4() const { return bytes_.subspan(12).template first<4>(); }

    BidCondition bid_condition() const { return static_cast<BidCondition>(wire::read_char(at(16))); }

    void print(std::ostream& out) const {
        out << "WideBid{";
        out << "wide_bid_price=";
        out << wide_bid_price();
        out << ", wide_bid_size=";
        out << wide_bid_size();
        out << ", reserved_4=";
        print::hex(out, reserved_4().data(), reserved_4().size());
        out << ", bid_condition=";
        out << bid_condition();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const WideBid& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
