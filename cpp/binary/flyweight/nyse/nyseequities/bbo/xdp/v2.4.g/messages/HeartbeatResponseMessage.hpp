#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace nyse::nyseequities::bbo::xdp::v2_4_g {

// Clients who remain connected to the Retransmission Server intraday must respond to a
// Heartbeat with a Heartbeat Response message within 5 seconds. If no timely client response
// is received, the connection will be closed.
class HeartbeatResponseMessage {
  public:
    static constexpr const char* name = "HeartbeatResponseMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit HeartbeatResponseMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every HeartbeatResponseMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 10;
    static constexpr std::size_t fixed_size = 10;
    std::size_t encoded_size() const { return 10; }

    std::string_view source_id() const { return view::text(at(0), 10, '\0'); }

    void print(std::ostream& out) const {
        out << "HeartbeatResponseMessage{";
        out << "source_id=";
        print::text(out, source_id());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const HeartbeatResponseMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::nyseequities::bbo::xdp::v2_4_g
