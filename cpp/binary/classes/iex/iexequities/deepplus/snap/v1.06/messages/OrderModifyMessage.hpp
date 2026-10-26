#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../bitfields/ModifyFlags.hpp"
#include "../common/Decimal.hpp"
#include "../messages/IexTpMessageData.hpp"

namespace iex::iexequities::deepplus::snap::v1_06 {

class IexTpMessageDataVisitor;

// A displayed order that had its Price, Size, or Priority component changed as a result of
// user or system action
class OrderModifyMessage : public IexTpMessageData {
  public:
    // The code that selects this message
    static constexpr IexTpMessageDataCode message_type = IexTpMessageType::OrderModifyMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 37;

    OrderModifyMessage() = default;
    OrderModifyMessage(const ModifyFlags& modify_flags, std::chrono::nanoseconds timestamp, const std::string& symbol, std::uint64_t order_id_reference, std::uint32_t size, Decimal price);

    // Modify Flags: Modify Flags
    const ModifyFlags& modify_flags() const;
    ModifyFlags& modify_flags();
    void set_modify_flags(const ModifyFlags& value);

    // Timestamp: Time stamp of the system event
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Symbol: Security identifier
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Order Id Reference: Order ID of the referenced order
    std::uint64_t order_id_reference() const;
    void set_order_id_reference(std::uint64_t value);

    // Size: Quoted size
    std::uint32_t size() const;
    void set_size(std::uint32_t value);

    // Price: Booking price on the IEX Order Book
    Decimal price() const;
    void set_price(Decimal value);

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

    bool operator==(const OrderModifyMessage& other) const;
    bool operator!=(const OrderModifyMessage& other) const;

  private:
    ModifyFlags modify_flags_{};
    std::chrono::nanoseconds timestamp_{};
    std::string symbol_{};
    std::uint64_t order_id_reference_{};
    std::uint32_t size_{};
    Decimal price_{ 0, -4 };
};

} // namespace iex::iexequities::deepplus::snap::v1_06
