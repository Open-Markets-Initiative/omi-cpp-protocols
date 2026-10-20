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

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

// EmptyBook_9Message
class EmptyBookMessage {
  public:
    static constexpr const char* name = "EmptyBookMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit EmptyBookMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every EmptyBookMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 20;
    static constexpr std::size_t fixed_size = 20;
    std::size_t encoded_size() const { return 20; }

    std::uint64_t security_id() const { return wire::read_u64_le(at(0)); }

    MatchEventIndicator match_event_indicator() const { return MatchEventIndicator{ bytes_.subspan(8) }; }

    std::span<const std::byte, 3> offset_9_padding_3() const { return bytes_.subspan(9).template first<3>(); }

    std::optional<std::chrono::nanoseconds> md_entry_timestamp() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(12)), static_cast<std::uint64_t>(0ULL)); }

    void print(std::ostream& out) const {
        out << "EmptyBookMessage{";
        out << "security_id=";
        out << security_id();
        out << ", match_event_indicator=";
        match_event_indicator().print(out);
        out << ", offset_9_padding_3=";
        print::hex(out, offset_9_padding_3().data(), offset_9_padding_3().size());
        out << ", md_entry_timestamp=";
        print::optional_duration(out, md_entry_timestamp());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const EmptyBookMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_1
