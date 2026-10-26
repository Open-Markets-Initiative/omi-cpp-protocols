#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/CrossType.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// Published on completion of a crossing from the opening and re-opening auction, showing the
// bulk volume that traded in the auction.
class OptionsCrossTradeMessage {
  public:
    static constexpr const char* name = "OptionsCrossTradeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OptionsCrossTradeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OptionsCrossTradeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 25;
    static constexpr std::size_t fixed_size = 25;
    std::size_t encoded_size() const { return 25; }

    std::uint32_t source_time_ns() const { return wire::read_u32_le(at(0)); }

    std::uint32_t series_index() const { return wire::read_u32_le(at(4)); }

    std::uint32_t series_seq_num() const { return wire::read_u32_le(at(8)); }

    std::uint32_t cross_id() const { return wire::read_u32_le(at(12)); }

    std::int32_t price() const { return wire::read_i32_le(at(16)); }

    std::uint32_t volume() const { return wire::read_u32_le(at(20)); }

    CrossType cross_type() const { return static_cast<CrossType>(wire::read_char(at(24))); }

    void print(std::ostream& out) const {
        out << "OptionsCrossTradeMessage{";
        out << "source_time_ns=";
        out << source_time_ns();
        out << ", series_index=";
        out << series_index();
        out << ", series_seq_num=";
        out << series_seq_num();
        out << ", cross_id=";
        out << cross_id();
        out << ", price=";
        out << price();
        out << ", volume=";
        out << volume();
        out << ", cross_type=";
        out << cross_type();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OptionsCrossTradeMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
