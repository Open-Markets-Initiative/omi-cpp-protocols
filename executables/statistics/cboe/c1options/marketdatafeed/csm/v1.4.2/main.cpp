// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: main.cpp
#include "Settings.hpp"

int main(const int argc, char** argv) {
    try {
        const auto settings = args(argc, argv);

        packet::Parser parser{ settings.pcap };
        statistics::Statistics statistics{ settings.statistics, parser };

        while (parser.next()) {
            ++statistics.total_packets;
            if (parser.identify() == packet::result::cboe_c1options_marketdatafeed_csm_v1_4_2) {
                statistics.udp();
            } else {
                ++statistics.unknown_packets;
            }
        }

        statistics.report();
        return 0;
    }
    catch (const std::exception &exception) {
        std::cerr << "Error: " << exception.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown exception" << std::endl;
        return 1;
    }
}