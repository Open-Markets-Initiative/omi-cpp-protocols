#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2026 {

// Informs data recipients what the daily MWCB breach points are set to for the current trading
// day.
class MwcbDeclineLevelMessage {
  public:
    static constexpr const char* name = "MwcbDeclineLevelMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MwcbDeclineLevelMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MwcbDeclineLevelMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 34;
    static constexpr std::size_t fixed_size = 34;
    std::size_t encoded_size() const { return 34; }

    std::uint16_t stock_locate() const { return wire::read_u16_be(at(0)); }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(2)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(4)))); }

    Decimal level_1() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(10))), -8); }

    Decimal level_2() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(18))), -8); }

    Decimal level_3() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(26))), -8); }

    void print(std::ostream& out) const {
        out << "MwcbDeclineLevelMessage{";
        out << "stock_locate=";
        out << stock_locate();
        out << ", tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        out << timestamp().count();
        out << ", level_1=";
        out << level_1();
        out << ", level_2=";
        out << level_2();
        out << ", level_3=";
        out << level_3();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MwcbDeclineLevelMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2026
