#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/MessageCategory.hpp"

namespace siac::cts::output::cta::v1_91 {

// Repeating message block
class Frame {
  public:
    static constexpr const char* name = "Frame";

    // the bytes it reads, which it does not own: they must outlive it
    explicit Frame(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every Frame has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 3;
    static constexpr std::size_t fixed_size = 3;
    std::size_t encoded_size() const { return 3; }

    std::uint16_t message_length() const { return wire::read_u16_be(at(0)); }

    MessageCategory message_category() const { return static_cast<MessageCategory>(wire::read_char(at(2))); }

    void print(std::ostream& out) const {
        out << "Frame{";
        out << "message_length=";
        out << message_length();
        out << ", message_category=";
        out << message_category();
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

} // namespace siac::cts::output::cta::v1_91
