#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/IndexValueDenominatorCode.hpp"
#include "../messages/UnderlyingValueMessagePayload.hpp"

namespace siac::opra::output::obi::v6_2 {

class UnderlyingValueMessagePayloadVisitor;

// Underlying Value last sale Message
class UnderlyingValueLastSaleMessage : public UnderlyingValueMessagePayload {
  public:
    // The code that selects this message
    static constexpr UnderlyingValueMessagePayloadCode message_type = UnderlyingValueMessageType::IndexBasedOnLastSale;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 24;

    UnderlyingValueLastSaleMessage() = default;
    UnderlyingValueLastSaleMessage(char message_indicator, std::uint32_t transaction_id, std::uint32_t participant_reference_number, const std::string& security_symbol, const std::array<std::byte, 1>& reserved_1, IndexValueDenominatorCode index_value_denominator_code, Decimal index_value, const std::array<std::byte, 4>& reserved_4);

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

    // Index Value: Contains the index value using last sale values of index components.
    Decimal index_value() const;
    void set_index_value(Decimal value);
    // the exponent index_value_denominator_code states, or 0 for a code it does not state
    static int index_value_exponent(char code);

    // Reserved 4: Four reserved bytes
    const std::array<std::byte, 4>& reserved_4() const;
    std::array<std::byte, 4>& reserved_4();
    void set_reserved_4(const std::array<std::byte, 4>& value);

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

    bool operator==(const UnderlyingValueLastSaleMessage& other) const;
    bool operator!=(const UnderlyingValueLastSaleMessage& other) const;

  private:
    char message_indicator_{};
    std::uint32_t transaction_id_{};
    std::uint32_t participant_reference_number_{};
    std::string security_symbol_{};
    std::array<std::byte, 1> reserved_1_{};
    IndexValueDenominatorCode index_value_denominator_code_{};
    Decimal index_value_{};
    std::array<std::byte, 4> reserved_4_{};
};

} // namespace siac::opra::output::obi::v6_2
