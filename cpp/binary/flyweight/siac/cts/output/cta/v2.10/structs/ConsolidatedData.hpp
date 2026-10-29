#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/LastParticipantId.hpp"
#include "../common/Decimal.hpp"
#include "../enums/Tick.hpp"

namespace siac::cts::output::cta::v2_10 {

// Consolidated Data
class ConsolidatedData {
  public:
    static constexpr const char* name = "ConsolidatedData";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ConsolidatedData(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ConsolidatedData has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 34;
    static constexpr std::size_t fixed_size = 34;
    std::size_t encoded_size() const { return 34; }

    std::uint32_t previous_close_price_date() const { return wire::read_u32_be(at(0)); }

    LastParticipantId last_participant_id() const { return static_cast<LastParticipantId>(wire::read_char(at(4))); }

    Decimal last_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(5))), -6); }

    Decimal high_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(13))), -6); }

    Decimal low_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(21))), -6); }

    std::uint32_t total_volume_short() const { return wire::read_u32_be(at(29)); }

    Tick tick() const { return static_cast<Tick>(wire::read_char(at(33))); }

    void print(std::ostream& out) const {
        out << "ConsolidatedData{";
        out << "previous_close_price_date=";
        out << previous_close_price_date();
        out << ", last_participant_id=";
        out << last_participant_id();
        out << ", last_price=";
        out << last_price();
        out << ", high_price=";
        out << high_price();
        out << ", low_price=";
        out << low_price();
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

inline std::ostream& operator<<(std::ostream& out, const ConsolidatedData& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_10
