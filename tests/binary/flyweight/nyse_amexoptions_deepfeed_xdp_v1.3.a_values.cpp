// Nyse.AmexOptions.DeepFeed.Xdp.v1.3.a canonical values, through the Flyweight reader: every value Flyweight reads
// from each sample, at its address, held to what the model reads.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <span>
#include <string>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "tests/canonical/Canonical.hpp"
#include "cpp/binary/flyweight/nyse/amexoptions/deepfeed/xdp/v1.3.a/definitions.hpp"

namespace protocol = ::nyse::amexoptions::deepfeed::xdp::v1_3_a;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        values["packet.packetheader.packetsize"] = canonical::number(packet.packet_header().packet_size());
        values["packet.packetheader.deliveryflag"] = canonical::number(packet.packet_header().delivery_flag());
        values["packet.packetheader.messagecount"] = canonical::number(packet.packet_header().message_count());
        values["packet.packetheader.sequencenumber"] = canonical::number(packet.packet_header().sequence_number());
        values["packet.packetheader.sendtime.seconds"] = canonical::number(packet.packet_header().send_time().seconds());
        values["packet.packetheader.sendtime.nanoseconds"] = canonical::number(packet.packet_header().send_time().nanoseconds());
    }

    // a message this test prints no values of, or a code no message answers to, still takes its entry
    template <typename Message>
    void on(const Message&) {
        ++index;
    }

    template <typename Code>
    void on_unknown(Code, std::span<const std::byte>) {
        ++index;
    }

    void on(const protocol::OutrightMarketDepthBuyMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.outrightmarketdepthbuymessage";
        values[entry + ".payload.outrightmarketdepthbuymessage.sourcetime"] = canonical::number(message.source_time());
        values[entry + ".payload.outrightmarketdepthbuymessage.sourcens"] = canonical::number(message.source_ns());
        values[entry + ".payload.outrightmarketdepthbuymessage.seriesindex"] = canonical::number(message.series_index());
        values[entry + ".payload.outrightmarketdepthbuymessage.symbolseqnum"] = canonical::number(message.symbol_seq_num());
        values[entry + ".payload.outrightmarketdepthbuymessage.firstlevelprice"] = canonical::number(message.first_level_price());
        values[entry + ".payload.outrightmarketdepthbuymessage.secondlevelprice"] = canonical::number(message.second_level_price());
        values[entry + ".payload.outrightmarketdepthbuymessage.thirdlevelprice"] = canonical::number(message.third_level_price());
        values[entry + ".payload.outrightmarketdepthbuymessage.firstlevelvolume"] = canonical::number(message.first_level_volume());
        values[entry + ".payload.outrightmarketdepthbuymessage.secondlevelvolume"] = canonical::number(message.second_level_volume());
        values[entry + ".payload.outrightmarketdepthbuymessage.thirdlevelvolume"] = canonical::number(message.third_level_volume());
        values[entry + ".payload.outrightmarketdepthbuymessage.quotecondition"] = canonical::text(canonical::character(message.quote_condition()), '\0', false);
        values[entry + ".payload.outrightmarketdepthbuymessage.firstlevelcustomervolume"] = canonical::number(message.first_level_customer_volume());
        values[entry + ".payload.outrightmarketdepthbuymessage.secondlevelcustomervolume"] = canonical::number(message.second_level_customer_volume());
        values[entry + ".payload.outrightmarketdepthbuymessage.thirdlevelcustomervolume"] = canonical::number(message.third_level_customer_volume());
    }

    void on(const protocol::OutrightMarketDepthSellMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.outrightmarketdepthsellmessage";
        values[entry + ".payload.outrightmarketdepthsellmessage.sourcetime"] = canonical::number(message.source_time());
        values[entry + ".payload.outrightmarketdepthsellmessage.sourcens"] = canonical::number(message.source_ns());
        values[entry + ".payload.outrightmarketdepthsellmessage.seriesindex"] = canonical::number(message.series_index());
        values[entry + ".payload.outrightmarketdepthsellmessage.symbolseqnum"] = canonical::number(message.symbol_seq_num());
        values[entry + ".payload.outrightmarketdepthsellmessage.firstlevelprice"] = canonical::number(message.first_level_price());
        values[entry + ".payload.outrightmarketdepthsellmessage.secondlevelprice"] = canonical::number(message.second_level_price());
        values[entry + ".payload.outrightmarketdepthsellmessage.thirdlevelprice"] = canonical::number(message.third_level_price());
        values[entry + ".payload.outrightmarketdepthsellmessage.firstvolume"] = canonical::number(message.first_volume());
        values[entry + ".payload.outrightmarketdepthsellmessage.secondvolume"] = canonical::number(message.second_volume());
        values[entry + ".payload.outrightmarketdepthsellmessage.thirdvolume"] = canonical::number(message.third_volume());
        values[entry + ".payload.outrightmarketdepthsellmessage.quotecondition"] = canonical::text(canonical::character(message.quote_condition()), '\0', false);
        values[entry + ".payload.outrightmarketdepthsellmessage.firstlevelcustomervolume"] = canonical::number(message.first_level_customer_volume());
        values[entry + ".payload.outrightmarketdepthsellmessage.secondlevelcustomervolume"] = canonical::number(message.second_level_customer_volume());
        values[entry + ".payload.outrightmarketdepthsellmessage.thirdlevelcustomervolume"] = canonical::number(message.third_level_customer_volume());
    }

    void on(const protocol::UnderlyingStatusMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.underlyingstatusmessage";
        values[entry + ".payload.underlyingstatusmessage.sourcetime"] = canonical::number(message.source_time());
        values[entry + ".payload.underlyingstatusmessage.sourcetimens"] = canonical::number(message.source_time_ns());
        values[entry + ".payload.underlyingstatusmessage.underlyingindex"] = canonical::number(message.underlying_index());
        values[entry + ".payload.underlyingstatusmessage.underlyingseqnum"] = canonical::number(message.underlying_seq_num());
        values[entry + ".payload.underlyingstatusmessage.securitystatus"] = canonical::text(canonical::character(message.security_status()), '\0', false);
        values[entry + ".payload.underlyingstatusmessage.haltcondition"] = canonical::text(canonical::character(message.halt_condition()), '\0', false);
    }

    void on(const protocol::OutrightSeriesStatusMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.outrightseriesstatusmessage";
        values[entry + ".payload.outrightseriesstatusmessage.sourcetime"] = canonical::number(message.source_time());
        values[entry + ".payload.outrightseriesstatusmessage.sourcetimens"] = canonical::number(message.source_time_ns());
        values[entry + ".payload.outrightseriesstatusmessage.seriesindex"] = canonical::number(message.series_index());
        values[entry + ".payload.outrightseriesstatusmessage.symbolseqnum"] = canonical::number(message.symbol_seq_num());
        values[entry + ".payload.outrightseriesstatusmessage.securitystatus"] = canonical::text(canonical::character(message.security_status()), '\0', false);
        values[entry + ".payload.outrightseriesstatusmessage.haltcondition"] = canonical::text(canonical::character(message.halt_condition()), '\0', false);
    }

    void on(const protocol::RefreshOutrightMarketDepthBuyMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.refreshoutrightmarketdepthbuymessage";
        values[entry + ".payload.refreshoutrightmarketdepthbuymessage.sourcetime"] = canonical::number(message.source_time());
        values[entry + ".payload.refreshoutrightmarketdepthbuymessage.sourcens"] = canonical::number(message.source_ns());
        values[entry + ".payload.refreshoutrightmarketdepthbuymessage.seriesindex"] = canonical::number(message.series_index());
        values[entry + ".payload.refreshoutrightmarketdepthbuymessage.symbolseqnum"] = canonical::number(message.symbol_seq_num());
        values[entry + ".payload.refreshoutrightmarketdepthbuymessage.firstlevelprice"] = canonical::number(message.first_level_price());
        values[entry + ".payload.refreshoutrightmarketdepthbuymessage.secondlevelprice"] = canonical::number(message.second_level_price());
        values[entry + ".payload.refreshoutrightmarketdepthbuymessage.thirdlevelprice"] = canonical::number(message.third_level_price());
        values[entry + ".payload.refreshoutrightmarketdepthbuymessage.firstvolume"] = canonical::number(message.first_volume());
        values[entry + ".payload.refreshoutrightmarketdepthbuymessage.secondvolume"] = canonical::number(message.second_volume());
        values[entry + ".payload.refreshoutrightmarketdepthbuymessage.thirdvolume"] = canonical::number(message.third_volume());
        values[entry + ".payload.refreshoutrightmarketdepthbuymessage.quotecondition"] = canonical::text(canonical::character(message.quote_condition()), '\0', false);
        values[entry + ".payload.refreshoutrightmarketdepthbuymessage.firstlevelcustomervolume"] = canonical::number(message.first_level_customer_volume());
        values[entry + ".payload.refreshoutrightmarketdepthbuymessage.secondlevelcustomervolume"] = canonical::number(message.second_level_customer_volume());
        values[entry + ".payload.refreshoutrightmarketdepthbuymessage.thirdlevelcustomervolume"] = canonical::number(message.third_level_customer_volume());
    }

    void on(const protocol::RefreshOutrightMarketDepthSellMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.refreshoutrightmarketdepthsellmessage";
        values[entry + ".payload.refreshoutrightmarketdepthsellmessage.sourcetime"] = canonical::number(message.source_time());
        values[entry + ".payload.refreshoutrightmarketdepthsellmessage.sourcetimens"] = canonical::number(message.source_time_ns());
        values[entry + ".payload.refreshoutrightmarketdepthsellmessage.seriesindex"] = canonical::number(message.series_index());
        values[entry + ".payload.refreshoutrightmarketdepthsellmessage.symbolseqnum"] = canonical::number(message.symbol_seq_num());
        values[entry + ".payload.refreshoutrightmarketdepthsellmessage.firstlevelprice"] = canonical::number(message.first_level_price());
        values[entry + ".payload.refreshoutrightmarketdepthsellmessage.secondlevelprice"] = canonical::number(message.second_level_price());
        values[entry + ".payload.refreshoutrightmarketdepthsellmessage.thirdlevelprice"] = canonical::number(message.third_level_price());
        values[entry + ".payload.refreshoutrightmarketdepthsellmessage.firstvolume"] = canonical::number(message.first_volume());
        values[entry + ".payload.refreshoutrightmarketdepthsellmessage.secondvolume"] = canonical::number(message.second_volume());
        values[entry + ".payload.refreshoutrightmarketdepthsellmessage.thirdvolume"] = canonical::number(message.third_volume());
        values[entry + ".payload.refreshoutrightmarketdepthsellmessage.quotecondition"] = canonical::text(canonical::character(message.quote_condition()), '\0', false);
        values[entry + ".payload.refreshoutrightmarketdepthsellmessage.firstlevelcustomervolume"] = canonical::number(message.first_level_customer_volume());
        values[entry + ".payload.refreshoutrightmarketdepthsellmessage.secondlevelcustomervolume"] = canonical::number(message.second_level_customer_volume());
        values[entry + ".payload.refreshoutrightmarketdepthsellmessage.thirdlevelcustomervolume"] = canonical::number(message.third_level_customer_volume());
    }

    void on(const protocol::UnderlyingIndexMappingMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.underlyingindexmappingmessage";
        values[entry + ".payload.underlyingindexmappingmessage.underlyingindex"] = canonical::number(message.underlying_index());
        values[entry + ".payload.underlyingindexmappingmessage.underlyingsymbol"] = canonical::text(std::string(message.underlying_symbol()), '\0', false);
        values[entry + ".payload.underlyingindexmappingmessage.channelid"] = canonical::number(message.channel_id());
        values[entry + ".payload.underlyingindexmappingmessage.marketid"] = canonical::number(message.market_id());
        values[entry + ".payload.underlyingindexmappingmessage.systemid"] = canonical::number(message.system_id());
        values[entry + ".payload.underlyingindexmappingmessage.exchangecode"] = canonical::text(canonical::character(message.exchange_code()), '\0', false);
        values[entry + ".payload.underlyingindexmappingmessage.pricescalecode"] = canonical::number(message.price_scale_code());
        values[entry + ".payload.underlyingindexmappingmessage.securitytype"] = canonical::text(canonical::character(message.security_type()), '\0', false);
        values[entry + ".payload.underlyingindexmappingmessage.priceresolution"] = canonical::number(message.price_resolution());
    }

    void on(const protocol::SeriesIndexMappingMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.seriesindexmappingmessage";
        values[entry + ".payload.seriesindexmappingmessage.seriesindex"] = canonical::number(message.series_index());
        values[entry + ".payload.seriesindexmappingmessage.channelid"] = canonical::number(message.channel_id());
        values[entry + ".payload.seriesindexmappingmessage.marketid"] = canonical::number(message.market_id());
        values[entry + ".payload.seriesindexmappingmessage.systemid"] = canonical::number(message.system_id());
        values[entry + ".payload.seriesindexmappingmessage.streamid"] = canonical::number(message.stream_id());
        values[entry + ".payload.seriesindexmappingmessage.underlyingindex"] = canonical::number(message.underlying_index());
        values[entry + ".payload.seriesindexmappingmessage.contractmultiplier"] = canonical::number(message.contract_multiplier());
        values[entry + ".payload.seriesindexmappingmessage.maturitydate"] = canonical::text(std::string(message.maturity_date()), '\0', false);
        values[entry + ".payload.seriesindexmappingmessage.putorcall"] = canonical::number(message.put_or_call());
        values[entry + ".payload.seriesindexmappingmessage.strikeprice"] = canonical::text(std::string(message.strike_price()), '\0', false);
        values[entry + ".payload.seriesindexmappingmessage.pricescalecode"] = canonical::number(message.price_scale_code());
        values[entry + ".payload.seriesindexmappingmessage.underlyingsymbol"] = canonical::text(std::string(message.underlying_symbol()), '\0', false);
        values[entry + ".payload.seriesindexmappingmessage.optionsymbolroot"] = canonical::text(std::string(message.option_symbol_root()), '\0', false);
        values[entry + ".payload.seriesindexmappingmessage.groupid"] = canonical::number(message.group_id());
    }

    void on(const protocol::StreamIdMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.streamidmessage";
        values[entry + ".payload.streamidmessage.streamid"] = canonical::number(message.stream_id());
    }

    void on(const protocol::SequenceNumberResetMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.sequencenumberresetmessage";
        values[entry + ".payload.sequencenumberresetmessage.sourcetime"] = canonical::number(message.source_time());
        values[entry + ".payload.sequencenumberresetmessage.sourcetimens"] = canonical::number(message.source_time_ns());
        values[entry + ".payload.sequencenumberresetmessage.productid"] = canonical::number(message.product_id());
        values[entry + ".payload.sequencenumberresetmessage.channelid"] = canonical::number(message.channel_id());
    }
};

// The values the Flyweight reader reads from one datagram, by indexed address. A datagram it cannot
// read is a value the model never reads, so it fails rather than passing with nothing compared.
canonical::Listing read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::PacketReader::read(std::span<const std::byte>(frame.payload, frame.payload_len), reader);
    } catch (const protocol::DecodeError& error) {
        reader.values["(does not decode)"] = error.what();
    }

    return reader.values;
}

// Read each datagram of a sample with Flyweight and hold it to the model's values
int check(const char* name, const char* capture, const char* expected) {
    const char* packets = std::getenv("OMI_PACKETS_DIR");

    if (packets == nullptr) {
        std::printf("FAIL: OMI_PACKETS_DIR is not set\n");
        return 1;
    }

    const auto model = canonical::load(canonical::root() + "/" + expected);
    std::vector<std::pair<std::string, std::int64_t>> sources;
    sources.emplace_back(std::string{packets} + "/" + capture, 0);

    packet::PcapIterator captures(sources);
    std::size_t datagram = 0;
    int differences = 0;

    while (captures.advance()) {
        const packet::Frame frame(captures.data(), captures.length());

        if (!frame.valid() || !frame.is_udp()) { continue; }

        if (datagram >= model.size()) {
            std::printf("FAIL %s: more datagrams than the model read\n", name);
            return 1;
        }

        differences += canonical::compare(name, datagram, model[datagram], read(frame));
        ++datagram;
    }

    if (datagram != model.size()) {
        std::printf("FAIL %s: %zu datagrams, the model read %zu\n", name, datagram, model.size());
        return 1;
    }

    if (differences == 0) {
        std::printf("ok   %s: %zu datagrams\n", name, datagram);
    }

    return differences == 0 ? 0 : 1;
}

}

int main() {
    std::printf("== Nyse.AmexOptions.DeepFeed.Xdp.v1.3.a (flyweight values)\n");
    int failures = 0;
    failures += check("OutrightMarketDepthBuyMessage", "Nyse/AmexOptions.DeepFeed.Xdp.v1.3.a/OutrightMarketDepthBuyMessage.pcap", "nyse/amexoptions/deepfeed/xdp/v1.3.a/OutrightMarketDepthBuyMessage.values");
    failures += check("OutrightMarketDepthSellMessage", "Nyse/AmexOptions.DeepFeed.Xdp.v1.3.a/OutrightMarketDepthSellMessage.pcap", "nyse/amexoptions/deepfeed/xdp/v1.3.a/OutrightMarketDepthSellMessage.values");
    failures += check("RefreshOutrightMarketDepthBuyMessage", "Nyse/AmexOptions.DeepFeed.Xdp.v1.3.a/RefreshOutrightMarketDepthBuyMessage.pcap", "nyse/amexoptions/deepfeed/xdp/v1.3.a/RefreshOutrightMarketDepthBuyMessage.values");
    failures += check("RefreshOutrightMarketDepthSellMessage", "Nyse/AmexOptions.DeepFeed.Xdp.v1.3.a/RefreshOutrightMarketDepthSellMessage.pcap", "nyse/amexoptions/deepfeed/xdp/v1.3.a/RefreshOutrightMarketDepthSellMessage.values");
    failures += check("StreamIdMessage", "Nyse/AmexOptions.DeepFeed.Xdp.v1.3.a/StreamIdMessage.pcap", "nyse/amexoptions/deepfeed/xdp/v1.3.a/StreamIdMessage.values");
    return failures == 0 ? 0 : 1;
}
