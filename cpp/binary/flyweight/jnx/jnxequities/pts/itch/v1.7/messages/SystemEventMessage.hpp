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
#include "../enums/Group.hpp"
#include "../enums/SystemEvent.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

// System Event Messages signal data feed, system and market events.
class SystemEventMessage {
  public:
    static constexpr const char* name = "SystemEventMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SystemEventMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SystemEventMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 9;
    static constexpr std::size_t fixed_size = 9;
    std::size_t encoded_size() const { return 9; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::string_view group() const { return view::text(at(4), 4, ' '); }

    SystemEvent system_event() const { return static_cast<SystemEvent>(wire::read_char(at(8))); }

    void print(std::ostream& out) const {
        out << "SystemEventMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", group=";
        print::text(out, group());
        out << ", system_event=";
        out << system_event();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SystemEventMessage& value) {
    value.print(out);
    return out;
}

} // namespace jnx::jnxequities::pts::itch::v1_7
