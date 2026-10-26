#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// Options Only. The Transaction Begin message indicates any subsequent messages, up to the
// accompanying Transaction End message, are all part of the same transaction block. All PITCH
// messages corresponding to such an event would be included between a Transaction Begin
// message and Transaction End message. It is important to note that transaction blocks are
// currently used in US Options for symbol state transitions only, but may be expanded to other
// use cases with notice. Transaction Begin messages do not alter the book and can be ignored
// if messages are being used solely to build a book.
class TransactionBeginMessage {
  public:
    static constexpr const char* name = "TransactionBeginMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TransactionBeginMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TransactionBeginMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 4;
    static constexpr std::size_t fixed_size = 4;
    std::size_t encoded_size() const { return 4; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    void print(std::ostream& out) const {
        out << "TransactionBeginMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TransactionBeginMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
