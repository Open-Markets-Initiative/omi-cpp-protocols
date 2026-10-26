#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

// This message disseminates Volume and Open Interest (VOI) information for each trade date
class VolumeAndOpenInterestMessage {
  public:
    static constexpr const char* name = "VolumeAndOpenInterestMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit VolumeAndOpenInterestMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every VolumeAndOpenInterestMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 28;
    static constexpr std::size_t fixed_size = 28;
    std::size_t encoded_size() const { return 28; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint16_t trade_date() const { return wire::read_u16_be(at(4)); }

    std::uint32_t tradeable_instrument_id() const { return wire::read_u32_be(at(6)); }

    std::uint64_t cumulative_volume() const { return wire::read_u64_be(at(10)); }

    std::uint64_t open_interest() const { return wire::read_u64_be(at(18)); }

    std::uint16_t voi_trade_date() const { return wire::read_u16_be(at(26)); }

    void print(std::ostream& out) const {
        out << "VolumeAndOpenInterestMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", trade_date=";
        out << trade_date();
        out << ", tradeable_instrument_id=";
        out << tradeable_instrument_id();
        out << ", cumulative_volume=";
        out << cumulative_volume();
        out << ", open_interest=";
        out << open_interest();
        out << ", voi_trade_date=";
        out << voi_trade_date();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const VolumeAndOpenInterestMessage& value) {
    value.print(out);
    return out;
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
