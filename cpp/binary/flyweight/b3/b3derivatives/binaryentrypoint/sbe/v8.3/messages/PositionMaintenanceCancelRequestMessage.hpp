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

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// PositionMaintenanceCancelRequestMessage
class PositionMaintenanceCancelRequestMessage {
  public:
    static constexpr const char* name = "PositionMaintenanceCancelRequestMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PositionMaintenanceCancelRequestMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PositionMaintenanceCancelRequestMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 65;
    static constexpr std::size_t fixed_size = 65;
    std::size_t encoded_size() const { return 65; }

    InboundBusinessHeader inbound_business_header() const { return InboundBusinessHeader{ bytes_.subspan(0) }; }

    std::uint64_t pos_req_id() const { return wire::read_u64_le(at(18)); }

    std::uint64_t security_id() const { return wire::read_u64_le(at(26)); }

    std::optional<std::uint64_t> orig_pos_req_ref_id() const { return wire::nullable(wire::read_u64_le(at(34)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint64_t> pos_maint_rpt_ref_id() const { return wire::nullable(wire::read_u64_le(at(42)), static_cast<std::uint64_t>(0ULL)); }

    std::string_view sender_location() const { return view::text(at(50), 10, '\0'); }

    std::string_view entering_trader() const { return view::text(at(60), 5, '\0'); }

    void print(std::ostream& out) const {
        out << "PositionMaintenanceCancelRequestMessage{";
        out << "inbound_business_header=";
        inbound_business_header().print(out);
        out << ", pos_req_id=";
        out << pos_req_id();
        out << ", security_id=";
        out << security_id();
        out << ", orig_pos_req_ref_id=";
        print::optional(out, orig_pos_req_ref_id());
        out << ", pos_maint_rpt_ref_id=";
        print::optional(out, pos_maint_rpt_ref_id());
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

inline std::ostream& operator<<(std::ostream& out, const PositionMaintenanceCancelRequestMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
