#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Informs the market of the daily market wide circuit breaker decline levels, disseminated at
// the start of the trading day.
class MwcbDeclineLevelMessage {
  public:
    static constexpr const char* name = "MwcbDeclineLevelMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MwcbDeclineLevelMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MwcbDeclineLevelMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 24;
    static constexpr std::size_t fixed_size = 24;
    std::size_t encoded_size() const { return 24; }

    Decimal level_1() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(0))), -8); }

    Decimal level_2() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(8))), -8); }

    Decimal level_3() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(16))), -8); }

    void print(std::ostream& out) const {
        out << "MwcbDeclineLevelMessage{";
        out << "level_1=";
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

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
