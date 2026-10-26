#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/SimpleBinaryHeader.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// Message Size followed by the Simple Binary Header
class MessageHeader {
  public:
    static constexpr const char* name = "MessageHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MessageHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MessageHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 10;
    static constexpr std::size_t fixed_size = 10;
    std::size_t encoded_size() const { return 10; }

    std::uint16_t message_size() const { return wire::read_u16_le(at(0)); }

    SimpleBinaryHeader simple_binary_header() const { return SimpleBinaryHeader{ bytes_.subspan(2) }; }

    void print(std::ostream& out) const {
        out << "MessageHeader{";
        out << "message_size=";
        out << message_size();
        out << ", simple_binary_header=";
        simple_binary_header().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MessageHeader& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
