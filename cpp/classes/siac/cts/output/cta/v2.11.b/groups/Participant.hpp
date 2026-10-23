#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/ParticipantId.hpp"

namespace siac::cts::output::cta::v2_11_b {

// Active Participants
class Participant {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 9;

    Participant() = default;
    Participant(ParticipantId participant_id, std::uint64_t fractional_trade_total_volume);

    // Participant Id: Identifies the Participant or Processor that initiated the message
    ParticipantId participant_id() const;
    void set_participant_id(ParticipantId value);

    // Fractional Trade Total Volume: Contains the total number of shares traded for each
    // Participant. Has implied 6 decimal places
    std::uint64_t fractional_trade_total_volume() const;
    void set_fractional_trade_total_volume(std::uint64_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const Participant& other) const;
    bool operator!=(const Participant& other) const;

  private:
    ParticipantId participant_id_{};
    std::uint64_t fractional_trade_total_volume_{};
};

std::ostream& operator<<(std::ostream& out, const Participant& value);

} // namespace siac::cts::output::cta::v2_11_b
