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

// Information on a tick size for a price range.
class TickSizeTableEntry {
  public:
    static constexpr const char* name = "TickSizeTableEntry";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TickSizeTableEntry(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TickSizeTableEntry has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 24;
    static constexpr std::size_t fixed_size = 24;
    std::size_t encoded_size() const { return 24; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint32_t order_book_id() const { return wire::read_u32_be(at(4)); }

    std::uint64_t tick_size() const { return wire::read_u64_be(at(8)); }

    std::int32_t price_from() const { return wire::read_i32_be(at(16)); }

    std::int32_t price_to() const { return wire::read_i32_be(at(20)); }

    void print(std::ostream& out) const {
        out << "TickSizeTableEntry{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", order_book_id=";
        out << order_book_id();
        out << ", tick_size=";
        out << tick_size();
        out << ", price_from=";
        out << price_from();
        out << ", price_to=";
        out << price_to();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TickSizeTableEntry& value) {
    value.print(out);
    return out;
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
