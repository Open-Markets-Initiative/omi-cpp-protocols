#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/PremiumPriceDenominatorCode.hpp"
#include "../enums/StrikePriceDenominatorCode.hpp"
#include "../messages/EquityAndIndexLastSaleMessagePayload.hpp"
#include "../structs/ExpirationBlock.hpp"

namespace siac::opra::output::obi::v6_2 {

class EquityAndIndexLastSaleMessagePayloadVisitor;

// Equity and Index Last Sale Message
class EquityAndIndexLastSaleMessage : public EquityAndIndexLastSaleMessagePayload {
  public:
    // The code that selects this message
    static constexpr EquityAndIndexLastSaleMessagePayloadCode message_type = EquityAndIndexLastSaleMessageType::Canc;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 40;

    EquityAndIndexLastSaleMessage() = default;
    EquityAndIndexLastSaleMessage(char message_indicator, std::uint32_t transaction_id, std::uint32_t participant_reference_number, const std::string& security_symbol, const std::array<std::byte, 1>& reserved_1, const ExpirationBlock& expiration_block, StrikePriceDenominatorCode strike_price_denominator_code, Decimal strike_price, std::uint32_t volume, PremiumPriceDenominatorCode premium_price_denominator_code, Decimal premium_price, std::uint32_t trade_identifier, const std::array<std::byte, 4>& reserved_4);

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

    // Volume: Represents the total number of contracts traded for an option in one trade, or
    // the total number of contracts traded for an option for the entire trading day.
    std::uint32_t volume() const;
    void set_volume(std::uint32_t value);

    // Premium Price Denominator Code: Represents the first price paid for an option during the
    // trading day.
    PremiumPriceDenominatorCode premium_price_denominator_code() const;
    void set_premium_price_denominator_code(PremiumPriceDenominatorCode value);

    // Premium Price: Represents the price of an option contract, determined in the competitive
    // marketplace, which the buyer of the option pays to the option writer for the rights
    // conveyed by the option contract.
    Decimal premium_price() const;
    void set_premium_price(Decimal value);
    // the exponent premium_price_denominator_code states, or 0 for a code it does not state
    static int premium_price_exponent(char code);

    // Trade Identifier: FOR FUTURE USE. Filled with Hex 0x00.
    std::uint32_t trade_identifier() const;
    void set_trade_identifier(std::uint32_t value);

    // Reserved 4: Four reserved bytes
    const std::array<std::byte, 4>& reserved_4() const;
    std::array<std::byte, 4>& reserved_4();
    void set_reserved_4(const std::array<std::byte, 4>& value);

    // EquityAndIndexLastSaleMessagePayload
    EquityAndIndexLastSaleMessagePayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(EquityAndIndexLastSaleMessagePayloadVisitor& visitor) const override;
    std::unique_ptr<EquityAndIndexLastSaleMessagePayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const EquityAndIndexLastSaleMessagePayload& other) const override;

    bool operator==(const EquityAndIndexLastSaleMessage& other) const;
    bool operator!=(const EquityAndIndexLastSaleMessage& other) const;

  private:
    char message_indicator_{};
    std::uint32_t transaction_id_{};
    std::uint32_t participant_reference_number_{};
    std::string security_symbol_{};
    std::array<std::byte, 1> reserved_1_{};
    ExpirationBlock expiration_block_{};
    StrikePriceDenominatorCode strike_price_denominator_code_{};
    Decimal strike_price_{};
    std::uint32_t volume_{};
    PremiumPriceDenominatorCode premium_price_denominator_code_{};
    Decimal premium_price_{};
    std::uint32_t trade_identifier_{};
    std::array<std::byte, 4> reserved_4_{};
};

} // namespace siac::opra::output::obi::v6_2
