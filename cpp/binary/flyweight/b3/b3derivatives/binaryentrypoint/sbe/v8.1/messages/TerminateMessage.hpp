#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/TerminationCode.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// TerminateMessage
class TerminateMessage {
  public:
    static constexpr const char* name = "TerminateMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TerminateMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TerminateMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 13;
    static constexpr std::size_t fixed_size = 13;
    std::size_t encoded_size() const { return 13; }

    std::uint32_t session_id() const { return wire::read_u32_le(at(0)); }

    std::uint64_t session_ver_id() const { return wire::read_u64_le(at(4)); }

    TerminationCode termination_code() const { return static_cast<TerminationCode>(wire::read_u8(at(12))); }

    void print(std::ostream& out) const {
        out << "TerminateMessage{";
        out << "session_id=";
        out << session_id();
        out << ", session_ver_id=";
        out << session_ver_id();
        out << ", termination_code=";
        out << termination_code();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TerminateMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
