// Iex.IexEquities.Tops.IexTp.v1.56 canonical values, through the Flyweight reader: every value Flyweight reads
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
#include "cpp/flyweight/iex/iexequities/tops/iextp/v1.56/definitions.hpp"

namespace protocol = ::iex::iexequities::tops::iextp::v1_56;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        values["packet.iextpheader.version"] = canonical::number(packet.iextp_header().version());
        values["packet.iextpheader.messageprotocolid"] = canonical::number(packet.iextp_header().message_protocol_id());
        values["packet.iextpheader.channelid"] = canonical::number(packet.iextp_header().channel_id());
        values["packet.iextpheader.sessionid"] = canonical::number(packet.iextp_header().session_id());
        values["packet.iextpheader.payloadlength"] = canonical::number(packet.iextp_header().payload_length());
        values["packet.iextpheader.messagecount"] = canonical::number(packet.iextp_header().message_count());
        values["packet.iextpheader.streamoffset"] = canonical::number(packet.iextp_header().stream_offset());
        values["packet.iextpheader.firstmessagesequencenumber"] = canonical::number(packet.iextp_header().first_message_sequence_number());
        values["packet.iextpheader.sendtime"] = canonical::number(packet.iextp_header().send_time());
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

    void on(const protocol::QuoteUpdateMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.quoteupdatemessage";
        values[entry + ".messagedata.quoteupdatemessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".messagedata.quoteupdatemessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
        values[entry + ".messagedata.quoteupdatemessage.bidsize"] = canonical::number(message.bid_size());
        values[entry + ".messagedata.quoteupdatemessage.bidprice"] = canonical::scaled(message.bid_price().mantissa(), message.bid_price().exponent());
        values[entry + ".messagedata.quoteupdatemessage.askprice"] = canonical::scaled(message.ask_price().mantissa(), message.ask_price().exponent());
        values[entry + ".messagedata.quoteupdatemessage.asksize"] = canonical::number(message.ask_size());
    }

    void on(const protocol::TradeReportMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.tradereportmessage";
        values[entry + ".messagedata.tradereportmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".messagedata.tradereportmessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
        values[entry + ".messagedata.tradereportmessage.size"] = canonical::number(message.size());
        values[entry + ".messagedata.tradereportmessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".messagedata.tradereportmessage.tradeid"] = canonical::number(message.trade_id());
        values[entry + ".messagedata.tradereportmessage.reserved4"] = canonical::number(message.reserved_4());
    }

    void on(const protocol::TradeBreakMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.tradebreakmessage";
        values[entry + ".messagedata.tradebreakmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".messagedata.tradebreakmessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
        values[entry + ".messagedata.tradebreakmessage.size"] = canonical::number(message.size());
        values[entry + ".messagedata.tradebreakmessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".messagedata.tradebreakmessage.tradeid"] = canonical::number(message.trade_id());
        values[entry + ".messagedata.tradebreakmessage.reserved4"] = canonical::number(message.reserved_4());
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
    std::printf("== Iex.IexEquities.Tops.IexTp.v1.56 (flyweight values)\n");
    int failures = 0;
    failures += check("QuoteUpdateMessage", "Iex/IexEquities.Tops.IexTp.v1.56/QuoteUpdateMessage.pcap", "iex/iexequities/tops/iextp/v1.56/QuoteUpdateMessage.values");
    failures += check("TradeReportMessage", "Iex/IexEquities.Tops.IexTp.v1.56/TradeReportMessage.pcap", "iex/iexequities/tops/iextp/v1.56/TradeReportMessage.values");
    return failures == 0 ? 0 : 1;
}