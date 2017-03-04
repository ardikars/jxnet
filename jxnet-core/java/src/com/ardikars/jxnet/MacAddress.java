/**
 * Copyright (C) 2017  Ardika Rommy Sanjaya
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

package com.ardikars.jxnet;

import com.ardikars.jxnet.util.FormatUtils;

import java.util.Arrays;

/**
 * @author Ardika Rommy Sanjaya
 * @since 1.0.0
 * @version 1.1.0
 */
public final class MacAddress {

	private static native void initIDs();
	
	public static final int MAC_ADDRESS_LENGTH = 6;

	/**
	 * Zero MAC Address (00:00:00:00:00:00).
	 */
	public static final MacAddress ZERO = valueOf("00:00:00:00:00:00");

	/**
	 * Broadcast MAC Address (ff:ff:ff:ff:ff:ff).
	 */
	public static final MacAddress BROADCAST = valueOf("ff:ff:ff:ff:ff:ff");
	
	public static final MacAddress IPV4_MULTICAST = valueOf("01:00:5e:00:00:00");
	
	public static final MacAddress IPV4_MULTICAST_MASK = valueOf("ff:ff:ff:80:00:00");
	
	private byte[] address = new byte[MacAddress.MAC_ADDRESS_LENGTH];
	
	private MacAddress(final byte[] address) {
		this.address = Arrays.copyOf(address, MacAddress.MAC_ADDRESS_LENGTH);
	}

	/**
	 * Create MacAddress object.
	 * @param address string MAC Address.
	 * @return MacAddress object.
	 */
	public static MacAddress valueOf(final String address) {
		final String[] elements = address.split(":");
		if (elements.length != MacAddress.MAC_ADDRESS_LENGTH) {
			throw new IllegalArgumentException(
					"Specified MAC Address must contain 12 hex digits" + " separated pairwise by :'s.");
		}
		final byte[] b = new byte[MacAddress.MAC_ADDRESS_LENGTH];
		for (int i = 0; i < MacAddress.MAC_ADDRESS_LENGTH; i++) {
			final String element = elements[i];
			b[i] = (byte) Integer.parseInt(element, 16);
		}
		return new MacAddress(b);
	}

	/**
	 * Create MacAddress object.
	 * @param address bytes MAC Address.
	 * @return MacAddress object.
	 */
	public static MacAddress valueOf(final byte[] address) {
		if (address.length != MacAddress.MAC_ADDRESS_LENGTH) {
			throw new IllegalArgumentException("the length is not "
					+ MacAddress.MAC_ADDRESS_LENGTH);
		}
		return new MacAddress(address);
	}

	/**
	 * Create MacAddress object.
	 * @param address long MAC Address.
	 * @return MacAddress object.
	 */
	public static MacAddress valueOf(final long address) {
		final byte[] bytes = new byte[] {
				(byte) (address >> 40 & 0xff),
				(byte) (address >> 32 & 0xff),
				(byte) (address >> 24 & 0xff),
				(byte) (address >> 16 & 0xff),
				(byte) (address >> 8 & 0xff),
				(byte) (address >> 0 & 0xff)};
		return new MacAddress(bytes);
	}

	/**
	 * Reuturning length of MAC Address.
	 * @return MAC Address length.
	 */
	public int length() {
		return this.address.length;
	}

	/**
	 * Returning bytes MAC Address.
	 * @return bytes MAC Address.
	 */
	public byte[] toBytes() {
		return Arrays.copyOf(this.address, this.address.length);
	}

	/**
	 * Returning long MAC Address.
	 * @return long MAC Address.
	 */
	public long toLong() {
		long addr = 0;
		for (int i=0; i<MAC_ADDRESS_LENGTH; i++) {
			long tmp = (this.address[i] & 0xffL) << (5 - i) *8;
			addr |= tmp;
		}
		return addr;
	}

	/**
	 * Return true if Broadcast MAC Address.
	 * @return true if Broadcast MAC Address, false otherwise.
	 */
	public boolean isBroadcast() {
		for (final byte b : this.address) {
			if (b != -1) {
				return false;
			}
		}
		return true;
	}

	/**
	 * Return true if Multicast MAC Address.
	 * @return true if Multicast MAC Address, false otherwise.
	 */
	public boolean isMulticast() {
		if (this.isBroadcast()) {
			return false;
		}
		return (this.address[0] & 0x01) != 0;
	}

	@Override
	public boolean equals(Object obj) {
		if (obj == this)
			return true;
		if (obj.getClass() != getClass())
			return false;
		if (obj instanceof MacAddress) {
			final MacAddress addr = (MacAddress) obj;
			return Arrays.equals(this.address, addr.toBytes());
		}
		return false;
	}

	@Override
	public int hashCode() {
		return Long.hashCode(toLong());
	}

	@Override
	public String toString() {
		final StringBuilder sb = new StringBuilder();
		for (final byte b : this.address) {
			if (sb.length() > 0) {
				sb.append(":");
			}
			sb.append(FormatUtils.toHexString(b));
		}
		return sb.toString();
	}

	static {
		try {
			Class.forName("com.ardikars.jxnet.Jxnet");
			initIDs();
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
	}
	
}