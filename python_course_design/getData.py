import DoubanSpider
import csv

books_sum = 4000
file_name = "book_items.csv"
spider = DoubanSpider.DoubanSpider()
# book_types = ['推理', '文学', '诗歌', '计算机', '科普', '爱情', '心理', '经济学', '历史', '漫画']
book_types = ['历史', '漫画']
books = []
for tag in book_types:
    books = spider.getTagBooks(tag, int(books_sum / len(book_types)))