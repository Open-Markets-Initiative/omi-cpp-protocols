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
#include "../bitfields/MatchEventIndicator.hpp"
#include "../enums/MdEntryType.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// DeleteOrder_MBO_51Message
class DeleteOrderMbO51Message {
  public:
    static constexpr const char* name = "DeleteOrderMbO51Message";

    // the bytes it reads, which it does not own: they must outlive it
    explicit DeleteOrderMbO51Message(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every DeleteOrderMbO51Message has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 44;
    static constexpr std::size_t fixed_size = 44;
    std::size_t encoded_size() const { return 44; }

    std::uint64_t security_id() const { return wire::read_u64_le(at(0)); }

    MatchEventIndicator match_event_indicator() const { return MatchEventIndicator{ bytes_.subspan(8) }; }

    std::span<const std::byte, 1> offset_9_padding_1() const { return bytes_.subspan(9).template first<1>(); }

    MdEntryType md_entry_type() const { return static_cast<MdEntryType>(wire::read_char(at(10))); }

    std::span<const std::byte, 1> offset_11_padding_1() const { return bytes_.subspan(11).template first<1>(); }

    std::uint32_t md_entry_position_no() const { return wire::read_u32_le(at(12)); }

    std::optional<std::int64_t> md_entry_size_quantity_optional() const { return wire::nullable(wire::read_i64_le(at(16)), static_cast<std::int64_t>(-9223372036854775807LL - 1)); }

    std::uint64_t secondary_order_id() const { return wire::read_u64_le(at(24)); }

    std::optional<std::chrono::nanoseconds> md_entry_timestamp() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(32)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint32_t> rpt_seq() const { return wire::nullable(wire::read_u32_le(at(40)), static_cast<std::uint32_t>(0ULL)); }

    void print(std::ostream& out) const {
        out << "DeleteOrderMbO51Message{";
        out << "security_id=";
        out << security_id();
        out << ", match_event_indicator=";
        match_event_indicator().print(out);
        out << ", offset_9_padding_1=";
        print::hex(out, offset_9_padding_1().data(), offset_9_padding_1().size());
        out << ", md_entry_type=";
        out << md_entry_type();
        out << ", offset_11_padding_1=";
        print::hex(out, offset_11_padding_1().data(), offset_11_padding_1().size());
        out << ", md_entry_position_no=";
        out << md_entry_position_no();
        out << ", md_entry_size_quantity_optional=";
        print::optional(out, md_entry_size_quantity_optional());
        out << ", secondary_order_id=";
        out << secondary_order_id();
        out << ", md_entry_timestamp=";
        print::optional_duration(out, md_entry_timestamp());
        out << ", rpt_seq=";
        print::optional(out, rpt_seq());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const DeleteOrderMbO51Message& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
