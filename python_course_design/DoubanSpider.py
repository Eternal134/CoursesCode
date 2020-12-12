# -*- coding: utf-8 -*-
import requests
import re
import time
import csv
from lxml import etree

class DoubanSpider():
    
    def __init__(self):
        
        self.basic_tag_url = "https://book.douban.com/tag/"
    
    def getTagBooks(self, tag, num):
        """根据书籍标签tag抓取num本书"""
        index = 600
        i = 0
        for page_start in range(index, num + index, 20):
            # 要爬取的网址实例：https://book.douban.com/tag/文学?start=page_start/
            # page_start表示每页20本书中第一本书的序号
            time.sleep(1)
            url = self.basic_tag_url + tag + "?start=" + str(page_start)
            headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) \
                AppleWebKit/537.36 (KHTML, like Gecko) Chrome/85.0.4183.120 Safari/537.36',
                }
            # 提交网络请求
            response = requests.get(url, headers = headers, timeout = 2)
            # 生成etree对象
            r_html = etree.HTML(response.content)
            # 获取页面上所有的li标签
            item_list = r_html.xpath("//li[@class='subject-item']")
            for item in item_list:
                book = [tag]
                info = item.xpath("./div[2]")[0]
                try:
                    ''' 有些书籍的页面很不规则，如果在提取信息的时候发生错误，选择直接舍弃掉该本书 '''
                    # 书名
                    book.append(info.xpath("./h2/a/text()")[0].strip())
                    # 评分
                    book.append(info.xpath("./div/span[@class='rating_nums']/text()")[0])
                    # 作者
                    book.append(info.xpath("./div[@class='pub']/text()")[0].split('/')[0].replace('\n', '').strip())
                    # 详情页网址
                    content_url = item.xpath("./div[@class='info']/h2/a/@href")[0]
                    content = etree.HTML(requests.get(content_url, headers = headers).content)
                    info = content.xpath("//div[@id='info']")[0]
                    ''' 提取感兴趣的信息 '''
                    info_str = etree.tostring(info, encoding = 'utf-8').decode()
                    # 出版社
                    book.append(re.findall(r'<span class="pl">出版社:</span> (.*)<br/>', info_str)[0])
                    # 出版日期
                    book.append(re.findall(r'<span class="pl">出版年:</span> (.*)<br/>', info_str)[0])
                    # 价格
                    price = re.findall(r'<span class="pl">定价:</span> (.*)<br/>', info_str)[0]
                    try:
                        # 如果price不是纯数字，此处会报错，如果是纯数字，则保留这个值
                        float(price)
                        book.append(price)
                    except:
                        # 如果不是纯数字而且price里没有'元'，大概率不是人民币价格，舍弃掉此样本
                        if '元' in price:
                            book.append(re.findall(r'(\d+.?\d+)', price)[0])
                        else:
                            continue
                    # 页数
                    book.append(re.findall(r'<span class="pl">页数:</span> (\d+).*<br/>', info_str)[0])
                    ''' 写入文件 '''
                    file = open('book_item.csv', 'a+', newline = '', encoding='utf-8')
                    writer = csv.writer(file)
                    writer.writerow(book)
                    file.close()
                    # 打印本次爬取了多少本书
                    print(i)
                    i += 1
                except:
                    continue
                
if __name__ == "__main__":

    # 要爬取图书的总量
    books_sum = 4000
    spider = DoubanSpider()
    # book_types = ['推理', '文学', '诗歌', '计算机', '科普', '爱情', '心理', '经济学', '历史', '漫画']
    book_types = ['漫画']
    books = []
    for tag in book_types:
        books = spider.getTagBooks(tag, int(books_sum / len(book_types)))