#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

// The Broken Trade Message is sent whenever an execution on NASDAQ is broken.
class PayloadBrokenTradeMessage {
  public:
    static constexpr const char* name = "PayloadBrokenTradeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PayloadBrokenTradeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PayloadBrokenTradeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 12;
    static constexpr std::size_t fixed_size = 12;
    std::size_t encoded_size() const { return 12; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint64_t match_number() const { return wire::read_u64_be(at(4)); }

    void print(std::ostream& out) const {
        out << "PayloadBrokenTradeMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", match_number=";
        out << match_number();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PayloadBrokenTradeMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
