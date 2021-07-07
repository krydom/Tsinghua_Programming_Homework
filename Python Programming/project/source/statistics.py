import pandas
import xlsxwriter


china_province = ["北京", "天津", "上海", "重庆", "河北", "山西", "辽宁", "吉林", "黑龙江", "江苏", "浙江", "安徽", "福建", "江西", "山东", "河南", "湖北", "湖南", "广东", "海南", "四川", "贵州", "云南", "陕西", "甘肃", "青海", "台湾", "内蒙古", "广西", "西藏", "宁夏", "新疆", "香港", "澳门"]
days = [31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
weeks = [4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5]
workbook = xlsxwriter.Workbook('statistics.xlsx')
worksheet_dailyprovince = workbook.add_worksheet("day_province")
worksheet_monthlyprovince = workbook.add_worksheet("month_province")
worksheet_top3province = workbook.add_worksheet("month_top4_province")
worksheet_dailycountry = workbook.add_worksheet("day_country-region")
worksheet_monthlycountry = workbook.add_worksheet("month_country-region")
worksheet_top3country = workbook.add_worksheet("month_top4_country-region")
worksheet_weeklyprovince = workbook.add_worksheet("week_province")


def get_month(day):
    for i in range(12):
        day = day - days[i]
        if (day <= 0):
            return i + 1


def get_day(day):
    for i in range(12):
        day = day - days[i]
        if (day <= 0):
            return day + days[i]


def output_dailyprovince():
    for i in range(len(china_province)):
        worksheet_dailyprovince.write(0, i + 1, china_province[i])
    for i in range(1, 367):
        worksheet_dailyprovince.write(i, 0, "{}/{}".format(get_month(i), get_day(i)))
        for j in range(len(china_province)):
            if (appear[i][j] == 1):
                worksheet_dailyprovince.write(i, j + 1, 1)


def output_dailycountry():
    for i in range(len(world_country)):
        worksheet_dailycountry.write(0, i + 1, world_country[i])
    for i in range(1, 367):
        worksheet_dailycountry.write(i, 0, "{}/{}".format(get_month(i), get_day(i)))
        for j in range(len(world_country)):
            if (appear[i][j] == 1):
                worksheet_dailycountry.write(i, j + 1, 1)


def output_weeklyprovince():
    for i in range(len(china_province)):
        worksheet_weeklyprovince.write(0, i + 1, china_province[i])
    for i in range(1, 54):
        worksheet_weeklyprovince.write(i, 0, i)
    sum = [[0 for i in range(len(china_province))] for i in range(55)]
    worksheet_weeklyprovince.write(54, 0, 'total')
    for j in range(len(china_province)):
        now = 0
        for i in range(53):
            for k in range(weeks[i]):
                now = now + 1
                sum[i+1][j] = sum[i+1][j] + appear[now][j]
                sum[54][j] = sum[54][j] + appear[now][j]
            worksheet_monthlyprovince.write(i + 1, j + 1, sum[i+1][j])
        worksheet_monthlyprovince.write(54, j + 1, sum[54][j])

def output_monthlyprovince():
    for i in range(len(china_province)):
        worksheet_monthlyprovince.write(0, i + 1, china_province[i])
    for i in range(1, 13):
        worksheet_monthlyprovince.write(i, 0, i)
        worksheet_top3province.write(i, 0, i)
    sum = [[0 for i in range(len(china_province))] for i in range(14)]
    worksheet_monthlyprovince.write(13, 0, 'total')
    worksheet_top3province.write(13, 0, 'total')
    for j in range(len(china_province)):
        now = 0
        for i in range(12):
            for k in range(days[i]):
                now = now + 1
                sum[i+1][j] = sum[i+1][j] + appear[now][j]
                sum[13][j] = sum[13][j] + appear[now][j]
            worksheet_monthlyprovince.write(i + 1, j + 1, sum[i+1][j])
        worksheet_monthlyprovince.write(13, j + 1, sum[13][j])

    for i in range(1, 5):
        worksheet_top3province.write(0, i, "top{}".format(i))
    wh4 = ''
    wh3 = ''
    wh2 = ''
    wh1 = ''
    for i in range(1, 14):
        mx1 = 0
        mx2 = 0
        mx3 = 0
        mx4 = 0
        for j in range(len(china_province)):
            if sum[i][j] > mx1:
                mx4 = mx3
                wh4 = wh3
                mx3 = mx2
                wh3 = wh2
                mx2 = mx1
                wh2 = wh1
                mx1 = sum[i][j]
                wh1 = china_province[j]
            elif sum[i][j] > mx2:
                mx4 = mx3
                wh4 = wh3
                mx3 = mx2
                wh3 = wh2
                mx2 = sum[i][j]
                wh2 = china_province[j]
            elif sum[i][j] > mx3:
                mx4 = mx3
                wh4 = wh3
                mx3 = sum[i][j]
                wh3 = china_province[j]
            elif sum[i][j] > mx4:
                mx4 = sum[i][j]
                wh4 = china_province[j]
        worksheet_top3province.write(i, 1, wh1)
        worksheet_top3province.write(i, 2, wh2)
        worksheet_top3province.write(i, 3, wh3)
        worksheet_top3province.write(i, 4, wh4)


def output_monthlycountry():
    for i in range(len(world_country)):
        worksheet_monthlycountry.write(0, i + 1, world_country[i])
    for i in range(1, 13):
        worksheet_monthlycountry.write(i, 0, i)
        worksheet_top3country.write(i, 0, i)
    sum = [[0 for i in range(len(world_country))] for i in range(14)]
    worksheet_monthlycountry.write(13, 0, 'total')
    worksheet_top3country.write(13, 0, 'total')
    for j in range(len(world_country)):
        now = 0
        for i in range(12):
            for k in range(days[i]):
                now = now + 1
                sum[i+1][j] = sum[i+1][j] + appear[now][j]
                sum[13][j] = sum[13][j] + appear[now][j]
            worksheet_monthlycountry.write(i + 1, j + 1, sum[i+1][j])
        worksheet_monthlycountry.write(13, j + 1, sum[13][j])

    for i in range(1, 5):
        worksheet_top3country.write(0, i, "top{}".format(i))
    wh4 = ''
    wh3 = ''
    wh2 = ''
    wh1 = ''
    for i in range(1, 14):
        mx1 = 0
        mx2 = 0
        mx3 = 0
        mx4 = 0
        for j in range(len(world_country)):
            if sum[i][j] > mx1:
                mx4 = mx3
                wh4 = wh3
                mx3 = mx2
                wh3 = wh2
                mx2 = mx1
                wh2 = wh1
                mx1 = sum[i][j]
                wh1 = world_country[j]
            elif sum[i][j] > mx2:
                mx4 = mx3
                wh4 = wh3
                mx3 = mx2
                wh3 = wh2
                mx2 = sum[i][j]
                wh2 = world_country[j]
            elif sum[i][j] > mx3:
                mx4 = mx3
                wh4 = wh3
                mx3 = sum[i][j]
                wh3 = world_country[j]
            elif sum[i][j] > mx4:
                mx4 = sum[i][j]
                wh4 = world_country[j]
        worksheet_top3country.write(i, 1, wh1)
        worksheet_top3country.write(i, 2, wh2)
        worksheet_top3country.write(i, 3, wh3)
        worksheet_top3country.write(i, 4, wh4)


loc_list = []
appear = []
world_country = []
data = pandas.read_csv("final_2020news.csv", encoding='utf-8')
appear.append([0 for j in range(len(china_province))])
for day in range(366):
    appear_day = [0 for j in range(len(china_province))]
    loc_list = eval(data.iloc[day, 10])  # 统计出现省份
    for prov in range(len(china_province)):
        if (loc_list.count(china_province[prov])) > 0:
            appear_day[prov] = 1
    appear.append(appear_day)
    loc_list = eval(data.iloc[day, 11])  # 统计出现国家
    for coun in loc_list:
        if (china_province.count(coun) == 0 and world_country.count(coun) == 0):
            world_country.append(coun)

output_dailyprovince()
output_monthlyprovince()

appear = []
appear.append([0 for j in range(len(world_country))])
for day in range(366):
    appear_day = [0 for j in range(len(world_country))]
    loc_list = eval(data.iloc[day, 11])
    for coun in range(len(world_country)):
        if (loc_list.count(world_country[coun])) > 0:
            appear_day[coun] = 1
    appear.append(appear_day)

output_dailycountry()
output_monthlycountry()

workbook.close()
