#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../groups/FractionalParticipants.hpp"

namespace siac::cts::output::cta::v2_10 {

// Approximate Adjusted Volume Market Center message is used to report the volume of adjusted
// trading activity for each Participant.
class FractionalApproximateAdjustedVolumeMarketCenterMessage {
  public:
    static constexpr const char* name = "FractionalApproximateAdjustedVolumeMarketCenterMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit FractionalApproximateAdjustedVolumeMarketCenterMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every FractionalApproximateAdjustedVolumeMarketCenterMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 23;
    std::size_t encoded_size() const { return fractional_participants_end(); }

    ParticipantId participant_id() const { return static_cast<ParticipantId>(wire::read_char(at(0))); }

    Timestamp1 timestamp_1() const { return Timestamp1{ bytes_.subspan(1) }; }

    std::uint8_t message_id() const { return wire::read_u8(at(9)); }

    std::uint32_t transaction_id() const { return wire::read_u32_be(at(10)); }

    std::int64_t participant_reference_number() const { return wire::read_i64_be(at(14)); }

    std::uint8_t number_of_participants() const { return wire::read_u8(at(22)); }

    view::entries<FractionalParticipants> fractional_participants() const { return view::entries<FractionalParticipants>{ bytes_.subspan(23), wire::count(number_of_participants()) }; }

    void print(std::ostream& out) const {
        out << "FractionalApproximateAdjustedVolumeMarketCenterMessage{";
        out << "participant_id=";
        out << participant_id();
        out << ", timestamp_1=";
        timestamp_1().print(out);
        out << ", message_id=";
        out << static_cast<int>(message_id());
        out << ", transaction_id=";
        out << transaction_id();
        out << ", participant_reference_number=";
        out << participant_reference_number();
        out << ", number_of_participants=";
        out << static_cast<int>(number_of_participants());
        out << ", fractional_participants=";
        print::sequence(out, fractional_participants());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t fractional_participants_end() const { return 23 + fractional_participants().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const FractionalApproximateAdjustedVolumeMarketCenterMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_10
