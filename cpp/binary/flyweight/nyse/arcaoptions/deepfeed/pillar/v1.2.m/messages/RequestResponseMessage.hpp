#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/Status.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// Sent immediately via TCP/IP in response to the client's request for retransmission, refresh
// or Symbol Mapping messages.
class RequestResponseMessage {
  public:
    static constexpr const char* name = "RequestResponseMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RequestResponseMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RequestResponseMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 25;
    static constexpr std::size_t fixed_size = 25;
    std::size_t encoded_size() const { return 25; }

    std::uint32_t request_seq_num() const { return wire::read_u32_le(at(0)); }

    std::uint32_t begin_seq_num() const { return wire::read_u32_le(at(4)); }

    std::uint32_t end_seq_num() const { return wire::read_u32_le(at(8)); }

    std::string_view source_id() const { return view::text(at(12), 10, '\0'); }

    std::uint8_t product_id() const { return wire::read_u8(at(22)); }

    std::uint8_t channel_id() const { return wire::read_u8(at(23)); }

    Status status() const { return static_cast<Status>(wire::read_char(at(24))); }

    void print(std::ostream& out) const {
        out << "RequestResponseMessage{";
        out << "request_seq_num=";
        out << request_seq_num();
        out << ", begin_seq_num=";
        out << begin_seq_num();
        out << ", end_seq_num=";
        out << end_seq_num();
        out << ", source_id=";
        print::text(out, source_id());
        out << ", product_id=";
        out << static_cast<int>(product_id());
        out << ", channel_id=";
        out << static_cast<int>(channel_id());
        out << ", status=";
        out << status();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RequestResponseMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
