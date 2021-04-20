json = require('json')
dump = require('dump')
wifi = require('wifi')

print(dump.table(sys.info()))
lcd.write('BATT', 0)
lcd.write('WIFI', 0)
sys.delay(2000)
if (not wifi.start_sta('esp-office-2.4G', '1qazxsw2')) then
    print('Connect to AP and log in to http://192.168.1.1 and configure router information')
    wifi.start_ap('doggie_clock', '')
else
    sys.delay(1000)
    print(dump.table(net.info()))
end

sys.sntp('ntp1.aliyun.com')
print(os.date("%Y-%m-%d %H:%M:%S"))
print(dump.table(sys.info()))

local last_1s = os.time()
local last_30s = os.time() - 25
local sys_info = sys.info()
local net_info = net.info()
local sys_stats = sys.stats(1000)
while (1) do
    if (os.difftime (os.time(), last_1s) >= 1) then
        sys_info = sys.info()
        net_info = net.info()
        lcd.write('CLOCK', os.date("%H:%M:%S"))
        lcd.write('DATE', os.date("%m月%d"))
        if (net_info.ip.sta == '0.0.0.0') then
            lcd.write('WIFI', 0)
        else
            lcd.write('WIFI', 1)
        end
        print(string.format('RAM left: %dB', tonumber(sys_info.total_heap)))
        print(string.format('CPU load: %d%%', 100 - sys_stats.IDLE.load))
        last_1s = os.time()
    end

    sys_stats = sys.stats(1000)
end
