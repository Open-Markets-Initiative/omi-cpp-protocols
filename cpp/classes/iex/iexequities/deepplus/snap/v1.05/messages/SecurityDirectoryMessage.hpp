#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../bitfields/SecurityDirectoryFlags.hpp"
#include "../common/Decimal.hpp"
#include "../enums/LuldTier.hpp"
#include "../messages/IexTpMessageData.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

class IexTpMessageDataVisitor;

// The System Event Message is used to indicate events that apply to the market or the data
// feed.
class SecurityDirectoryMessage : public IexTpMessageData {
  public:
    // The code that selects this message
    static constexpr IexTpMessageDataCode message_type = IexTpMessageType::SecurityDirectoryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 30;

    SecurityDirectoryMessage() = default;
    SecurityDirectoryMessage(const SecurityDirectoryFlags& security_directory_flags, std::chrono::nanoseconds timestamp, const std::string& symbol, std::uint32_t round_lot_size, Decimal adjusted_poc_price, LuldTier luld_tier);

    // Security Directory Flags: Security Directory Flags
    const SecurityDirectoryFlags& security_directory_flags() const;
    SecurityDirectoryFlags& security_directory_flags();
    void set_security_directory_flags(const SecurityDirectoryFlags& value);

    // Timestamp: Time stamp of the system event
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Symbol: Security identifier
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Round Lot Size: Number of shares that represent a round lot
    std::uint32_t round_lot_size() const;
    void set_round_lot_size(std::uint32_t value);

    // Adjusted Poc Price: Corporate action adjusted previous official closing price
    Decimal adjusted_poc_price() const;
    void set_adjusted_poc_price(Decimal value);

    // Luld Tier: Indicates which Limit Up-Limit Down price band calculation parameter is to be
    // used
    LuldTier luld_tier() const;
    void set_luld_tier(LuldTier value);

    // IexTpMessageData
    IexTpMessageDataCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(IexTpMessageDataVisitor& visitor) const override;
    std::unique_ptr<IexTpMessageData> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const IexTpMessageData& other) const override;

    bool operator==(const SecurityDirectoryMessage& other) const;
    bool operator!=(const SecurityDirectoryMessage& other) const;

  private:
    SecurityDirectoryFlags security_directory_flags_{};
    std::chrono::nanoseconds timestamp_{};
    std::string symbol_{};
    std::uint32_t round_lot_size_{};
    Decimal adjusted_poc_price_{ 0, -4 };
    LuldTier luld_tier_{};
};

} // namespace iex::iexequities::deepplus::snap::v1_05
