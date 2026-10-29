#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Day.hpp"

namespace jnx::jnxequities::pts::itch::v1_6 {

// Reflects the number of seconds past midnight that the Timestamp message was generated.
class SecondsMessage {
  public:
    static constexpr const char* name = "SecondsMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SecondsMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SecondsMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 4;
    static constexpr std::size_t fixed_size = 4;
    std::size_t encoded_size() const { return 4; }

    std::chrono::seconds seconds() const { return std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }
    std::int64_t seconds_utc(const calendar::Day& day) const { return calendar::midnight(day, "Asia/Tokyo").utc(static_cast<std::int64_t>(seconds().count()) * 1000000000); }

    void print(std::ostream& out) const {
        out << "SecondsMessage{";
        out << "seconds=";
        calendar::print(out, seconds().count(), 1000000000, "Asia/Tokyo");
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SecondsMessage& value) {
    value.print(out);
    return out;
}

} // namespace jnx::jnxequities::pts::itch::v1_6
