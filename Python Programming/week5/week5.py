import requests
import time
import re
import os
from bs4 import BeautifulSoup

my_cookies = ''
HASH = dict()
output_data = '楼层,UID,regdate,回复内容\n'


def set_cookies():
    # NGA的cookies经过了setcookie，requests得到的cookies和浏览器中的cookies不一致，直接访问的话会403。因此先要做一个cookies供requests使用。
    req = requests.get('https://bbs.nga.cn/read.php?tid=11451419')
    j = req.cookies.get_dict()
    k = int(j['lastvisit'])-1
    cookies_ = {'guestJs': str(k)}
    requests.utils.add_dict_to_cookiejar(req.cookies, cookies_)
    return req.cookies


def get_pages():   # 读取指定的投票专楼中特定的页码
    print("请输入你要计票的帖子ID。例：11451419")
    try:
        postid = input()
        int(postid)
        basic_url = 'https://bbs.nga.cn/read.php?tid={}'.format(postid)
    except:
        print(">>错误<<：请正确地输入一个帖子ID。")
        input()
        exit()

    left = 1
    right = 200

    all_comments = []
    for page in range(left, right+1):
        url = basic_url + '&page={}'.format(page)
        print("正在读取第{}页".format(page))
        for i in range(5):
            try:
                this_page_comment = get_single_page(url)
            except:
                print("出现了一个错误。正在重试({}/5)".format(i+1))
                time.sleep(1)
                continue
            break
        else:
            print(">>错误<<：看来你遇到了一个企鹅。你可以后退访问其他页面或报告管理员。")
            input()
            exit()
        # 如果本页的内容与上页完全相同，就代表已经到了末页，丢弃本页并结束循环
        if all_comments[-len(this_page_comment):] == this_page_comment:
            break
        all_comments += this_page_comment


def get_single_page(url):
    global output_data
    global HASH

    # 获取页面信息
    r = requests.get(url, cookies=my_cookies)
    r.raise_for_status()
    r.encoding = 'gbk'
    soup = BeautifulSoup(r.text.replace('<br/>', '\n'), "lxml")

    # 获取本页用户的注册时间
    userinfo = re.findall(r'"uid":([0-9]+).*?"regdate":([0-9]+)', r.text)
    for thisuser in userinfo:
        HASH.update({thisuser[0]: thisuser[1]})

    # 获取本页的所有回复
    floors = soup.find_all('a', attrs={'name': re.compile('^l')})
    comments = soup.find_all('span', class_='postcontent ubbcode')
    uids = [re.search(r'uid=([0-9]+)', str(i)).group(1) for i in soup.find_all('a', class_='author b')]
    if len(uids) != len(comments):
        uids.pop(0)  # 第一页的楼层包含了楼主而comments中没有包含，这一情况下剔除uids[0]和floors[0]
        floors.pop(0)
    comments_list = []
    for i in range(len(comments)):
        comments_list += floors[i].attrs['name'][1:]
        output_data += floors[i].attrs['name'][1:] + ',' + uids[i] + ',' + HASH[uids[i]] + ',"' + comments[i].text + '"\n'
    return comments_list


if __name__ == '__main__':
    my_cookies = set_cookies()
    get_pages()
    with open('output.csv', 'w', encoding='gbk') as f:
        f.write(output_data)
    print("已经读取完毕所有楼层的数据并保存为output.csv。按Enter键继续...")
    os.system('pause')
