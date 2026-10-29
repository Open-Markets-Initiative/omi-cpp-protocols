#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// ExecutionReport_TradeMessage
class ImpliedEventId {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 6;

    ImpliedEventId() = default;
    ImpliedEventId(std::uint32_t event_id, std::uint16_t no_related_trades);

    // Event Id: eventID
    std::uint32_t event_id() const;
    void set_event_id(std::uint32_t value);

    // No Related Trades: noRelatedTrades
    std::uint16_t no_related_trades() const;
    void set_no_related_trades(std::uint16_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const ImpliedEventId& other) const;
    bool operator!=(const ImpliedEventId& other) const;

  private:
    std::uint32_t event_id_{};
    std::uint16_t no_related_trades_{};
};

std::ostream& operator<<(std::ostream& out, const ImpliedEventId& value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
