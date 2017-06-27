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

package com.ardikars.jxnet.packet.ip.ipv6;

/**
 * @author Ardika Rommy Sanjaya
 * @since 1.1.0
 */
public class Fragment extends IPv6ExtensionHeader {

    private byte nextHeader;
    private short fragmentOffset;
    private byte moreFragment;
    private int identification;

    public byte getNextHeader() {
        return this.nextHeader;
    }

    public Fragment setNextHeader(final byte nextHeader) {
        this.nextHeader = nextHeader;
        return this;
    }

    public short getFragmentOffset() {
        return this.fragmentOffset;
    }

    public Fragment setFragmentOffset(final short fragmentOffset) {
        this.fragmentOffset = fragmentOffset;
        return this;
    }

    public byte getMoreFragment() {
        return this.moreFragment;
    }

    public Fragment setMoreFragment(final byte moreFragment) {
        this.moreFragment = moreFragment;
        return this;
    }

    public int getIdentification() {
        return this.identification;
    }

    public Fragment setIdentification(final int identification) {
        this.identification = identification;
        return this;
    }

}
