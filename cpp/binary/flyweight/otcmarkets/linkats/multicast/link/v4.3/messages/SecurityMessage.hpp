#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SecurityAction.hpp"
#include "../enums/AssetClass.hpp"
#include "../bitfields/SecurityFlags.hpp"
#include "../enums/Tier.hpp"
#include "../enums/ReportingStatus.hpp"
#include "../enums/SecurityStatus.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// The Security Message is included in all the quote channels and provides basic security
// attribute information.
class SecurityMessage {
  public:
    static constexpr const char* name = "SecurityMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SecurityMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SecurityMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    std::uint32_t channel_seq_num() const { return wire::read_u32_be(at(0)); }

    std::string_view symbol() const { return view::text(at(4), 10, ' '); }

    std::uint64_t last_update_milli() const { return wire::read_u64_be(at(14)); }

    SecurityAction security_action() const { return static_cast<SecurityAction>(wire::read_u8(at(22))); }

    AssetClass asset_class() const { return static_cast<AssetClass>(wire::read_u8(at(23))); }

    std::uint32_t security_id() const { return wire::read_u32_be(at(24)); }

    SecurityFlags security_flags() const { return SecurityFlags{ bytes_.subspan(28) }; }

    Tier tier() const { return static_cast<Tier>(wire::read_u8(at(29))); }

    ReportingStatus reporting_status() const { return static_cast<ReportingStatus>(wire::read_char(at(30))); }

    SecurityStatus security_status() const { return static_cast<SecurityStatus>(wire::read_char(at(31))); }

    void print(std::ostream& out) const {
        out << "SecurityMessage{";
        out << "channel_seq_num=";
        out << channel_seq_num();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", last_update_milli=";
        out << last_update_milli();
        out << ", security_action=";
        out << security_action();
        out << ", asset_class=";
        out << asset_class();
        out << ", security_id=";
        out << security_id();
        out << ", security_flags=";
        security_flags().print(out);
        out << ", tier=";
        out << tier();
        out << ", reporting_status=";
        out << reporting_status();
        out << ", security_status=";
        out << security_status();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SecurityMessage& value) {
    value.print(out);
    return out;
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
