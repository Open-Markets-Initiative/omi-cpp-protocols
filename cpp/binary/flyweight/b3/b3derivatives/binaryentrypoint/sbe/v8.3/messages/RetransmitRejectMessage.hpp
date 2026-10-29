#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/RetransmitRejectCode.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// RetransmitRejectMessage
class RetransmitRejectMessage {
  public:
    static constexpr const char* name = "RetransmitRejectMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RetransmitRejectMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RetransmitRejectMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 13;
    static constexpr std::size_t fixed_size = 13;
    std::size_t encoded_size() const { return 13; }

    std::uint32_t session_id() const { return wire::read_u32_le(at(0)); }

    std::chrono::nanoseconds request_timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(4)))); }

    RetransmitRejectCode retransmit_reject_code() const { return static_cast<RetransmitRejectCode>(wire::read_u8(at(12))); }

    void print(std::ostream& out) const {
        out << "RetransmitRejectMessage{";
        out << "session_id=";
        out << session_id();
        out << ", request_timestamp=";
        out << request_timestamp().count();
        out << ", retransmit_reject_code=";
        out << retransmit_reject_code();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RetransmitRejectMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
