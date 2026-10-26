#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/RefreshMessageType.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Sent by MIAX Options over the ToM Retransmission Interface (SesM Unsequenced Data Packet)
// when the refresh response is complete.
class EndOfRefreshNotificationMessage {
  public:
    static constexpr const char* name = "EndOfRefreshNotificationMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit EndOfRefreshNotificationMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every EndOfRefreshNotificationMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    RefreshMessageType refresh_message_type() const { return static_cast<RefreshMessageType>(wire::read_char(at(0))); }

    void print(std::ostream& out) const {
        out << "EndOfRefreshNotificationMessage{";
        out << "refresh_message_type=";
        out << refresh_message_type();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const EndOfRefreshNotificationMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
