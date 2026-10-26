#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/TemplateId.hpp"
#include "../messages/ChannelReset.hpp"
#include "../messages/AdminHeartbeat.hpp"
#include "../messages/AdminLogin.hpp"
#include "../messages/AdminLogout.hpp"
#include "../messages/SecurityStatus.hpp"
#include "../messages/MdIncrementalRefreshVolume.hpp"
#include "../messages/QuoteRequest.hpp"
#include "../messages/MdIncrementalRefreshBook.hpp"
#include "../messages/MdIncrementalRefreshOrderBook.hpp"
#include "../messages/MdIncrementalRefreshTradeSummary.hpp"
#include "../messages/MdIncrementalRefreshDailyStatistics.hpp"
#include "../messages/MdIncrementalRefreshLimitsBanding.hpp"
#include "../messages/MdIncrementalRefreshSessionStatistics.hpp"
#include "../messages/SnapshotFullRefresh.hpp"
#include "../messages/SnapshotFullRefreshOrderBook.hpp"
#include "../messages/MdInstrumentDefinitionFuture.hpp"
#include "../messages/MdInstrumentDefinitionOption.hpp"
#include "../messages/MdInstrumentDefinitionSpread.hpp"
#include "../messages/MdInstrumentDefinitionFixedIncome.hpp"
#include "../messages/MdInstrumentDefinitionRepo.hpp"
#include "../messages/SnapshotRefreshTopOrders.hpp"
#include "../messages/SecurityStatusWorkup.hpp"
#include "../messages/SnapshotFullRefreshTcp.hpp"
#include "../messages/CollateralMarketValue.hpp"
#include "../messages/MdInstrumentDefinitionFx.hpp"
#include "../messages/MdIncrementalRefreshBookLongQty.hpp"
#include "../messages/MdIncrementalRefreshTradeSummaryLongQty.hpp"
#include "../messages/MdIncrementalRefreshVolumeLongQty.hpp"
#include "../messages/MdIncrementalRefreshSessionStatisticsLongQty.hpp"
#include "../messages/SnapshotFullRefreshTcpLongQty.hpp"
#include "../messages/SnapshotFullRefreshLongQty.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// Message of sbe schema mktdata (schema id 1)
class MktdataMessage {
  public:
    static constexpr const char* name = "MktdataMessage";

    // the bytes it reads, which it does not own: they must outlive it
    // and the fields of the frame around it a branch in it switches on
    MktdataMessage(std::span<const std::byte> bytes, TemplateId template_id) noexcept
      : bytes_{ bytes }, template_id_{ template_id } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MktdataMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 0;
    std::size_t encoded_size() const { return mktdata_payload_end(); }

    // the bytes the message it selects is read from
    std::span<const std::byte> mktdata_payload_bytes() const {
        wire::require("MktdataMessage", 0, bytes_.size());
        return bytes_.subspan(0);
    }

    // the message its template_id selects, handed to the handler as its view
    template <typename Handler>
    void mktdata_payload(Handler& handler) const {
        const auto bytes = mktdata_payload_bytes();
        switch (template_id_) {
            case TemplateId::ChannelReset: {
                wire::require(ChannelReset::name, ChannelReset::minimum_size, bytes.size());
                const ChannelReset message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::AdminHeartbeat: {
                wire::require(AdminHeartbeat::name, AdminHeartbeat::minimum_size, bytes.size());
                const AdminHeartbeat message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::AdminLogin: {
                wire::require(AdminLogin::name, AdminLogin::minimum_size, bytes.size());
                const AdminLogin message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::AdminLogout: {
                wire::require(AdminLogout::name, AdminLogout::minimum_size, bytes.size());
                const AdminLogout message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::SecurityStatus: {
                wire::require(SecurityStatus::name, SecurityStatus::minimum_size, bytes.size());
                const SecurityStatus message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::MdIncrementalRefreshVolume: {
                wire::require(MdIncrementalRefreshVolume::name, MdIncrementalRefreshVolume::minimum_size, bytes.size());
                const MdIncrementalRefreshVolume message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::QuoteRequest: {
                wire::require(QuoteRequest::name, QuoteRequest::minimum_size, bytes.size());
                const QuoteRequest message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::MdIncrementalRefreshBook: {
                wire::require(MdIncrementalRefreshBook::name, MdIncrementalRefreshBook::minimum_size, bytes.size());
                const MdIncrementalRefreshBook message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::MdIncrementalRefreshOrderBook: {
                wire::require(MdIncrementalRefreshOrderBook::name, MdIncrementalRefreshOrderBook::minimum_size, bytes.size());
                const MdIncrementalRefreshOrderBook message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::MdIncrementalRefreshTradeSummary: {
                wire::require(MdIncrementalRefreshTradeSummary::name, MdIncrementalRefreshTradeSummary::minimum_size, bytes.size());
                const MdIncrementalRefreshTradeSummary message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::MdIncrementalRefreshDailyStatistics: {
                wire::require(MdIncrementalRefreshDailyStatistics::name, MdIncrementalRefreshDailyStatistics::minimum_size, bytes.size());
                const MdIncrementalRefreshDailyStatistics message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::MdIncrementalRefreshLimitsBanding: {
                wire::require(MdIncrementalRefreshLimitsBanding::name, MdIncrementalRefreshLimitsBanding::minimum_size, bytes.size());
                const MdIncrementalRefreshLimitsBanding message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::MdIncrementalRefreshSessionStatistics: {
                wire::require(MdIncrementalRefreshSessionStatistics::name, MdIncrementalRefreshSessionStatistics::minimum_size, bytes.size());
                const MdIncrementalRefreshSessionStatistics message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::SnapshotFullRefresh: {
                wire::require(SnapshotFullRefresh::name, SnapshotFullRefresh::minimum_size, bytes.size());
                const SnapshotFullRefresh message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::SnapshotFullRefreshOrderBook: {
                wire::require(SnapshotFullRefreshOrderBook::name, SnapshotFullRefreshOrderBook::minimum_size, bytes.size());
                const SnapshotFullRefreshOrderBook message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::MdInstrumentDefinitionFuture: {
                wire::require(MdInstrumentDefinitionFuture::name, MdInstrumentDefinitionFuture::minimum_size, bytes.size());
                const MdInstrumentDefinitionFuture message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::MdInstrumentDefinitionOption: {
                wire::require(MdInstrumentDefinitionOption::name, MdInstrumentDefinitionOption::minimum_size, bytes.size());
                const MdInstrumentDefinitionOption message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::MdInstrumentDefinitionSpread: {
                wire::require(MdInstrumentDefinitionSpread::name, MdInstrumentDefinitionSpread::minimum_size, bytes.size());
                const MdInstrumentDefinitionSpread message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::MdInstrumentDefinitionFixedIncome: {
                wire::require(MdInstrumentDefinitionFixedIncome::name, MdInstrumentDefinitionFixedIncome::minimum_size, bytes.size());
                const MdInstrumentDefinitionFixedIncome message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::MdInstrumentDefinitionRepo: {
                wire::require(MdInstrumentDefinitionRepo::name, MdInstrumentDefinitionRepo::minimum_size, bytes.size());
                const MdInstrumentDefinitionRepo message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::SnapshotRefreshTopOrders: {
                wire::require(SnapshotRefreshTopOrders::name, SnapshotRefreshTopOrders::minimum_size, bytes.size());
                const SnapshotRefreshTopOrders message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::SecurityStatusWorkup: {
                wire::require(SecurityStatusWorkup::name, SecurityStatusWorkup::minimum_size, bytes.size());
                const SecurityStatusWorkup message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::SnapshotFullRefreshTcp: {
                wire::require(SnapshotFullRefreshTcp::name, SnapshotFullRefreshTcp::minimum_size, bytes.size());
                const SnapshotFullRefreshTcp message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::CollateralMarketValue: {
                wire::require(CollateralMarketValue::name, CollateralMarketValue::minimum_size, bytes.size());
                const CollateralMarketValue message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::MdInstrumentDefinitionFx: {
                wire::require(MdInstrumentDefinitionFx::name, MdInstrumentDefinitionFx::minimum_size, bytes.size());
                const MdInstrumentDefinitionFx message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::MdIncrementalRefreshBookLongQty: {
                wire::require(MdIncrementalRefreshBookLongQty::name, MdIncrementalRefreshBookLongQty::minimum_size, bytes.size());
                const MdIncrementalRefreshBookLongQty message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::MdIncrementalRefreshTradeSummaryLongQty: {
                wire::require(MdIncrementalRefreshTradeSummaryLongQty::name, MdIncrementalRefreshTradeSummaryLongQty::minimum_size, bytes.size());
                const MdIncrementalRefreshTradeSummaryLongQty message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::MdIncrementalRefreshVolumeLongQty: {
                wire::require(MdIncrementalRefreshVolumeLongQty::name, MdIncrementalRefreshVolumeLongQty::minimum_size, bytes.size());
                const MdIncrementalRefreshVolumeLongQty message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::MdIncrementalRefreshSessionStatisticsLongQty: {
                wire::require(MdIncrementalRefreshSessionStatisticsLongQty::name, MdIncrementalRefreshSessionStatisticsLongQty::minimum_size, bytes.size());
                const MdIncrementalRefreshSessionStatisticsLongQty message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::SnapshotFullRefreshTcpLongQty: {
                wire::require(SnapshotFullRefreshTcpLongQty::name, SnapshotFullRefreshTcpLongQty::minimum_size, bytes.size());
                const SnapshotFullRefreshTcpLongQty message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::SnapshotFullRefreshLongQty: {
                wire::require(SnapshotFullRefreshLongQty::name, SnapshotFullRefreshLongQty::minimum_size, bytes.size());
                const SnapshotFullRefreshLongQty message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            default:
                if constexpr (requires { handler.on_unknown(template_id_, bytes); }) { handler.on_unknown(template_id_, bytes); }
                return;
        }
    }

    // the bytes the message it selects takes
    std::size_t mktdata_payload_size() const {
        const auto bytes = mktdata_payload_bytes();
        switch (template_id_) {
            case TemplateId::ChannelReset: return ChannelReset{ bytes }.encoded_size();
            case TemplateId::AdminHeartbeat: return AdminHeartbeat{ bytes }.encoded_size();
            case TemplateId::AdminLogin: return AdminLogin{ bytes }.encoded_size();
            case TemplateId::AdminLogout: return AdminLogout{ bytes }.encoded_size();
            case TemplateId::SecurityStatus: return SecurityStatus{ bytes }.encoded_size();
            case TemplateId::MdIncrementalRefreshVolume: return MdIncrementalRefreshVolume{ bytes }.encoded_size();
            case TemplateId::QuoteRequest: return QuoteRequest{ bytes }.encoded_size();
            case TemplateId::MdIncrementalRefreshBook: return MdIncrementalRefreshBook{ bytes }.encoded_size();
            case TemplateId::MdIncrementalRefreshOrderBook: return MdIncrementalRefreshOrderBook{ bytes }.encoded_size();
            case TemplateId::MdIncrementalRefreshTradeSummary: return MdIncrementalRefreshTradeSummary{ bytes }.encoded_size();
            case TemplateId::MdIncrementalRefreshDailyStatistics: return MdIncrementalRefreshDailyStatistics{ bytes }.encoded_size();
            case TemplateId::MdIncrementalRefreshLimitsBanding: return MdIncrementalRefreshLimitsBanding{ bytes }.encoded_size();
            case TemplateId::MdIncrementalRefreshSessionStatistics: return MdIncrementalRefreshSessionStatistics{ bytes }.encoded_size();
            case TemplateId::SnapshotFullRefresh: return SnapshotFullRefresh{ bytes }.encoded_size();
            case TemplateId::SnapshotFullRefreshOrderBook: return SnapshotFullRefreshOrderBook{ bytes }.encoded_size();
            case TemplateId::MdInstrumentDefinitionFuture: return MdInstrumentDefinitionFuture{ bytes }.encoded_size();
            case TemplateId::MdInstrumentDefinitionOption: return MdInstrumentDefinitionOption{ bytes }.encoded_size();
            case TemplateId::MdInstrumentDefinitionSpread: return MdInstrumentDefinitionSpread{ bytes }.encoded_size();
            case TemplateId::MdInstrumentDefinitionFixedIncome: return MdInstrumentDefinitionFixedIncome{ bytes }.encoded_size();
            case TemplateId::MdInstrumentDefinitionRepo: return MdInstrumentDefinitionRepo{ bytes }.encoded_size();
            case TemplateId::SnapshotRefreshTopOrders: return SnapshotRefreshTopOrders{ bytes }.encoded_size();
            case TemplateId::SecurityStatusWorkup: return SecurityStatusWorkup{ bytes }.encoded_size();
            case TemplateId::SnapshotFullRefreshTcp: return SnapshotFullRefreshTcp{ bytes }.encoded_size();
            case TemplateId::CollateralMarketValue: return CollateralMarketValue{ bytes }.encoded_size();
            case TemplateId::MdInstrumentDefinitionFx: return MdInstrumentDefinitionFx{ bytes }.encoded_size();
            case TemplateId::MdIncrementalRefreshBookLongQty: return MdIncrementalRefreshBookLongQty{ bytes }.encoded_size();
            case TemplateId::MdIncrementalRefreshTradeSummaryLongQty: return MdIncrementalRefreshTradeSummaryLongQty{ bytes }.encoded_size();
            case TemplateId::MdIncrementalRefreshVolumeLongQty: return MdIncrementalRefreshVolumeLongQty{ bytes }.encoded_size();
            case TemplateId::MdIncrementalRefreshSessionStatisticsLongQty: return MdIncrementalRefreshSessionStatisticsLongQty{ bytes }.encoded_size();
            case TemplateId::SnapshotFullRefreshTcpLongQty: return SnapshotFullRefreshTcpLongQty{ bytes }.encoded_size();
            case TemplateId::SnapshotFullRefreshLongQty: return SnapshotFullRefreshLongQty{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void mktdata_payload_print(std::ostream& out) const {
        const auto bytes = mktdata_payload_bytes();
        switch (template_id_) {
            case TemplateId::ChannelReset: ChannelReset{ bytes }.print(out); return;
            case TemplateId::AdminHeartbeat: AdminHeartbeat{ bytes }.print(out); return;
            case TemplateId::AdminLogin: AdminLogin{ bytes }.print(out); return;
            case TemplateId::AdminLogout: AdminLogout{ bytes }.print(out); return;
            case TemplateId::SecurityStatus: SecurityStatus{ bytes }.print(out); return;
            case TemplateId::MdIncrementalRefreshVolume: MdIncrementalRefreshVolume{ bytes }.print(out); return;
            case TemplateId::QuoteRequest: QuoteRequest{ bytes }.print(out); return;
            case TemplateId::MdIncrementalRefreshBook: MdIncrementalRefreshBook{ bytes }.print(out); return;
            case TemplateId::MdIncrementalRefreshOrderBook: MdIncrementalRefreshOrderBook{ bytes }.print(out); return;
            case TemplateId::MdIncrementalRefreshTradeSummary: MdIncrementalRefreshTradeSummary{ bytes }.print(out); return;
            case TemplateId::MdIncrementalRefreshDailyStatistics: MdIncrementalRefreshDailyStatistics{ bytes }.print(out); return;
            case TemplateId::MdIncrementalRefreshLimitsBanding: MdIncrementalRefreshLimitsBanding{ bytes }.print(out); return;
            case TemplateId::MdIncrementalRefreshSessionStatistics: MdIncrementalRefreshSessionStatistics{ bytes }.print(out); return;
            case TemplateId::SnapshotFullRefresh: SnapshotFullRefresh{ bytes }.print(out); return;
            case TemplateId::SnapshotFullRefreshOrderBook: SnapshotFullRefreshOrderBook{ bytes }.print(out); return;
            case TemplateId::MdInstrumentDefinitionFuture: MdInstrumentDefinitionFuture{ bytes }.print(out); return;
            case TemplateId::MdInstrumentDefinitionOption: MdInstrumentDefinitionOption{ bytes }.print(out); return;
            case TemplateId::MdInstrumentDefinitionSpread: MdInstrumentDefinitionSpread{ bytes }.print(out); return;
            case TemplateId::MdInstrumentDefinitionFixedIncome: MdInstrumentDefinitionFixedIncome{ bytes }.print(out); return;
            case TemplateId::MdInstrumentDefinitionRepo: MdInstrumentDefinitionRepo{ bytes }.print(out); return;
            case TemplateId::SnapshotRefreshTopOrders: SnapshotRefreshTopOrders{ bytes }.print(out); return;
            case TemplateId::SecurityStatusWorkup: SecurityStatusWorkup{ bytes }.print(out); return;
            case TemplateId::SnapshotFullRefreshTcp: SnapshotFullRefreshTcp{ bytes }.print(out); return;
            case TemplateId::CollateralMarketValue: CollateralMarketValue{ bytes }.print(out); return;
            case TemplateId::MdInstrumentDefinitionFx: MdInstrumentDefinitionFx{ bytes }.print(out); return;
            case TemplateId::MdIncrementalRefreshBookLongQty: MdIncrementalRefreshBookLongQty{ bytes }.print(out); return;
            case TemplateId::MdIncrementalRefreshTradeSummaryLongQty: MdIncrementalRefreshTradeSummaryLongQty{ bytes }.print(out); return;
            case TemplateId::MdIncrementalRefreshVolumeLongQty: MdIncrementalRefreshVolumeLongQty{ bytes }.print(out); return;
            case TemplateId::MdIncrementalRefreshSessionStatisticsLongQty: MdIncrementalRefreshSessionStatisticsLongQty{ bytes }.print(out); return;
            case TemplateId::SnapshotFullRefreshTcpLongQty: SnapshotFullRefreshTcpLongQty{ bytes }.print(out); return;
            case TemplateId::SnapshotFullRefreshLongQty: SnapshotFullRefreshLongQty{ bytes }.print(out); return;
            default:
                out << "UnknownMktdataPayload{type=" << template_id_ << ", body=";
                print::hex(out, bytes.data(), bytes.size());
                out << '}';
                return;
        }
    }

    void print(std::ostream& out) const {
        out << "MktdataMessage{";
        out << "mktdata_payload=";
        mktdata_payload_print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t mktdata_payload_end() const { return 0 + mktdata_payload_size(); }

    std::span<const std::byte> bytes_;
    // the Template Id the frame handed it, which selects its mktdata_payload
    TemplateId template_id_;
};

inline std::ostream& operator<<(std::ostream& out, const MktdataMessage& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
