#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

// MatchEventIndicator bit set
class MatchEventIndicator {
  public:
    static constexpr const char* name = "MatchEventIndicator";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MatchEventIndicator(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    std::uint8_t raw() const { return wire::read_u8(bytes_.data()); }

    bool last_trade_msg() const { return (raw() & static_cast<std::uint8_t>(0x1)) != 0; }

    bool last_volume_msg() const { return (raw() & static_cast<std::uint8_t>(0x2)) != 0; }

    bool last_quote_msg() const { return (raw() & static_cast<std::uint8_t>(0x4)) != 0; }

    bool last_stats_msg() const { return (raw() & static_cast<std::uint8_t>(0x8)) != 0; }

    bool last_implied_msg() const { return (raw() & static_cast<std::uint8_t>(0x10)) != 0; }

    bool recovery_msg() const { return (raw() & static_cast<std::uint8_t>(0x20)) != 0; }

    bool reserved() const { return (raw() & static_cast<std::uint8_t>(0x40)) != 0; }

    bool end_of_event() const { return (raw() & static_cast<std::uint8_t>(0x80)) != 0; }

    void print(std::ostream& out) const {
        out << "MatchEventIndicator{";
        out << "last_trade_msg=";
        out << (last_trade_msg() ? "true" : "false");
        out << ", last_volume_msg=";
        out << (last_volume_msg() ? "true" : "false");
        out << ", last_quote_msg=";
        out << (last_quote_msg() ? "true" : "false");
        out << ", last_stats_msg=";
        out << (last_stats_msg() ? "true" : "false");
        out << ", last_implied_msg=";
        out << (last_implied_msg() ? "true" : "false");
        out << ", recovery_msg=";
        out << (recovery_msg() ? "true" : "false");
        out << ", reserved=";
        out << (reserved() ? "true" : "false");
        out << ", end_of_event=";
        out << (end_of_event() ? "true" : "false");
        out << '}';
    }

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MatchEventIndicator& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
