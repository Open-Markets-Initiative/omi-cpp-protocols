#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/InboundBusinessHeader.hpp"
#include "../enums/AllocTransType.hpp"
#include "../enums/AllocType.hpp"
#include "../enums/AllocNoOrdersType.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/Memo.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// AllocationInstructionMessage
class AllocationInstructionMessage {
  public:
    static constexpr const char* name = "AllocationInstructionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AllocationInstructionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AllocationInstructionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 86;
    std::size_t encoded_size() const { return memo_end(); }

    InboundBusinessHeader inbound_business_header() const { return InboundBusinessHeader{ bytes_.subspan(0) }; }

    std::uint64_t alloc_id() const { return wire::read_u64_le(at(18)); }

    std::uint64_t security_id() const { return wire::read_u64_le(at(26)); }

    AllocTransType alloc_trans_type() const { return static_cast<AllocTransType>(wire::read_char(at(34))); }

    AllocType alloc_type() const { return static_cast<AllocType>(wire::read_char(at(35))); }

    AllocNoOrdersType alloc_no_orders_type() const { return static_cast<AllocNoOrdersType>(wire::read_char(at(36))); }

    std::uint64_t quantity() const { return wire::read_u64_le(at(37)); }

    std::string_view sender_location() const { return view::text(at(45), 10, '\0'); }

    std::string_view entering_trader() const { return view::text(at(55), 5, '\0'); }

    std::uint32_t trade_id() const { return wire::read_u32_le(at(60)); }

    std::optional<std::uint16_t> trade_date_optional() const { return wire::nullable(wire::read_u16_le(at(64)), static_cast<std::uint16_t>(0ULL)); }

    std::uint64_t individual_alloc_id() const { return wire::read_u64_le(at(66)); }

    std::uint32_t alloc_account() const { return wire::read_u32_le(at(74)); }

    std::uint64_t alloc_qty() const { return wire::read_u64_le(at(78)); }

    DeskId desk_id() const { return DeskId{ bytes_.subspan(86) }; }

    Memo memo() const {
        wire::require("AllocationInstructionMessage", desk_id_end() + Memo::minimum_size, bytes_.size());
        return Memo{ bytes_.subspan(desk_id_end()) };
    }

    void print(std::ostream& out) const {
        out << "AllocationInstructionMessage{";
        out << "inbound_business_header=";
        inbound_business_header().print(out);
        out << ", alloc_id=";
        out << alloc_id();
        out << ", security_id=";
        out << security_id();
        out << ", alloc_trans_type=";
        out << alloc_trans_type();
        out << ", alloc_type=";
        out << alloc_type();
        out << ", alloc_no_orders_type=";
        out << alloc_no_orders_type();
        out << ", quantity=";
        out << quantity();
        out << ", sender_location=";
        print::text(out, sender_location());
        out << ", entering_trader=";
        print::text(out, entering_trader());
        out << ", trade_id=";
        out << trade_id();
        out << ", trade_date_optional=";
        print::optional(out, trade_date_optional());
        out << ", individual_alloc_id=";
        out << individual_alloc_id();
        out << ", alloc_account=";
        out << alloc_account();
        out << ", alloc_qty=";
        out << alloc_qty();
        out << ", desk_id=";
        desk_id().print(out);
        out << ", memo=";
        memo().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t desk_id_end() const { return 86 + desk_id().encoded_size(); }
    std::size_t memo_end() const { return desk_id_end() + memo().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AllocationInstructionMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
