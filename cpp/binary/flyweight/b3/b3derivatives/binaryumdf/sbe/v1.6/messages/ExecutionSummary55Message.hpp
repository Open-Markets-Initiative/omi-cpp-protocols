#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/AggressorSide.hpp"
#include "../common/Decimal.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// ExecutionSummary_55Message
class ExecutionSummary55Message {
  public:
    static constexpr const char* name = "ExecutionSummary55Message";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ExecutionSummary55Message(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ExecutionSummary55Message has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 64;
    static constexpr std::size_t fixed_size = 64;
    std::size_t encoded_size() const { return 64; }

    std::uint64_t security_id() const { return wire::read_u64_le(at(0)); }

    std::span<const std::byte, 2> offset_8_padding_2() const { return bytes_.subspan(8).template first<2>(); }

    AggressorSide aggressor_side() const { return static_cast<AggressorSide>(wire::read_u8(at(10))); }

    std::span<const std::byte, 1> offset_11_padding_1() const { return bytes_.subspan(11).template first<1>(); }

    Decimal last_px() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(12))), -4); }

    std::int64_t fill_qty() const { return wire::read_i64_le(at(20)); }

    std::optional<std::int64_t> traded_hidden_qty() const { return wire::nullable(wire::read_i64_le(at(28)), static_cast<std::int64_t>(-9223372036854775807LL - 1)); }

    std::optional<std::int64_t> cxl_qty() const { return wire::nullable(wire::read_i64_le(at(36)), static_cast<std::int64_t>(-9223372036854775807LL - 1)); }

    std::optional<std::chrono::nanoseconds> aggressor_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(44)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint32_t> rpt_seq() const { return wire::nullable(wire::read_u32_le(at(52)), static_cast<std::uint32_t>(0ULL)); }

    std::optional<std::chrono::nanoseconds> md_entry_timestamp() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(56)), static_cast<std::uint64_t>(0ULL)); }

    void print(std::ostream& out) const {
        out << "ExecutionSummary55Message{";
        out << "security_id=";
        out << security_id();
        out << ", offset_8_padding_2=";
        print::hex(out, offset_8_padding_2().data(), offset_8_padding_2().size());
        out << ", aggressor_side=";
        out << aggressor_side();
        out << ", offset_11_padding_1=";
        print::hex(out, offset_11_padding_1().data(), offset_11_padding_1().size());
        out << ", last_px=";
        out << last_px();
        out << ", fill_qty=";
        out << fill_qty();
        out << ", traded_hidden_qty=";
        print::optional(out, traded_hidden_qty());
        out << ", cxl_qty=";
        print::optional(out, cxl_qty());
        out << ", aggressor_time=";
        print::optional_duration(out, aggressor_time());
        out << ", rpt_seq=";
        print::optional(out, rpt_seq());
        out << ", md_entry_timestamp=";
        print::optional_duration(out, md_entry_timestamp());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ExecutionSummary55Message& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
