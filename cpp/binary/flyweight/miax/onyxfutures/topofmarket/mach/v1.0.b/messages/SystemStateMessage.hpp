// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: messages/SystemStateMessage.hpp
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

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

class SystemStateMessage {
  public:
    static constexpr const char* name = "SystemStateMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SystemStateMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SystemStateMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 18;
    static constexpr std::size_t fixed_size = 18;
    std::size_t encoded_size() const { return 18; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    std::string_view tom_version() const { return view::text(at(8), 8, ' '); }

    std::uint8_t session_id() const { return wire::read_u8(at(16)); }

    SystemStatus system_status() const { return static_cast<SystemStatus>(wire::read_char(at(17))); }

    void print(std::ostream& out) const {
        out << "SystemStateMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", tom_version=";
        print::text(out, tom_version());
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

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
