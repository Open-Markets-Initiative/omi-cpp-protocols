#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

// This message is disseminated in response to changes in the equilibrium price for an order
// book during a pre-open period
class EquilibriumPriceMessage {
  public:
    static constexpr const char* name = "EquilibriumPriceMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit EquilibriumPriceMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every EquilibriumPriceMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 42;
    static constexpr std::size_t fixed_size = 42;
    std::size_t encoded_size() const { return 42; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint16_t trade_date() const { return wire::read_u16_be(at(4)); }

    std::uint32_t tradeable_instrument_id() const { return wire::read_u32_be(at(6)); }

    Decimal equilibrium_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_be(at(10))), -2); }

    std::uint64_t matched_quantity() const { return wire::read_u64_be(at(18)); }

    std::uint64_t bid_quantity() const { return wire::read_u64_be(at(26)); }

    std::uint64_t ask_quantity() const { return wire::read_u64_be(at(34)); }

    void print(std::ostream& out) const {
        out << "EquilibriumPriceMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", trade_date=";
        out << trade_date();
        out << ", tradeable_instrument_id=";
        out << tradeable_instrument_id();
        out << ", equilibrium_price=";
        out << equilibrium_price();
        out << ", matched_quantity=";
        out << matched_quantity();
        out << ", bid_quantity=";
        out << bid_quantity();
        out << ", ask_quantity=";
        out << ask_quantity();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const EquilibriumPriceMessage& value) {
    value.print(out);
    return out;
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
