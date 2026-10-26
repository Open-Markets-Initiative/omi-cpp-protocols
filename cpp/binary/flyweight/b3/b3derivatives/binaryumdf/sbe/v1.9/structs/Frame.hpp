#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/FramingHeader.hpp"
#include "../structs/MessageHeader.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// B3 Market Data Message
class Frame {
  public:
    static constexpr const char* name = "Frame";

    // the bytes it reads, which it does not own: they must outlive it
    explicit Frame(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every Frame has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 12;
    static constexpr std::size_t fixed_size = 12;
    std::size_t encoded_size() const { return 12; }

    FramingHeader framing_header() const { return FramingHeader{ bytes_.subspan(0) }; }

    MessageHeader message_header() const { return MessageHeader{ bytes_.subspan(4) }; }

    void print(std::ostream& out) const {
        out << "Frame{";
        out << "framing_header=";
        framing_header().print(out);
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

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
