# -*- coding: utf-8 -*-
import requests
import re
import time
import csv
from lxml import etree

class DoubanSpider():
    
    def __init__(self):
        
        self.s = requests.session()
        self.url = "https://book.douban.com/"
        self.basic_tag_url = "https://book.douban.com/tag/"
    
    def getTagBooks(self, tag, num):
        """根据书籍标签tag抓取num本书"""
        index = 500
        i = 0
        for page_start in range(index, num + index, 20):
            # 要爬取的网址实例：https://book.douban.com/tag/文学?start=page_start/
            # page_start表示每页20本书中第一本书的序号
            time.sleep(1)
            url = self.basic_tag_url + tag + "?start=" + str(page_start)
            headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) \
                AppleWebKit/537.36 (KHTML, like Gecko) Chrome/85.0.4183.120 Safari/537.36',
                }
            response = requests.get(url, headers = headers)
            r_html = etree.HTML(response.content)
            item_list = r_html.xpath("//li[@class='subject-item']")
            for item in item_list:
                book = [tag]
                info = item.xpath("./div[2]")[0]
                try:
                    book.append(info.xpath("./h2/a/text()")[0].strip())
                    book.append(info.xpath("./div/span[@class='rating_nums']/text()")[0])
                    book.append(info.xpath("./div[@class='pub']/text()")[0].split('/')[0].replace('\n', '').strip())
                # 进入详情页获取更多信息
                    content_url = item.xpath("./div[@class='info']/h2/a/@href")[0]
                    content = etree.HTML(requests.get(content_url, headers = headers).content)
                    info = content.xpath("//div[@id='info']")[0]
                    # book['writer'] = info.xpath("./a[@href]/text()")[0]
                    info_str = etree.tostring(info, encoding = 'utf-8').decode()
                    book.append(re.findall(r'<span class="pl">出版社:</span> (.*)<br/>', info_str)[0])
                    book.append(re.findall(r'<span class="pl">出版年:</span> (.*)<br/>', info_str)[0])
                    book.append(re.findall(r'<span class="pl">定价:</span>\D+(\d+\.?\d+).*<br/>', info_str)[0])
                    book.append(re.findall(r'<span class="pl">页数:</span> (\d+).*<br/>', info_str)[0])
                    
                    file = open('book_item.csv', 'a+', newline = '', encoding='utf-8')
                    writer = csv.writer(file)
                    writer.writerow(book)
                    file.close()
                    print(i)
                    i += 1
                except:
                    continue