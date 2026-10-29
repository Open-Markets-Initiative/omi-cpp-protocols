// Siac.Opra.Output.Obi.v6.2 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/siac/opra/output/obi/v6.2.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "executables/benchmark/Benchmark.hpp"
#include "cpp/binary/flyweight/siac/opra/output/obi/v6.2/definitions.hpp"

namespace protocol = ::siac::opra::output::obi::v6_2;

namespace {

// The messages Administrative Message Payload selects, their values set in the entry of the message holding it
struct AdministrativeMessagePayloadHandler {
    std::uint64_t& checksum;

    void on(const protocol::AdministrativeMessage& message) {
        checksum += bench::digest(message.message_indicator());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.message_data_length());
    }
};

// The messages Control Message Payload selects, their values set in the entry of the message holding it
struct ControlMessagePayloadHandler {
    std::uint64_t& checksum;

    void on(const protocol::ControlMessage& message) {
        checksum += bench::digest(message.message_indicator());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
    }
};

// The messages Equity And Index Last Sale Message Payload selects, their values set in the entry of the message holding it
struct EquityAndIndexLastSaleMessagePayloadHandler {
    std::uint64_t& checksum;

    void on(const protocol::EquityAndIndexLastSaleMessage& message) {
        checksum += bench::digest(message.message_indicator());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.expiration_block().expiration_month());
        checksum += bench::digest(message.expiration_block().expiration_day());
        checksum += bench::digest(message.expiration_block().expiration_year());
        checksum += bench::digest(message.strike_price_denominator_code());
        checksum += bench::digest(message.strike_price().mantissa());
        checksum += bench::digest(message.volume());
        checksum += bench::digest(message.premium_price_denominator_code());
        checksum += bench::digest(message.premium_price().mantissa());
        checksum += bench::digest(message.trade_identifier());
    }
};

// The messages Open Interest Message Payload selects, their values set in the entry of the message holding it
struct OpenInterestMessagePayloadHandler {
    std::uint64_t& checksum;

    void on(const protocol::OpenInterestMessage& message) {
        checksum += bench::digest(message.message_indicator());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.expiration_block().expiration_month());
        checksum += bench::digest(message.expiration_block().expiration_day());
        checksum += bench::digest(message.expiration_block().expiration_year());
        checksum += bench::digest(message.strike_price_denominator_code());
        checksum += bench::digest(message.strike_price().mantissa());
        checksum += bench::digest(message.open_interest_volume());
    }
};

// The messages Equity And Index End Of Day Summary Message Payload selects, their values set in the entry of the message holding it
struct EquityAndIndexEndOfDaySummaryMessagePayloadHandler {
    std::uint64_t& checksum;

    void on(const protocol::EquityAndIndexEndOfDaySummaryMessage& message) {
        checksum += bench::digest(message.message_indicator());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.expiration_block().expiration_month());
        checksum += bench::digest(message.expiration_block().expiration_day());
        checksum += bench::digest(message.expiration_block().expiration_year());
        checksum += bench::digest(message.strike_price_denominator_code());
        checksum += bench::digest(message.strike_price().mantissa());
        checksum += bench::digest(message.volume());
        checksum += bench::digest(message.open_interest_volume());
        checksum += bench::digest(message.premium_price_denominator_code());
        checksum += bench::digest(message.open_price());
        checksum += bench::digest(message.high_price());
        checksum += bench::digest(message.low_price());
        checksum += bench::digest(message.last_price());
        checksum += bench::digest(message.net_change());
        checksum += bench::digest(message.underlying_price_denominator_code());
        checksum += bench::digest(message.underlying_price().mantissa());
        checksum += bench::digest(message.bid_price());
        checksum += bench::digest(message.offer_price());
    }
};

// The messages Long Equity And Index Quote Message Payload selects, their values set in the entry of the message holding it
struct LongEquityAndIndexQuoteMessagePayloadHandler {
    std::uint64_t& checksum;

    void on(const protocol::LongEquityAndIndexQuoteMessage& message) {
        checksum += bench::digest(message.bbo_indicator());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.expiration_block().expiration_month());
        checksum += bench::digest(message.expiration_block().expiration_day());
        checksum += bench::digest(message.expiration_block().expiration_year());
        checksum += bench::digest(message.strike_price_denominator_code());
        checksum += bench::digest(message.strike_price().mantissa());
        checksum += bench::digest(message.premium_price_denominator_code());
        checksum += bench::digest(message.bid_price());
        checksum += bench::digest(message.bid_size());
        checksum += bench::digest(message.offer_price());
        checksum += bench::digest(message.offer_size());
    }
};

// The messages Short Equity And Index Quote Message Payload selects, their values set in the entry of the message holding it
struct ShortEquityAndIndexQuoteMessagePayloadHandler {
    std::uint64_t& checksum;

    void on(const protocol::ShortEquityAndIndexQuoteMessage& message) {
        checksum += bench::digest(message.bbo_indicator());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol_short());
        checksum += bench::digest(message.expiration_block().expiration_month());
        checksum += bench::digest(message.expiration_block().expiration_day());
        checksum += bench::digest(message.expiration_block().expiration_year());
        checksum += bench::digest(message.strike_price_short().mantissa());
        checksum += bench::digest(message.bid_price_short().mantissa());
        checksum += bench::digest(message.bid_size_short());
        checksum += bench::digest(message.offer_price_short().mantissa());
        checksum += bench::digest(message.offer_size_short());
    }
};

// The messages Underlying Value Message Payload selects, their values set in the entry of the message holding it
struct UnderlyingValueMessagePayloadHandler {
    std::uint64_t& checksum;

    void on(const protocol::UnderlyingValueLastSaleMessage& message) {
        checksum += bench::digest(message.message_indicator());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.index_value_denominator_code());
        checksum += bench::digest(message.index_value().mantissa());
    }

    void on(const protocol::UnderlyingValueBidAndOfferMessage& message) {
        checksum += bench::digest(message.message_indicator());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.index_value_denominator_code());
        checksum += bench::digest(message.bid_index_value());
        checksum += bench::digest(message.offer_index_value());
    }
};

// The handler the reader hands each datagram's views to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        checksum += bench::digest(packet.block_header().version());
        checksum += bench::digest(packet.block_header().block_size());
        checksum += bench::digest(packet.block_header().data_feed_indicator());
        checksum += bench::digest(packet.block_header().retransmission_indicator());
        checksum += bench::digest(packet.block_header().session_indicator());
        checksum += bench::digest(packet.block_header().block_sequence_number());
        checksum += bench::digest(packet.block_header().messages_in_block());
        checksum += bench::digest(packet.block_header().block_timestamp().seconds());
        checksum += bench::digest(packet.block_header().block_timestamp().nanoseconds());
        checksum += bench::digest(packet.block_header().block_checksum());
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
        checksum += index++;
        checksum += bench::digest(message.administrative_message_type());
        AdministrativeMessagePayloadHandler selected{ checksum };
        message.administrative_message_payload(selected);
    }

    void on(const protocol::ControlCategory& message) {
        checksum += index++;
        checksum += bench::digest(message.control_message_type());
        ControlMessagePayloadHandler selected{ checksum };
        message.control_message_payload(selected);
    }

    void on(const protocol::EquityAndIndexLastSaleCategory& message) {
        checksum += index++;
        checksum += bench::digest(message.equity_and_index_last_sale_message_type());
        EquityAndIndexLastSaleMessagePayloadHandler selected{ checksum };
        message.equity_and_index_last_sale_message_payload(selected);
    }

    void on(const protocol::OpenInterestCategory& message) {
        checksum += index++;
        checksum += bench::digest(message.open_interest_message_type());
        OpenInterestMessagePayloadHandler selected{ checksum };
        message.open_interest_message_payload(selected);
    }

    void on(const protocol::EquityAndIndexEndOfDaySummaryCategory& message) {
        checksum += index++;
        checksum += bench::digest(message.equity_and_index_end_of_day_summary_message_type());
        EquityAndIndexEndOfDaySummaryMessagePayloadHandler selected{ checksum };
        message.equity_and_index_end_of_day_summary_message_payload(selected);
    }

    void on(const protocol::LongEquityAndIndexQuoteCategory& message) {
        checksum += index++;
        checksum += bench::digest(message.long_equity_and_index_quote_message_type());
        LongEquityAndIndexQuoteMessagePayloadHandler selected{ checksum };
        message.long_equity_and_index_quote_message_payload(selected);
    }

    void on(const protocol::ShortEquityAndIndexQuoteCategory& message) {
        checksum += index++;
        checksum += bench::digest(message.short_equity_and_index_quote_message_type());
        ShortEquityAndIndexQuoteMessagePayloadHandler selected{ checksum };
        message.short_equity_and_index_quote_message_payload(selected);
    }

    void on(const protocol::UnderlyingValueCategory& message) {
        checksum += index++;
        checksum += bench::digest(message.underlying_value_message_type());
        UnderlyingValueMessagePayloadHandler selected{ checksum };
        message.underlying_value_message_payload(selected);
    }
};

// The values the Flyweight reader reads from one datagram, folded into a checksum. A datagram it cannot
// read is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::PacketReader::read(std::span<const std::byte>(frame.payload, frame.payload_len), reader);
    } catch (const protocol::DecodeError& error) {
        throw;
    }

    return reader.checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Siac.Opra.Output.Obi.v6.2", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
