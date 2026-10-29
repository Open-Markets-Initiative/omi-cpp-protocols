#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../bitfields/SecurityFlags.hpp"
#include "../common/Decimal.hpp"
#include "../enums/AssetClass.hpp"
#include "../enums/DisclosureStatus.hpp"
#include "../enums/ReportingStatus.hpp"
#include "../enums/SecurityAction.hpp"
#include "../enums/SecurityStatus.hpp"
#include "../enums/Tier.hpp"
#include "../messages/Message.hpp"
#include "../structs/Issuer.hpp"
#include "../structs/SecurityDetail.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

class Visitor;

// Extended Security message without CUSIP information. This message may be sent at system
// startup or intraday following a technical outage.
class ExtendedSecurityNoCusipMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ExtendedSecurityNoCusipMessage;

    ExtendedSecurityNoCusipMessage() = default;
    ExtendedSecurityNoCusipMessage(std::uint32_t channel_seq_num, const std::string& symbol, std::uint64_t last_update_milli, SecurityAction security_action, std::uint32_t otc_issuer_id, const std::string& security_desc, const std::string& short_name, AssetClass asset_class, const std::string& security_type, const std::string& primary_market, std::uint32_t security_id, const SecurityFlags& security_flags, Tier tier, ReportingStatus reporting_status, DisclosureStatus disclosure_status, SecurityStatus security_status, Decimal par_value, Decimal coupon, std::uint64_t maturity_date_milli, std::uint64_t callable_date_milli, Decimal adr_ratio, const std::string& adr_level, const SecurityDetail& security_detail, const Issuer& issuer);

    // Channel Seq Num: Monotonically increasing message sequence number at the channel level.
    std::uint32_t channel_seq_num() const;
    void set_channel_seq_num(std::uint32_t value);

    // Symbol: Ticker symbol. Fixed income symbols may not have a symbol. For these securities,
    // the security ID or CUSIP (Reference Data Security Message) must be used as an
    // identifier.
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Last Update Milli: Milliseconds from UTC epoch.
    std::uint64_t last_update_milli() const;
    void set_last_update_milli(std::uint64_t value);

    // Security Action: Security action indicator.
    SecurityAction security_action() const;
    void set_security_action(SecurityAction value);

    // Otc Issuer Id: Unique issuer ID.
    std::uint32_t otc_issuer_id() const;
    void set_otc_issuer_id(std::uint32_t value);

    // Security Desc: Security description.
    const std::string& security_desc() const;
    std::string& security_desc();
    void set_security_desc(const std::string& value);

    // Short Name: Short name of the security.
    const std::string& short_name() const;
    std::string& short_name();
    void set_short_name(const std::string& value);

    // Asset Class: Asset class indicator.
    AssetClass asset_class() const;
    void set_asset_class(AssetClass value);

    // Security Type: Indicates the type of security.
    const std::string& security_type() const;
    std::string& security_type();
    void set_security_type(const std::string& value);

    // Primary Market: Primary trading market or exchange.
    const std::string& primary_market() const;
    std::string& primary_market();
    void set_primary_market(const std::string& value);

    // Security Id: Unique security ID issued by OTC Markets.
    std::uint32_t security_id() const;
    void set_security_id(std::uint32_t value);

    // Security Flags: Notes security level attributes
    const SecurityFlags& security_flags() const;
    SecurityFlags& security_flags();
    void set_security_flags(const SecurityFlags& value);

    // Tier: The market tier assigned by OTC Markets Group.
    Tier tier() const;
    void set_tier(Tier value);

    // Reporting Status: Reporting status.
    ReportingStatus reporting_status() const;
    void set_reporting_status(ReportingStatus value);

    // Disclosure Status: Current disclosure status of the issuer.
    DisclosureStatus disclosure_status() const;
    void set_disclosure_status(DisclosureStatus value);

    // Security Status: Security status.
    SecurityStatus security_status() const;
    void set_security_status(SecurityStatus value);

    // Par Value: Par value with 6 decimal places assumed. 0 indicates not available.
    Decimal par_value() const;
    void set_par_value(Decimal value);

    // Coupon: Coupon with 6 decimal places assumed. Applies to fixed income securities only.
    Decimal coupon() const;
    void set_coupon(Decimal value);

    // Maturity Date Milli: Maturity date in milliseconds from UTC epoch. Applies to fixed
    // income securities only.
    std::uint64_t maturity_date_milli() const;
    void set_maturity_date_milli(std::uint64_t value);

    // Callable Date Milli: Callable date in milliseconds from UTC epoch. Applies to fixed
    // income securities only.
    std::uint64_t callable_date_milli() const;
    void set_callable_date_milli(std::uint64_t value);

    // Adr Ratio: ADR ratio with 6 decimal places assumed. Applies to ADR/GDR/NYRS securities
    // only.
    Decimal adr_ratio() const;
    void set_adr_ratio(Decimal value);

    // Adr Level: ADR level. Applies to ADR/GDR/NYRS securities only.
    const std::string& adr_level() const;
    std::string& adr_level();
    void set_adr_level(const std::string& value);

    // Security Detail: SecurityDetail
    const SecurityDetail& security_detail() const;
    SecurityDetail& security_detail();
    void set_security_detail(const SecurityDetail& value);

    // Issuer: Issuer
    const Issuer& issuer() const;
    Issuer& issuer();
    void set_issuer(const Issuer& value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const ExtendedSecurityNoCusipMessage& other) const;
    bool operator!=(const ExtendedSecurityNoCusipMessage& other) const;

  private:
    std::uint32_t channel_seq_num_{};
    std::string symbol_{};
    std::uint64_t last_update_milli_{};
    SecurityAction security_action_{};
    std::uint32_t otc_issuer_id_{};
    std::string security_desc_{};
    std::string short_name_{};
    AssetClass asset_class_{};
    std::string security_type_{};
    std::string primary_market_{};
    std::uint32_t security_id_{};
    SecurityFlags security_flags_{};
    Tier tier_{};
    ReportingStatus reporting_status_{};
    DisclosureStatus disclosure_status_{};
    SecurityStatus security_status_{};
    Decimal par_value_{ 0, -6 };
    Decimal coupon_{ 0, -6 };
    std::uint64_t maturity_date_milli_{};
    std::uint64_t callable_date_milli_{};
    Decimal adr_ratio_{ 0, -6 };
    std::string adr_level_{};
    SecurityDetail security_detail_{};
    Issuer issuer_{};
};

} // namespace otcmarkets::linkats::multicast::link::v4_3
