#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// MDInstrumentDefinitionFuture
class MaturityMonthYear {
  public:
    static constexpr const char* name = "MaturityMonthYear";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MaturityMonthYear(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MaturityMonthYear has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 5;
    static constexpr std::size_t fixed_size = 5;
    std::size_t encoded_size() const { return 5; }

    std::optional<std::uint16_t> year() const { return wire::nullable(wire::read_u16_le(at(0)), static_cast<std::uint16_t>(65535ULL)); }

    std::optional<std::uint8_t> month() const { return wire::nullable(wire::read_u8(at(2)), static_cast<std::uint8_t>(255ULL)); }

    std::optional<std::uint8_t> day() const { return wire::nullable(wire::read_u8(at(3)), static_cast<std::uint8_t>(255ULL)); }

    std::optional<std::uint8_t> week() const { return wire::nullable(wire::read_u8(at(4)), static_cast<std::uint8_t>(255ULL)); }

    void print(std::ostream& out) const {
        out << "MaturityMonthYear{";
        out << "year=";
        print::optional(out, year());
        out << ", month=";
        print::optional(out, month());
        out << ", day=";
        print::optional(out, day());
        out << ", week=";
        print::optional(out, week());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MaturityMonthYear& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
