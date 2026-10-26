#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>

#include "../bitfields/FuturesFlags.hpp"
#include "../common/Decimal.hpp"
#include "../enums/ListingState.hpp"
#include "../groups/FutureLeg.hpp"
#include "../messages/Message.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

class Visitor;

// The Futures Instrument Definition message can be sent as a sequenced message or an
// un-sequenced message. It is sent as a sequenced message when the system starts up at the
// beginning of a trading session or an the instrument is created or modified during a trading
// day.
class FuturesInstrumentDefinitionMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::FuturesInstrumentDefinitionMessage;

    FuturesInstrumentDefinitionMessage() = default;
    FuturesInstrumentDefinitionMessage(std::chrono::nanoseconds time_offset, const std::string& symbol, std::uint32_t unit_timestamp, const std::string& report_symbol, const FuturesFlags& futures_flags, std::uint32_t expiration_date, std::uint16_t contract_size, ListingState listing_state, Decimal price_increment, std::uint8_t leg_count, std::uint8_t leg_offset, std::uint8_t reserved_1, std::uint32_t contract_date, const std::vector<FutureLeg>& future_leg);

    // Time Offset: Nanosecond offset from last unit timestamp.
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Symbol: Six character, base 62 symbol.
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Unit Timestamp: Unit timestamp expressed as number of whole seconds since the Epoch
    // (Midnight, January 1, 1970 UTC).
    std::uint32_t unit_timestamp() const;
    void set_unit_timestamp(std::uint32_t value);

    // Report Symbol: Symbol for product or underlying security.
    const std::string& report_symbol() const;
    std::string& report_symbol();
    void set_report_symbol(const std::string& value);

    // Futures Flags: Futures Flags bitfields
    const FuturesFlags& futures_flags() const;
    FuturesFlags& futures_flags();
    void set_futures_flags(const FuturesFlags& value);

    // Expiration Date: Expiration Date of Instrument.
    std::uint32_t expiration_date() const;
    void set_expiration_date(std::uint32_t value);

    // Contract Size: Contract size of Instrument. Contract sizes less than 1 are represented
    // with a 0 value; refer to the product specification for the contract size.
    std::uint16_t contract_size() const;
    void set_contract_size(std::uint16_t value);

    // Listing State: Listing State Values
    ListingState listing_state() const;
    void set_listing_state(ListingState value);

    // Price Increment: Minimum Price Increment.
    Decimal price_increment() const;
    void set_price_increment(Decimal value);

    // Leg Count: Values greater than 0 indicate this is a spread instrument.
    std::uint8_t leg_count() const;
    void set_leg_count(std::uint8_t value);

    // Leg Offset: Leg definitions, if any, begin at this offset from the beginning of the
    // message. Possible values are 0 (no legs present) or 45 (spread instrument).
    std::uint8_t leg_offset() const;
    void set_leg_offset(std::uint8_t value);

    // Reserved 1: Reserved. Value will always be zero.
    std::uint8_t reserved_1() const;
    void set_reserved_1(std::uint8_t value);

    // Contract Date: Populated for single leg instruments only. Zero-filled for spread
    // instruments. The date that should be used in describing the future's third party symbol
    // and the measurement period of the contract.
    std::uint32_t contract_date() const;
    void set_contract_date(std::uint32_t value);

    // Future Leg: Future Leg
    const std::vector<FutureLeg>& future_leg() const;
    std::vector<FutureLeg>& future_leg();
    void set_future_leg(const std::vector<FutureLeg>& value);

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

    bool operator==(const FuturesInstrumentDefinitionMessage& other) const;
    bool operator!=(const FuturesInstrumentDefinitionMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::string symbol_{};
    std::uint32_t unit_timestamp_{};
    std::string report_symbol_{};
    FuturesFlags futures_flags_{};
    std::uint32_t expiration_date_{};
    std::uint16_t contract_size_{};
    ListingState listing_state_{};
    Decimal price_increment_{ 0, -4 };
    std::uint8_t leg_count_{};
    std::uint8_t leg_offset_{};
    std::uint8_t reserved_1_{};
    std::uint32_t contract_date_{};
    std::vector<FutureLeg> future_leg_{};
};

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
