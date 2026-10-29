#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace nyse::nyseequities::bbo::xdp::v2_4_g {

// This message will be sent over the Retransmission multicast channels to inform clients of
// unavailability of a range of messages (or part of a range) for which they may have requested
// a retransmission.
class MessageUnavailableMessage {
  public:
    static constexpr const char* name = "MessageUnavailableMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MessageUnavailableMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MessageUnavailableMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 10;
    static constexpr std::size_t fixed_size = 10;
    std::size_t encoded_size() const { return 10; }

    std::uint32_t begin_seq_num() const { return wire::read_u32_le(at(0)); }

    std::uint32_t end_seq_num() const { return wire::read_u32_le(at(4)); }

    std::uint8_t product_id() const { return wire::read_u8(at(8)); }

    std::uint8_t channel_id() const { return wire::read_u8(at(9)); }

    void print(std::ostream& out) const {
        out << "MessageUnavailableMessage{";
        out << "begin_seq_num=";
        out << begin_seq_num();
        out << ", end_seq_num=";
        out << end_seq_num();
        out << ", product_id=";
        out << static_cast<int>(product_id());
        out << ", channel_id=";
        out << static_cast<int>(channel_id());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MessageUnavailableMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::nyseequities::bbo::xdp::v2_4_g
