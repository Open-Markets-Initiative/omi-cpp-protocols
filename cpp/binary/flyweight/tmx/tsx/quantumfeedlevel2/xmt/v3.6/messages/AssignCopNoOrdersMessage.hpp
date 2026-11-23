// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/AssignCopNoOrdersMessage.hpp
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

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

class AssignCopNoOrdersMessage {
  public:
    static constexpr const char* name = "AssignCopNoOrdersMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AssignCopNoOrdersMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AssignCopNoOrdersMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 28;
    static constexpr std::size_t fixed_size = 28;
    std::size_t encoded_size() const { return 28; }

    std::string_view symbol() const { return view::text(at(0), 12, ' '); }

    std::optional<Decimal> calculated_opening_price() const { return wire::nullable_decimal(wire::read_u64_le(at(12)), static_cast<std::uint64_t>(0ULL), -6); }

    std::optional<std::chrono::nanoseconds> trading_system_time_stamp() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(20)), static_cast<std::uint64_t>(0ULL)); }

    void print(std::ostream& out) const {
        out << "AssignCopNoOrdersMessage{";
        out << "symbol=";
        print::text(out, symbol());
        out << ", calculated_opening_price=";
        print::optional(out, calculated_opening_price());
        out << ", trading_system_time_stamp=";
        print::optional_duration(out, trading_system_time_stamp());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AssignCopNoOrdersMessage& value) {
    value.print(out);
    return out;
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
