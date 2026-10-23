#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// Published every 60 seconds on a separate multicast channel. Provides high, low, open, close
// and total volume per series.
class OptionsOutrightSeriesSummaryMessage {
  public:
    static constexpr const char* name = "OptionsOutrightSeriesSummaryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OptionsOutrightSeriesSummaryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OptionsOutrightSeriesSummaryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    std::uint32_t source_time() const { return wire::read_u32_le(at(0)); }

    std::uint32_t source_time_ns() const { return wire::read_u32_le(at(4)); }

    std::uint32_t series_index() const { return wire::read_u32_le(at(8)); }

    std::int32_t high_price() const { return wire::read_i32_le(at(12)); }

    std::int32_t low_price() const { return wire::read_i32_le(at(16)); }

    std::int32_t open() const { return wire::read_i32_le(at(20)); }

    std::int32_t close() const { return wire::read_i32_le(at(24)); }

    std::uint32_t total_volume() const { return wire::read_u32_le(at(28)); }

    void print(std::ostream& out) const {
        out << "OptionsOutrightSeriesSummaryMessage{";
        out << "source_time=";
        out << source_time();
        out << ", source_time_ns=";
        out << source_time_ns();
        out << ", series_index=";
        out << series_index();
        out << ", high_price=";
        out << high_price();
        out << ", low_price=";
        out << low_price();
        out << ", open=";
        out << open();
        out << ", close=";
        out << close();
        out << ", total_volume=";
        out << total_volume();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OptionsOutrightSeriesSummaryMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
