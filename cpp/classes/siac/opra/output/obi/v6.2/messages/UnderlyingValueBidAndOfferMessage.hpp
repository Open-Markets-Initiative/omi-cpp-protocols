#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/IndexValueDenominatorCode.hpp"
#include "../messages/UnderlyingValueMessagePayload.hpp"

namespace siac::opra::output::obi::v6_2 {

class UnderlyingValueMessagePayloadVisitor;

// Underlying value bid and offer message
class UnderlyingValueBidAndOfferMessage : public UnderlyingValueMessagePayload {
  public:
    // The code that selects this message
    static constexpr UnderlyingValueMessagePayloadCode message_type = UnderlyingValueMessageType::IndexBasedOnBidAndOffer;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 28;

    UnderlyingValueBidAndOfferMessage() = default;
    UnderlyingValueBidAndOfferMessage(char message_indicator, std::uint32_t transaction_id, std::uint32_t participant_reference_number, const std::string& security_symbol, const std::array<std::byte, 1>& reserved_1, IndexValueDenominatorCode index_value_denominator_code, std::int32_t bid_index_value, std::int64_t offer_index_value);

    // Message Indicator: Message identifier
    char message_indicator() const;
    void set_message_indicator(char value);

    // Transaction Id: Reserved for Internal Use only
    std::uint32_t transaction_id() const;
    void set_transaction_id(std::uint32_t value);

    // Participant Reference Number: The PRN is for optional use by the Participant
    std::uint32_t participant_reference_number() const;
    void set_participant_reference_number(std::uint32_t value);

    // Security Symbol: Identifies the unique symbol assigned to the underlying security.
    const std::string& security_symbol() const;
    std::string& security_symbol();
    void set_security_symbol(const std::string& value);

    // Reserved 1: One reserved byte
    const std::array<std::byte, 1>& reserved_1() const;
    std::array<std::byte, 1>& reserved_1();
    void set_reserved_1(const std::array<std::byte, 1>& value);

    // Index Value Denominator Code: Contains the index value using last sale values of index
    // components.
    IndexValueDenominatorCode index_value_denominator_code() const;
    void set_index_value_denominator_code(IndexValueDenominatorCode value);

    // Bid Index Value: The Bid Index Value represents the value of the index’s calculation
    // formula using the current bid values of the component securities.
    std::int32_t bid_index_value() const;
    void set_bid_index_value(std::int32_t value);

    // Offer Index Value: The Offer Index Value represents the value of the index’s calculation
    // formula using the current Offer values of the component securities.
    std::int64_t offer_index_value() const;
    void set_offer_index_value(std::int64_t value);

    // UnderlyingValueMessagePayload
    UnderlyingValueMessagePayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(UnderlyingValueMessagePayloadVisitor& visitor) const override;
    std::unique_ptr<UnderlyingValueMessagePayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const UnderlyingValueMessagePayload& other) const override;

    bool operator==(const UnderlyingValueBidAndOfferMessage& other) const;
    bool operator!=(const UnderlyingValueBidAndOfferMessage& other) const;

  private:
    char message_indicator_{};
    std::uint32_t transaction_id_{};
    std::uint32_t participant_reference_number_{};
    std::string security_symbol_{};
    std::array<std::byte, 1> reserved_1_{};
    IndexValueDenominatorCode index_value_denominator_code_{};
    std::int32_t bid_index_value_{};
    std::int64_t offer_index_value_{};
};

} // namespace siac::opra::output::obi::v6_2
