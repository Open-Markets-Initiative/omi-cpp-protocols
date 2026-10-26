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

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// OrderAddedMessage
class OrderAddedMessage {
  public:
    static constexpr const char* name = "OrderAddedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderAddedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderAddedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 31;
    static constexpr std::size_t fixed_size = 31;
    std::size_t encoded_size() const { return 31; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(at(0)))); }

    std::uint16_t security_id() const { return wire::read_u16_be(at(8)); }

    std::uint64_t order_id() const { return wire::read_u64_be(at(10)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(18))); }

    std::uint32_t quantity() const { return wire::read_u32_be(at(19)); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_be(at(23))), -6); }

    void print(std::ostream& out) const {
        out << "OrderAddedMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", security_id=";
        out << security_id();
        out << ", order_id=";
        out << order_id();
        out << ", side=";
        out << side();
        out << ", quantity=";
        out << quantity();
        out << ", price=";
        out << price();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderAddedMessage& value) {
    value.print(out);
    return out;
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
