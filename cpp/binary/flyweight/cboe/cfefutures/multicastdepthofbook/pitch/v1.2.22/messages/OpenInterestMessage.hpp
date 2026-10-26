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

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// The Open Interest message is sent to communicate a symbol's open interest, usually for the
// prior trading date.
class OpenInterestMessage {
  public:
    static constexpr const char* name = "OpenInterestMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OpenInterestMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OpenInterestMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 18;
    static constexpr std::size_t fixed_size = 18;
    std::size_t encoded_size() const { return 18; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::string_view symbol() const { return view::text(at(4), 6, ' '); }

    std::uint32_t trade_date() const { return wire::read_u32_le(at(10)); }

    std::uint32_t open_interest() const { return wire::read_u32_le(at(14)); }

    void print(std::ostream& out) const {
        out << "OpenInterestMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", trade_date=";
        out << trade_date();
        out << ", open_interest=";
        out << open_interest();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OpenInterestMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
