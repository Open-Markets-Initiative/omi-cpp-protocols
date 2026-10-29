#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

// End of Session message
class EndOfSessionMessage {
  public:
    static constexpr const char* name = "EndOfSessionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit EndOfSessionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every EndOfSessionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 4;
    static constexpr std::size_t fixed_size = 4;
    std::size_t encoded_size() const { return 4; }

    std::uint32_t timestamp() const { return wire::read_u32_le(at(0)); }

    void print(std::ostream& out) const {
        out << "EndOfSessionMessage{";
        out << "timestamp=";
        out << timestamp();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const EndOfSessionMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
