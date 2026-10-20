#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace iex::iexequities::deepplus::snap::v1_06 {

// IexTp header of the wrapped feed message
class IextpHeader {
  public:
    static constexpr const char* name = "IextpHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit IextpHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every IextpHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 40;
    static constexpr std::size_t fixed_size = 40;
    std::size_t encoded_size() const { return 40; }

    std::uint8_t version() const { return wire::read_u8(at(0)); }

    std::span<const std::byte, 1> reserved() const { return bytes_.subspan(1).template first<1>(); }

    std::uint16_t message_protocol_id() const { return wire::read_u16_le(at(2)); }

    std::uint32_t channel_id() const { return wire::read_u32_le(at(4)); }

    std::uint32_t session_id() const { return wire::read_u32_le(at(8)); }

    std::uint16_t payload_length() const { return wire::read_u16_le(at(12)); }

    std::uint16_t message_count() const { return wire::read_u16_le(at(14)); }

    std::uint64_t stream_offset() const { return wire::read_u64_le(at(16)); }

    std::uint64_t first_message_sequence_number() const { return wire::read_u64_le(at(24)); }

    std::chrono::nanoseconds send_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_i64_le(at(32)))); }

    void print(std::ostream& out) const {
        out << "IextpHeader{";
        out << "version=";
        out << static_cast<int>(version());
        out << ", reserved=";
        print::hex(out, reserved().data(), reserved().size());
        out << ", message_protocol_id=";
        out << message_protocol_id();
        out << ", channel_id=";
        out << channel_id();
        out << ", session_id=";
        out << session_id();
        out << ", payload_length=";
        out << payload_length();
        out << ", message_count=";
        out << message_count();
        out << ", stream_offset=";
        out << stream_offset();
        out << ", first_message_sequence_number=";
        out << first_message_sequence_number();
        out << ", send_time=";
        out << send_time().count();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const IextpHeader& value) {
    value.print(out);
    return out;
}

} // namespace iex::iexequities::deepplus::snap::v1_06
