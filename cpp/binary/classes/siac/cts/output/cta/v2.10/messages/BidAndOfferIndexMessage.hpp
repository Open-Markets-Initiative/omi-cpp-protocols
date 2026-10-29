#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/ParticipantId.hpp"
#include "../messages/IndicesMessagePayload.hpp"
#include "../structs/Timestamp1.hpp"

namespace siac::cts::output::cta::v2_10 {

class IndicesMessagePayloadVisitor;

// The Bid and Offer Index message contains the index Bid and Offer index values
class BidAndOfferIndexMessage : public IndicesMessagePayload {
  public:
    // The code that selects this message
    static constexpr IndicesMessagePayloadCode message_type = IndicesMessageType::BidAndOfferIndexMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 49;

    BidAndOfferIndexMessage() = default;
    BidAndOfferIndexMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& index_symbol, Decimal bid_index_value, Decimal offer_index_value);

    // Participant Id: Participant or Processor that generated the message
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

    // Transaction Id: The Transaction Id will be populated by CQS and is Reserved for Internal
    // Use only
    std::uint32_t transaction_id() const;
    void set_transaction_id(std::uint32_t value);

    // Participant Reference Number: Participant Reference Number is a pass-thru of the inbound
    // Participant Reference number assigned to a transaction
    std::int64_t participant_reference_number() const;
    void set_participant_reference_number(std::int64_t value);

    // Index Symbol: Contains the Index symbol
    const std::string& index_symbol() const;
    std::string& index_symbol();
    void set_index_symbol(const std::string& value);

    // Bid Index Value: The Bid Index Value represents the value of the index’s calculation
    // formula using the current Bid values of the component securities.
    Decimal bid_index_value() const;
    void set_bid_index_value(Decimal value);

    // Offer Index Value: Represents the value of the index calculation formula using the
    // current offer values of the component securities
    Decimal offer_index_value() const;
    void set_offer_index_value(Decimal value);

    // IndicesMessagePayload
    IndicesMessagePayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(IndicesMessagePayloadVisitor& visitor) const override;
    std::unique_ptr<IndicesMessagePayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const IndicesMessagePayload& other) const override;

    bool operator==(const BidAndOfferIndexMessage& other) const;
    bool operator!=(const BidAndOfferIndexMessage& other) const;

  private:
    ParticipantId participant_id_{};
    Timestamp1 timestamp_1_{};
    std::uint8_t message_id_{};
    std::uint32_t transaction_id_{};
    std::int64_t participant_reference_number_{};
    std::string index_symbol_{};
    Decimal bid_index_value_{ 0, -6 };
    Decimal offer_index_value_{ 0, -6 };
};

} // namespace siac::cts::output::cta::v2_10
