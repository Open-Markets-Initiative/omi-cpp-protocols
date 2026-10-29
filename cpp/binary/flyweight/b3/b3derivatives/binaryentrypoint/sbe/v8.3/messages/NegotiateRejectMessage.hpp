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
#include "../enums/NegotiationRejectCode.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// NegotiateRejectMessage
class NegotiateRejectMessage {
  public:
    static constexpr const char* name = "NegotiateRejectMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit NegotiateRejectMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every NegotiateRejectMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 36;
    static constexpr std::size_t fixed_size = 36;
    std::size_t encoded_size() const { return 36; }

    std::uint32_t session_id() const { return wire::read_u32_le(at(0)); }

    std::uint64_t session_ver_id() const { return wire::read_u64_le(at(4)); }

    std::chrono::nanoseconds request_timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(12)))); }

    std::optional<std::uint32_t> entering_firm_optional() const { return wire::nullable(wire::read_u32_le(at(20)), static_cast<std::uint32_t>(0ULL)); }

    NegotiationRejectCode negotiation_reject_code() const { return static_cast<NegotiationRejectCode>(wire::read_u8(at(24))); }

    std::span<const std::byte, 3> offset_25_padding_3() const { return bytes_.subspan(25).template first<3>(); }

    std::optional<std::uint64_t> current_session_ver_id() const { return wire::nullable(wire::read_u64_le(at(28)), static_cast<std::uint64_t>(0ULL)); }

    void print(std::ostream& out) const {
        out << "NegotiateRejectMessage{";
        out << "session_id=";
        out << session_id();
        out << ", session_ver_id=";
        out << session_ver_id();
        out << ", request_timestamp=";
        out << request_timestamp().count();
        out << ", entering_firm_optional=";
        print::optional(out, entering_firm_optional());
        out << ", negotiation_reject_code=";
        out << negotiation_reject_code();
        out << ", offset_25_padding_3=";
        print::hex(out, offset_25_padding_3().data(), offset_25_padding_3().size());
        out << ", current_session_ver_id=";
        print::optional(out, current_session_ver_id());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const NegotiateRejectMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
