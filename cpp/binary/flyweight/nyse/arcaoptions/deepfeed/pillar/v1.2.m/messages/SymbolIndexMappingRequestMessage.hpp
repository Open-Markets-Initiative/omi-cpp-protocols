#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/RetransmitMethod.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// Sent by clients via TCP/IP requesting the Symbol Index Mapping messages for one or all
// symbols in a specified channel.
class SymbolIndexMappingRequestMessage {
  public:
    static constexpr const char* name = "SymbolIndexMappingRequestMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SymbolIndexMappingRequestMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SymbolIndexMappingRequestMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 17;
    static constexpr std::size_t fixed_size = 17;
    std::size_t encoded_size() const { return 17; }

    std::uint32_t symbol_index() const { return wire::read_u32_le(at(0)); }

    std::string_view source_id() const { return view::text(at(4), 10, '\0'); }

    std::uint8_t product_id() const { return wire::read_u8(at(14)); }

    std::uint8_t channel_id() const { return wire::read_u8(at(15)); }

    RetransmitMethod retransmit_method() const { return static_cast<RetransmitMethod>(wire::read_u8(at(16))); }

    void print(std::ostream& out) const {
        out << "SymbolIndexMappingRequestMessage{";
        out << "symbol_index=";
        out << symbol_index();
        out << ", source_id=";
        print::text(out, source_id());
        out << ", product_id=";
        out << static_cast<int>(product_id());
        out << ", channel_id=";
        out << static_cast<int>(channel_id());
        out << ", retransmit_method=";
        out << retransmit_method();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SymbolIndexMappingRequestMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
