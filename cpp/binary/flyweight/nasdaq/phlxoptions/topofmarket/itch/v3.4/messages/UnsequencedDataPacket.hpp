#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// The Unsequenced Data Packets act as an envelope to carry the actual data messages that are
// transferred from the client to the server
class UnsequencedDataPacket {
  public:
    static constexpr const char* name = "UnsequencedDataPacket";

    // the bytes it reads, which it does not own: they must outlive it
    explicit UnsequencedDataPacket(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every UnsequencedDataPacket has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return unsequenced_message_end(); }

    char unsequenced_message_type() const { return wire::read_char(at(0)); }

    std::size_t unsequenced_message_size() const { return bytes_.size() - (1); }
    std::span<const std::byte> unsequenced_message() const {
        wire::require("UnsequencedDataPacket", 1 + unsequenced_message_size(), bytes_.size());
        return bytes_.subspan(1, unsequenced_message_size());
    }

    void print(std::ostream& out) const {
        out << "UnsequencedDataPacket{";
        out << "unsequenced_message_type=";
        print::character(out, unsequenced_message_type());
        out << ", unsequenced_message=";
        print::hex(out, unsequenced_message().data(), unsequenced_message().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t unsequenced_message_end() const { return 1 + unsequenced_message_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const UnsequencedDataPacket& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
