#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace nyse::arcaequities::bbo::xdp::v2_4_c {

// Clients who have experienced a failure and need a refresh of the state of one or all symbols
// in a specific channel should send a Retransmission Request message via TCP to the Request
// Controller. A Request Response message will be sent over the TCP connection back to the
// client, and if the request was valid, the requested message(s) will be published over the
// relevant Refresh multicast channel.
class RefreshRequestMessage {
  public:
    static constexpr const char* name = "RefreshRequestMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RefreshRequestMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RefreshRequestMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 16;
    static constexpr std::size_t fixed_size = 16;
    std::size_t encoded_size() const { return 16; }

    std::uint32_t symbol_index() const { return wire::read_u32_le(at(0)); }

    std::string_view source_id() const { return view::text(at(4), 10, '\0'); }

    std::uint8_t product_id() const { return wire::read_u8(at(14)); }

    std::uint8_t channel_id() const { return wire::read_u8(at(15)); }

    void print(std::ostream& out) const {
        out << "RefreshRequestMessage{";
        out << "symbol_index=";
        out << symbol_index();
        out << ", source_id=";
        print::text(out, source_id());
        out << ", product_id=";
        out << static_cast<int>(product_id());
        out << ", channel_id=";
        out << static_cast<int>(channel_id());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RefreshRequestMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::arcaequities::bbo::xdp::v2_4_c
