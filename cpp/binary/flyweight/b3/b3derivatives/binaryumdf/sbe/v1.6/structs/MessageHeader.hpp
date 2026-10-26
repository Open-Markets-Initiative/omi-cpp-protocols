#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/TemplateId.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// B3 Sbe message header — message identifiers and length of message root
class MessageHeader {
  public:
    static constexpr const char* name = "MessageHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MessageHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MessageHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 8;
    static constexpr std::size_t fixed_size = 8;
    std::size_t encoded_size() const { return 8; }

    std::uint16_t block_length() const { return wire::read_u16_le(at(0)); }

    TemplateId template_id() const { return static_cast<TemplateId>(wire::read_u16_le(at(2))); }

    std::uint16_t schema_id() const { return wire::read_u16_le(at(4)); }

    std::uint16_t version() const { return wire::read_u16_le(at(6)); }

    void print(std::ostream& out) const {
        out << "MessageHeader{";
        out << "block_length=";
        out << block_length();
        out << ", template_id=";
        out << template_id();
        out << ", schema_id=";
        out << schema_id();
        out << ", version=";
        out << version();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MessageHeader& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
