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
#include "../enums/RetailLiquidityIndicator.hpp"

namespace iex::iexequities::deepplus::iextp::v1_05 {

// broadcasts a real-time Retail Liquidity Indicator Message each time there is an update to
// IEX's eligible retail liquidity interest during the trading day
class RetailLiquidityIndicatorMessage {
  public:
    static constexpr const char* name = "RetailLiquidityIndicatorMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RetailLiquidityIndicatorMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RetailLiquidityIndicatorMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 17;
    static constexpr std::size_t fixed_size = 17;
    std::size_t encoded_size() const { return 17; }

    RetailLiquidityIndicator retail_liquidity_indicator() const { return static_cast<RetailLiquidityIndicator>(wire::read_char(at(0))); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_i64_le(at(1)))); }

    std::string_view symbol() const { return view::text(at(9), 8, ' '); }

    void print(std::ostream& out) const {
        out << "RetailLiquidityIndicatorMessage{";
        out << "retail_liquidity_indicator=";
        out << retail_liquidity_indicator();
        out << ", timestamp=";
        out << timestamp().count();
        out << ", symbol=";
        print::text(out, symbol());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RetailLiquidityIndicatorMessage& value) {
    value.print(out);
    return out;
}

} // namespace iex::iexequities::deepplus::iextp::v1_05
