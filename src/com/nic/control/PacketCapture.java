package com.nic.control;

import java.io.IOException;
import java.text.*;
import java.util.*;
import javax.swing.*;
import javax.swing.table.*;
import jpcap.*;
import jpcap.packet.*;

/*抓包*/
public class PacketCapture implements Runnable {

	NetworkInterface device;
	static DefaultTableModel tablemodel;
	static String FilterMess = "";
	static ArrayList<Packet> packetlist = new ArrayList<Packet>();
	public PacketCapture() {
	}
	public void setDevice(NetworkInterface device){
		this.device = device;
	}
	public void setTable(DefaultTableModel tablemodel){
		this.tablemodel = tablemodel;
	}
	public void setFilter(String FilterMess){
		this.FilterMess = FilterMess;
	}
	public void clearpackets(){
		packetlist.clear();
	}
	@Override
	public void run() {
		// TODO Auto-generated method stub
		Packet packet;
		try {
			JpcapCaptor captor = JpcapCaptor.openDevice(device, 65535,true, 20);
			//System.out.println(device.name);
			while(true){
				long startTime = System.currentTimeMillis();
				while (startTime + 600 >= System.currentTimeMillis()) {
					//captor.setFilter(FilterMess, true);
					packet = captor.getPacket();
					// 设置过滤器
					if(packet!=null&&TestFilter(packet)){
						//System.out.println(packet);
						packetlist.add(packet);
						showTable(packet);
					}
				}
				Thread.sleep(2000);
			}
		} catch (IOException e) {
			e.printStackTrace();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}	
	}
	//将抓到包的信息添加到列表
	public static void showTable(Packet packet){
		String[] rowData = getObj(packet);
		tablemodel.addRow(rowData);
	}
	//其他类通过此方法获取Packet的列表
	public static ArrayList<Packet> getpacketlist(){
		return packetlist;
	}
	//设置过滤规则
	public static boolean TestFilter(Packet packet){
		if(FilterMess.contains("sip")){
			String sip = FilterMess.substring(4, FilterMess.length());
			if(new PacketAnalyze(packet).packetClass().get("源IP").equals(sip)){
				return true;
			}
		}else if(FilterMess.contains("dip")){
			String dip = FilterMess.substring(4, FilterMess.length());
			if(new PacketAnalyze(packet).packetClass().get("目的IP").equals(dip)){
				return true;
			}
		}else if(FilterMess.contains("ICMP")){
			if(new PacketAnalyze(packet).packetClass().get("协议").equals("ICMP")){
				return true;
			}
		}
		else if(FilterMess.contains("UDP")){
			if(new PacketAnalyze(packet).packetClass().get("协议").equals("UDP")){
				return true;
			}
		}else if(FilterMess.contains("TCP")){
			if(new PacketAnalyze(packet).packetClass().get("协议").equals("TCP")){
				return true;
			}
		}else if(FilterMess.contains("keyword")){
			String keyword = FilterMess.substring(8, FilterMess.length());
			if(new PacketAnalyze(packet).packetClass().get("数据").contains(keyword)){
				return true;
			}
		}else if(FilterMess.equals("")){
			return true;
		}
		return false;
	}
	//将抓的包的基本信息显示在列表上，返回信息的String[]形式
	public static String[] getObj(Packet packet){
		String[] data = new String[6];
		if (packet != null&&new PacketAnalyze(packet).packetClass().size()>=3) {
			Date d = new Date();
			DateFormat df = new SimpleDateFormat("HH:mm:ss");
			data[0]=df.format(d);
			data[1]=new PacketAnalyze(packet).packetClass().get("源IP");
			data[2]=new PacketAnalyze(packet).packetClass().get("目的IP");
			data[3]=new PacketAnalyze(packet).packetClass().get("协议");
			data[4]=String.valueOf(packet.len);
		}
		return data;
	}
}
