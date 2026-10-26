#pragma once

#include <cstddef>
#include <memory>
#include <ostream>

#include "../messages/Payload.hpp"
#include "../structs/SbeHeader.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

class PayloadVisitor;

// Sbe Message
class SbeMessage {
  public:

    SbeMessage() = default;
    SbeMessage(const SbeMessage& other);
    SbeMessage& operator=(const SbeMessage& other);
    SbeMessage(SbeMessage&& other) noexcept = default;
    SbeMessage& operator=(SbeMessage&& other) noexcept = default;
    ~SbeMessage() = default;

    // Sbe Header: Sbe Header
    const SbeHeader& sbe_header() const;
    SbeHeader& sbe_header();
    void set_sbe_header(const SbeHeader& value);

    // Payload: Branch
    const Payload* payload() const;
    Payload* payload();
    void set_payload(std::unique_ptr<Payload> value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SbeMessage& other) const;
    bool operator!=(const SbeMessage& other) const;

  private:
    SbeHeader sbe_header_{};
    std::unique_ptr<Payload> payload_{};
};

std::ostream& operator<<(std::ostream& out, const SbeMessage& value);

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
