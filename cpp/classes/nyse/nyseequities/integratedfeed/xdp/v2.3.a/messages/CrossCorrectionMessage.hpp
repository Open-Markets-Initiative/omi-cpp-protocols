#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

class Visitor;

// In the event that an earlier Cross Trade has been reported in error, a Cross Correction
// message is sent.
class CrossCorrectionMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::CrossCorrectionMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 20;

    CrossCorrectionMessage() = default;
    CrossCorrectionMessage(std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint32_t cross_id, std::uint32_t volume);

    // Source Time Ns: The nanosecond offset from the SourceTime
    std::uint32_t source_time_ns() const;
    void set_source_time_ns(std::uint32_t value);

    // Symbol Index: The unique ID of this symbol for all products within this market. This ID
    // cannot be used to cross reference a security between markets.
    std::uint32_t symbol_index() const;
    void set_symbol_index(std::uint32_t value);

    // Symbol Seq Num: Reserved for future use. Ignore any content. This usage will become
    // standard across all products in future releases.
    std::uint32_t symbol_seq_num() const;
    void set_symbol_seq_num(std::uint32_t value);

    // Cross Id: Unique identifier for this Cross Trade. Used in Cross Correction message to
    // identify the Cross Trade to correct.
    std::uint32_t cross_id() const;
    void set_cross_id(std::uint32_t value);

    // Volume: The order quantity in shares
    std::uint32_t volume() const;
    void set_volume(std::uint32_t value);

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

    bool operator==(const CrossCorrectionMessage& other) const;
    bool operator!=(const CrossCorrectionMessage& other) const;

  private:
    std::uint32_t source_time_ns_{};
    std::uint32_t symbol_index_{};
    std::uint32_t symbol_seq_num_{};
    std::uint32_t cross_id_{};
    std::uint32_t volume_{};
};

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a
