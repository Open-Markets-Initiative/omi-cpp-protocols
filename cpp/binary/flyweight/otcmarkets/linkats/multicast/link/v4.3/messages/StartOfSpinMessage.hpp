#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SpinType.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// This message appears on all quote channels and indicates the beginning of a spin message
// cycle.
class StartOfSpinMessage {
  public:
    static constexpr const char* name = "StartOfSpinMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit StartOfSpinMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every StartOfSpinMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 17;
    static constexpr std::size_t fixed_size = 17;
    std::size_t encoded_size() const { return 17; }

    std::uint32_t channel_seq_num() const { return wire::read_u32_be(at(0)); }

    SpinType spin_type() const { return static_cast<SpinType>(wire::read_u8(at(4))); }

    std::uint64_t spin_start_time_milli() const { return wire::read_u64_be(at(5)); }

    std::uint32_t spin_last_seq_num() const { return wire::read_u32_be(at(13)); }

    void print(std::ostream& out) const {
        out << "StartOfSpinMessage{";
        out << "channel_seq_num=";
        out << channel_seq_num();
        out << ", spin_type=";
        out << spin_type();
        out << ", spin_start_time_milli=";
        out << spin_start_time_milli();
        out << ", spin_last_seq_num=";
        out << spin_last_seq_num();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const StartOfSpinMessage& value) {
    value.print(out);
    return out;
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
