// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: messages/AssignLimitMessage.hpp
#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"
#include "../enums/OrderSide.hpp"
#include "../groups/CopLimit.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

class AssignLimitMessage {
  public:
    static constexpr const char* name = "AssignLimitMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AssignLimitMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AssignLimitMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 296;
    static constexpr std::size_t fixed_size = 296;
    std::size_t encoded_size() const { return 296; }

    std::string_view symbol() const { return view::text(at(0), 9, ' '); }

    std::optional<Decimal> calculated_opening_price() const { return wire::nullable_decimal(wire::read_u64_le(at(9)), static_cast<std::uint64_t>(0ULL), -6); }

    OrderSide order_side() const { return static_cast<OrderSide>(wire::read_char(at(17))); }

    view::entries<CopLimit> cop_limit() const { return view::entries<CopLimit>{ bytes_.subspan(18), 15 }; }

    std::optional<std::chrono::microseconds> trading_system_time_stamp() const { return wire::nullable_duration<std::chrono::microseconds>(wire::read_u64_le(at(288)), static_cast<std::uint64_t>(0ULL)); }

    void print(std::ostream& out) const {
        out << "AssignLimitMessage{";
        out << "symbol=";
        print::text(out, symbol());
        out << ", calculated_opening_price=";
        print::optional(out, calculated_opening_price());
        out << ", order_side=";
        out << order_side();
        out << ", cop_limit=";
        print::sequence(out, cop_limit());
        out << ", trading_system_time_stamp=";
        print::optional_duration(out, trading_system_time_stamp());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AssignLimitMessage& value) {
    value.print(out);
    return out;
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
