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

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// The Modify Order message is sent whenever an open order is visibly modified. The Order Id
// refers to the Order Id of the original Add Order message.
class ModifyOrderShortMessage {
  public:
    static constexpr const char* name = "ModifyOrderShortMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ModifyOrderShortMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ModifyOrderShortMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 17;
    static constexpr std::size_t fixed_size = 17;
    std::size_t encoded_size() const { return 17; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(4)); }

    std::uint16_t short_quantity() const { return wire::read_u16_le(at(12)); }

    Decimal short_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u16_le(at(14))), -2); }

    ModifyFlags modify_flags() const { return ModifyFlags{ bytes_.subspan(16) }; }

    void print(std::ostream& out) const {
        out << "ModifyOrderShortMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", order_id=";
        out << order_id();
        out << ", short_quantity=";
        out << short_quantity();
        out << ", short_price=";
        out << short_price();
        out << ", modify_flags=";
        modify_flags().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ModifyOrderShortMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
