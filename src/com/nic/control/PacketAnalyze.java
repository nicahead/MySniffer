package com.nic.control;
import java.io.UnsupportedEncodingException;
import java.util.HashMap;
import jpcap.packet.*;


public class PacketAnalyze {
	static Packet packet;
	static HashMap<String,String> att,att1;
	public PacketAnalyze(Packet packet){
		this.packet = packet;	
	}
	public static HashMap<String,String> packetClass(){
		att1 = new HashMap<String,String>();
		if(packet.getClass().equals(ICMPPacket.class)){
			att1 = ICMPanalyze();
		}else if(packet.getClass().equals(TCPPacket.class)){
			att1 = TCPanalyze();
		}else if(packet.getClass().equals(UDPPacket.class)){
			att1 = UDPanalyze();
		}
		return att;
	}
	public static HashMap<String,String> IPanalyze(){
		att = new HashMap<String,String>();
		if(packet instanceof IPPacket){
			IPPacket ippacket = (IPPacket) packet;
			att.put("协议", new String("IP"));
			att.put("源IP", ippacket.src_ip.toString().substring(1, ippacket.src_ip.toString().length()));
			att.put("目的IP", ippacket.dst_ip.toString().substring(1, ippacket.dst_ip.toString().length()));
			att.put("TTL", String.valueOf(ippacket.hop_limit));
			att.put("头长度", String.valueOf(ippacket.header.length));
			att.put("是否有其他切片", String.valueOf(ippacket.more_frag));
		}
		return att;
	}
	public static HashMap<String,String> ICMPanalyze(){
		att = new HashMap<String,String>();
		ICMPPacket icmppacket = (ICMPPacket) packet;
		att.put("协议", new String("ICMP"));
		att.put("源IP", icmppacket.src_ip.toString().substring(1, icmppacket.src_ip.toString().length()));
		att.put("目的IP", icmppacket.dst_ip.toString().substring(1, icmppacket.dst_ip.toString().length()));
		return att;
	}
	public static HashMap<String,String> TCPanalyze(){
		att = new HashMap<String,String>();
		TCPPacket tcppacket = (TCPPacket) packet;
		EthernetPacket ethernetPacket=(EthernetPacket)packet.datalink;
		att.put("协议", new String("TCP"));
		att.put("源IP", tcppacket.src_ip.toString().substring(1, tcppacket.src_ip.toString().length()));
		att.put("源端口", String.valueOf(tcppacket.src_port));
		att.put("目的IP", tcppacket.dst_ip.toString().substring(1, tcppacket.dst_ip.toString().length()));
		att.put("目的端口", String.valueOf(tcppacket.dst_port));
		att.put("源MAC", ethernetPacket.getSourceAddress());
		att.put("目的MAC", ethernetPacket.getDestinationAddress());
		try {
			att.put("数据", new String(tcppacket.data,"gbk"));
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		}
		return att;
	}
	public static HashMap<String,String> UDPanalyze(){
		att = new HashMap<String,String>();
		UDPPacket udpppacket = (UDPPacket) packet;
		EthernetPacket ethernetPacket=(EthernetPacket)packet.datalink;
		att.put("协议", new String("UDP"));
		att.put("源IP", udpppacket.src_ip.toString().substring(1, udpppacket.src_ip.toString().length()));
		att.put("源端口", String.valueOf(udpppacket.src_port));
		att.put("目的IP", udpppacket.dst_ip.toString().substring(1, udpppacket.dst_ip.toString().length()));
		att.put("目的端口", String.valueOf(udpppacket.dst_port));
		att.put("源MAC", ethernetPacket.getSourceAddress());
		att.put("目的MAC", ethernetPacket.getDestinationAddress());
		try {
			att.put("数据", new String(udpppacket.data,"gbk"));
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		}
	
		return att;
	}
}
