#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"
#include "../enums/Tick.hpp"

namespace siac::cts::output::cta::v2_10 {

// Participant Data
class ParticipantData {
  public:
    static constexpr const char* name = "ParticipantData";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ParticipantData(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ParticipantData has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 41;
    static constexpr std::size_t fixed_size = 41;
    std::size_t encoded_size() const { return 41; }

    std::uint32_t previous_close_price_date() const { return wire::read_u32_be(at(0)); }

    Decimal last_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(4))), -6); }

    Decimal high_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(12))), -6); }

    Decimal low_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(20))), -6); }

    Decimal open_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(28))), -6); }

    std::uint32_t total_volume_short() const { return wire::read_u32_be(at(36)); }

    Tick tick() const { return static_cast<Tick>(wire::read_char(at(40))); }

    void print(std::ostream& out) const {
        out << "ParticipantData{";
        out << "previous_close_price_date=";
        out << previous_close_price_date();
        out << ", last_price=";
        out << last_price();
        out << ", high_price=";
        out << high_price();
        out << ", low_price=";
        out << low_price();
        out << ", open_price=";
        out << open_price();
        out << ", total_volume_short=";
        out << total_volume_short();
        out << ", tick=";
        out << tick();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ParticipantData& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_10
