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
#include "../enums/MarketStatus.hpp"
#include "../enums/StatusFlag.hpp"
#include "../enums/ShortSellingStatus.hpp"
#include "../enums/PricingMethod.hpp"
#include "../common/Decimal.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Provides information about the status of trading on a per-issue basis. Delivered when there
// is a change in the tag.
class TradingStatusMessage {
  public:
    static constexpr const char* name = "TradingStatusMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradingStatusMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradingStatusMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 17;
    static constexpr std::size_t fixed_size = 17;
    std::size_t encoded_size() const { return 17; }

    std::chrono::microseconds time_microseconds() const { return std::chrono::microseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    MarketStatus market_status() const { return static_cast<MarketStatus>(wire::read_u8(at(4))); }

    std::string_view status_flag() const { return view::text(at(5), 2, ' '); }

    ShortSellingStatus short_selling_status() const { return static_cast<ShortSellingStatus>(wire::read_u8(at(7))); }

    PricingMethod pricing_method() const { return static_cast<PricingMethod>(wire::read_u8(at(8))); }

    Decimal book_center_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(9))), -4); }

    void print(std::ostream& out) const {
        out << "TradingStatusMessage{";
        out << "time_microseconds=";
        out << time_microseconds().count();
        out << ", market_status=";
        out << market_status();
        out << ", status_flag=";
        print::text(out, status_flag());
        out << ", short_selling_status=";
        out << short_selling_status();
        out << ", pricing_method=";
        out << pricing_method();
        out << ", book_center_price=";
        out << book_center_price();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradingStatusMessage& value) {
    value.print(out);
    return out;
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
