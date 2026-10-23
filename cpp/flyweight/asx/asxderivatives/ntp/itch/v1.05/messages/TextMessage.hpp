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

namespace asx::asxderivatives::ntp::itch::v1_05 {

// This message disseminates free text information describing ad-hoc market events
class TextMessage {
  public:
    static constexpr const char* name = "TextMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TextMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TextMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 112;
    static constexpr std::size_t fixed_size = 112;
    std::size_t encoded_size() const { return 112; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint16_t trade_date() const { return wire::read_u16_be(at(4)); }

    std::string_view source_id() const { return view::text(at(6), 6, ' '); }

    std::string_view text() const { return view::text(at(12), 100, ' '); }

    void print(std::ostream& out) const {
        out << "TextMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", trade_date=";
        out << trade_date();
        out << ", source_id=";
        print::text(out, source_id());
        out << ", text=";
        print::text(out, text());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TextMessage& value) {
    value.print(out);
    return out;
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
