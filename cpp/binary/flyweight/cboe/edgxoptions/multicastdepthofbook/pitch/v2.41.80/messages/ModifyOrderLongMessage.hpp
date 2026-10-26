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
#include "../bitfields/ModifyFlags.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// The Modify Order message is sent whenever an open order is visibly modified. The Order Id
// refers to the Order Id of the original Add Order message. Note that Modify Order messages
// that appear to be "No Ops" (i.e. they do not appear to modify any relevant fields) will
// still lose priority.
class ModifyOrderLongMessage {
  public:
    static constexpr const char* name = "ModifyOrderLongMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ModifyOrderLongMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ModifyOrderLongMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 25;
    static constexpr std::size_t fixed_size = 25;
    std::size_t encoded_size() const { return 25; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(4)); }

    std::uint32_t quantity_long() const { return wire::read_u32_le(at(12)); }

    Decimal price_long() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(16))), -4); }

    ModifyFlags modify_flags() const { return ModifyFlags{ bytes_.subspan(24) }; }

    void print(std::ostream& out) const {
        out << "ModifyOrderLongMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", order_id=";
        out << order_id();
        out << ", quantity_long=";
        out << quantity_long();
        out << ", price_long=";
        out << price_long();
        out << ", modify_flags=";
        modify_flags().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ModifyOrderLongMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
