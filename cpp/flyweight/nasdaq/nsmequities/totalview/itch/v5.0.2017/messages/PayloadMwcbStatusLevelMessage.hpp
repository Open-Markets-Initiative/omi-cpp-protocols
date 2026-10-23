#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/BreachedLevel.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

// Informs data recipients when a MWCB has breached one of the established levels
class PayloadMwcbStatusLevelMessage {
  public:
    static constexpr const char* name = "PayloadMwcbStatusLevelMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PayloadMwcbStatusLevelMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PayloadMwcbStatusLevelMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 11;
    static constexpr std::size_t fixed_size = 11;
    std::size_t encoded_size() const { return 11; }

    std::uint16_t stock_locate() const { return wire::read_u16_be(at(0)); }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(2)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(4)))); }

    BreachedLevel breached_level() const { return static_cast<BreachedLevel>(wire::read_char(at(10))); }

    void print(std::ostream& out) const {
        out << "PayloadMwcbStatusLevelMessage{";
        out << "stock_locate=";
        out << stock_locate();
        out << ", tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        out << timestamp().count();
        out << ", breached_level=";
        out << breached_level();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PayloadMwcbStatusLevelMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2017
