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
#include "../bitfields/ExtendedSecurityFlags.hpp"
#include "../enums/Tier.hpp"
#include "../enums/ReportingStatus.hpp"
#include "../enums/DisclosureStatus.hpp"
#include "../enums/SecurityStatus.hpp"
#include "../common/Decimal.hpp"
#include "../structs/SecurityDetail.hpp"
#include "../structs/Issuer.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Extended Security message providing additional security and issuer attributes.
class ExtendedSecurityMessage {
  public:
    static constexpr const char* name = "ExtendedSecurityMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ExtendedSecurityMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ExtendedSecurityMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 160;
    std::size_t encoded_size() const { return cusip_end(); }

    std::uint32_t channel_seq_num() const { return wire::read_u32_be(at(0)); }

    std::string_view symbol() const { return view::text(at(4), 10, ' '); }

    std::uint64_t last_update_milli() const { return wire::read_u64_be(at(14)); }

    SecurityAction security_action() const { return static_cast<SecurityAction>(wire::read_u8(at(22))); }

    std::uint32_t otc_issuer_id() const { return wire::read_u32_be(at(23)); }

    std::string_view security_desc() const { return view::text(at(27), 25, ' '); }

    std::string_view short_name() const { return view::text(at(52), 25, ' '); }

    AssetClass asset_class() const { return static_cast<AssetClass>(wire::read_u8(at(77))); }

    std::string_view security_type() const { return view::text(at(78), 5, ' '); }

    std::string_view primary_market() const { return view::text(at(83), 3, ' '); }

    std::uint32_t security_id() const { return wire::read_u32_be(at(86)); }

    ExtendedSecurityFlags extended_security_flags() const { return ExtendedSecurityFlags{ bytes_.subspan(90) }; }

    Tier tier() const { return static_cast<Tier>(wire::read_u8(at(92))); }

    ReportingStatus reporting_status() const { return static_cast<ReportingStatus>(wire::read_char(at(93))); }

    DisclosureStatus disclosure_status() const { return static_cast<DisclosureStatus>(wire::read_u8(at(94))); }

    SecurityStatus security_status() const { return static_cast<SecurityStatus>(wire::read_char(at(95))); }

    Decimal par_value() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(96))), -6); }

    Decimal coupon() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(104))), -6); }

    std::uint64_t maturity_date_milli() const { return wire::read_u64_be(at(112)); }

    std::uint64_t callable_date_milli() const { return wire::read_u64_be(at(120)); }

    Decimal adr_ratio() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(128))), -6); }

    std::string_view adr_level() const { return view::text(at(136), 15, ' '); }

    SecurityDetail security_detail() const { return SecurityDetail{ bytes_.subspan(151) }; }

    Issuer issuer() const {
        wire::require("ExtendedSecurityMessage", security_detail_end() + Issuer::minimum_size, bytes_.size());
        return Issuer{ bytes_.subspan(security_detail_end()) };
    }

    std::string_view cusip() const {
        wire::require("ExtendedSecurityMessage", issuer_end() + 9, bytes_.size());
        return view::text(at(issuer_end()), 9, ' ');
    }

    void print(std::ostream& out) const {
        out << "ExtendedSecurityMessage{";
        out << "channel_seq_num=";
        out << channel_seq_num();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", last_update_milli=";
        out << last_update_milli();
        out << ", security_action=";
        out << security_action();
        out << ", otc_issuer_id=";
        out << otc_issuer_id();
        out << ", security_desc=";
        print::text(out, security_desc());
        out << ", short_name=";
        print::text(out, short_name());
        out << ", asset_class=";
        out << asset_class();
        out << ", security_type=";
        print::text(out, security_type());
        out << ", primary_market=";
        print::text(out, primary_market());
        out << ", security_id=";
        out << security_id();
        out << ", extended_security_flags=";
        extended_security_flags().print(out);
        out << ", tier=";
        out << tier();
        out << ", reporting_status=";
        out << reporting_status();
        out << ", disclosure_status=";
        out << disclosure_status();
        out << ", security_status=";
        out << security_status();
        out << ", par_value=";
        out << par_value();
        out << ", coupon=";
        out << coupon();
        out << ", maturity_date_milli=";
        out << maturity_date_milli();
        out << ", callable_date_milli=";
        out << callable_date_milli();
        out << ", adr_ratio=";
        out << adr_ratio();
        out << ", adr_level=";
        print::text(out, adr_level());
        out << ", security_detail=";
        security_detail().print(out);
        out << ", issuer=";
        issuer().print(out);
        out << ", cusip=";
        print::text(out, cusip());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t security_detail_end() const { return 151 + security_detail().encoded_size(); }
    std::size_t issuer_end() const { return security_detail_end() + issuer().encoded_size(); }
    std::size_t cusip_end() const { return issuer_end() + 9; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ExtendedSecurityMessage& value) {
    value.print(out);
    return out;
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
