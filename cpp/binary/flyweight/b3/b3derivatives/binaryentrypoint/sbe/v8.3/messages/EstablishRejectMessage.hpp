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
#include "../enums/EstablishmentRejectCode.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// EstablishRejectMessage
class EstablishRejectMessage {
  public:
    static constexpr const char* name = "EstablishRejectMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit EstablishRejectMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every EstablishRejectMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 26;
    static constexpr std::size_t fixed_size = 26;
    std::size_t encoded_size() const { return 26; }

    std::uint32_t session_id() const { return wire::read_u32_le(at(0)); }

    std::uint64_t session_ver_id() const { return wire::read_u64_le(at(4)); }

    std::chrono::nanoseconds request_timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(12)))); }

    EstablishmentRejectCode establishment_reject_code() const { return static_cast<EstablishmentRejectCode>(wire::read_u8(at(20))); }

    std::span<const std::byte, 1> offset_21_padding_1() const { return bytes_.subspan(21).template first<1>(); }

    std::optional<std::uint32_t> last_incoming_seq_no_optional() const { return wire::nullable(wire::read_u32_le(at(22)), static_cast<std::uint32_t>(0ULL)); }

    void print(std::ostream& out) const {
        out << "EstablishRejectMessage{";
        out << "session_id=";
        out << session_id();
        out << ", session_ver_id=";
        out << session_ver_id();
        out << ", request_timestamp=";
        out << request_timestamp().count();
        out << ", establishment_reject_code=";
        out << establishment_reject_code();
        out << ", offset_21_padding_1=";
        print::hex(out, offset_21_padding_1().data(), offset_21_padding_1().size());
        out << ", last_incoming_seq_no_optional=";
        print::optional(out, last_incoming_seq_no_optional());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const EstablishRejectMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
