package com.ardikars.jxnet.packet.ipv6;

import com.ardikars.jxnet.Jxnet;
import com.ardikars.jxnet.Pcap;
import com.ardikars.jxnet.packet.Packet;
import com.ardikars.jxnet.packet.PacketListener;
import com.ardikars.jxnet.packet.ethernet.Ethernet;
import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

@RunWith(JUnit4.class)
public class ESPTest {

    private static int index = 0;

    private String pcap_source_file = getClass().getResource("/sample-capture/IPv6-ESP.pcapng.pcapng").getPath();

    private StringBuilder errbuf = new StringBuilder();
    private Pcap pcap = null;
    private Logger logger = LoggerFactory.getLogger(ESPTest.class);
    @Before
    public void OpenHandle() {
        pcap = Jxnet.PcapOpenOffline(pcap_source_file, errbuf);
        logger.debug("Open handle.");
        Assert.assertNotEquals(errbuf.toString(), null, pcap);
    }

    @Test
    public void validate() {
        PacketListener.List<String> callback = (arg, pktHdr, packets) -> {
            Ethernet eth = (Ethernet) packets.get(0);
            if (eth != null) {

                index++;
            }
        };
        PacketListener.loop(pcap, -1, callback, "");
    }

    @Test
    public void foreach() {
        PacketListener.List<String> listCallback = (arg, pktHdr, packets) -> {
            logger.info("==========================================");
            packets.stream().forEach(packet -> logger.info(packet.toString()));
            logger.info("-------------------------------------------");
            Packet packet = packets.get(0);
            packet.forEachRemaining(packet1 -> logger.info(packet1.toString()));
            logger.info("-------------------------------------------");
            Packet packet2 = packets.get(0);
            while (packet2.hasNext()) { // false
                logger.info(packet2.next().toString());
            }
            logger.info("==========================================");
        };
        PacketListener.Map<String> mapCallback = (arg, pktHdr, packets) -> {
            logger.info("==========================================");
            packets.forEach((aClass, packet) -> {
                logger.info(aClass + ": "+ packet.toString());
            });
            logger.info("-------------------------------------------");
            Packet packet = packets.get(Ethernet.class);
            packet.forEachRemaining(packet1 -> logger.info(packet1.toString()));
            logger.info("-------------------------------------------");
            Packet packet2 = packets.get(Ethernet.class);
            while (packet2.hasNext()) { // false
                logger.info(packet2.next().toString());
            }
            logger.info("==========================================");
        };

        PacketListener.loop(pcap, -1, listCallback, "");
        PacketListener.loop(pcap, -1, mapCallback, "");
    }

    @After
    public void close() {
        if (!pcap.isClosed()) {
            logger.info("Close handle.");
            Jxnet.PcapClose(pcap);
        } else {
            logger.info("Handle already closed.");
        }
    }

}
