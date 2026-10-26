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

// ChannelReset_11Message
class ChannelReset11Message {
  public:
    static constexpr const char* name = "ChannelReset11Message";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ChannelReset11Message(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ChannelReset11Message has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 12;
    static constexpr std::size_t fixed_size = 12;
    std::size_t encoded_size() const { return 12; }

    MatchEventIndicator match_event_indicator() const { return MatchEventIndicator{ bytes_.subspan(0) }; }

    std::span<const std::byte, 3> offset_1_padding_3() const { return bytes_.subspan(1).template first<3>(); }

    std::optional<std::chrono::nanoseconds> md_entry_timestamp() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(4)), static_cast<std::uint64_t>(0ULL)); }

    void print(std::ostream& out) const {
        out << "ChannelReset11Message{";
        out << "match_event_indicator=";
        match_event_indicator().print(out);
        out << ", offset_1_padding_3=";
        print::hex(out, offset_1_padding_3().data(), offset_1_padding_3().size());
        out << ", md_entry_timestamp=";
        print::optional_duration(out, md_entry_timestamp());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ChannelReset11Message& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_1
