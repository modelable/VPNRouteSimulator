<h2>명령어 예시</h2>

<h3>장치 설정</h3>
<pre>
<code>
config 192.168.1.1 255.255.255.0
config 192.168.2.1 255.255.255.0
config 1.0.0.1 255.0.0.0
config 2.0.0.1 255.0.0.0
config 3.0.0.1 255.0.0.0
</code>
</pre>

<h3>라우팅 설정</h3>
<pre>
<code>
route 192.168.1.1 1.0.0.1
route 1.0.0.1 2.0.0.1
route 2.0.0.1 3.0.0.1
route 3.0.0.1 192.168.2.1
</code>
</pre>

<h3>테스트 (tracert)</h3>
<pre>
<code>
tracert 192.168.1.1 192.168.2.1
</code>
</pre>

<h3>터널링 설정</h3>
<pre>
<code>
tunnel 1.0.0.1 3.0.0.1
</code>
</pre>

<h3>테스트 (tracert, ping)</h3>
<pre>
<code>
tracert 192.168.1.1 192.168.2.1
ping 192.168.1.1 192.168.2.1
</code>
</pre>