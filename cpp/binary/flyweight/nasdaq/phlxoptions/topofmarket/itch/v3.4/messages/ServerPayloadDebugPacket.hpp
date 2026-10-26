#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// Debug packets are intended to provide human readable text that may aid in debugging problems
class ServerPayloadDebugPacket {
  public:
    static constexpr const char* name = "ServerPayloadDebugPacket";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ServerPayloadDebugPacket(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ServerPayloadDebugPacket has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 0;
    std::size_t encoded_size() const { return debug_text_end(); }

    std::size_t debug_text_size() const { return bytes_.size() - (0); }
    std::string_view debug_text() const {
        wire::require("ServerPayloadDebugPacket", 0 + debug_text_size(), bytes_.size());
        return view::characters(at(0), debug_text_size());
    }

    void print(std::ostream& out) const {
        out << "ServerPayloadDebugPacket{";
        out << "debug_text=";
        print::text(out, debug_text());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t debug_text_end() const { return 0 + debug_text_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ServerPayloadDebugPacket& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
