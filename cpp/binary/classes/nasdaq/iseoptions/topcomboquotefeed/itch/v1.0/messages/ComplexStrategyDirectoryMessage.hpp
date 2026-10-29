#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>

#include "../common/Day.hpp"
#include "../enums/StrategyType.hpp"
#include "../groups/LegInformation.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

class Visitor;

// Whenever a complex order is added in the system for an underlying, the order is normalized
// and results in either the creation of a new complex strategy or is added to an existing
// strategy. A Complex Strategy Message containing the strategy definition will be sent.
class ComplexStrategyDirectoryMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ComplexStrategyDirectoryMessage;

    ComplexStrategyDirectoryMessage() = default;
    ComplexStrategyDirectoryMessage(std::chrono::nanoseconds timestamp, std::uint32_t strategy_id, StrategyType strategy_type, std::uint8_t source, const std::string& underlying_symbol, std::uint8_t number_of_legs, const std::vector<LegInformation>& leg_information);

    // Timestamp: The time, expressed as the number of nanoseconds after midnight.
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Strategy Id: ISE’s Strategy ID assigned daily, valid while there are any open complex
    // orders for the day
    std::uint32_t strategy_id() const;
    void set_strategy_id(std::uint32_t value);

    // Strategy Type: StrategyType value
    StrategyType strategy_type() const;
    void set_strategy_type(StrategyType value);

    // Source: Identifies the source of the Strategy, valid for the trading day
    std::uint8_t source() const;
    void set_source(std::uint8_t value);

    // Underlying Symbol: Underlying Symbol for the strategy. All legs in this strategy belong
    // to this Underlying
    const std::string& underlying_symbol() const;
    std::string& underlying_symbol();
    void set_underlying_symbol(const std::string& value);

    // Number Of Legs: Number of legs in the strategy NOTE: Leg field offsets below are an
    // equation, where “n” is the zero based leg number (0, 1, …)
    std::uint8_t number_of_legs() const;
    void set_number_of_legs(std::uint8_t value);

    // Leg Information: Leg information
    const std::vector<LegInformation>& leg_information() const;
    std::vector<LegInformation>& leg_information();
    void set_leg_information(const std::vector<LegInformation>& value);

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

    bool operator==(const ComplexStrategyDirectoryMessage& other) const;
    bool operator!=(const ComplexStrategyDirectoryMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint32_t strategy_id_{};
    StrategyType strategy_type_{};
    std::uint8_t source_{};
    std::string underlying_symbol_{};
    std::uint8_t number_of_legs_{};
    std::vector<LegInformation> leg_information_{};
};

} // namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0
