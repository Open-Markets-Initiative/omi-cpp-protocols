// Siac.Opra.Output.Obi.v6.2 canonical values, through the Flyweight reader: every value Flyweight reads
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
#include "cpp/flyweight/siac/opra/output/obi/v6.2/definitions.hpp"

namespace protocol = ::siac::opra::output::obi::v6_2;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        values["packet.blockheader.version"] = canonical::number(packet.block_header().version());
        values["packet.blockheader.blocksize"] = canonical::number(packet.block_header().block_size());
        values["packet.blockheader.datafeedindicator"] = canonical::text(canonical::character(packet.block_header().data_feed_indicator()));
        values["packet.blockheader.retransmissionindicator"] = canonical::text(canonical::character(packet.block_header().retransmission_indicator()));
        values["packet.blockheader.sessionindicator"] = canonical::number(packet.block_header().session_indicator());
        values["packet.blockheader.blocksequencenumber"] = canonical::number(packet.block_header().block_sequence_number());
        values["packet.blockheader.messagesinblock"] = canonical::number(packet.block_header().messages_in_block());
        values["packet.blockheader.blocktimestamp.seconds"] = canonical::number(packet.block_header().block_timestamp().seconds());
        values["packet.blockheader.blocktimestamp.nanoseconds"] = canonical::number(packet.block_header().block_timestamp().nanoseconds());
        values["packet.blockheader.blockchecksum"] = canonical::number(packet.block_header().block_checksum());
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

    void on(const protocol::AdministrativeCategory& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.administrativecategory";
        values[entry + ".payload.administrativecategory.administrativemessagetype"] = canonical::text(canonical::character(message.administrative_message_type()));
    }

    void on(const protocol::ControlCategory& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.controlcategory";
        values[entry + ".payload.controlcategory.controlmessagetype"] = canonical::text(canonical::character(message.control_message_type()));
    }

    void on(const protocol::EquityAndIndexLastSaleCategory& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.equityandindexlastsalecategory";
        values[entry + ".payload.equityandindexlastsalecategory.equityandindexlastsalemessagetype"] = canonical::text(canonical::character(message.equity_and_index_last_sale_message_type()));
    }

    void on(const protocol::OpenInterestCategory& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.openinterestcategory";
        values[entry + ".payload.openinterestcategory.openinterestmessagetype"] = canonical::text(canonical::character(message.open_interest_message_type()));
    }

    void on(const protocol::EquityAndIndexEndOfDaySummaryCategory& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.equityandindexendofdaysummarycategory";
        values[entry + ".payload.equityandindexendofdaysummarycategory.equityandindexendofdaysummarymessagetype"] = canonical::text(canonical::character(message.equity_and_index_end_of_day_summary_message_type()));
    }

    void on(const protocol::LongEquityAndIndexQuoteCategory& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.longequityandindexquotecategory";
        values[entry + ".payload.longequityandindexquotecategory.longequityandindexquotemessagetype"] = canonical::text(canonical::character(message.long_equity_and_index_quote_message_type()));
    }

    void on(const protocol::ShortEquityAndIndexQuoteCategory& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.shortequityandindexquotecategory";
        values[entry + ".payload.shortequityandindexquotecategory.shortequityandindexquotemessagetype"] = canonical::text(canonical::character(message.short_equity_and_index_quote_message_type()));
    }

    void on(const protocol::UnderlyingValueCategory& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.underlyingvaluecategory";
        values[entry + ".payload.underlyingvaluecategory.underlyingvaluemessagetype"] = canonical::text(canonical::character(message.underlying_value_message_type()));
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
    std::printf("== Siac.Opra.Output.Obi.v6.2 (flyweight values)\n");
    int failures = 0;
    failures += check("AdministrativeMessage", "Siac/Opra.Output.Obi.v6.2/AdministrativeMessage.pcap", "siac/opra/output/obi/v6.2/AdministrativeMessage.values");
    failures += check("ControlMessage", "Siac/Opra.Output.Obi.v6.2/ControlMessage.pcap", "siac/opra/output/obi/v6.2/ControlMessage.values");
    failures += check("LongEquityAndIndexQuoteMessage", "Siac/Opra.Output.Obi.v6.2/LongEquityAndIndexQuoteMessage.pcap", "siac/opra/output/obi/v6.2/LongEquityAndIndexQuoteMessage.values");
    failures += check("ShortEquityAndIndexQuoteMessage", "Siac/Opra.Output.Obi.v6.2/ShortEquityAndIndexQuoteMessage.pcap", "siac/opra/output/obi/v6.2/ShortEquityAndIndexQuoteMessage.values");
    return failures == 0 ? 0 : 1;
}