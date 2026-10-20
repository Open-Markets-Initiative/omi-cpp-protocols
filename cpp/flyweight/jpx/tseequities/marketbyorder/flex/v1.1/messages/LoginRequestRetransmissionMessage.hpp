#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Tcp login request selecting retransmission, sent by the user. One of the two Packet Type
// codes the document gives the 18 byte Login Request.
class LoginRequestRetransmissionMessage {
  public:
    static constexpr const char* name = "LoginRequestRetransmissionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit LoginRequestRetransmissionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every LoginRequestRetransmissionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 15;
    static constexpr std::size_t fixed_size = 15;
    std::size_t encoded_size() const { return 15; }

    std::string_view user_id() const { return view::text(at(0), 6, ' '); }

    std::uint8_t multicast_group_number() const { return wire::read_u8(at(6)); }

    std::uint8_t number_of_system_reboots() const { return wire::read_u8(at(7)); }

    std::uint32_t sequence_number() const { return wire::read_u32_be(at(8)); }

    std::uint32_t requested_message_count() const { return wire::read_u24_be(at(12)); }

    void print(std::ostream& out) const {
        out << "LoginRequestRetransmissionMessage{";
        out << "user_id=";
        print::text(out, user_id());
        out << ", multicast_group_number=";
        out << static_cast<int>(multicast_group_number());
        out << ", number_of_system_reboots=";
        out << static_cast<int>(number_of_system_reboots());
        out << ", sequence_number=";
        out << sequence_number();
        out << ", requested_message_count=";
        out << requested_message_count();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const LoginRequestRetransmissionMessage& value) {
    value.print(out);
    return out;
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
