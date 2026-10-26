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

namespace siac::cts::output::cta::v2_11_b {

class IndicesMessagePayloadVisitor;

// The Index message contains the index and the index value
class IndexMessage : public IndicesMessagePayload {
  public:
    // The code that selects this message
    static constexpr IndicesMessagePayloadCode message_type = IndicesMessageType::Indices;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 41;

    IndexMessage() = default;
    IndexMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& index_symbol, Decimal index_value);

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

    // Index Symbol: Contains the Index symbol. Left justified, space-filled
    const std::string& index_symbol() const;
    std::string& index_symbol();
    void set_index_symbol(const std::string& value);

    // Index Value: Represents a statistical composite that measures changes in the economy or
    // in financial markets. Has implied 6 decimal places
    Decimal index_value() const;
    void set_index_value(Decimal value);

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

    bool operator==(const IndexMessage& other) const;
    bool operator!=(const IndexMessage& other) const;

  private:
    ParticipantId participant_id_{};
    Timestamp1 timestamp_1_{};
    std::uint8_t message_id_{};
    std::uint32_t transaction_id_{};
    std::int64_t participant_reference_number_{};
    std::string index_symbol_{};
    Decimal index_value_{ 0, -6 };
};

} // namespace siac::cts::output::cta::v2_11_b
