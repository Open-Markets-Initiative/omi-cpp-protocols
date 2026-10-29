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
#include "../enums/BreachedLevel.hpp"

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

// Informs data recipients when a MWCB has breached one of the established levels
class MwcbStatusMessage {
  public:
    static constexpr const char* name = "MwcbStatusMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MwcbStatusMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MwcbStatusMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 11;
    static constexpr std::size_t fixed_size = 11;
    std::size_t encoded_size() const { return 11; }

    std::uint16_t stock_locate() const { return wire::read_u16_be(at(0)); }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(2)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(4)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp().count())); }

    BreachedLevel breached_level() const { return static_cast<BreachedLevel>(wire::read_char(at(10))); }

    void print(std::ostream& out) const {
        out << "MwcbStatusMessage{";
        out << "stock_locate=";
        out << stock_locate();
        out << ", tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        calendar::print(out, timestamp().count(), 1, "America/New_York");
        out << ", breached_level=";
        out << breached_level();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MwcbStatusMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::ntxequities::totalview::itch::v5_0
