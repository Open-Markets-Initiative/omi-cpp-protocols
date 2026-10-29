#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/ParticipantId.hpp"
#include "../common/Decimal.hpp"

namespace siac::cts::output::cta::v2_10 {

// Active Fractional Participants
class FractionalParticipants {
  public:
    static constexpr const char* name = "FractionalParticipants";

    // the bytes it reads, which it does not own: they must outlive it
    explicit FractionalParticipants(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every FractionalParticipants has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 9;
    static constexpr std::size_t fixed_size = 9;
    std::size_t encoded_size() const { return 9; }

    ParticipantId participant_id() const { return static_cast<ParticipantId>(wire::read_char(at(0))); }

    Decimal fractional_trade_total_volume() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(1))), -6); }

    void print(std::ostream& out) const {
        out << "FractionalParticipants{";
        out << "participant_id=";
        out << participant_id();
        out << ", fractional_trade_total_volume=";
        out << fractional_trade_total_volume();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const FractionalParticipants& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_10
