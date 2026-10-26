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
#include "../enums/MdUpdateAction.hpp"
#include "../enums/MdEntryType.hpp"
#include "../common/Decimal.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

// Order_MBO_50Message
class OrderMbO50Message {
  public:
    static constexpr const char* name = "OrderMbO50Message";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderMbO50Message(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderMbO50Message has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 64;
    static constexpr std::size_t fixed_size = 64;
    std::size_t encoded_size() const { return 64; }

    std::uint64_t security_id() const { return wire::read_u64_le(at(0)); }

    MatchEventIndicator match_event_indicator() const { return MatchEventIndicator{ bytes_.subspan(8) }; }

    MdUpdateAction md_update_action() const { return static_cast<MdUpdateAction>(wire::read_u8(at(9))); }

    MdEntryType md_entry_type() const { return static_cast<MdEntryType>(wire::read_char(at(10))); }

    std::span<const std::byte, 1> offset_11_padding_1() const { return bytes_.subspan(11).template first<1>(); }

    std::optional<Decimal> md_corporate_offset_price_optional() const { return wire::nullable_decimal(wire::read_i64_le(at(12)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4); }

    std::int64_t md_entry_size_quantity() const { return wire::read_i64_le(at(20)); }

    std::optional<std::uint32_t> md_entry_position_no() const { return wire::nullable(wire::read_u32_le(at(28)), static_cast<std::uint32_t>(0ULL)); }

    std::optional<std::uint32_t> entering_firm() const { return wire::nullable(wire::read_u32_le(at(32)), static_cast<std::uint32_t>(0ULL)); }

    std::optional<std::chrono::nanoseconds> md_insert_timestamp() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(36)), static_cast<std::uint64_t>(0ULL)); }

    std::uint64_t secondary_order_id() const { return wire::read_u64_le(at(44)); }

    std::optional<std::uint32_t> rpt_seq() const { return wire::nullable(wire::read_u32_le(at(52)), static_cast<std::uint32_t>(0ULL)); }

    std::optional<std::uint64_t> transact_time() const { return wire::nullable(wire::read_u64_le(at(56)), static_cast<std::uint64_t>(0ULL)); }

    void print(std::ostream& out) const {
        out << "OrderMbO50Message{";
        out << "security_id=";
        out << security_id();
        out << ", match_event_indicator=";
        match_event_indicator().print(out);
        out << ", md_update_action=";
        out << md_update_action();
        out << ", md_entry_type=";
        out << md_entry_type();
        out << ", offset_11_padding_1=";
        print::hex(out, offset_11_padding_1().data(), offset_11_padding_1().size());
        out << ", md_corporate_offset_price_optional=";
        print::optional(out, md_corporate_offset_price_optional());
        out << ", md_entry_size_quantity=";
        out << md_entry_size_quantity();
        out << ", md_entry_position_no=";
        print::optional(out, md_entry_position_no());
        out << ", entering_firm=";
        print::optional(out, entering_firm());
        out << ", md_insert_timestamp=";
        print::optional_duration(out, md_insert_timestamp());
        out << ", secondary_order_id=";
        out << secondary_order_id();
        out << ", rpt_seq=";
        print::optional(out, rpt_seq());
        out << ", transact_time=";
        print::optional(out, transact_time());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderMbO50Message& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_1
