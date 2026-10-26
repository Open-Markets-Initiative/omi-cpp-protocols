#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/Side.hpp"
#include "../common/Decimal.hpp"
#include "../enums/AdoptedPricingMethod.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Provides information about registered orders in case of Itayose execution. Delivered when an
// execution occurs by the Itayose method or while an SQ or STQ is displayed.
class OrderExecutedWithPriceMessage {
  public:
    static constexpr const char* name = "OrderExecutedWithPriceMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderExecutedWithPriceMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderExecutedWithPriceMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 28;
    static constexpr std::size_t fixed_size = 28;
    std::size_t encoded_size() const { return 28; }

    std::chrono::microseconds time_microseconds() const { return std::chrono::microseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint32_t order_id() const { return wire::read_u32_be(at(4)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(8))); }

    std::uint64_t volume() const { return wire::read_u48_be(at(9)); }

    std::uint32_t match_id() const { return wire::read_u32_be(at(15)); }

    Decimal execution_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(19))), -4); }

    AdoptedPricingMethod adopted_pricing_method() const { return static_cast<AdoptedPricingMethod>(wire::read_u8(at(27))); }

    void print(std::ostream& out) const {
        out << "OrderExecutedWithPriceMessage{";
        out << "time_microseconds=";
        out << time_microseconds().count();
        out << ", order_id=";
        out << order_id();
        out << ", side=";
        out << side();
        out << ", volume=";
        out << volume();
        out << ", match_id=";
        out << match_id();
        out << ", execution_price=";
        out << execution_price();
        out << ", adopted_pricing_method=";
        out << adopted_pricing_method();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderExecutedWithPriceMessage& value) {
    value.print(out);
    return out;
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
