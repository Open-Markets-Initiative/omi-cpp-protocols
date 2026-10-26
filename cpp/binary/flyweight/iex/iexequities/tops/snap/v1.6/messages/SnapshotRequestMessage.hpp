#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace iex::iexequities::tops::snap::v1_6 {

// The Snapshot Request message is sent from the client to the Tops Snap server to authenticate
// and request a Snapshot Response
class SnapshotRequestMessage {
  public:
    static constexpr const char* name = "SnapshotRequestMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SnapshotRequestMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SnapshotRequestMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 56;
    static constexpr std::size_t fixed_size = 56;
    std::size_t encoded_size() const { return 56; }

    std::string_view authentication_token() const { return view::text(at(0), 40, ' '); }

    std::uint32_t channel_id() const { return wire::read_u32_le(at(40)); }

    std::uint32_t session_id() const { return wire::read_u32_le(at(44)); }

    std::uint64_t minimum_sequence_number() const { return wire::read_u64_le(at(48)); }

    void print(std::ostream& out) const {
        out << "SnapshotRequestMessage{";
        out << "authentication_token=";
        print::text(out, authentication_token());
        out << ", channel_id=";
        out << channel_id();
        out << ", session_id=";
        out << session_id();
        out << ", minimum_sequence_number=";
        out << minimum_sequence_number();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SnapshotRequestMessage& value) {
    value.print(out);
    return out;
}

} // namespace iex::iexequities::tops::snap::v1_6
