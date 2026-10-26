#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/RefreshMessageType.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Sent by the firm over the DoM Retransmission Interface (ESeSM Unsequenced Data Packet) to
// request a Last Value Refresh of a particular data set identified by Refresh Message Type.
class RefreshRequestMessage {
  public:
    static constexpr const char* name = "RefreshRequestMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RefreshRequestMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RefreshRequestMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    RefreshMessageType refresh_message_type() const { return static_cast<RefreshMessageType>(wire::read_char(at(0))); }

    void print(std::ostream& out) const {
        out << "RefreshRequestMessage{";
        out << "refresh_message_type=";
        out << refresh_message_type();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RefreshRequestMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
