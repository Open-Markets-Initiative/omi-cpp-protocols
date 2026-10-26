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

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

// Informs data recipients when a MWCB has breached one of the established levels
class MwcbBreachMessage {
  public:
    static constexpr const char* name = "MwcbBreachMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MwcbBreachMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MwcbBreachMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 9;
    static constexpr std::size_t fixed_size = 9;
    std::size_t encoded_size() const { return 9; }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(0)); }

    std::chrono::nanoseconds time_stamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(2)))); }
    std::int64_t time_stamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(time_stamp().count())); }

    BreachedLevel breached_level() const { return static_cast<BreachedLevel>(wire::read_char(at(8))); }

    void print(std::ostream& out) const {
        out << "MwcbBreachMessage{";
        out << "tracking_number=";
        out << tracking_number();
        out << ", time_stamp=";
        calendar::print(out, time_stamp().count(), 1, "America/New_York");
        out << ", breached_level=";
        out << breached_level();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MwcbBreachMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
