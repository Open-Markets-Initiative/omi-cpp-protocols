#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

class Visitor;

// Auction Cancel messages are used to disseminate the cancelation of an earlier Auction
// Notification message as a result of a user cancelation of the original complex auction, a
// user modification request to change the complex auction price or increase the original
// complex auction quantity, a fading of the NBBO or to cancel any remaining complex auction
// quantity from the original Auction Notification following the complex auction termination.
class AuctionCancelMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::AuctionCancelMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 12;

    AuctionCancelMessage() = default;
    AuctionCancelMessage(std::chrono::nanoseconds time_offset, std::uint64_t auction_id);

    // Time Offset: Nanosecond offset from last unit timestamp
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Auction Id: Day specific identifier assigned to this auction.
    std::uint64_t auction_id() const;
    void set_auction_id(std::uint64_t value);

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

    bool operator==(const AuctionCancelMessage& other) const;
    bool operator!=(const AuctionCancelMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::uint64_t auction_id_{};
};

} // namespace cboe::c1options::complex::pitch::v2_1_18
