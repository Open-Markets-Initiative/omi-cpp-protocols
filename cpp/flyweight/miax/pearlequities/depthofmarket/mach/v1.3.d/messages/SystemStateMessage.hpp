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
#include "../enums/SystemStatus.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// This is the message format that will be used to notify firms of the state changes of the
// system. This is a notification that applies to all symbols on the feed.
class SystemStateMessage {
  public:
    static constexpr const char* name = "SystemStateMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SystemStateMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SystemStateMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 14;
    static constexpr std::size_t fixed_size = 14;
    std::size_t encoded_size() const { return 14; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::string_view do_m_version() const { return view::text(at(4), 8, ' '); }

    std::uint8_t session_id() const { return wire::read_u8(at(12)); }

    SystemStatus system_status() const { return static_cast<SystemStatus>(wire::read_char(at(13))); }

    void print(std::ostream& out) const {
        out << "SystemStateMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", do_m_version=";
        print::text(out, do_m_version());
        out << ", session_id=";
        out << static_cast<int>(session_id());
        out << ", system_status=";
        out << system_status();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SystemStateMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
