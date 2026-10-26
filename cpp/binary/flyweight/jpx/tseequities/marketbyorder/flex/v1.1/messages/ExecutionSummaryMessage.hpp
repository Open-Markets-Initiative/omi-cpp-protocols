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
#include "../enums/TriggeredSide.hpp"
#include "../common/Decimal.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Provides summary information about execution. Delivered when an execution occurs.
class ExecutionSummaryMessage {
  public:
    static constexpr const char* name = "ExecutionSummaryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ExecutionSummaryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ExecutionSummaryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 45;
    static constexpr std::size_t fixed_size = 45;
    std::size_t encoded_size() const { return 45; }

    std::chrono::microseconds time_microseconds() const { return std::chrono::microseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    TriggeredSide triggered_side() const { return static_cast<TriggeredSide>(wire::read_char(at(4))); }

    std::uint64_t total_volume() const { return wire::read_u48_be(at(5)); }

    std::uint64_t total_invalidation() const { return wire::read_u48_be(at(11)); }

    Decimal last_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(17))), -4); }

    std::uint32_t match_id() const { return wire::read_u32_be(at(25)); }

    std::optional<Decimal> best_offer() const { return wire::nullable_decimal(wire::read_u64_be(at(29)), static_cast<std::uint64_t>(0ULL), -4); }

    std::optional<Decimal> best_bid() const { return wire::nullable_decimal(wire::read_u64_be(at(37)), static_cast<std::uint64_t>(0ULL), -4); }

    void print(std::ostream& out) const {
        out << "ExecutionSummaryMessage{";
        out << "time_microseconds=";
        out << time_microseconds().count();
        out << ", triggered_side=";
        out << triggered_side();
        out << ", total_volume=";
        out << total_volume();
        out << ", total_invalidation=";
        out << total_invalidation();
        out << ", last_price=";
        out << last_price();
        out << ", match_id=";
        out << match_id();
        out << ", best_offer=";
        print::optional(out, best_offer());
        out << ", best_bid=";
        print::optional(out, best_bid());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ExecutionSummaryMessage& value) {
    value.print(out);
    return out;
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
