#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

// The SoupBinTCP server sends a Login Accepted Packet in response to receiving a valid Login
// Request from the client
class LoginAcceptedPacket {
  public:
    static constexpr const char* name = "LoginAcceptedPacket";

    // the bytes it reads, which it does not own: they must outlive it
    explicit LoginAcceptedPacket(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every LoginAcceptedPacket has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 30;
    static constexpr std::size_t fixed_size = 30;
    std::size_t encoded_size() const { return 30; }

    std::string_view accepted_session() const { return view::text(at(0), 10, ' '); }

    std::string_view accepted_sequence_number() const { return view::text(at(10), 20, ' '); }

    void print(std::ostream& out) const {
        out << "LoginAcceptedPacket{";
        out << "accepted_session=";
        print::text(out, accepted_session());
        out << ", accepted_sequence_number=";
        print::text(out, accepted_sequence_number());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const LoginAcceptedPacket& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2017
