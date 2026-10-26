#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "../enums/ParticipantId.hpp"
#include "../groups/ApproximateVolumeParticipant.hpp"
#include "../messages/MarketStatusMessagePayload.hpp"
#include "../structs/Timestamp1.hpp"

namespace siac::cts::output::cta::v2_11_b {

class MarketStatusMessagePayloadVisitor;

// Used to report the volume of adjusted trading activity for each Participant. To be descoped
// when Fractional Trade Volume publication is activated
class ApproximateAdjustedVolumeMarketCenterMessage : public MarketStatusMessagePayload {
  public:
    // The code that selects this message
    static constexpr MarketStatusMessagePayloadCode message_type = MarketStatusMessageType::ApproximateAdjustedVolumeMarketCenter;

    ApproximateAdjustedVolumeMarketCenterMessage() = default;
    ApproximateAdjustedVolumeMarketCenterMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, std::uint8_t number_of_participants, const std::vector<ApproximateVolumeParticipant>& approximate_volume_participant);

    // Participant Id: Identifies the Participant or Processor that initiated the message
    ParticipantId participant_id() const;
    void set_participant_id(ParticipantId value);

    // Timestamp 1: Timestamp 1
    const Timestamp1& timestamp_1() const;
    Timestamp1& timestamp_1();
    void set_timestamp_1(const Timestamp1& value);

    // Message Id: The Message ID identifies the individual message within the block beginning
    // with number one
    std::uint8_t message_id() const;
    void set_message_id(std::uint8_t value);

    // Transaction Id: Identifies the transaction
    std::uint32_t transaction_id() const;
    void set_transaction_id(std::uint32_t value);

    // Participant Reference Number: Contains the Participant Reference Number
    std::int64_t participant_reference_number() const;
    void set_participant_reference_number(std::int64_t value);

    // Number Of Participants: Represents the actual number of Participants for which an issue
    // will be reported
    std::uint8_t number_of_participants() const;
    void set_number_of_participants(std::uint8_t value);

    // Approximate Volume Participant: Active Participants for Approximate Adjusted Volume
    // Market Center
    const std::vector<ApproximateVolumeParticipant>& approximate_volume_participant() const;
    std::vector<ApproximateVolumeParticipant>& approximate_volume_participant();
    void set_approximate_volume_participant(const std::vector<ApproximateVolumeParticipant>& value);

    // MarketStatusMessagePayload
    MarketStatusMessagePayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(MarketStatusMessagePayloadVisitor& visitor) const override;
    std::unique_ptr<MarketStatusMessagePayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const MarketStatusMessagePayload& other) const override;

    bool operator==(const ApproximateAdjustedVolumeMarketCenterMessage& other) const;
    bool operator!=(const ApproximateAdjustedVolumeMarketCenterMessage& other) const;

  private:
    ParticipantId participant_id_{};
    Timestamp1 timestamp_1_{};
    std::uint8_t message_id_{};
    std::uint32_t transaction_id_{};
    std::int64_t participant_reference_number_{};
    std::uint8_t number_of_participants_{};
    std::vector<ApproximateVolumeParticipant> approximate_volume_participant_{};
};

} // namespace siac::cts::output::cta::v2_11_b
