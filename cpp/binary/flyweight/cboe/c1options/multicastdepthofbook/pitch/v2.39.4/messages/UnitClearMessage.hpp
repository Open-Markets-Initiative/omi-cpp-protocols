#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// The Unit Clear message instructs feed recipients to clear all orders for the Cboe book in
// the unit specified in the Sequenced Unit Header. This message will be sent at startup each
// day.
class UnitClearMessage {
  public:
    static constexpr const char* name = "UnitClearMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit UnitClearMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every UnitClearMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 4;
    static constexpr std::size_t fixed_size = 4;
    std::size_t encoded_size() const { return 4; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    void print(std::ostream& out) const {
        out << "UnitClearMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const UnitClearMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
