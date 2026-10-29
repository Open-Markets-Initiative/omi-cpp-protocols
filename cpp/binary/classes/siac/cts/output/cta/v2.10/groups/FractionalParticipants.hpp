#pragma once

#include <cstddef>
#include <ostream>

#include "../common/Decimal.hpp"
#include "../enums/ParticipantId.hpp"

namespace siac::cts::output::cta::v2_10 {

// Active Fractional Participants
class FractionalParticipants {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 9;

    FractionalParticipants() = default;
    FractionalParticipants(ParticipantId participant_id, Decimal fractional_trade_total_volume);

    // Participant Id: Participant or Processor that generated the message
    ParticipantId participant_id() const;
    void set_participant_id(ParticipantId value);

    // Fractional Trade Total Volume: Contains the total number of shares traded for each
    // Participant.
    Decimal fractional_trade_total_volume() const;
    void set_fractional_trade_total_volume(Decimal value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const FractionalParticipants& other) const;
    bool operator!=(const FractionalParticipants& other) const;

  private:
    ParticipantId participant_id_{};
    Decimal fractional_trade_total_volume_{ 0, -6 };
};

std::ostream& operator<<(std::ostream& out, const FractionalParticipants& value);

} // namespace siac::cts::output::cta::v2_10
