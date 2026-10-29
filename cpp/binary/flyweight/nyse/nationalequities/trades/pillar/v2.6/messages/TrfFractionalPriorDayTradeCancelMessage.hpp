#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

// If a TRF participant firm discovers that it has reported a trade with an inaccurate price or
// volume on a previous day, the firm may correct the trade on a subsequent day by publishing a
// Prior Day Trade Cancel message, followed by a Prior Day Trade. New message effective
// 1/12/26.
class TrfFractionalPriorDayTradeCancelMessage {
  public:
    static constexpr const char* name = "TrfFractionalPriorDayTradeCancelMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TrfFractionalPriorDayTradeCancelMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TrfFractionalPriorDayTradeCancelMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 40;
    static constexpr std::size_t fixed_size = 40;
    std::size_t encoded_size() const { return 40; }

    std::uint32_t source_time() const { return wire::read_u32_le(at(0)); }

    std::uint32_t source_time_ns() const { return wire::read_u32_le(at(4)); }

    std::uint32_t symbol_index() const { return wire::read_u32_le(at(8)); }

    std::uint32_t symbol_seq_num() const { return wire::read_u32_le(at(12)); }

    std::uint32_t trade_id() const { return wire::read_u32_le(at(16)); }

    std::int32_t price() const { return wire::read_i32_le(at(20)); }

    std::uint64_t fractional_volume() const { return wire::read_u64_le(at(24)); }

    std::uint32_t prior_day_time() const { return wire::read_u32_le(at(32)); }

    std::uint32_t prior_day_time_ns() const { return wire::read_u32_le(at(36)); }

    void print(std::ostream& out) const {
        out << "TrfFractionalPriorDayTradeCancelMessage{";
        out << "source_time=";
        out << source_time();
        out << ", source_time_ns=";
        out << source_time_ns();
        out << ", symbol_index=";
        out << symbol_index();
        out << ", symbol_seq_num=";
        out << symbol_seq_num();
        out << ", trade_id=";
        out << trade_id();
        out << ", price=";
        out << price();
        out << ", fractional_volume=";
        out << fractional_volume();
        out << ", prior_day_time=";
        out << prior_day_time();
        out << ", prior_day_time_ns=";
        out << prior_day_time_ns();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TrfFractionalPriorDayTradeCancelMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::nationalequities::trades::pillar::v2_6
