#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// EstablishAckMessage
class EstablishAckMessage {
  public:
    static constexpr const char* name = "EstablishAckMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit EstablishAckMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every EstablishAckMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 36;
    static constexpr std::size_t fixed_size = 36;
    std::size_t encoded_size() const { return 36; }

    std::uint32_t session_id() const { return wire::read_u32_le(at(0)); }

    std::uint64_t session_ver_id() const { return wire::read_u64_le(at(4)); }

    std::chrono::nanoseconds request_timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(12)))); }

    std::uint64_t keep_alive_interval() const { return wire::read_u64_le(at(20)); }

    std::uint32_t next_seq_no() const { return wire::read_u32_le(at(28)); }

    std::uint32_t last_incoming_seq_no() const { return wire::read_u32_le(at(32)); }

    void print(std::ostream& out) const {
        out << "EstablishAckMessage{";
        out << "session_id=";
        out << session_id();
        out << ", session_ver_id=";
        out << session_ver_id();
        out << ", request_timestamp=";
        out << request_timestamp().count();
        out << ", keep_alive_interval=";
        out << keep_alive_interval();
        out << ", next_seq_no=";
        out << next_seq_no();
        out << ", last_incoming_seq_no=";
        out << last_incoming_seq_no();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const EstablishAckMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
