#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2026 {

// The SoupBinTCP client must send a Login Request Packet immediately upon establishing a new
// TCP/IP socket connection to the server
class LoginRequestPacket {
  public:
    static constexpr const char* name = "LoginRequestPacket";

    // the bytes it reads, which it does not own: they must outlive it
    explicit LoginRequestPacket(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every LoginRequestPacket has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 46;
    static constexpr std::size_t fixed_size = 46;
    std::size_t encoded_size() const { return 46; }

    std::string_view username() const { return view::text(at(0), 6, ' '); }

    std::string_view password() const { return view::text(at(6), 10, ' '); }

    std::string_view requested_session() const { return view::text(at(16), 10, ' '); }

    std::string_view requested_sequence_number() const { return view::text(at(26), 20, ' '); }

    void print(std::ostream& out) const {
        out << "LoginRequestPacket{";
        out << "username=";
        print::text(out, username());
        out << ", password=";
        print::text(out, password());
        out << ", requested_session=";
        print::text(out, requested_session());
        out << ", requested_sequence_number=";
        print::text(out, requested_sequence_number());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const LoginRequestPacket& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2026
