#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/MessageType.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Jpx Flex tag header carrying length prefix and message type discriminator
class MessageHeader {
  public:
    static constexpr const char* name = "MessageHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MessageHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MessageHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 2;
    static constexpr std::size_t fixed_size = 2;
    std::size_t encoded_size() const { return 2; }

    std::uint8_t tag_length() const { return wire::read_u8(at(0)); }

    MessageType message_type() const { return static_cast<MessageType>(wire::read_char(at(1))); }

    void print(std::ostream& out) const {
        out << "MessageHeader{";
        out << "tag_length=";
        out << static_cast<int>(tag_length());
        out << ", message_type=";
        out << message_type();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MessageHeader& value) {
    value.print(out);
    return out;
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
