#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/OpenState.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// The options system uses this administrative message to indicate when an option has completed
// the opening process and is now available for auto execution or when the option has closed
// and is no longer available for auto execution.
class PayloadSecurityOpenClosedMessage {
  public:
    static constexpr const char* name = "PayloadSecurityOpenClosedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PayloadSecurityOpenClosedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PayloadSecurityOpenClosedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 9;
    static constexpr std::size_t fixed_size = 9;
    std::size_t encoded_size() const { return 9; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint32_t option_id() const { return wire::read_u32_be(at(4)); }

    OpenState open_state() const { return static_cast<OpenState>(wire::read_char(at(8))); }

    void print(std::ostream& out) const {
        out << "PayloadSecurityOpenClosedMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", option_id=";
        out << option_id();
        out << ", open_state=";
        out << open_state();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PayloadSecurityOpenClosedMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
