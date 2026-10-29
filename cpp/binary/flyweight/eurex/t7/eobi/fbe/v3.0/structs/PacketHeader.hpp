#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/EobiHeader.hpp"
#include "../enums/CompletionIndicator.hpp"
#include "../enums/ApplSeqResetIndicator.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

// Eurex Eobi Packet Header
class PacketHeader {
  public:
    static constexpr const char* name = "PacketHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PacketHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PacketHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    EobiHeader eobi_header() const { return EobiHeader{ bytes_.subspan(0) }; }

    std::uint32_t appl_seq_num() const { return wire::read_u32_le(at(8)); }

    std::optional<std::int32_t> market_segment_id() const { return wire::nullable(wire::read_i32_le(at(12)), static_cast<std::int32_t>(0x80000000LL)); }

    std::optional<std::uint8_t> partition_id() const { return wire::nullable(wire::read_u8(at(16)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<CompletionIndicator> completion_indicator() const { return wire::nullable_enum<CompletionIndicator>(wire::read_u8(at(17)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<ApplSeqResetIndicator> appl_seq_reset_indicator() const { return wire::nullable_enum<ApplSeqResetIndicator>(wire::read_u8(at(18)), static_cast<std::uint8_t>(0xFFULL)); }

    std::span<const std::byte, 5> pad5() const { return bytes_.subspan(19).template first<5>(); }

    std::optional<std::chrono::nanoseconds> transact_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(24)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    void print(std::ostream& out) const {
        out << "PacketHeader{";
        out << "eobi_header=";
        eobi_header().print(out);
        out << ", appl_seq_num=";
        out << appl_seq_num();
        out << ", market_segment_id=";
        print::optional(out, market_segment_id());
        out << ", partition_id=";
        print::optional(out, partition_id());
        out << ", completion_indicator=";
        print::optional(out, completion_indicator());
        out << ", appl_seq_reset_indicator=";
        print::optional(out, appl_seq_reset_indicator());
        out << ", pad5=";
        print::hex(out, pad5().data(), pad5().size());
        out << ", transact_time=";
        print::optional_duration(out, transact_time());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v3_0
