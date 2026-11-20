// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.3: structs/BidirectionalBusinessHeader.hpp
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
#include "../bitfields/EventIndicator.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// BidirectionalBusinessHeader
class BidirectionalBusinessHeader {
  public:
    static constexpr const char* name = "BidirectionalBusinessHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit BidirectionalBusinessHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every BidirectionalBusinessHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 20;
    static constexpr std::size_t fixed_size = 20;
    std::size_t encoded_size() const { return 20; }

    std::uint32_t session_id() const { return wire::read_u32_le(at(0)); }

    std::uint32_t msg_seq_num() const { return wire::read_u32_le(at(4)); }

    std::optional<std::chrono::nanoseconds> sending_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(8)), static_cast<std::uint64_t>(0ULL)); }

    EventIndicator event_indicator() const { return EventIndicator{ bytes_.subspan(16) }; }

    std::optional<std::uint8_t> market_segment_id_optional() const { return wire::nullable(wire::read_u8(at(17)), static_cast<std::uint8_t>(0ULL)); }

    std::string_view padding_char_2() const { return view::text(at(18), 2, '\0'); }

    void print(std::ostream& out) const {
        out << "BidirectionalBusinessHeader{";
        out << "session_id=";
        out << session_id();
        out << ", msg_seq_num=";
        out << msg_seq_num();
        out << ", sending_time=";
        print::optional_duration(out, sending_time());
        out << ", event_indicator=";
        event_indicator().print(out);
        out << ", market_segment_id_optional=";
        print::optional(out, market_segment_id_optional());
        out << ", padding_char_2=";
        print::text(out, padding_char_2());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const BidirectionalBusinessHeader& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
