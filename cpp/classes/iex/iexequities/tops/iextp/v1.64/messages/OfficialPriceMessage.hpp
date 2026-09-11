#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/PriceType.hpp"
#include "../messages/Message.hpp"

namespace iex::iexequities::tops::iextp::v1_64 {

class Visitor;

// Official Price Messages are sent for each IEX-listed security to indicate the IEX Official
// Opening Price and IEX Official Closing Price.
class OfficialPriceMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OfficialPriceMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 25;

    OfficialPriceMessage() = default;
    OfficialPriceMessage(PriceType price_type, std::chrono::nanoseconds timestamp, const std::string& symbol, Decimal official_price);

    // Price Type: Price type identifier
    PriceType price_type() const;
    void set_price_type(PriceType value);

    // Timestamp: Time stamp of the system event
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Symbol: Security identifier
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Official Price: Official opening or closing price, as specified
    Decimal official_price() const;
    void set_official_price(Decimal value);

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

    bool operator==(const OfficialPriceMessage& other) const;
    bool operator!=(const OfficialPriceMessage& other) const;

  private:
    PriceType price_type_{};
    std::chrono::nanoseconds timestamp_{};
    std::string symbol_{};
    Decimal official_price_{ 0, -4 };
};

} // namespace iex::iexequities::tops::iextp::v1_64
