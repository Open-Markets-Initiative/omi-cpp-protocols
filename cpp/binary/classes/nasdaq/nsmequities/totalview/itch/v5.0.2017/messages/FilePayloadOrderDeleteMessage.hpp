#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../messages/FileMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

class FileMessageVisitor;

// This message is sent whenever an order on the book is being cancelled. All remaining shares
// are no longer accessible so the order must be removed from the book.
class FilePayloadOrderDeleteMessage : public FileMessage {
  public:
    // The code that selects this message
    static constexpr FileMessageCode message_type = MessageType::OrderDeleteMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 18;

    FilePayloadOrderDeleteMessage() = default;
    FilePayloadOrderDeleteMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t order_reference_number);

    // Stock Locate: Always 0
    std::uint16_t stock_locate() const;
    void set_stock_locate(std::uint16_t value);

    // Tracking Number: NASDAQ OMX internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight.
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Order Reference Number: The unique reference number assigned to the new order at the
    // time of receipt.
    std::uint64_t order_reference_number() const;
    void set_order_reference_number(std::uint64_t value);

    // FileMessage
    FileMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(FileMessageVisitor& visitor) const override;
    std::unique_ptr<FileMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const FileMessage& other) const override;

    bool operator==(const FilePayloadOrderDeleteMessage& other) const;
    bool operator!=(const FilePayloadOrderDeleteMessage& other) const;

  private:
    std::uint16_t stock_locate_{};
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t order_reference_number_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2017
