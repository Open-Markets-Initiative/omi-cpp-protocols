#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "messages/Message.hpp"
#include "structs/CommonHeader.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

class Visitor;

// A packet: the common header, and the one message they select. Decode reads a
// whole packet; encode writes one back, deriving its length and code from the message held.
class Packet {
  public:
    Packet() = default;
    explicit Packet(std::unique_ptr<Message> message);
    Packet(const Packet& other);
    Packet& operator=(const Packet& other);
    Packet(Packet&& other) noexcept = default;
    Packet& operator=(Packet&& other) noexcept = default;
    ~Packet() = default;

    // Common Header: Common Header
    const CommonHeader& common_header() const;
    CommonHeader& common_header();
    void set_common_header(const CommonHeader& value);

    // The message this packet carries, or null before one is set
    const Message* message() const;
    Message* message();
    void set_message(std::unique_ptr<Message> message);
    std::unique_ptr<Message> release();

    // Read a whole packet from the bytes at data, and return how many were consumed; throws DecodeError
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write a whole packet to the bytes at data, and return how many were written; throws EncodeError
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    std::size_t encoded_size() const;
    // Hand the message to the visitor
    void accept(Visitor& visitor) const;
    void print(std::ostream& out) const;

    // Same headers and, both present, the same message
    bool operator==(const Packet& other) const;
    bool operator!=(const Packet& other) const;

  private:
    CommonHeader common_header_{};
    std::unique_ptr<Message> message_;
};

std::ostream& operator<<(std::ostream& out, const Packet& packet);

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
