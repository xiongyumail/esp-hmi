json = require('json')
dump = require('dump')
wifi = require('wifi')

print(dump.table(sys.info()))
sys.delay(1000)
lcd.write('BATT', 0)
lcd.write('WIFI', 0)
lcd.write('WEATHER', '晴天')
lcd.write('TEMP', "20'C")
lcd.write('CLOCK', os.date("%H:%M:%S"))
lcd.write('DATE', os.date("%Y:%m:%d:%w"))
sys.delay(1000)
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

local info = {}
local city_sub = 'sh_temp'
local location = web.rest('GET', 'http://pv.sohu.com/cityjson')
if (location) then
    local location_json = string.match(location, '({.*});')
    local location_t = json.decode(location_json)
    print (dump.table(location_t))
    local cid_pre = string.sub(location_t.cid, 1, 3)
    if (cid_pre == '310') then
        city_sub = 'sh_temp'
    elseif (cid_pre == '360') then
        city_sub = 'nc_temp'
    end
    info.location = location_t
end

local mqtt_connected = false
mqtt.start('mqtt://mqtt.emake.run')
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
        lcd.write('DATE', os.date("%Y:%m:%d:%w"))
        if (net_info.ip.sta == '0.0.0.0') then
            lcd.write('WIFI', 0)
        else
            lcd.write('WIFI', 1)
        end
        print(string.format('RAM left: %dB', tonumber(sys_info.total_heap)))
        print(string.format('CPU load: %d%%', 100 - sys_stats.IDLE.load))
        last_1s = os.time()
    end

    local handle = mqtt.run()
    if (handle) then
        if (handle.event == 'MQTT_EVENT_DATA') then
            if (handle.topic == 'doggie_clock_msg') then
                print(handle.data)
            end
            if (handle.topic == city_sub) then
                local display = '#FF6100 '..os.date("%Y-%m-%d")..'#\n'..'#00BFFF '..net_info.ip.sta..'#\n'..'#FFC0CB '..net_info.mac.sta..'#'
                local t = json.decode(handle.data)
                display = display..'\n#FF8C00 '..LV_SYMBOL_LEFT..'WEATHER'..LV_SYMBOL_RIGHT..'#\n'..string.format('#87CEEB %s#\n#FFA500 %s %s\'C#', t.results[1].location.name, t.results[1].now.text, t.results[1].now.temperature)
                print(display)
                info.clock = os.clock()
                info.date = os.date("%Y-%m-%d %H:%M:%S")
                info.info = sys_info
                info.net = net_info
                info.cpu = 100 - sys_stats.IDLE.load
                print(json.encode(info))
                mqtt.pub('doggie_clock_info', json.encode(info), 0)
            end
        elseif (handle.event == 'MQTT_EVENT_CONNECTED') then
            mqtt_connected = true
            mqtt.sub('doggie_clock_msg', 0)
            mqtt.sub(city_sub, 0)
        elseif (handle.event == 'MQTT_EVENT_DISCONNECTED') then
            mqtt_connected = false
        end
    end

    sys_stats = sys.stats(1000)
end