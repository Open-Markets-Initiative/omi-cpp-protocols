#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Provides information about the time of processing on the Trading Server to the nearest
// second. Always delivered at the time the information is generated, except for Reset and
// Communication Control. Only one tag is delivered per process and stored at the top of the
// first packet.
class SecondsTimestampMessage {
  public:
    static constexpr const char* name = "SecondsTimestampMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SecondsTimestampMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SecondsTimestampMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 4;
    static constexpr std::size_t fixed_size = 4;
    std::size_t encoded_size() const { return 4; }

    std::chrono::seconds time_seconds() const { return std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    void print(std::ostream& out) const {
        out << "SecondsTimestampMessage{";
        out << "time_seconds=";
        out << time_seconds().count();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SecondsTimestampMessage& value) {
    value.print(out);
    return out;
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
