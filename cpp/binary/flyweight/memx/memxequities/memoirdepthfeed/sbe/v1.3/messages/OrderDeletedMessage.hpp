#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// OrderDeletedMessage
class OrderDeletedMessage {
  public:
    static constexpr const char* name = "OrderDeletedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderDeletedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderDeletedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 18;
    static constexpr std::size_t fixed_size = 18;
    std::size_t encoded_size() const { return 18; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(at(0)))); }

    std::uint16_t security_id() const { return wire::read_u16_be(at(8)); }

    std::uint64_t order_id() const { return wire::read_u64_be(at(10)); }

    void print(std::ostream& out) const {
        out << "OrderDeletedMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", security_id=";
        out << security_id();
        out << ", order_id=";
        out << order_id();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderDeletedMessage& value) {
    value.print(out);
    return out;
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
