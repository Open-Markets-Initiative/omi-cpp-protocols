#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g {

// Sequence number fields that only the full Refresh Header carries.
class FullRefreshHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 8;

    FullRefreshHeader() = default;
    FullRefreshHeader(std::uint32_t last_seq_num, std::uint32_t last_symbol_seq_num);

    // Last Seq Num: The last sequence number sent on the channel for any symbol. The refresh
    // is the state of the order book as of this sequence number.
    std::uint32_t last_seq_num() const;
    void set_last_seq_num(std::uint32_t value);

    // Last Symbol Seq Num: The last symbol sequence number sent for this symbol. The refresh
    // is the symbol state of this symbol as of this symbol sequence number.
    std::uint32_t last_symbol_seq_num() const;
    void set_last_symbol_seq_num(std::uint32_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const FullRefreshHeader& other) const;
    bool operator!=(const FullRefreshHeader& other) const;

  private:
    std::uint32_t last_seq_num_{};
    std::uint32_t last_symbol_seq_num_{};
};

std::ostream& operator<<(std::ostream& out, const FullRefreshHeader& value);

} // namespace nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g
