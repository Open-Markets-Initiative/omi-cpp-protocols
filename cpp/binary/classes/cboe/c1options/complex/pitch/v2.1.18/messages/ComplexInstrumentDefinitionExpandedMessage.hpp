#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>

#include "../groups/ComplexInstrumentLeg.hpp"
#include "../messages/Message.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

class Visitor;

// A Complex Instrument Definition Expanded message represents a complex instrument that is
// available to place orders.
class ComplexInstrumentDefinitionExpandedMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ComplexInstrumentDefinitionExpandedMessage;

    ComplexInstrumentDefinitionExpandedMessage() = default;
    ComplexInstrumentDefinitionExpandedMessage(std::chrono::nanoseconds time_offset, const std::string& complex_instrument_id, const std::string& complex_instrument_underlying, const std::string& complex_instrument_type, std::uint8_t leg_count, const std::vector<ComplexInstrumentLeg>& complex_instrument_leg);

    // Time Offset: Nanosecond offset from last unit timestamp
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Complex Instrument Id: Complex Instrument Id right padded with spaces.
    const std::string& complex_instrument_id() const;
    std::string& complex_instrument_id();
    void set_complex_instrument_id(const std::string& value);

    // Complex Instrument Underlying: Complex Instrument Underlying right padded with spaces.
    const std::string& complex_instrument_underlying() const;
    std::string& complex_instrument_underlying();
    void set_complex_instrument_underlying(const std::string& value);

    // Complex Instrument Type: 4 character field; each field describes a characteristic.
    const std::string& complex_instrument_type() const;
    std::string& complex_instrument_type();
    void set_complex_instrument_type(const std::string& value);

    // Leg Count: The number of legs in the complex instrument. The maximum number of legs is
    // 12.
    std::uint8_t leg_count() const;
    void set_leg_count(std::uint8_t value);

    // Complex Instrument Leg: Leg for multi-leg strategies
    const std::vector<ComplexInstrumentLeg>& complex_instrument_leg() const;
    std::vector<ComplexInstrumentLeg>& complex_instrument_leg();
    void set_complex_instrument_leg(const std::vector<ComplexInstrumentLeg>& value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const ComplexInstrumentDefinitionExpandedMessage& other) const;
    bool operator!=(const ComplexInstrumentDefinitionExpandedMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::string complex_instrument_id_{};
    std::string complex_instrument_underlying_{};
    std::string complex_instrument_type_{};
    std::uint8_t leg_count_{};
    std::vector<ComplexInstrumentLeg> complex_instrument_leg_{};
};

} // namespace cboe::c1options::complex::pitch::v2_1_18
