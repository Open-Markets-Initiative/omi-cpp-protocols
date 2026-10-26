#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/ServerTechnicalHeader.hpp"
#include "../structs/MessageHeader.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

// One technical header and the message it carries: the unit the wire repeats
class ServerTcpFrame {
  public:
    static constexpr const char* name = "ServerTcpFrame";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ServerTcpFrame(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ServerTcpFrame has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 24;
    static constexpr std::size_t fixed_size = 24;
    std::size_t encoded_size() const { return 24; }

    ServerTechnicalHeader server_technical_header() const { return ServerTechnicalHeader{ bytes_.subspan(0) }; }

    MessageHeader message_header() const { return MessageHeader{ bytes_.subspan(14) }; }

    void print(std::ostream& out) const {
        out << "ServerTcpFrame{";
        out << "server_technical_header=";
        server_technical_header().print(out);
        out << ", message_header=";
        message_header().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ServerTcpFrame& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_8
