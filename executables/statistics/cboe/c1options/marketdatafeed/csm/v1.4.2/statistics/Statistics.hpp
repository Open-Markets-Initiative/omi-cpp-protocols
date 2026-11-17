// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: statistics/Statistics.hpp
#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/binary/modern/cboe/c1options/marketdatafeed/csm/v1.4.2/definitions.hpp"

namespace statistics {

// Cboe Csm C++ statistics
struct Statistics {

    cboe::c1options::marketdatafeed::csm::v1_4_2::MessageIterator message;
    packet::Parser& parser;
    const statistics::Options& options;

    // counters
    uint64_t total_packets = 0;
    uint64_t unknown_packets = 0;
    uint64_t total_messages = 0;
    uint64_t unknown_messages = 0;
    uint64_t heartbeats = 0;

    // message counters
    uint64_t security_definition_message = 0;
    uint64_t current_market_refresh_message = 0;
    uint64_t market_data_refresh_message = 0;
    uint64_t current_market_update_message = 0;
    uint64_t recap_update_message = 0;
    uint64_t ticker_message = 0;
    uint64_t expected_opening_price_and_size_message = 0;
    uint64_t index_value_message = 0;
    uint64_t settlement_value_message = 0;
    uint64_t summary_message = 0;
    uint64_t market_data_control_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process a frame: every tree carrying its transport reads it
    void udp() {
        const auto& frame = parser.frame();

        if (frame.is_udp()) {
            walk_message(frame);
        }
    }

    // walk the Packet tree's datagrams
    void walk_message(const packet::Frame& frame) {
        message.initialize(frame.payload, frame.payload_len);

        while (message.next()) {
            if (message.template_id == 16) {
                ++heartbeats;
                continue;
            }

            process_message(message.message, message.template_id);
        }
    }

    // count a message of the Packet tree
    void process_message(const std::byte*, const std::uint8_t template_id) {
        switch (template_id) {
            case 13:
                ++total_messages;
                ++security_definition_message;
                break;
            case 11:
                ++total_messages;
                ++current_market_refresh_message;
                break;
            case 20:
                ++total_messages;
                ++market_data_refresh_message;
                break;
            case 12:
                ++total_messages;
                ++current_market_update_message;
                break;
            case 21:
                ++total_messages;
                ++recap_update_message;
                break;
            case 14:
                ++total_messages;
                ++ticker_message;
                break;
            case 15:
                ++total_messages;
                ++expected_opening_price_and_size_message;
                break;
            case 22:
                ++total_messages;
                ++index_value_message;
                break;
            case 23:
                ++total_messages;
                ++settlement_value_message;
                break;
            case 24:
                ++total_messages;
                ++summary_message;
                break;
            case 25:
                ++total_messages;
                ++market_data_control_message;
                break;

            default:
                ++total_messages;
                ++unknown_messages;
                if (options.verbose) {
                    std::cerr << "Unknown template_id: " << static_cast<int>(template_id) << std::endl;
                }
                break;
        }
    }

    // report statistics
    void report() {
        std::cout << std::endl;
        std::cout << "Statistics Report" << std::endl;
        std::cout << "=================" << std::endl;
        std::cout << "Total packets:   " << total_packets << std::endl;
        std::cout << "Unknown packets: " << unknown_packets << std::endl;
        std::cout << "Total messages:  " << total_messages << std::endl;
        std::cout << "Unknown types:   " << unknown_messages << std::endl;
        std::cout << "Heartbeats:      " << heartbeats << std::endl;

        std::cout << std::endl;
        std::cout << "Message Counts:" << std::endl;
        std::cout << "--------------" << std::endl;
        std::cout << "  SecurityDefinitionMessage (13)           " << security_definition_message << std::endl;
        std::cout << "  CurrentMarketRefreshMessage (11)         " << current_market_refresh_message << std::endl;
        std::cout << "  MarketDataRefreshMessage (20)            " << market_data_refresh_message << std::endl;
        std::cout << "  CurrentMarketUpdateMessage (12)          " << current_market_update_message << std::endl;
        std::cout << "  RecapUpdateMessage (21)                  " << recap_update_message << std::endl;
        std::cout << "  TickerMessage (14)                       " << ticker_message << std::endl;
        std::cout << "  ExpectedOpeningPriceAndSizeMessage (15)  " << expected_opening_price_and_size_message << std::endl;
        std::cout << "  IndexValueMessage (22)                   " << index_value_message << std::endl;
        std::cout << "  SettlementValueMessage (23)              " << settlement_value_message << std::endl;
        std::cout << "  SummaryMessage (24)                      " << summary_message << std::endl;
        std::cout << "  MarketDataControlMessage (25)            " << market_data_control_message << std::endl;
    }
};
}
