#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// The Price Limits message is sent out at the start of a session for products subject to price
// limits per the contract specifications.
class PriceLimitsMessage {
  public:
    static constexpr const char* name = "PriceLimitsMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PriceLimitsMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PriceLimitsMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 26;
    static constexpr std::size_t fixed_size = 26;
    std::size_t encoded_size() const { return 26; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::string_view symbol() const { return view::text(at(4), 6, ' '); }

    Decimal upper_price_limit() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(10))), -4); }

    Decimal lower_price_limit() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(18))), -4); }

    void print(std::ostream& out) const {
        out << "PriceLimitsMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", upper_price_limit=";
        out << upper_price_limit();
        out << ", lower_price_limit=";
        out << lower_price_limit();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PriceLimitsMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
