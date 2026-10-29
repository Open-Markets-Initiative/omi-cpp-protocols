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

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// InboundBusinessHeader
class InboundBusinessHeader {
  public:
    static constexpr const char* name = "InboundBusinessHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit InboundBusinessHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every InboundBusinessHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 18;
    static constexpr std::size_t fixed_size = 18;
    std::size_t encoded_size() const { return 18; }

    std::uint32_t session_id() const { return wire::read_u32_le(at(0)); }

    std::uint32_t msg_seq_num() const { return wire::read_u32_le(at(4)); }

    std::optional<std::chrono::nanoseconds> sending_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(8)), static_cast<std::uint64_t>(0ULL)); }

    std::uint8_t market_segment_id() const { return wire::read_u8(at(16)); }

    char padding() const { return wire::read_char(at(17)); }

    void print(std::ostream& out) const {
        out << "InboundBusinessHeader{";
        out << "session_id=";
        out << session_id();
        out << ", msg_seq_num=";
        out << msg_seq_num();
        out << ", sending_time=";
        print::optional_duration(out, sending_time());
        out << ", market_segment_id=";
        out << static_cast<int>(market_segment_id());
        out << ", padding=";
        print::character(out, padding());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const InboundBusinessHeader& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
