json = require('json')
dump = require('dump')
wifi = require('wifi')

print(dump.table(sys.info()))
sys.delay(1000)
if (not wifi.start_sta('ziroom406', 'ziroomer002')) then
    print('Connect to AP and log in to http://192.168.1.1 and configure router information')
    wifi.start_ap('doggie_clock', '')
else
    sys.delay(1000)
    print(dump.table(net.info()))
end

sys.sntp('ntp1.aliyun.com')

while (1) do
    sys.delay(1000)
    print(os.date("%Y-%m-%d %H:%M:%S"))
    print(dump.table(sys.info()))
end
