#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/RejectReasonCode.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

// The SoupBinTCP server sends this packet in response to an invalid Login Request Packet from
// the client
class LoginRejectedPacket {
  public:
    static constexpr const char* name = "LoginRejectedPacket";

    // the bytes it reads, which it does not own: they must outlive it
    explicit LoginRejectedPacket(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every LoginRejectedPacket has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    RejectReasonCode reject_reason_code() const { return static_cast<RejectReasonCode>(wire::read_char(at(0))); }

    void print(std::ostream& out) const {
        out << "LoginRejectedPacket{";
        out << "reject_reason_code=";
        out << reject_reason_code();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const LoginRejectedPacket& value) {
    value.print(out);
    return out;
}

} // namespace jnx::jnxequities::pts::itch::v1_7
