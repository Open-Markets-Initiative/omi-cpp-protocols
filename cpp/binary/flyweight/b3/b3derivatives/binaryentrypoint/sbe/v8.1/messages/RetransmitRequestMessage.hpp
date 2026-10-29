#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// RetransmitRequestMessage
class RetransmitRequestMessage {
  public:
    static constexpr const char* name = "RetransmitRequestMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RetransmitRequestMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RetransmitRequestMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 20;
    static constexpr std::size_t fixed_size = 20;
    std::size_t encoded_size() const { return 20; }

    std::uint32_t session_id() const { return wire::read_u32_le(at(0)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(4)))); }

    std::uint32_t from_seq_no() const { return wire::read_u32_le(at(12)); }

    std::uint32_t count() const { return wire::read_u32_le(at(16)); }

    void print(std::ostream& out) const {
        out << "RetransmitRequestMessage{";
        out << "session_id=";
        out << session_id();
        out << ", timestamp=";
        out << timestamp().count();
        out << ", from_seq_no=";
        out << from_seq_no();
        out << ", count=";
        out << count();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RetransmitRequestMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
