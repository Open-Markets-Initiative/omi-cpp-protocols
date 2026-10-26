#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Provides changes in equilibrium price during auctions.
class EquilibriumPriceUpdate {
  public:
    static constexpr const char* name = "EquilibriumPriceUpdate";

    // the bytes it reads, which it does not own: they must outlive it
    explicit EquilibriumPriceUpdate(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every EquilibriumPriceUpdate has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 52;
    static constexpr std::size_t fixed_size = 52;
    std::size_t encoded_size() const { return 52; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint32_t order_book_id() const { return wire::read_u32_be(at(4)); }

    std::uint64_t available_bid_quantity_at_equilibrium_price() const { return wire::read_u64_be(at(8)); }

    std::uint64_t available_ask_quantity_at_equilibrium_price() const { return wire::read_u64_be(at(16)); }

    std::int32_t equilibrium_price() const { return wire::read_i32_be(at(24)); }

    std::span<const std::byte, 24> reserved_24() const { return bytes_.subspan(28).template first<24>(); }

    void print(std::ostream& out) const {
        out << "EquilibriumPriceUpdate{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", order_book_id=";
        out << order_book_id();
        out << ", available_bid_quantity_at_equilibrium_price=";
        out << available_bid_quantity_at_equilibrium_price();
        out << ", available_ask_quantity_at_equilibrium_price=";
        out << available_ask_quantity_at_equilibrium_price();
        out << ", equilibrium_price=";
        out << equilibrium_price();
        out << ", reserved_24=";
        print::hex(out, reserved_24().data(), reserved_24().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const EquilibriumPriceUpdate& value) {
    value.print(out);
    return out;
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
