///*
// * SPDX-License-Identifier: GPL-2.0-only
// */

//#include "ns3/applications-module.h"
//#include "ns3/core-module.h"
//#include "ns3/internet-module.h"
//#include "ns3/network-module.h"
//#include "ns3/point-to-point-module.h"
//#include <string>

//// Default Network Topology
////
////       10.1.1.0
//// n0 -------------- n1
////    point-to-point
////

//using namespace ns3;

//NS_LOG_COMPONENT_DEFINE("FirstScriptExample");

//int
//main(int argc, char* argv[])
//{
//    CommandLine cmd(__FILE__);
//    cmd.Parse(argc, argv);

//    Time::SetResolution(Time::NS);
//    LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
//    LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);

//    NodeContainer nodes;
//    nodes.Create(2);

//    PointToPointHelper pointToPoint;
//    pointToPoint.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
//    pointToPoint.SetChannelAttribute("Delay", StringValue("2ms"));

//    NetDeviceContainer devices;
//    devices = pointToPoint.Install(nodes);

//    InternetStackHelper stack;

//    // Disableing IPv6 because it is not necessary to show what we want to demonstrate here.
//    // Note:Normal networks typically have both IPv4 and IPv6 enabled.
//    stack.SetIpv6StackInstall(false);

//    stack.Install(nodes);

//    Ipv4AddressHelper address;
//    address.SetBase("10.1.1.0", "255.255.255.0");

//    Ipv4InterfaceContainer interfaces = address.Assign(devices);

//    UdpEchoServerHelper echoServer(9);

//    ApplicationContainer serverApps = echoServer.Install(nodes.Get(1));
//    serverApps.Start(Seconds(1));
//    serverApps.Stop(Seconds(10));

//    UdpEchoClientHelper echoClient(interfaces.GetAddress(1), 9);
//    echoClient.SetAttribute("MaxPackets", UintegerValue(1));
//    echoClient.SetAttribute("Interval", TimeValue(Seconds(1)));
//    echoClient.SetAttribute("PacketSize", UintegerValue(1024));

//    ApplicationContainer clientApps = echoClient.Install(nodes.Get(0));
//    clientApps.Start(Seconds(2));
//    clientApps.Stop(Seconds(10));

//    Simulator::Run();
//    Simulator::Destroy();
//    return 0;
//}



#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/spectrum-module.h"
#include "ns3/propagation-module.h"

#include "ns3/internet-module.h"
#include "ns3/wifi-module.h"
#include "ns3/applications-module.h"
#include "ns3/flow-monitor-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("IrsSimulationExample");

// int main(int argc, char* argv[]) {

//     CommandLine cmd (__FILE__);
//     cmd.Parse (argc, argv);

//     // 1. Create the nodes: Tx1, Tx2, IRS (Relay), and Receiver
//     NodeContainer txNodes;
//     txNodes.Create (2);
//     Ptr<Node> tx1 = txNodes.Get (0);
//     Ptr<Node> tx2 = txNodes.Get (1);

//     NodeContainer irsNode;
//     irsNode.Create (1);
//     Ptr<Node> irs = irsNode.Get (0);

//     NodeContainer rxNode;
//     rxNode.Create (1);
//     Ptr<Node> rx = rxNode.Get (0);

//     NodeContainer allNodes;
//     allNodes.Add (txNodes);
//     allNodes.Add (irsNode);
//     allNodes.Add (rxNode);

//     // 2. Set up Mobility (Positions of devices)
//     MobilityHelper mobility;

//     // Create a grid or custom layout to represent the network topology
//     Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
//     // Tx1 at (0, 0, 0), Tx2 at (0, 5, 0)
//     positionAlloc->Add (Vector (0.0, 0.0, 0.0));
//     positionAlloc->Add (Vector (0.0, 5.0, 0.0));
//     // IRS at (20, 25, 5) (Between transmitters and receiver)
//     positionAlloc->Add (Vector (20.0, 25.0, 5.0));
//     // Receiver at (40, 25, 0)
//     positionAlloc->Add (Vector (40.0, 25.0, 0.0));


//     mobility.SetPositionAllocator (positionAlloc);
//     mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
//     mobility.Install (allNodes);

//     // 3. Install Internet Stack
//     InternetStackHelper internet;
//     internet.Install (allNodes);

//     // 4. Install Wi-Fi Devices (Ad-hoc setup)
//     WifiHelper wifi;
//     wifi.SetStandard (WIFI_STANDARD_80211ax);

//     WifiMacHelper mac;
//     mac.SetType ("ns3::AdhocWifiMac");

//     YansWifiPhyHelper wifiPhy;
//     // YansWifiChannelHelper wifiChannel = YansWifiChannelHelper::Default ();
//     YansWifiChannelHelper wifiChannel;
//     wifiChannel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
//     wifiChannel.AddPropagationLoss ("ns3::LogDistancePropagationLossModel");
//     wifiPhy.SetChannel (wifiChannel.Create ());

//     NetDeviceContainer devices = wifi.Install (wifiPhy, mac, allNodes);

//     // 5. Assign IP Addresses
//     Ipv4AddressHelper address;
//     address.SetBase ("10.1.1.0", "255.255.255.0");
//     Ipv4InterfaceContainer interfaces = address.Assign (devices);

//     // 6. Set up UDP Echo Server on the receiver (Rx)
//     UdpEchoServerHelper echoServer (9);
//     ApplicationContainer serverApps = echoServer.Install (rx);
//     serverApps.Start (Seconds (1.0));
//     serverApps.Stop (Seconds (10.0));

//     // 7. Set up UDP Echo Clients on Tx1 and Tx2
//     // We send traffic from both transmitters to the receiver's IP
//     Ipv4Address rxAddress = interfaces.GetAddress (3); // Index 3 is the rxNode

//     UdpEchoClientHelper echoClient1 (rxAddress, 9);
//     echoClient1.SetAttribute ("MaxPackets", UintegerValue (10));
//     echoClient1.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
//     echoClient1.SetAttribute ("PacketSize", UintegerValue (1024));
//     ApplicationContainer clientApps1 = echoClient1.Install (tx1);
//     clientApps1.Start (Seconds (2.0));
//     clientApps1.Stop (Seconds (10.0));

//     UdpEchoClientHelper echoClient2 (rxAddress, 9);
//     echoClient2.SetAttribute ("MaxPackets", UintegerValue (10));
//     echoClient2.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
//     echoClient2.SetAttribute ("PacketSize", UintegerValue (1024));
//     ApplicationContainer clientApps2 = echoClient2.Install (tx2);
//     clientApps2.Start (Seconds (2.0));
//     clientApps2.Stop (Seconds (10.0));

//     // Run the simulation
//     Simulator::Run ();
//     Simulator::Destroy ();

//     return 0;
// }
int main (int argc, char *argv[]){
    CommandLine cmd (__FILE__);
    cmd.Parse (argc, argv);

    // Enable logging for UDP Echo Client and Server
    LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
    LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

    // Create the nodes: Tx1, Tx2, IRS (Relay), and Receiver
    NodeContainer txNodes;
    txNodes.Create (2);
    Ptr<Node> tx1 = txNodes.Get (0);
    Ptr<Node> tx2 = txNodes.Get (1);

    NodeContainer irsNode;
    irsNode.Create (1);
    Ptr<Node> irs = irsNode.Get (0);

    NodeContainer rxNode;
    rxNode.Create (1);
    Ptr<Node> rx = rxNode.Get (0);

    NodeContainer allNodes;
    allNodes.Add (txNodes);
    allNodes.Add (irsNode);
    allNodes.Add (rxNode);

    // 2. Set up Mobility (Positions of devices)
    MobilityHelper mobility;

    Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
    // Tx1 at (0, 0, 0), Tx2 at (0, 5, 0)
    positionAlloc->Add (Vector (0.0, 0.0, 0.0));
    positionAlloc->Add (Vector (0.0, 5.0, 0.0));
    // IRS at (20, 25, 5)
    positionAlloc->Add (Vector (20.0, 25.0, 5.0));
    // Receiver at (40, 25, 0)
    positionAlloc->Add (Vector (40.0, 25.0, 0.0));

    mobility.SetPositionAllocator (positionAlloc);
    mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
    mobility.Install (allNodes);

    // Install Internet Stack
    InternetStackHelper internet;
    internet.Install (allNodes);

    // Install Wi-Fi Devices (Ad-hoc setup)
    WifiHelper wifi;
    wifi.SetStandard (WIFI_STANDARD_80211ax);

    WifiMacHelper mac;
    mac.SetType ("ns3::AdhocWifiMac");

    // FIX: Instantiate helper directly without ::Default()
    YansWifiPhyHelper wifiPhy;

    // Create and configure the channel helper directly
    YansWifiChannelHelper wifiChannel;
    wifiChannel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
    wifiChannel.AddPropagationLoss ("ns3::LogDistancePropagationLossModel");

    wifiPhy.SetChannel (wifiChannel.Create ());

    NetDeviceContainer devices = wifi.Install (wifiPhy, mac, allNodes);

    // Assign IP Addresses
    Ipv4AddressHelper address;
    address.SetBase ("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces = address.Assign (devices);

    // Set up UDP Echo Server on the receiver (Rx)
    UdpEchoServerHelper echoServer (9);
    ApplicationContainer serverApps = echoServer.Install (rx);
    serverApps.Start (Seconds (1.0));
    serverApps.Stop (Seconds (10.0));

    // Set up UDP Echo Clients on Tx1 and Tx2
    Ipv4Address rxAddress = interfaces.GetAddress (3); // Index 3 is the rxNode

    UdpEchoClientHelper echoClient1 (rxAddress, 9);
    echoClient1.SetAttribute ("MaxPackets", UintegerValue (10));
    echoClient1.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
    echoClient1.SetAttribute ("PacketSize", UintegerValue (1024));
    ApplicationContainer clientApps1 = echoClient1.Install (tx1);
    clientApps1.Start (Seconds (2.0));
    clientApps1.Stop (Seconds (10.0));

    UdpEchoClientHelper echoClient2 (rxAddress, 9);
    echoClient2.SetAttribute ("MaxPackets", UintegerValue (10));
    echoClient2.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
    echoClient2.SetAttribute ("PacketSize", UintegerValue (1024));
    ApplicationContainer clientApps2 = echoClient2.Install (tx2);
    clientApps2.Start (Seconds (2.0));
    clientApps2.Stop (Seconds (10.0));

    // This is used for setting up the flow monitor to help allow us to retrieve data during the simulation
    // FlowMonitorHelper flowmon;
    // Ptr<FlowMonitor> monitor = flowmon.InstallAll ();

    // monitor->SerializeToXmlFile ("irs-flowmon.xml", true, true);

    Simulator::Run ();
    Simulator::Destroy ();

    // Post-simulation, we saved the data recorded during the simulation execution

    return 0;
}
