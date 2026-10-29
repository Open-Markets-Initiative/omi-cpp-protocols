#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../enums/BreachedLevel.hpp"
#include "../messages/FileMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2026 {

class FileMessageVisitor;

// Informs data recipients when a MWCB has breached one of the established levels
class FilePayloadMwcbStatusLevelMessage : public FileMessage {
  public:
    // The code that selects this message
    static constexpr FileMessageCode message_type = MessageType::MwcbStatusLevelMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 11;

    FilePayloadMwcbStatusLevelMessage() = default;
    FilePayloadMwcbStatusLevelMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, BreachedLevel breached_level);

    // Stock Locate: Locate Code uniquely assigned to the security symbol for the day
    std::uint16_t stock_locate() const;
    void set_stock_locate(std::uint16_t value);

    // Tracking Number: Nasdaq internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Breached Level: Denotes the MWCB Level that was breached
    BreachedLevel breached_level() const;
    void set_breached_level(BreachedLevel value);

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

    bool operator==(const FilePayloadMwcbStatusLevelMessage& other) const;
    bool operator!=(const FilePayloadMwcbStatusLevelMessage& other) const;

  private:
    std::uint16_t stock_locate_{};
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    BreachedLevel breached_level_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2026
