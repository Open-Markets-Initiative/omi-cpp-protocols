#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Day.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// An order on the book being cancelled in full
class OrderDeleteMessage {
  public:
    static constexpr const char* name = "OrderDeleteMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderDeleteMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderDeleteMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 18;
    static constexpr std::size_t fixed_size = 18;
    std::size_t encoded_size() const { return 18; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(at(0)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "UTC").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(8)); }

    std::uint64_t order_reference_number() const { return wire::read_u64_be(at(10)); }

    void print(std::ostream& out) const {
        out << "OrderDeleteMessage{";
        out << "timestamp=";
        calendar::print(out, timestamp().count(), 1, "UTC");
        out << ", tracking_number=";
        out << tracking_number();
        out << ", order_reference_number=";
        out << order_reference_number();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderDeleteMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
