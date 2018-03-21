package com.nic.control;

import jpcap.*;

public class NetworkCard {
	String[] devices;
	public static NetworkInterface[] getDevices() {
	    NetworkInterface[] devices = JpcapCaptor.getDeviceList();
		return devices;
	}
}
