<h2>명령어 예시</h2>
config 192.168.1.1 255.255.255.0<br>
config 192.168.2.1 255.255.255.0<br>
config 1.0.0.1 255.0.0.0<br>
config 2.0.0.1 255.0.0.0<br>
route 192.168.1.1 1.0.0.1<br>
route 1.0.0.1 2.0.0.1<br>
route 2.0.0.1 192.168.2.1<br>
tracert 192.168.1.1 192.168.2.1<br>
ping 192.168.1.1 192.168.2.1<br>
ping 192.168.1.1 192.168.3.1<br>
