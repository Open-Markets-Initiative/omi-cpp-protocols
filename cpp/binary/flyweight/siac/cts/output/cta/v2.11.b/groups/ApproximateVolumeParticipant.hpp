#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/ParticipantId.hpp"

namespace siac::cts::output::cta::v2_11_b {

// Active Participants for Approximate Adjusted Volume Market Center
class ApproximateVolumeParticipant {
  public:
    static constexpr const char* name = "ApproximateVolumeParticipant";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ApproximateVolumeParticipant(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ApproximateVolumeParticipant has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 9;
    static constexpr std::size_t fixed_size = 9;
    std::size_t encoded_size() const { return 9; }

    ParticipantId participant_id() const { return static_cast<ParticipantId>(wire::read_char(at(0))); }

    std::uint64_t trade_total_volume() const { return wire::read_u64_be(at(1)); }

    void print(std::ostream& out) const {
        out << "ApproximateVolumeParticipant{";
        out << "participant_id=";
        out << participant_id();
        out << ", trade_total_volume=";
        out << trade_total_volume();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ApproximateVolumeParticipant& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_11_b
