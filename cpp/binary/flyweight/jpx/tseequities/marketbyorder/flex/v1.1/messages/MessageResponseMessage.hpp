#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Tcp message response carrying tag data including their packet headers in response to a
// retransmission or snapshot request.
class MessageResponseMessage {
  public:
    static constexpr const char* name = "MessageResponseMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MessageResponseMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MessageResponseMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 0;
    static constexpr std::size_t fixed_size = 0;
    std::size_t encoded_size() const { return 0; }

    std::span<const std::byte, 0> data() const { return bytes_.subspan(0).template first<0>(); }

    void print(std::ostream& out) const {
        out << "MessageResponseMessage{";
        out << "data=";
        print::hex(out, data().data(), data().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MessageResponseMessage& value) {
    value.print(out);
    return out;
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
