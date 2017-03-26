package com.ardikars.test;

import static com.ardikars.jxnet.Jxnet.*;

import com.ardikars.jxnet.BpfProgram;
import com.ardikars.jxnet.Jxnet;
import com.ardikars.jxnet.Pcap;
import com.ardikars.jxnet.PcapPktHdr;
import com.ardikars.jxnet.exception.PcapCloseException;
import org.junit.Assert;
import org.junit.Test;

import java.nio.ByteBuffer;

public class PcapNext {
	
	@Test
	public void run() throws PcapCloseException {
		StringBuilder errbuf = new StringBuilder();
		String dev = "eth0";//AllTests.deviceName;
		Pcap handler = PcapOpenLive(dev, AllTests.snaplen, AllTests.promisc, AllTests.to_ms, errbuf);
		if (handler == null) {
			throw new PcapCloseException(errbuf.toString());
		}

		BpfProgram fp = new BpfProgram();
		Jxnet.PcapCompile(handler, fp, "icmp", 1, 0xffffffff);
		Jxnet.PcapSetFilter(handler, fp);

		Assert.assertNotEquals(null, handler);
		boolean err = false;
		PcapPktHdr pkthdr = new PcapPktHdr();
		for (int i = 0; i < 10; i++) {
			ByteBuffer buf = PcapNext(handler, pkthdr);
			System.out.println(buf);
			if (buf == null || pkthdr == null) {
				err = true;
			}
		}
		PcapClose(handler);
		//Assert.assertFalse(err);
	}
	
}