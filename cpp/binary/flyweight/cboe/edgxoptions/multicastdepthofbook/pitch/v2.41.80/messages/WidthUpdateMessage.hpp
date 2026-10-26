#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/WidthType.hpp"
#include "../common/Decimal.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// Options Only. The Width Update message is used to communicate opening quote width
// multiplier. This message will be sent in the event that the exchange decides to change the
// quote width multiplier on a per underlying basis. For complete details on the opening
// collars see the US Options Opening Process Specification.
class WidthUpdateMessage {
  public:
    static constexpr const char* name = "WidthUpdateMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit WidthUpdateMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every WidthUpdateMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 17;
    static constexpr std::size_t fixed_size = 17;
    std::size_t encoded_size() const { return 17; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::string_view underlying() const { return view::text(at(4), 8, ' '); }

    WidthType width_type() const { return static_cast<WidthType>(wire::read_char(at(12))); }

    Decimal multiplier() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_le(at(13))), -1); }

    void print(std::ostream& out) const {
        out << "WidthUpdateMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", underlying=";
        print::text(out, underlying());
        out << ", width_type=";
        out << width_type();
        out << ", multiplier=";
        out << multiplier();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const WidthUpdateMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
