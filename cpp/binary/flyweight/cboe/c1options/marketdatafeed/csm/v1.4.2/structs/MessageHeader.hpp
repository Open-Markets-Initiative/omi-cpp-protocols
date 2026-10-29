#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/TemplateId.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

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

    std::uint16_t message_length() const { return wire::read_u16_be(at(0)); }

    TemplateId template_id() const { return static_cast<TemplateId>(wire::read_u8(at(2))); }

    char message_type() const { return wire::read_char(at(3)); }

    std::uint32_t msg_seq_num() const { return wire::read_u32_be(at(4)); }

    void print(std::ostream& out) const {
        out << "MessageHeader{";
        out << "message_length=";
        out << message_length();
        out << ", template_id=";
        out << template_id();
        out << ", message_type=";
        print::character(out, message_type());
        out << ", msg_seq_num=";
        out << msg_seq_num();
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

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
