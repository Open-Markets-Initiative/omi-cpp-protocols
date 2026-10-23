#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/MessageHeader.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

// Cme Market Data Message
class Frame {
  public:
    static constexpr const char* name = "Frame";

    // the bytes it reads, which it does not own: they must outlive it
    explicit Frame(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every Frame has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 10;
    static constexpr std::size_t fixed_size = 10;
    std::size_t encoded_size() const { return 10; }

    std::uint16_t message_size() const { return wire::read_u16_le(at(0)); }

    MessageHeader message_header() const { return MessageHeader{ bytes_.subspan(2) }; }

    void print(std::ostream& out) const {
        out << "Frame{";
        out << "message_size=";
        out << message_size();
        out << ", message_header=";
        message_header().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const Frame& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
