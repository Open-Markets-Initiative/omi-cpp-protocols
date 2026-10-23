#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/ClientTechnicalHeader.hpp"
#include "../structs/MessageHeader.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

// One technical header and the message it carries: the unit the wire repeats
class ClientTcpFrame {
  public:
    static constexpr const char* name = "ClientTcpFrame";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ClientTcpFrame(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ClientTcpFrame has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 24;
    static constexpr std::size_t fixed_size = 24;
    std::size_t encoded_size() const { return 24; }

    ClientTechnicalHeader client_technical_header() const { return ClientTechnicalHeader{ bytes_.subspan(0) }; }

    MessageHeader message_header() const { return MessageHeader{ bytes_.subspan(16) }; }

    void print(std::ostream& out) const {
        out << "ClientTcpFrame{";
        out << "client_technical_header=";
        client_technical_header().print(out);
        out << ", message_header=";
        message_header().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ClientTcpFrame& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_8
