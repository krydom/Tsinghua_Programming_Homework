import pandas
from time import sleep
from random import randint
from geopy.geocoders import Nominatim


china_province = ["北京", "天津", "上海", "重庆", "河北", "山西", "辽宁", "吉林", "黑龙江", "江苏", "浙江", "安徽", "福建", "江西", "山东", "河南", "湖北", "湖南", "广东", "海南", "四川", "贵州", "云南", "陕西", "甘肃", "青海", "台湾", "内蒙古", "广西", "西藏", "宁夏", "新疆", "香港", "澳门"]


user_agent = 'user_me_{}'.format(randint(10000, 99999))
geolocator = Nominatim(user_agent=user_agent)


def reverse_geocode(geolocator, loc, sleep_sec, tmp):
    try:
        return geolocator.geocode(loc, language='zh')
    except Exception:
        if (tmp == 10):
            return None
        sleep(randint(1*100, sleep_sec*100)/100)
        return reverse_geocode(geolocator, loc, sleep_sec, tmp+1)


def get_province_country(loc):
    global day_province, day_country
    for prov in china_province:  # 省份直接判断
        if loc.find(prov) != -1:
            day_province.append(prov)
            return

    location = reverse_geocode(geolocator, loc, 2, 1)  # 否则用geopy获取地理信息
    if (location is None):
        return
    addr = location.address

    for prov in china_province:  # 获取省份
        if addr.find(prov) != -1:
            day_province.append(prov)
    if addr.find("臺灣") != -1:
        day_province.append("台湾")
        return

    while addr.find(",") != -1:  # 获取国家
        pos = addr.find(",")
        addr = addr[pos + 1: len(addr)]
    addr = addr.lstrip()
    if addr.find("/") != -1:
        pos = addr.find("/")
        addr = addr[0: pos]
    if addr != "中国":
        day_country.append(addr)


if __name__ == '__main__':
    pandas.options.mode.chained_assignment = None
    day_province = []
    day_country = []
    loc_list = []

    with open("processed_2020news.csv", encoding='utf-8') as f:
        data = pandas.read_csv(f)
        data['province'] = ' '
        data['country'] = ' '
        for day in range(0, 366):
            print("Now solving day {}".format(day+1))
            loc_list = eval(data.iloc[day, 8])
            loc_list = list(set(loc_list))
            for loc in loc_list:
                loc.rstrip("'")
                get_province_country(loc)
            day_province = list(set(day_province))
            st = ''.join(str(day_province))
            data['province'][day] = st
            day_province.clear()
            day_country = list(set(day_country))
            if day_country.count("美利坚合众国") == 0:
                st = data.iloc[day, 4]
                if (st.find("美国") != -1):
                    day_country.append("美利坚合众国")
            st = ''.join(str(day_country))
            data['country'][day] = st
            day_country.clear()
    data.to_csv('final_2020news.csv', encoding='utf_8_sig')
