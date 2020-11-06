from __future__ import print_function
import paddle
import paddle.fluid as fluid
import numpy as np
import math
import sys

BATCH_SIZE = 20

train_reader = paddle.batch(
    paddle.reader.shuffle(
        paddle.dataset.uci_housing.train(), buf_size = 500),
        batch_size = BATCH_SIZE
)

test_reader = paddle.batch(
    paddle.reader.shuffle(
        paddle.dataset.uci_housing.test(), buf_size = 500),
        batch_size = BATCH_SIZE
)