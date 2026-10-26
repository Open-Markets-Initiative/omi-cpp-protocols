#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/RefreshResponseMessageApplicationMessage.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Sent by MIAX Options over the ToM Retransmission Interface (SesM Unsequenced Data Packet)
// carrying one Application Message that satisfies a previous Refresh Request. Note: MIAX
// Options PDF assigns Response Type "R" (uppercase) to this message, colliding with the
// Request Type "R" byte; lowercase "r" is used here to match the Pearl convention for
// case-distinct discrimination.
class RefreshResponseMessage {
  public:
    static constexpr const char* name = "RefreshResponseMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RefreshResponseMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RefreshResponseMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 8;
    std::size_t encoded_size() const { return application_message_end(); }

    std::uint64_t sequence_number() const { return wire::read_u64_le(at(0)); }

    RefreshResponseMessageApplicationMessage application_message() const { return RefreshResponseMessageApplicationMessage{ bytes_.subspan(8) }; }

    void print(std::ostream& out) const {
        out << "RefreshResponseMessage{";
        out << "sequence_number=";
        out << sequence_number();
        out << ", application_message=";
        application_message().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t application_message_end() const { return 8 + application_message().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RefreshResponseMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
