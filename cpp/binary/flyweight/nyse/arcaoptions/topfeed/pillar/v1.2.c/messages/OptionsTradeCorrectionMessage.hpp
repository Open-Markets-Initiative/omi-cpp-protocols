#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/CorrectionCondition.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// In the event that an earlier trade has been reported with one or multiple fields in error
class OptionsTradeCorrectionMessage {
  public:
    static constexpr const char* name = "OptionsTradeCorrectionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OptionsTradeCorrectionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OptionsTradeCorrectionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 36;
    static constexpr std::size_t fixed_size = 36;
    std::size_t encoded_size() const { return 36; }

    std::uint32_t source_time() const { return wire::read_u32_le(at(0)); }

    std::uint32_t source_time_ns() const { return wire::read_u32_le(at(4)); }

    std::uint32_t series_index() const { return wire::read_u32_le(at(8)); }

    std::uint32_t series_seq_num() const { return wire::read_u32_le(at(12)); }

    std::uint32_t original_trade_id() const { return wire::read_u32_le(at(16)); }

    std::uint32_t trade_id() const { return wire::read_u32_le(at(20)); }

    std::int32_t price() const { return wire::read_i32_le(at(24)); }

    std::uint32_t volume() const { return wire::read_u32_le(at(28)); }

    CorrectionCondition correction_condition() const { return CorrectionCondition{ bytes_.subspan(32) }; }

    void print(std::ostream& out) const {
        out << "OptionsTradeCorrectionMessage{";
        out << "source_time=";
        out << source_time();
        out << ", source_time_ns=";
        out << source_time_ns();
        out << ", series_index=";
        out << series_index();
        out << ", series_seq_num=";
        out << series_seq_num();
        out << ", original_trade_id=";
        out << original_trade_id();
        out << ", trade_id=";
        out << trade_id();
        out << ", price=";
        out << price();
        out << ", volume=";
        out << volume();
        out << ", correction_condition=";
        correction_condition().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OptionsTradeCorrectionMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
