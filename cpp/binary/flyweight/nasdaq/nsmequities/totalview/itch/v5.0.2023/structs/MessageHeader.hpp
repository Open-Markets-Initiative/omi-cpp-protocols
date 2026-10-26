#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/MessageType.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Mold Udp 64 Message Header
class MessageHeader {
  public:
    static constexpr const char* name = "MessageHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MessageHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MessageHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 3;
    static constexpr std::size_t fixed_size = 3;
    std::size_t encoded_size() const { return 3; }

    std::uint16_t message_length() const { return wire::read_u16_be(at(0)); }

    MessageType message_type() const { return static_cast<MessageType>(wire::read_char(at(2))); }

    void print(std::ostream& out) const {
        out << "MessageHeader{";
        out << "message_length=";
        out << message_length();
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

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
