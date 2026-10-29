#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

// In all multicast channels, a Stream ID Message is sent immediately after each packet header
// to uniquely identify the source or Stream ID of the data in the packet.
class StreamIdMessage {
  public:
    static constexpr const char* name = "StreamIdMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit StreamIdMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every StreamIdMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 4;
    static constexpr std::size_t fixed_size = 4;
    std::size_t encoded_size() const { return 4; }

    std::uint16_t stream_id() const { return wire::read_u16_le(at(0)); }

    std::span<const std::byte, 2> reserved_2() const { return bytes_.subspan(2).template first<2>(); }

    void print(std::ostream& out) const {
        out << "StreamIdMessage{";
        out << "stream_id=";
        out << stream_id();
        out << ", reserved_2=";
        print::hex(out, reserved_2().data(), reserved_2().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const StreamIdMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
