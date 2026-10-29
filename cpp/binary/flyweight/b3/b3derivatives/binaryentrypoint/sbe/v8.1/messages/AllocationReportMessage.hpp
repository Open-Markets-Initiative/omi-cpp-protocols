#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/OutboundBusinessHeader.hpp"
#include "../enums/AllocTransType.hpp"
#include "../enums/AllocReportType.hpp"
#include "../enums/AllocNoOrdersType.hpp"
#include "../enums/AllocStatus.hpp"
#include "../enums/Side.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// AllocationReportMessage
class AllocationReportMessage {
  public:
    static constexpr const char* name = "AllocationReportMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AllocationReportMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AllocationReportMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 84;
    static constexpr std::size_t fixed_size = 84;
    std::size_t encoded_size() const { return 84; }

    OutboundBusinessHeader outbound_business_header() const { return OutboundBusinessHeader{ bytes_.subspan(0) }; }

    std::uint64_t alloc_id() const { return wire::read_u64_le(at(18)); }

    std::uint64_t security_id() const { return wire::read_u64_le(at(26)); }

    std::uint64_t alloc_report_id() const { return wire::read_u64_le(at(34)); }

    AllocTransType alloc_trans_type() const { return static_cast<AllocTransType>(wire::read_char(at(42))); }

    AllocReportType alloc_report_type() const { return static_cast<AllocReportType>(wire::read_char(at(43))); }

    AllocNoOrdersType alloc_no_orders_type() const { return static_cast<AllocNoOrdersType>(wire::read_char(at(44))); }

    std::optional<std::uint32_t> alloc_rej_code() const { return wire::nullable(wire::read_u32_le(at(45)), static_cast<std::uint32_t>(0ULL)); }

    std::uint64_t quantity() const { return wire::read_u64_le(at(49)); }

    AllocStatus alloc_status() const { return static_cast<AllocStatus>(wire::read_char(at(57))); }

    std::optional<std::uint16_t> trade_date_optional() const { return wire::nullable(wire::read_u16_le(at(58)), static_cast<std::uint16_t>(0ULL)); }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(60)))); }

    Side side() const { return static_cast<Side>(wire::read_char(at(68))); }

    std::string_view sender_location() const { return view::text(at(69), 10, '\0'); }

    std::string_view entering_trader() const { return view::text(at(79), 5, '\0'); }

    void print(std::ostream& out) const {
        out << "AllocationReportMessage{";
        out << "outbound_business_header=";
        outbound_business_header().print(out);
        out << ", alloc_id=";
        out << alloc_id();
        out << ", security_id=";
        out << security_id();
        out << ", alloc_report_id=";
        out << alloc_report_id();
        out << ", alloc_trans_type=";
        out << alloc_trans_type();
        out << ", alloc_report_type=";
        out << alloc_report_type();
        out << ", alloc_no_orders_type=";
        out << alloc_no_orders_type();
        out << ", alloc_rej_code=";
        print::optional(out, alloc_rej_code());
        out << ", quantity=";
        out << quantity();
        out << ", alloc_status=";
        out << alloc_status();
        out << ", trade_date_optional=";
        print::optional(out, trade_date_optional());
        out << ", transact_time=";
        out << transact_time().count();
        out << ", side=";
        out << side();
        out << ", sender_location=";
        print::text(out, sender_location());
        out << ", entering_trader=";
        print::text(out, entering_trader());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AllocationReportMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
