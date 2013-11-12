### logapi broken on 4.1.0



The code Working properly at 4.0.1 and 4.0.2


4.1.0 broken (such as cacheurl plugin)


	Usage:
		make
		cp logapi.so /usr/lib64/trafficserver/plugins

	config:
		add logapi.so to plugin.config


	run:
		restart ats
		
		
cat diags.log 

[Nov 12 10:45:50.540] {0x2ad9925ee520} STATUS: opened /var/log/trafficserver/diags.log

[Nov 12 10:45:50.540] {0x2ad9925ee520} NOTE: updated diags config
[Nov 12 10:45:50.544] Server {0x2ad9925ee520} NOTE: cache clustering disabled
[Nov 12 10:45:50.564] Server {0x2ad9925ee520} NOTE: ip_allow.config updated, reloading

[Nov 12 10:45:50.578] Server {0x2ad9925ee520} NOTE: cache clustering disabled

[Nov 12 10:45:50.581] Server {0x2ad9925ee520} NOTE: logging initialized[15], logging_mode = 3

[Nov 12 10:45:50.582] Server {0x2ad9925ee520} NOTE: loading plugin '/usr/lib64/trafficserver/plugins/logapi.so'

**[Nov 12 10:45:50.585] Server {0x2ad9925ee520} NOTE: Rolling interval adjusted from 0 sec to 300 sec for /var/log/trafficserver/logapi.log**

[Nov 12 10:45:50.601] Server {0x2ad9925ee520} NOTE: traffic server running
[Nov 12 10:45:51.877] Server {0x2ad993c23700} NOTE: cache enabled


	remap.config:
	
		map http://www.test.com/	http://172.16.1.1/


	for Test:
		
		wget -SO /dev/null -e http_proxy=127.0.0.1 http://www.test.com/ben.bc
		



