#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// This message is sent at the start of every second during periods of active data publication
class TimeReferenceMessage {
  public:
    static constexpr const char* name = "TimeReferenceMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TimeReferenceMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TimeReferenceMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 12;
    static constexpr std::size_t fixed_size = 12;
    std::size_t encoded_size() const { return 12; }

    std::uint32_t id() const { return wire::read_u32_le(at(0)); }

    std::span<const std::byte, 4> reserved_4() const { return bytes_.subspan(4).template first<4>(); }

    std::uint32_t source_time() const { return wire::read_u32_le(at(8)); }

    void print(std::ostream& out) const {
        out << "TimeReferenceMessage{";
        out << "id=";
        out << id();
        out << ", reserved_4=";
        print::hex(out, reserved_4().data(), reserved_4().size());
        out << ", source_time=";
        out << source_time();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TimeReferenceMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
