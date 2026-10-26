#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/StrikePriceDenominatorCode.hpp"
#include "../messages/OpenInterestMessagePayload.hpp"
#include "../structs/ExpirationBlock.hpp"

namespace siac::opra::output::obi::v6_2 {

class OpenInterestMessagePayloadVisitor;

// Open Interest Message
class OpenInterestMessage : public OpenInterestMessagePayload {
  public:
    // The code that selects this message
    static constexpr OpenInterestMessagePayloadCode message_type = OpenInterestMessageType::OpenInterest;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 27;

    OpenInterestMessage() = default;
    OpenInterestMessage(char message_indicator, std::uint32_t transaction_id, std::uint32_t participant_reference_number, const std::string& security_symbol, const std::array<std::byte, 1>& reserved_1, const ExpirationBlock& expiration_block, StrikePriceDenominatorCode strike_price_denominator_code, Decimal strike_price, std::uint32_t open_interest_volume);

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

    // Expiration Block: Expiration Block
    const ExpirationBlock& expiration_block() const;
    ExpirationBlock& expiration_block();
    void set_expiration_block(const ExpirationBlock& value);

    // Strike Price Denominator Code: The Strike Price Denominator Code field indicates the
    // position of the floating decimal point within the Strike Price field.
    StrikePriceDenominatorCode strike_price_denominator_code() const;
    void set_strike_price_denominator_code(StrikePriceDenominatorCode value);

    // Strike Price: Represents the stated price per share for which the underlying security
    // may be purchased (in the case of a call) or sold (in the case of a put) by the option
    // holder upon exercise of the option contract.
    Decimal strike_price() const;
    void set_strike_price(Decimal value);
    // the exponent strike_price_denominator_code states, or 0 for a code it does not state
    static int strike_price_exponent(char code);

    // Open Interest Volume: Represents the total number of outstanding option contracts that
    // have not been exercised and have not yet reached expiration.
    std::uint32_t open_interest_volume() const;
    void set_open_interest_volume(std::uint32_t value);

    // OpenInterestMessagePayload
    OpenInterestMessagePayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(OpenInterestMessagePayloadVisitor& visitor) const override;
    std::unique_ptr<OpenInterestMessagePayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const OpenInterestMessagePayload& other) const override;

    bool operator==(const OpenInterestMessage& other) const;
    bool operator!=(const OpenInterestMessage& other) const;

  private:
    char message_indicator_{};
    std::uint32_t transaction_id_{};
    std::uint32_t participant_reference_number_{};
    std::string security_symbol_{};
    std::array<std::byte, 1> reserved_1_{};
    ExpirationBlock expiration_block_{};
    StrikePriceDenominatorCode strike_price_denominator_code_{};
    Decimal strike_price_{};
    std::uint32_t open_interest_volume_{};
};

} // namespace siac::opra::output::obi::v6_2
