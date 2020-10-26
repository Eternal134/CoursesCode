import DoubanSpider
import json

books_sum = 1000
file_name = "book_items.json"
spider = DoubanSpider.DoubanSpider()
# book_types = ['推理', '文学', '诗歌', '计算机', '科普', '爱情', '心理', '经济学', '历史', '漫画']
book_types = ['爱情', '心理', '经济学', '历史', '漫画']
books = []
for tag in book_types:
    books = spider.getTagBooks(tag, int(books_sum / len(book_types)))
    with open(file_name, 'a', encoding = 'utf-8') as f:
        f.write(json.dumps(books, indent = 2, ensure_ascii = False))